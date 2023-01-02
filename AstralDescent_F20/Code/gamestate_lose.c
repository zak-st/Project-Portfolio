//---------------------------------------------------------
// file:	gamestate_lose.c
// author:	Rey Rosario, Zak Stephenson, Zac Clapper
// course:	GAM100
//
// brief:	losing screen
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "gamestate_lose.h"
#include "gamestate_hub.h"
#include "gamestate_splash.h"

void gamestate_lose_init(void)
{
	CP_Settings_TextSize(100.0f);
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	drawStars(600);
	CP_Font_DrawText("You Lost", CP_System_GetWindowWidth() * 0.5f, (CP_System_GetWindowHeight() * 0.5f) - 200.0f);
}

void gamestate_lose_update(void)
{
	// check input, update simulation, render etc.
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(100.0f);
	CP_Settings_Fill(CP_Color_Create(100, 100, 100, 255)); /* Grey rectangle */
	CP_Graphics_DrawRect(CP_System_GetWindowWidth() * 0.5f, CP_System_GetWindowHeight() * 0.5f, 250.0f, 100.0f);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255)); /* Black text for button */
	CP_Font_DrawText("Retry", CP_System_GetWindowWidth() * 0.5f, CP_System_GetWindowHeight() * 0.5f);


	// same as the hub button.
	if (CP_Input_GetMouseX() > 300 &&
		CP_Input_GetMouseX() < 500 &&
		CP_Input_GetMouseY() > 350 &&
		CP_Input_GetMouseY() < 450)
	{
		if (CP_Input_MouseClicked())
		{
			CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		}
	}
}

void gamestate_lose_exit(void)
{
	// shut down the gamestate and cleanup any dynamic memory
}
