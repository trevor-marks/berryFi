#include "main.h"
#include "menu.h"
#include "io.h"

#include <stdio.h>
#include <string.h>

menu Menu;
io ioDevice;

int main()
{
	ioDevice.init();
	Menu.init();

	printf("init complete...\n");

	//usleep(1000000);

	while (1)
	{
		if (ioDevice.io_pollButtons()) Menu.update();
		usleep(BUTTON_POLL);

	}
	return 0;
}