//---------------------------------------------------------
// file:	gamestate_win.c
// author:	Zak Stephenson, Zac Clapper, Mary Khuu, Rey Rosario
// course:	GAM100
//
// brief:	winning screen
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "gamestate_win.h"
#include "gamestate_menu.h"
#include "gamestate_splash.h"

CP_Image youWin = NULL;

CP_Image menu_button = NULL;
CP_Image menu_hovered = NULL;

CP_Image quit_button2 = NULL;
CP_Image quit_hovered2 = NULL;

void gamestate_win_init(void)
{
	youWin = CP_Image_Load("./OurAssets/youWin.png");

	menu_button = CP_Image_Load("./OurAssets/menu_button.png");
	menu_hovered = CP_Image_Load("./OurAssets/menu_hovered.png");

	quit_button2 = CP_Image_Load("./OurAssets/quit_button.png");
	quit_hovered2 = CP_Image_Load("./OurAssets/quit_hovered.png");

	CP_Settings_Background(CP_Color_Create(0,0,0,255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	drawStars(300);
	CP_Settings_TextSize(99.0f);

	CP_Image_Draw(youWin, CP_System_GetWindowWidth() * 0.5f + 25.0f, (CP_System_GetWindowHeight() * 0.5f) - 200.0f, 420.0f, 180.0f, 255);

}

void gamestate_win_update(void)
{
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	CP_Image_Draw(menu_button, CP_System_GetWindowWidth() * 0.5f + 10.0f, CP_System_GetWindowHeight() * 0.5f, 300.0f, 75.0f, 255);
	if (CP_Input_GetMouseX() > 300 &&
		CP_Input_GetMouseX() < 500 &&
		CP_Input_GetMouseY() > 350 &&
		CP_Input_GetMouseY() < 450)
	{
		CP_Image_Draw(menu_hovered, CP_System_GetWindowWidth() * 0.5f + 10.0f, CP_System_GetWindowHeight() * 0.5f, 300.0f, 75.0f, 255);
		if (CP_Input_MouseClicked())
		{
			CP_Engine_SetNextGameState(gamestate_menu_init, gamestate_menu_update, gamestate_menu_exit);
		}
	}

	CP_Image_Draw(quit_button2, CP_System_GetWindowWidth() * 0.5f + 15.0f, CP_System_GetWindowHeight() * 0.5f + 200.0f, 300.0f, 100.0f, 255);
	if (CP_Input_GetMouseX() > 300 &&
		CP_Input_GetMouseX() < 500 &&
		CP_Input_GetMouseY() > 550 &&
		CP_Input_GetMouseY() < 650)
	{
		CP_Image_Draw(quit_hovered2, CP_System_GetWindowWidth() * 0.5f + 15.0f, CP_System_GetWindowHeight() * 0.5f + 200.0f, 300.0f, 100.0f, 255);
		if (CP_Input_MouseClicked())
		{
			CP_Engine_Terminate();
		}
	}
}

void gamestate_win_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}
