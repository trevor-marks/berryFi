#include "main.h"
#include "menu.h"
#include <stdio.h>
#include <string.h>

menu Menu;


int main()
{
	printf("\nwelcome!\n");

	bool flag = true;

	while (flag)
	{
		char input[16];
		printf("?> ");
		scanf("%s", input);


		_button input_b = NOP;
		_buttonMode input_m = CLICK;

		if (strncmp(input, "1", 1) == 0) input_b = PLAY;
		if (strncmp(input, "11", 2) == 0) input_m = HOLD;
		if (strncmp(input, "'", 1) == 0) input_b = MENU;
		if (strncmp(input, "''", 2) == 0) input_m = HOLD;
		if (strncmp(input, "2", 1) == 0) input_b = NEXT;
		if (strncmp(input, "22", 2) == 0) input_m = HOLD;
		if (strncmp(input, "3", 1) == 0) input_b = PREV;
		if (strncmp(input, "33", 2) == 0) input_m = HOLD;
		if (strncmp(input, "A", 1) == 0) input_b = UP;
		if (strncmp(input, "AA", 2) == 0) input_m = HOLD;
		if (strncmp(input, ";", 1) == 0) input_b = DOWN;
		if (strncmp(input, ";;", 2) == 0) input_m = HOLD;
		if (strncmp(input, "O", 1) == 0) input_b = ADD;
		if (strncmp(input, "OO", 2) == 0) input_m = HOLD;
		if (strncmp(input, "Q", 1) == 0) input_b = SUB;
		if (strncmp(input, "QQ", 2) == 0) input_m = HOLD;

		Menu.pushButton(input_b, input_m);
		Menu.update();
	}



	return 0;
}