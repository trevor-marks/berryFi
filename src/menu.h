#include "screen.h"

enum _menuState {MAIN, FUNC, SETT, LAPL, ELPL, EPLO, SHUTDOWN};
enum _button {PLAY, MENU, NEXT, PREV, UP, DOWN, ADD, SUB};
enum _buttonMode {NONE, CLICK, HOLD};
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
		void pushButton(_button button, _buttonMode mode);
		void update();
		void off();

};