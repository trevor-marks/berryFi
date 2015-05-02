
class io
{
	private:
		void i2c_start();
		void i2c_stop();
		void i2c_byte(char data);

	public:
		int  mem_fd;
		void *gpio_map;
		volatile unsigned *gpio;

		void init();
		void i2c_write(unsigned char addr, char * buf, int length);
		void i2c_write_command(unsigned char addr, char command);
};
