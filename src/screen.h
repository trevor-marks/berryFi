


class screen
{
	private:
		unsigned char address;

		unsigned char buffer[8][128];

		void writeBuffer();

		i2c i2cdevice;


	public:
		screen(unsigned char addr);

		void start();
		void stop();
		void clearBuffer();
		void drawText(char *text, int x, int y, int size, int font);
		void drawSprite(int x, int y, int compositeMode, int spriteIndex);
		void updateScreen();
};