
class io
{
	private:
		void i2c_start();
		void i2c_stop();

		void i2c_byte(unsigned char data);

	public:
		int  mem_fd;
		void *gpio_map;
		volatile unsigned *gpio;

		void init();
		void i2c_setPos(unsigned char addr, unsigned char x, unsigned char y);
		void i2c_write(unsigned char addr, char * buf, int length);
		void i2c_write_command(unsigned char addr, unsigned char command);
};
