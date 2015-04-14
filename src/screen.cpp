#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "i2c.h"
#include "screen.h"
#include "sprites.h"

const char sprites_num = 2;
const int sprites[] = { (int)&sprite_1[0], (int)&sprite_2[0], };



screen::screen(unsigned char addr)
{
	address = addr;
	start();
}


void screen::start()
{
	i2cdevice.openDevice("/dev/i2c-1");
	i2cdevice.setAddress(address);

	i2cdevice.writeByte(0xAE); //display off
	i2cdevice.writeByte(0x00); //Set Memory Addressing Mode
	i2cdevice.writeByte(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	i2cdevice.writeByte(0x40); //Set Page Start Address for Page Addressing Mode,0-7
	i2cdevice.writeByte(0x81); //Set COM Output Scan Direction
	i2cdevice.writeByte(0xCF); //---set low column address
	i2cdevice.writeByte(0xA1); //---set high column address
	i2cdevice.writeByte(0xC8); //--set start line address
	i2cdevice.writeByte(0xA6); //--set contrast control register
	i2cdevice.writeByte(0xA8); 
	i2cdevice.writeByte(0x3F); //--set segment re-map 0 to 127
	i2cdevice.writeByte(0xD3); //--set normal display
	i2cdevice.writeByte(0x00); //--set multiplex ratio(1 to 64)
	i2cdevice.writeByte(0xD5); //
	i2cdevice.writeByte(0x80); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	i2cdevice.writeByte(0xD9); //-set display offset
	i2cdevice.writeByte(0xF1); //-not offset
	i2cdevice.writeByte(0xDA); //--set display clock divide ratio/oscillator frequency
	i2cdevice.writeByte(0x12); //--set divide ratio
	i2cdevice.writeByte(0xDB); //--set pre-charge period
	i2cdevice.writeByte(0x40); //
	i2cdevice.writeByte(0x20); //--set com pins hardware configuration
	i2cdevice.writeByte(0x02); 
	i2cdevice.writeByte(0x8D); //--set vcomh
	i2cdevice.writeByte(0x14); //0x20,0.77xVcc
	i2cdevice.writeByte(0xA4); //--set DC-DC enable
	i2cdevice.writeByte(0xA6); //
	i2cdevice.writeByte(0xAF); //--turn on oled panel 
}

void screen::stop()
{
	i2cdevice.writeByte(0xAE); //display off
	i2cdevice.closeDevice();
}

void screen::writeBuffer()
{
	i2cdevice.writeBuffer(&buffer[0][0], 1024);
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
	writeBuffer();
	// clear buffer for next render
	clearBuffer();
}
