#include "screen.h"

enum _menuState {MAIN, FUNC, SETT, LAPL, ELPL, EPLO};
enum _button {NOP, PLAY, MENU, NEXT, PREV, UP, DOWN, ADD, SUB};
enum _buttonMode {CLICK, HOLD};
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
		menu();
		void pushButton(_button button, _buttonMode mode);
		void update();
		void exit();

};