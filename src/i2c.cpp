#include "i2c.h"
#include <stdio.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

int file;

static void i2c_open(const char * deviceName)
{
	file = open(deviceName, O_RDWR);
	if (file == -1)
	{
		printf("Failed to open I2C device.");
	}
}

static void i2c_close()
{
	close(file);
}

static void i2c_addressSet(unsigned char address)
{
	int result = ioctl(file, I2C_SLAVE, address);
	if (result == -1)
	{
		printf("Failed to set address.");
	}
}

static void i2c_writeByte(unsigned char command, unsigned char data)
{
	int result = i2c_smbus_write_byte_data(file, command, data);
	if (result == -1)
	{
		printf("Failed to write byte to I2C.");
	}
}

static unsigned char i2c_readByte(unsigned char command)
{
	int result = i2c_smbus_read_byte_data(file, command);
	if (result == -1)
	{
		printf("Failed to read byte from I2C.");
	}
	return result;
}

static int i2c_tryReadByte(unsigned char command)
{
	return i2c_smbus_read_byte_data(file, command);
}

static void i2c_readBlock(unsigned char command, unsigned char size, unsigned char * data)
{
	int result = i2c_smbus_read_i2c_block_data(file, command, size, data);
	if (result != size)
	{
		printf("Failed to read block from I2C.");
	}
}