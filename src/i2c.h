static i2c_open(const char * deviceName);
static i2c_close();
static void i2c_addressSet(unsigned char address);
static void i2c_writeByte(unsigned char command, unsigned char data);
static unsigned char i2c_readByte(unsigned char command);
static int i2c_tryReadByte(unsigned char command);
static void i2c_readBlock(unsigned char command, unsigned char size, unsigned char * data);