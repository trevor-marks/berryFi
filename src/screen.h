


class screen
{
	private:
		unsigned char address;

		unsigned char buffer[8][128];

		void writeBuffer();

		


	public:
		void setAddress(unsigned char addr);
		void start();
		void stop();
		void clearBuffer();
		void drawText(char *text, int x, int y, int font);
		void drawSprite(int x, int y, int compositeMode, int spriteIndex);
		void updateScreen();
};