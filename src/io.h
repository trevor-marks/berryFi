#define scl 2
#define sda 3
#define BUTTONS_MAX 8
#define BUTTON_CLICK 10
#define BUTTON_HOLD 1000
#define BUTTON_POLL 10000

class io
{
	private:
		void i2c_start();
		void i2c_stop();

		void i2c_byte(unsigned char data);


		int button_time[buttons_max];
		static char const button_pin[] = {5, 6, 25, 8, 13, 19, 7, 1}
		//  5  XXXX  25
		//  6  XXXX   8

		// 13  XXXX   7
		// 19  XXXX   1



	public:
		int  mem_fd;
		void *gpio_map;
		volatile unsigned *gpio;

		void init();

		char io_pollButtons();

		void i2c_setPos(unsigned char addr, unsigned char x, unsigned char y);
		void i2c_write(unsigned char addr, char * buf, int length);
		void i2c_write_command(unsigned char addr, unsigned char command);
};
