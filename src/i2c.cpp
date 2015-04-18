#include "i2c.h"
#include <stdio.h>
#include <fcntl.h>
#include "i2c_dev.h"

#include <sys/ioctl.h>
#include <unistd.h>





void i2c::openDevice(const char * i2c_deviceName)
{
	i2c_device = open(i2c_deviceName, O_RDWR);
	if (i2c_device == -1)
	{
		printf("Failed to open %s.\n", i2c_deviceName);
	}
}

void i2c::closeDevice()
{
	close(i2c_device);
}

void i2c::setAddress(unsigned char address)
{
	int result = ioctl(i2c_device, I2C_SLAVE, address);
	if (result == -1)
	{
		printf("Failed to set address %#x.\n", address);
	}
}

void i2c::writeCommand(unsigned char value)
{
	writeByte(0x00);
	writeByte(value);
}

void i2c::writeByte(unsigned char value)
{
	//int result = write(i2c_device, &value, 1);
	int result = i2c_smbus_write_byte(i2c_device, &value);
	if (result == -1)
	{
		printf("Failed to write byte to I2C %#x.\n", value);
	}
}

void i2c::writeBuffer(unsigned char * buf, int length)
{
	//writeByte(address);
	writeCommand(0x40);								// data command
	/*int result = write(i2c_device, buf, length);
	if (result == -1)
	{
		printf("Failed to write %d bytes to I2C.\n", length);
	}*/
	for (int l = 0; l < length)
	{
		writeByte(buf[l]);
	}
}
