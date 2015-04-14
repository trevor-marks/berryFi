#include "i2c.h"
#include <stdio.h>
#include <iostream.h>
#include <fcntl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <cstring>
#include <sys/ioctl.h>
#include <sstream>



int i2c_device;

static void i2c_open(const char * i2c_deviceName)
{
	i2c_device = open(i2c_deviceName, O_RDWR);
	if (i2c_device == -1)
	{
		printf("Failed to open i2c_device.");
	}
}

static void i2c_close()
{
	close(i2c_device);
}

static void i2c_setAddress(unsigned char address)
{
	int result = ioctl(i2c_device, I2C_SLAVE, address);
	if (result == -1)
	{
		printf("Failed to set address.");
	}
}

static void i2c_writeByte(unsigned char value)
{
	int result = write(i2c_device, &value, 1);
	if (result == -1)
	{
		printf("Failed to write byte to I2C.");
	}
}

static void i2c_writeBuffer(unsigned char * buf, int length)
{
	int result = write(i2c_device, buf, length);
	if (result == -1)
	{
		printf("Failed to write byte to I2C.");
	}
}
/*
static unsigned char i2c_readByte(unsigned char command)
{
	int result = i2c_smbus_read_byte_data(i2c_device, command);
	if (result == -1)
	{
		printf("Failed to read byte from I2C.");
	}
	return result;
}

static int i2c_tryReadByte(unsigned char command)
{
	return i2c_smbus_read_byte_data(i2c_device, command);
}

static void i2c_readBlock(unsigned char command, unsigned char size, unsigned char * data)
{
	int result = i2c_smbus_read_i2c_block_data(i2c_device, command, size, data);
	if (result != size)
	{
		printf("Failed to read block from I2C.");
	}
}
*/