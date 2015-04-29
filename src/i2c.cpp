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
	else
		printf("%s opened\n", i2c_device);
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
	else
		printf("address set to: %d\n", address);
}

void i2c::writeCommand(unsigned char value)
{
	//writeByte(0x00);
	writeByte_noAck(value);
}

void i2c::writeByte(unsigned char value)
{
	//int result = write(i2c_device, &value, 1);
	int result = i2c_smbus_write_byte(i2c_device, value);
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
	for (int l = 0; l < length; l++)
	{
		writeByte(buf[l]);
	}
}




int i2c::writeByte_noAck(unsigned int addr, unsigned int offset, unsigned char *buf)
{
	struct i2c_rdwr_ioctl_data msg_rdwr;
	struct i2c_msg             i2cmsg;
	int i;

	if(len>1024) return -1;

	msg_rdwr.msgs = &i2cmsg;
	msg_rdwr.nmsgs = 1;

	i2cmsg.addr  = addr;
	i2cmsg.flags = I2C_M_IGNORE_NAK | I2C_M_NO_RD_ACK;
	i2cmsg.len   = 1+len;
	i2cmsg.buf   = buf;

	i = ioctl(i2c_device,I2C_RDWR,&msg_rdwr);
	return i;
}