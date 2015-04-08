#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "sprites.h"


// 0xAE   display off
// 0x20   Set Memory Addressing Mode	
// 0x10   00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
// 0xb0   Set Page Start Address for Page Addressing Mode,0-7
// 0xc8   Set COM Output Scan Direction
// 0x00   ---set low column address
// 0x10   ---set high column address
// 0x40   --set start line address
// 0x81   --set contrast control register
// 0x7f   0xa1   --set segment re-map 0 to 127
// 0xa6   --set normal display
// 0xa8   --set multiplex ratio(1 to 64)
// 0x3F   
// 0xa4   0xa4,Output follows RAM content;0xa5,Output ignores RAM content
// 0xd3   -set display offset
// 0x00   -not offset
// 0xd5   --set display clock divide ratio/oscillator frequency
// 0xf0   --set divide ratio
// 0xd9   --set pre-charge period
// 0x22   
// 0xda   --set com pins hardware configuration
// 0x12   0xdb   --set vcomh
// 0x20   0x20,0.77xVcc
// 0x8d   --set DC-DC enable
// 0x14   
// 0xaf   --turn on oled panel





screen::screen(int addr)
{
	address = addr;
}


void clearBuffer()
{
	// clear the buffer
	memset(buffer, 0, 1024);
}

void drawText(char *text, int x, int y, int size, int font)
{
	// render text to buffer
	int offset = 0;
	while (*(text+offset) != '\n' && *(text+offset) != '\0')
	{
		// copy 6 byte font character into the buffer
		memcpy(&buffer[y][x + offset * 6], &font6x8[*(text + offset) + 32], 6);
		offset++;
	}
}

void drawSprite(int x, int y, int compositeMode, int spriteIndex)
{
	// draw sprite to buffer
}

void updateScreen()
{
	// send buffer to screen
}