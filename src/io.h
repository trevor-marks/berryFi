
class io
{
	private:
		int  mem_fd;
		void *gpio_map;
		volatile unsigned *gpio;

		void i2c_start();
		void i2c_stop();
		void i2c_byte(unsigned char byte);

	public:
		io();
		void i2c_write(unsigned char addr, unsigned char * buf, int length);
		void i2c_write_command(unsigned char addr, unsigned char command);
};
