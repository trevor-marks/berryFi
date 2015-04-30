
class i2c
{
	private:
		int  mem_fd;
		void *gpio_map;
		volatile unsigned *gpio;

		void start();
		void stop();
		void byte(unsigned char byte);

	public:
		i2c();
		void write(unsigned char addr, unsigned char * buf, int length);
		void write_command(unsigned char addr, unsigned char command);
};
