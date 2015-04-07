#include <stdio.h>
#include <stdlib.h>
#include "screen.h"


screen::screen(int Address)
{
	address = Address;
}







void clearBuffer()
{
	// clear the buffer
}

void drawText(char *text, int x, int y, int size, int font)
{
	// render text to buffer
}

void drawSprite(int x, int y, int compositeMode, int spriteIndex)
{
	// draw sprite to buffer
}

void updateScreen()
{
	// send buffer to screen
}