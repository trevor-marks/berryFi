#include <stdio.h>
#include <stdlib.h>
#include "menu.h"



void menu::init()
{
	printf("------\nmenu init...\n");
	// default view init
	view.current = ARTIST;
	view.scroll = &view.artist;

	//topScreen.start(0x3c);
	topScreen.start(0x78);
}


void menu::exit()
{
	topScreen.stop();
}

void menu::update()
{
	system("clear");
	switch (state)
	{
		//--------------------------------------------------------------------------------
		case MAIN:
			printf("screen: main\n");
			topScreen.drawText("screen: main\n", 0, 0, 1);
			break;

		//--------------------------------------------------------------------------------
		case FUNC:
			printf("screen: funciton\n");
			topScreen.drawText("I love Olivia!!!\n", 0, 0, 1);
			topScreen.drawText("SO MUCH  <3\n", 0, 1, 2);
			break;

		//--------------------------------------------------------------------------------
		case SETT:
			printf("screen: settings\n");
			topScreen.drawSprite(0, 0, 0, 6)
			break;

		//--------------------------------------------------------------------------------
		case LAPL:
			printf("screen: load a playlist\n");

			break;

		//--------------------------------------------------------------------------------
		case ELPL:
			printf("screen: edit Queue\n");

			break;

		//--------------------------------------------------------------------------------
		case EPLO:
			printf("screen: edit playlist order\n");

			break;

		//--------------------------------------------------------------------------------
		default:
			printf("screen: ???\n");
			break;
	}

	topScreen.updateScreen();
}


void menu::pushButton(_button button, _buttonMode mode)
{
	if (button == NOP) return;
	_menuState NS = state;

	// dedicated buttons here
	if (button == PLAY)
	{
		//if (mode == CLICK)		//> PLAY / PAUSE
		//if (mode == HOLD)		//> STOP
	}

	if (button == NEXT)
	{
		//if (mode == CLICK)		//> NEXT TRACK
		//if (mode == HOLD)		//> --
	}

	if (button == PREV)
	{
		//if (mode == CLICK)		//> PREV TRACK
		//if (mode == HOLD)		//> --
	}


	// state machine here
	switch (state)
	{
		//--------------------------------------------------------------------------------
		case MAIN:
			if (button == MENU)
			{
				//if (mode == CLICK)		//> --
				if (mode == HOLD) 			NS = FUNC;
			}
			if (button == ADD)
			{
				//if (mode == CLICK)		//> Add track/album/artist to playlist
				//if (mode == HOLD) 		//> Add track/album/artist to front of playlist and play NOW
			}
			if (button == SUB)
			{
				//if (mode == CLICK)		//> Remove track/album/artist from playlist
				//if (mode == HOLD) 		//> --
			}
			if (button == UP)
			{
				if (mode == CLICK)			//> scroll up
				{
					if (view.scroll->index < view.scroll->size - 1) view.scroll->index++;
				}
				//if (mode == HOLD) 		//> browse out to artist/album list
			}
			if (button == DOWN)
			{
				if (mode == CLICK)			//> scroll down
				{
					if (view.scroll->index > 0) view.scroll->index--;
				}
				//if (mode == HOLD) 		//> browse into album/track list
			}
			break;

		//--------------------------------------------------------------------------------
		case FUNC:
			if (button == MENU)
			{
				if (mode == CLICK)			NS = MAIN;
				if (mode == HOLD)			NS = SETT;
			}
			if (button == ADD)
			{
				//if (mode == CLICK)		//> Save Playlist
				//if (mode == HOLD) 		//> Save Playlist and empty live playlist
			}
			if (button == SUB)
			{
				if (mode == CLICK)			NS = LAPL;
				if (mode == HOLD) 			NS = ELPL;
			}
			if (button == UP)
			{
				//if (mode == CLICK)		//> toggle shuffle
				//if (mode == HOLD) 		//> --
			}
			if (button == DOWN)
			{
				//if (mode == CLICK)		//> toggle repeat
				//if (mode == HOLD) 		//> --
			}
			break;

		//--------------------------------------------------------------------------------
		case SETT:
			if (button == MENU)
			{
				if (mode == CLICK)			NS = MAIN;
				//if (mode == HOLD)			// --
			}
			if (button == ADD)
			{
				//if (mode == CLICK)		//> Rescan Library
				//if (mode == HOLD) 		//> --
			}
			if (button == SUB)
			{
				//if (mode == CLICK)		//> Toggle fade effects
				//if (mode == HOLD) 		//> --
			}
			if (button == UP)
			{
				//if (mode == CLICK)		//> Cycle power save timer setting
				//if (mode == HOLD) 		//> --
			}
			if (button == DOWN)
			{
				//if (mode == CLICK)		//> --
				//if (mode == HOLD) 		//> --
			}
			break;

		//--------------------------------------------------------------------------------
		case LAPL:
			if (button == MENU)
			{
				if (mode == CLICK)			NS = MAIN;
				//if (mode == HOLD)			// --
			}
			if (button == ADD)
			{
				//if (mode == CLICK)		//> Enque this playlist to live playlist
				//if (mode == HOLD) 		//> Replace current live playlist with this one
			}
			if (button == SUB)
			{
				//if (mode == CLICK)		//> --
				//if (mode == HOLD) 		//> Delete this playlist
			}
			if (button == UP)
			{
				//if (mode == CLICK)		//> scroll selection up
				//if (mode == HOLD) 		//> Top of list
			}
			if (button == DOWN)
			{
				//if (mode == CLICK)		//> scroll selection down
				//if (mode == HOLD) 		//> Bottom of list
			}
			break;

		//--------------------------------------------------------------------------------
		case ELPL:
			if (button == MENU)
			{
				if (mode == CLICK)			NS = MAIN;
				//if (mode == HOLD)			// --
			}
			if (button == ADD)
			{
				if (mode == CLICK)			
				{
					//> select current song
					NS = EPLO;
				}
				//if (mode == HOLD) 		//> --
			}
			if (button == SUB)
			{
				//if (mode == CLICK)		//> Remove Song from live playlist
				//if (mode == HOLD) 		//> empty live playlist
			}
			if (button == UP)
			{
				//if (mode == CLICK)		//> scroll selection up
				//if (mode == HOLD) 		//> to top of list
			}
			if (button == DOWN)
			{
				//if (mode == CLICK)		//> scroll selection down
				//if (mode == HOLD) 		//> to bottom of list
			}
			break;

		//--------------------------------------------------------------------------------
		case EPLO:
			if (button == MENU)
			{
				if (mode == CLICK)			NS = MAIN;
				//if (mode == HOLD)			// --
			}
			if (button == ADD)
			{
				if (mode == CLICK)			
				{
					//> drop song at new location
					NS = ELPL;
				}
				//if (mode == HOLD) 		//> --
			}
			if (button == SUB)
			{
				if (mode == CLICK)			
				{
					//> remove current song
					NS = ELPL;
				}
				//if (mode == HOLD) 		//> --
			}
			if (button == UP)
			{
				//if (mode == CLICK)		//> drag song up
				//if (mode == HOLD) 		//> drag song to top of playlist
			}
			if (button == DOWN)
			{
				//if (mode == CLICK)		//> drag song down
				//if (mode == HOLD) 		//> drag song to bottom of playlist
			}
			break;

		//--------------------------------------------------------------------------------
		default:
			break;
	}


	state = NS;
}