


class screen
{
	private:
		unsigned char address;

		char buffer[8][128];

		void writeBuffer();


	public:
		screen(unsigned char addr);

		void start();
		void stop();
		void clearBuffer();
		void drawText(char *text, int x, int y, int size, int font);
		void drawSprite(int x, int y, int compositeMode, int spriteIndex);
		void updateScreen();
};