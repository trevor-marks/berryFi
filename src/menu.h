
enum _menuState {MAIN, FUNC, SETT, LAPL, ELPL, EPLO};
enum _button {NOP, PLAY, MENU, NEXT, PREV, UP, DOWN, ADD, SUB};
enum _buttonMode {CLICK, HOLD};

class menu
{

	_menuState state;

	int scrollIndex;
	int menuTimeout;

	public:
	void pushButton(_button button, _buttonMode mode);

	void update();


};