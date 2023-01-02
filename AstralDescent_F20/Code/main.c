//---------------------------------------------------------
// file:	main.c
// author:	Mary Khuu, Rey Rosario, Zak Stephenson, Zac Clapper
// course:	GAM100
//
// brief:	Main entry point for the Astral Descent game
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "gamestate_splash.h"
#include "gamestate_menu.h"

int main(void)
{
	CP_System_SetWindowSize(800, 800);
	CP_Engine_SetNextGameState(gamestate_splash_init, gamestate_splash_update, gamestate_splash_exit);
	CP_Engine_Run();
	return 0;
}
