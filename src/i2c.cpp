#include "i2c.h"
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

#define _scl 5
#define _sda 6


// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
 
#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0
 
#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH
 
#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock


i2c::i2c()
{
	// open /dev/mem
	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) 
	{
		printf("can't open /dev/mem \n");
	}

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
		printf("mmap error %d\n", (int)gpio_map); // errno also set!
	}

	// Always use volatile pointer!
	gpio = (volatile unsigned *)gpio_map;

	// set i2c pins to output
	INP_GPIO(_scl);
	INP_GPIO(_sda);
	OUT_GPIO(_scl);
	OUT_GPIO(_sda);
}


void i2c::start()
{
	GPIO_SET = 1 << _scl;
	usleep(500);
	GPIO_SET = 1 << _sda;
	usleep(500);
	GPIO_CLR = 1 << _sda;
	usleep(500);
	GPIO_CLR = 1 << _scl;
	usleep(500);
}

void i2c::stop()
{
	GPIO_CLR = 1 << _scl;
	usleep(500);
	GPIO_CLR = 1 << _sda;
	usleep(500);
	GPIO_SET = 1 << _scl;
	usleep(500);
	GPIO_SET = 1 << _sda;	
	usleep(500);
}

void i2c::byte(unsigned char byte)
{
	for (char bit = 0x00; bit < 0x10; bit<<1)
	{
		if (byte << bit & 0x80)
			GPIO_SET = 1 << _sda;
		else
			GPIO_CLR = 1 << _sda;
		usleep(10);
		GPIO_SET = 1 << _scl;
		usleep(500);
		GPIO_CLR = 1 << _scl;
		usleep(500);
	}
	// fake ack bit
	GPIO_SET = 1 << _sda;
	usleep(10);
	GPIO_SET = 1 << _scl;
	usleep(500);
	GPIO_CLR = 1 << _scl;
	usleep(500);
}


//==========================================================
//    Custom i2c bit-bang code because LCD isn't 
//    totally i2c compliant and doesn't support ACK'ing
//----------------------------------------------------------
void i2c::write(unsigned char addr, unsigned char * buf, int length)
{
	start();
	byte(addr);                                      // Write address
	byte(0x40);                                      // Write data command
	for (int i = 0; i < length; i++) byte(buf[i])    // Write data buffer
	stop();
}


void i2c::write_command(unsigned char addr, unsigned char command)
{
	start();
	address(addr);
	byte(0x00);                                      // write a zero to init a command
	byte(command);                                   // write command
	stop();
}
