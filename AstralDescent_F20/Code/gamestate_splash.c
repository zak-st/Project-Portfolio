//---------------------------------------------------------
// file:	gamestate_splash.c
// author:	Rey Rosario, Zak Stephenson
// course:	GAM100
//
// brief:	splash screen
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "gamestate_splash.h"
#include "gamestate_team.h"
#include "gamestate_menu.h"

/*local variables*/
CP_Image digipen_logo = NULL;

void drawStars(int numStars)
{
	int i; /*loop counter*/
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));     /*star outline color*/
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 100)); /*star color*/
	/*drawing the given number of stars*/
	for (i = 0; i <= numStars; i++)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 100));
		int xPos = CP_Random_RangeInt(0, 800); /*random X position*/
		int yPos = CP_Random_RangeInt(0, 800); /*random Y position*/
		int diameter = CP_Random_RangeInt(3, 10);
		int colorRandomizer = CP_Random_RangeInt(0, 9);
		if (diameter == 5 || diameter == 6)
		{
			if (colorRandomizer == 0 || colorRandomizer == 1)
			{
				CP_Settings_Fill(CP_Color_Create(255, 140, 0, 100));
			}
			if (colorRandomizer == 2 || colorRandomizer == 3)
			{
				CP_Settings_Fill(CP_Color_Create(255, 215, 0, 100));
			}
			if (colorRandomizer == 4 || colorRandomizer == 5)
			{
				CP_Settings_Fill(CP_Color_Create(0, 250, 154, 100));
			}
		}

		CP_Graphics_DrawCircle((float)xPos, (float)yPos, (float)diameter);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	}
}

void gamestate_splash_init(void)
{
	digipen_logo = CP_Image_Load("./Assets/DigiPen_WHITE.png");
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	drawStars(500);
}

void gamestate_splash_update(void)
{
	double imageW = (double)CP_Image_GetWidth(digipen_logo)/1.5; /*logo width*/
	double imageH = (double)CP_Image_GetHeight(digipen_logo)/1.5; /*logo height*/
	CP_Image_Draw(digipen_logo, 400.0f, 400.0f, (float)imageW, (float)imageH, (int) CP_System_GetMillis()/100); /*fading logo in*/
																												
	/*skips to menu after 5 seconds or a key press*/
	if (CP_System_GetSeconds() >= 5.0f || CP_Input_KeyTriggered(KEY_ANY))
	{
		CP_Engine_SetNextGameState(gamestate_team_init, gamestate_team_update, gamestate_team_exit);
	}


}

void gamestate_splash_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory

}
