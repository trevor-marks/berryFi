#include "screen.h"

enum _menuState {MAIN, FUNC, SETT, LAPL, ELPL, EPLO, SHUTDOWN};

#define BTN_PLAY 0
#define BTN_FUNC 1
#define BTN_NEXT 2
#define BTN_PREV 3
#define BTN_UP   4 
#define BTN_DOWN 5
#define BTN_ADD  6
#define BTN_SUB  7

#define BTN_M_NONE  0
#define BTN_M_CLICK 1
#define BTN_M_HOLD  2

enum _view {ARTIST, ALBUM, SONG, PLAYLIST};

struct _scroll
{
	int index;
	int size;
};

struct _scrollMenus
{
	_view current;
	_scroll artist, album, song, playlist;
	_scroll *scroll;
};



class menu
{
	private:
		int menuTimeout;
		_menuState state;
		_scrollMenus view;
		screen topScreen;

	public:
		void init();
		void pushButton(char button, char mode);
		void update();
		void off();

};