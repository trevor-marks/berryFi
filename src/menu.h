
enum _menuState {MAIN, FUNC, SETT, LAPL, ELPL, EPLO};
enum _button {PLAY, MENU, NEXT, PREV, UP, DOWN, ADD, SUB};
enum _butMode {CLICK, HOLD};

class menu
{
	_menuState state;

	void pushButton(_button button, _butMode mode);

	void update();


};