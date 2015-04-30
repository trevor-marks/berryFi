
class i2c
{
	private:
		int i2c_device;

	public:
		void openDevice(const char * deviceName);
		void closeDevice();
		void setAddress(unsigned char address);
		void writeCommand(unsigned char value);
		void writeByte(unsigned char value);
		void writeBuffer(unsigned char * buf, int length);

		int write_noAck(unsigned int addr, unsigned char *buf, unsigned char len);
};
