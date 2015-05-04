enum _sprite_names
{ 
	SPRITE_SPRITE_1 = 0, 
	SPRITE_SPRITE_2,
	SPRITE_SHUFFLE,
	SPRITE_STOP,
	SPRITE_STOP_AFTER,
	SPRITE_BATTERY,
	SPRITE_BERRYFI,
	SPRITE_PAUSE,
	SPRITE_PLAY,
	SPRITE_REPEAT,
	SPRITE_REPEAT_ONE,
	SPRITE_MAX,
};

enum _sprite_compMode
{
	SPRITE_MODE_REPLACE,
	SPRITE_MODE_AND,
	SPRITE_MODE_OR,
};



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