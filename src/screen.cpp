#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"
#include "sprites.h"

const char sprites_num = 2;
const int sprites[] = { (int)&sprite_1[0], (int)&sprite_2[0], };



screen::screen(int addr)
{
	address = addr;
}


void screen::i2c_write(char data)
{
	// i2c IO stuff here
	// will write data to address
}

void screen::i2c_start()
{
	i2c_write(0xAE); //display off
	i2c_write(0x00); //Set Memory Addressing Mode
	i2c_write(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	i2c_write(0x40); //Set Page Start Address for Page Addressing Mode,0-7
	i2c_write(0x81); //Set COM Output Scan Direction
	i2c_write(0xCF); //---set low column address
	i2c_write(0xA1); //---set high column address
	i2c_write(0xC8); //--set start line address
	i2c_write(0xA6); //--set contrast control register
	i2c_write(0xA8); 
	i2c_write(0x3F); //--set segment re-map 0 to 127
	i2c_write(0xD3); //--set normal display
	i2c_write(0x00); //--set multiplex ratio(1 to 64)
	i2c_write(0xD5); //
	i2c_write(0x80); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	i2c_write(0xD9); //-set display offset
	i2c_write(0xF1); //-not offset
	i2c_write(0xDA); //--set display clock divide ratio/oscillator frequency
	i2c_write(0x12); //--set divide ratio
	i2c_write(0xDB); //--set pre-charge period
	i2c_write(0x40); //
	i2c_write(0x20); //--set com pins hardware configuration
	i2c_write(0x02); 
	i2c_write(0x8D); //--set vcomh
	i2c_write(0x14); //0x20,0.77xVcc
	i2c_write(0xA4); //--set DC-DC enable
	i2c_write(0xA6); //
	i2c_write(0xAF); //--turn on oled panel 
}

void screen::i2c_stop()
{
	i2c_write(0xAE); //display off
}

void screen::i2c_writeCommand()
{
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
}

void screen::i2c_writeBuffer()
{

}











void screen::clearBuffer()
{
	// clear the buffer
	memset(buffer, 0, 1024);
}

void screen::drawText(char *text, int x, int y, int size, int font)
{
	// render text to buffer
	int offset = 0;
	while (*(text+offset) != '\n' && *(text+offset) != '\0')
	{
		if (font == 1)
		{
			// copy 6 byte font character into the buffer
			memcpy(&buffer[y][x + offset * 6], &font6x8[(*(text + offset) - 32) * 6], 6);
			offset++;
		}
		if (font == 2)
		{
			// copy 16 byte font character into the buffer
			memcpy(&buffer[y    ][x + offset * 6], &font8X16[(*(text + offset) - 32) * 16    ], 8);
			memcpy(&buffer[y + 1][x + offset * 6], &font8X16[(*(text + offset) - 32) * 16 + 8], 8);
			offset++;
		}
	}
}

void screen::drawSprite(int x, int y, int compositeMode, int spriteIndex)
{
	if (spriteIndex >= sprites_num) return;

	// get sprite pointer
	char * sprite;
	sprite = (char*)sprites[spriteIndex];

	// get width / height
	char width = sprite[0];
	char height = sprite[1];

	// render segments to buffer
	for (int u = 0; u < height; u++)
	{
		memcpy(buffer, &sprite[2 + width * u], width);
	}

}

void screen::updateScreen()
{
	// send buffer to screen
	i2c_writeBuffer();
	// clear buffer for next render
	clearBuffer();
}
