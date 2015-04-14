
class i2c
{
	private:
		int i2c_device;

	public:
		void open(const char * deviceName);
		void close();
		void setAddress(unsigned char address);
		void writeByte(unsigned char value);
		void writeBuffer(unsigned char * buf, int length);

};
