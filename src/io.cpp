#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <unistd.h>



#define BCM2708_PERI_BASE  0x20000000
#define GPIO_BASE         (BCM2708_PERI_BASE + 0x200000)
#define PAGE_SIZE         (4*1024)
#define BLOCK_SIZE        (4*1024)

#define scl 5
#define sda 6


// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
 
#define GPIO_SET(p) *(gpio+7)=1<<(p)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR(p) *(gpio+10)=1<<(p) // clears bits which are 1 ignores bits which are 0
 
#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH
 
#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock




void io::init()
{
	printf("------\nio init...\n");
	printf("opening /dev/mem ...\n");


	// open /dev/mem
	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) 
	{
		printf("Error: can't open /dev/mem \n");
	}

	printf("mmap...\n");
	// mmap GPIO 
	gpio_map = mmap(
		NULL,                 // Any adddress in our space will do
		BLOCK_SIZE,           // Map length
		PROT_READ|PROT_WRITE, // Enable reading & writting to mapped memory
		MAP_SHARED,           // Shared with other processes
		mem_fd,               // File to map
		GPIO_BASE);           // Offset to GPIO peripheral

	close(mem_fd); // No need to keep mem_fd open after mmap

	if (gpio_map == MAP_FAILED) 
	{
		printf("Error: mmap error %d\n", (int)gpio_map); // errno also set!
	}

	printf("map gpio pointer...\n");
	// Always use volatile pointer!
	gpio = (volatile unsigned *)gpio_map;

	printf("setting up i2c pins...\n");
	// set i2c pins to output
	INP_GPIO(scl);
	INP_GPIO(sda);
	OUT_GPIO(scl);
	OUT_GPIO(sda);
}


void io::i2c_start()
{
	printf("\ti2c_start\n");
	GPIO_SET(scl);
	usleep(50);
	GPIO_SET(sda);
	usleep(50);
	GPIO_CLR(sda);
	usleep(50);
	GPIO_CLR(scl);
	usleep(50);
}

void io::i2c_stop()
{
	printf("\ti2c_stop\n");
	GPIO_CLR(scl);
	usleep(50);
	GPIO_CLR(sda);
	usleep(50);
	GPIO_SET(scl);
	usleep(50);
	GPIO_SET(sda);	
	usleep(50);
}

void io::i2c_byte(char byte)
{
	printf("\ti2c_byte  %#02x\n", byte);
	for (char bit = 0; bit < 8; bit++)
	{
		if (byte & (0x01 << bit) == 0)
			GPIO_CLR(sda);
		else
			GPIO_SET(sda);
		usleep(10);
		GPIO_SET(scl);
		usleep(50);
		GPIO_CLR(scl);
		usleep(50);
	}
	// fake ack bit
	GPIO_SET(sda);
	usleep(10);
	GPIO_SET(scl);
	usleep(50);
	GPIO_CLR(scl);
	usleep(50);
}


//==========================================================
//    Custom i2c bit-bang code because LCD isn't 
//    totally i2c compliant and doesn't support ACK'ing
//----------------------------------------------------------
void io::i2c_write(unsigned char addr, char * buf, int length)
{
	printf("io.write\n");
	i2c_start();
	i2c_byte(addr);                                      // Write address
	i2c_byte(0x40);                                      // Write data command
	for (int i = 0; i < length; i++) i2c_byte(buf[i]);   // Write data buffer
	i2c_stop();
}


void io::i2c_write_command(unsigned char addr, char command)
{
	printf("io.command\n");
	i2c_start();
	i2c_byte(addr);
	i2c_byte(0x00);                                      // write a zero to init a command
	i2c_byte(command);                                   // write command
	i2c_stop();
}
