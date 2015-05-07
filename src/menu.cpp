#include <stdio.h>
#include <stdlib.h>


#include "menu.h"


void menu::init()
{
	// default view init
	view.current = ARTIST;
	view.scroll = &view.artist;

	//topScreen.start(0x3c);
	topScreen.start(0x78);

	// draw logo
	topScreen.drawSprite(0, 0, SPRITE_MODE_REPLACE, SPRITE_BERRYFI);
	topScreen.updateScreen();
}


void menu::off()
{
	// draw logo so it will display on power-on
	topScreen.drawSprite(0, 0, SPRITE_MODE_REPLACE, SPRITE_BERRYFI);
	topScreen.updateScreen();
	topScreen.stop();
	exit(0);
}

void menu::update()
{
	switch (state)
	{
		//--------------------------------------------------------------------------------
		case MAIN:
			printf("screen: main\n");
			topScreen.drawText("main\n", 0, 0, 2);
			break;

		//--------------------------------------------------------------------------------
		case FUNC:
			printf("screen: function\n");
			topScreen.drawText("func control\n", 0, 0, 2);
			break;

		//--------------------------------------------------------------------------------
		case SETT:
			printf("screen: settings\n");
			topScreen.drawText("settings\n", 0, 0, 2);
			break;

		//--------------------------------------------------------------------------------
		case LAPL:
			printf("screen: load a playlist\n");
			topScreen.drawText("load a playlist\n", 0, 0, 2);
			break;

		//--------------------------------------------------------------------------------
		case ELPL:
			printf("screen: edit Queue\n");
			topScreen.drawText("edit Queue\n", 0, 0, 2);
			break;

		//--------------------------------------------------------------------------------
		case EPLO:
			printf("screen: edit playlist order\n");
			topScreen.drawText("EPLO\n", 0, 0, 2);
			break;

		//--------------------------------------------------------------------------------
		case SHUTDOWN:
			printf("Program shutting down.\n");
			off();
			break;

		//--------------------------------------------------------------------------------
		default:
			printf("screen: ???\n");
			break;
	}

	topScreen.updateScreen();
}


void menu::pushButton(char button, char mode)
{
	_menuState NS = state;
	FILE *fp;

	// dedicated buttons here
	if (button == BTN_PLAY)
	{
		if (mode == BTN_M_CLICK)		//> PLAY / PAUSE
		{
			fp = popen("mpc play", "r");
			pclose(fp);
		}
		if (mode == BTN_M_HOLD)		//> STOP
		{
			fp = popen("mpc stop", "r");
			pclose(fp);
		}
	}

	if (button == BTN_NEXT)
	{
		if (mode == BTN_M_CLICK)		//> NEXT TRACK
		{
			fp = popen("mpc next", "r");
			pclose(fp);
		}
		//if (mode == BTN_M_HOLD)		//> --
	}

	if (button == BTN_PREV)
	{
		if (mode == BTN_M_CLICK)		//> PREV TRACK
		{
			fp = popen("mpc prev", "r");
			pclose(fp);
		}
		//if (mode == BTN_M_HOLD)		//> --
	}


	// state machine here
	switch (state)
	{
		//--------------------------------------------------------------------------------
		case MAIN:
			if (button == BTN_FUNC)
			{
				//if (mode == BTN_M_CLICK)		//> --
				if (mode == BTN_M_HOLD) 		NS = FUNC;
			}
			if (button == BTN_ADD)
			{
				//if (mode == BTN_M_CLICK)		//> Add track/album/artist to playlist
				//if (mode == BTN_M_HOLD) 		//> Add track/album/artist to front of playlist and play NOW
			}
			if (button == BTN_SUB)
			{
				//if (mode == BTN_M_CLICK)		//> Remove track/album/artist from playlist
				//if (mode == BTN_M_HOLD) 		//> --
			}
			if (button == BTN_UP)
			{
				if (mode == BTN_M_CLICK)		//> scroll up
				{
					if (view.scroll->index < view.scroll->size - 1) view.scroll->index++;
				}
				//if (mode == BTN_M_HOLD) 		//> browse out to artist/album list
			}
			if (button == BTN_DOWN)
			{
				if (mode == BTN_M_CLICK)		//> scroll down
				{
					if (view.scroll->index > 0) view.scroll->index--;
				}
				//if (mode == BTN_M_HOLD) 		//> browse into album/track list
			}
			break;

		//--------------------------------------------------------------------------------
		case FUNC:
			if (button == BTN_FUNC)
			{
				if (mode == BTN_M_CLICK)		NS = MAIN;
				if (mode == BTN_M_HOLD)			NS = SETT;
			}
			if (button == BTN_ADD)
			{
				//if (mode == BTN_M_CLICK)		//> Save Playlist
				//if (mode == BTN_M_HOLD) 		//> Save Playlist and empty live playlist
			}
			if (button == BTN_SUB)
			{
				if (mode == BTN_M_CLICK)		NS = LAPL;
				if (mode == BTN_M_HOLD) 		NS = ELPL;
			}
			if (button == BTN_UP)
			{
				//if (mode == BTN_M_CLICK)		//> toggle shuffle
				//if (mode == BTN_M_HOLD) 		//> --
			}
			if (button == BTN_DOWN)
			{
				//if (mode == BTN_M_CLICK)		//> toggle repeat
				//if (mode == BTN_M_HOLD) 		//> --
			}
			break;

		//--------------------------------------------------------------------------------
		case SETT:
			if (button == BTN_FUNC)
			{
				if (mode == BTN_M_CLICK)		NS = MAIN;
				if (mode == BTN_M_HOLD)			NS = SHUTDOWN;
			}
			if (button == BTN_ADD)
			{
				if (mode == BTN_M_CLICK)		//> Rescan Library
				{
					fp = popen("mpc update", "r");
					pclose(fp);
				}
				//if (mode == BTN_M_HOLD) 		//> --
			}
			if (button == BTN_SUB)
			{
				//if (mode == BTN_M_CLICK)		//> Toggle fade effects
				//if (mode == BTN_M_HOLD) 		//> --
			}
			if (button == BTN_UP)
			{
				//if (mode == BTN_M_CLICK)		//> Cycle power save timer setting
				//if (mode == BTN_M_HOLD) 		//> --
			}
			if (button == BTN_DOWN)
			{
				//if (mode == BTN_M_CLICK)		//> --
				//if (mode == BTN_M_HOLD) 		//> --
			}
			break;

		//--------------------------------------------------------------------------------
		case LAPL:
			if (button == BTN_FUNC)
			{
				if (mode == BTN_M_CLICK)		NS = MAIN;
				//if (mode == BTN_M_HOLD)		// --
			}
			if (button == BTN_ADD)
			{
				//if (mode == BTN_M_CLICK)		//> Enque this playlist to live playlist
				//if (mode == BTN_M_HOLD) 		//> Replace current live playlist with this one
			}
			if (button == BTN_SUB)
			{
				//if (mode == BTN_M_CLICK)		//> --
				//if (mode == BTN_M_HOLD) 		//> Delete this playlist
			}
			if (button == BTN_UP)
			{
				//if (mode == BTN_M_CLICK)		//> scroll selection up
				//if (mode == BTN_M_HOLD) 		//> Top of list
			}
			if (button == BTN_DOWN)
			{
				//if (mode == BTN_M_CLICK)		//> scroll selection down
				//if (mode == BTN_M_HOLD) 		//> Bottom of list
			}
			break;

		//--------------------------------------------------------------------------------
		case ELPL:
			if (button == BTN_FUNC)
			{
				if (mode == BTN_M_CLICK)		NS = MAIN;
				//if (mode == BTN_M_HOLD)		// --
			}
			if (button == BTN_ADD)
			{
				if (mode == BTN_M_CLICK)			
				{
					//> select current song
					NS = EPLO;
				}
				//if (mode == BTN_M_HOLD) 		//> --
			}
			if (button == BTN_SUB)
			{
				//if (mode == BTN_M_CLICK)		//> Remove Song from live playlist
				//if (mode == BTN_M_HOLD) 		//> empty live playlist
			}
			if (button == BTN_UP)
			{
				//if (mode == BTN_M_CLICK)		//> scroll selection up
				//if (mode == BTN_M_HOLD) 		//> to top of list
			}
			if (button == BTN_DOWN)
			{
				//if (mode == BTN_M_CLICK)		//> scroll selection down
				//if (mode == BTN_M_HOLD) 		//> to bottom of list
			}
			break;

		//--------------------------------------------------------------------------------
		case EPLO:
			if (button == BTN_FUNC)
			{
				if (mode == BTN_M_CLICK)		NS = MAIN;
				//if (mode == BTN_M_HOLD)		// --
			}
			if (button == BTN_ADD)
			{
				if (mode == BTN_M_CLICK)			
				{
					//> drop song at new location
					NS = ELPL;
				}
				//if (mode == BTN_M_HOLD) 		//> --
			}
			if (button == BTN_SUB)
			{
				if (mode == BTN_M_CLICK)			
				{
					//> remove current song
					NS = ELPL;
				}
				//if (mode == BTN_M_HOLD) 		//> --
			}
			if (button == BTN_UP)
			{
				//if (mode == BTN_M_CLICK)		//> drag song up
				//if (mode == BTN_M_HOLD) 		//> drag song to top of playlist
			}
			if (button == BTN_DOWN)
			{
				//if (mode == BTN_M_CLICK)		//> drag song down
				//if (mode == BTN_M_HOLD) 		//> drag song to bottom of playlist
			}
			break;

		//--------------------------------------------------------------------------------
		default:
			break;
	}


	state = NS;
}