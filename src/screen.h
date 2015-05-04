
#include "sprites.h"

class screen
{
	private:
		unsigned char address;

		char buffer[8][128];

		void writeBuffer();


	public:
		void start(unsigned char addr);
		void stop();
		void clearBuffer();
		void drawText(char *text, int x, int y, int font);
		void drawSprite(int x, int y, int compositeMode, int spriteIndex);
		void updateScreen();
};