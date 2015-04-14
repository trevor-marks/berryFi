static void i2c_open(const char * deviceName);
static void i2c_close();
static void i2c_setAddress(unsigned char address);
static void i2c_writeByte(unsigned char value);
static void i2c_writeBuffer(unsigned char * buf, int length);
//static unsigned char i2c_readByte(unsigned char command);
//static int i2c_tryReadByte(unsigned char command);
//static void i2c_readBlock(unsigned char command, unsigned char size, unsigned char * data);