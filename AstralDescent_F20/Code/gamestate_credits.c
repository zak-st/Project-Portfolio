//---------------------------------------------------------
// file:	gamestate_credits.c
// author:	Zak Stephenson
// course:	GAM100
//
// brief:	template file for holding gamestate functions
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "gamestate_credits.h"
#include "gamestate_menu.h"
#include "gamestate_splash.h"

CP_Image back_button2 = NULL;
CP_Image back_hovered2 = NULL;

void gamestate_credits_init(void)
{
	back_button2 = CP_Image_Load("./OurAssets/backArrow.png");
	back_hovered2 = CP_Image_Load("./OurAssets/backArrowPressed.png");

	CP_Settings_TextSize(100.0f);
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	drawStars(600);
	CP_Font_DrawText("Credits", CP_System_GetWindowWidth() * 0.5f, (CP_System_GetWindowHeight() * 0.5f) - 300.0f);
	CP_Settings_TextSize(75.0f);
	CP_Font_DrawText("ASTRAL DECENT", CP_System_GetWindowHeight() * 0.5f, (CP_System_GetWindowHeight() * 0.5f) - 200.0f);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("All content (c) 2020 DigiPen (USA) Corporation, all rights reserved.", CP_System_GetWindowHeight() * 0.5f, (CP_System_GetWindowHeight() * 0.5f) - 125.0f);
	CP_Font_DrawText("Zach Clapper, Mary Khuu, Rey Rosario, and Zak Stephenson", CP_System_GetWindowHeight() * 0.5f, (CP_System_GetWindowHeight() * 0.5f) - 50.0f);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("Instructors", CP_System_GetWindowHeight() * 0.5f, (CP_System_GetWindowHeight() * 0.5f) + 25.0f);
	CP_Font_DrawText("Justin Chambers and Douglas Scilling", CP_System_GetWindowHeight() * 0.5f, (CP_System_GetWindowHeight() * 0.5f) + 100.0f);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Made with FMOD Studio by Firelight Technologies Pty Ltd.", CP_System_GetWindowHeight() * 0.5f, (CP_System_GetWindowHeight() * 0.5f) + 175.0f);
}
void gamestate_credits_update(void)
{

	CP_Image_Draw(back_button2, CP_System_GetWindowWidth() * 0.5f - 300.0f, CP_System_GetWindowHeight() * 0.5f - 300.0f, 75.0f, 75.0f, 255);

	if (CP_Input_GetMouseX() > 50 &&
		CP_Input_GetMouseX() < 150 &&
		CP_Input_GetMouseY() > 50 &&
		CP_Input_GetMouseY() < 150)
	{
		CP_Image_Draw(back_hovered2, CP_System_GetWindowWidth() * 0.5f - 300.0f, CP_System_GetWindowHeight() * 0.5f - 300.0f, 75.0f, 75.0f, 255);
		if (CP_Input_MouseClicked())
		{
			CP_Engine_SetNextGameState(gamestate_menu_init, gamestate_menu_update, gamestate_menu_exit);
		}
	}
}


void gamestate_credits_exit(void)
{

}
