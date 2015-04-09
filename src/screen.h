
class screen
{
	private:
		int address;

		char buffer[8][128];

		void i2c_start();
		void i2c_stop();
		void i2c_writeCommand();
		void i2c_writeBuffer();


	public:
		screen(int addr);


		void clearBuffer();
		void drawText(char *text, int x, int y, int size, int font);
		void drawSprite(int x, int y, int compositeMode, int spriteIndex);
		void updateScreen();
};