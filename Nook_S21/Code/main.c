// ---------------------------------------------------------------------------
// Project Name		:	Nook
// File Name		:	main.c
// Author			:	Justin Li, Zak Stephenson, Rey Rosario
// Creation Date	:	25 Jan 2021
// Purpose			:	main entry point2 for the test program
// History			:
// - 25 Jan 2021	:	- initial implementation
// All content © 2021 DigiPen (USA) Corporation, all rights reserved.
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// includes

#include "framework.h"
#include "AEEngine.h"
#include "fmod.h"
#include "GameStateManager.h"

// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
// globals
static	FMOD_SYSTEM* FmodSystem;
static	FMOD_SOUND* sound;
static	FMOD_CHANNEL* channel = 0;
FMOD_RESULT result;
static float dt;

// ---------------------------------------------------------------------------
// Static function protoypes

// ---------------------------------------------------------------------------
// main

void ERRCHECK(FMOD_RESULT checkResult)
{
	if (checkResult != FMOD_OK)
	{
		printf("There was an error in the audio system");
	}
}
int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	UNREFERENCED_PARAMETER(prevInstanceH);
	UNREFERENCED_PARAMETER(command_line);

	// Initialize the FMOD System
	result = FMOD_System_Create(&FmodSystem);
	ERRCHECK(result);


	result = FMOD_System_Init(FmodSystem, 32, FMOD_INIT_NORMAL, NULL);
	ERRCHECK(result);

	// Create and Play the sound
	// Note: this should be generalized for multiple sounds and
	//       be placed in a function to be used outside of init.
	result = FMOD_System_CreateStream(FmodSystem, "sample_beep.wav", FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
	ERRCHECK(result);

	result = FMOD_System_PlaySound(FmodSystem, sound, 0, false, &channel);
	ERRCHECK(result);

	// Create and Initialize the AE system 
	AESysInitInfo sysInitInfo;
	sysInitInfo.mCreateWindow = 1;
	sysInitInfo.mAppInstance = instanceH;
	sysInitInfo.mShow = show;
	sysInitInfo.mWinWidth = 800;
	sysInitInfo.mWinHeight = 600;
	sysInitInfo.mCreateConsole = 1;
	sysInitInfo.mMaxFrameRate = 60;
	sysInitInfo.mpWinCallBack = NULL;//MyWinCallBack;
	sysInitInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;
	sysInitInfo.mWindowStyle = WS_OVERLAPPEDWINDOW;//WS_POPUP | WS_VISIBLE | WS_SYSMENU | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;;	
	sysInitInfo.mWindowHandle = NULL;
	sysInitInfo.mHandleWindowMessages = 1;
	AESysInit(&sysInitInfo);

	// Initialize the game state manager
	GameStateManagerInit();

	// Change the window title.
	AESysSetWindowTitle("Nook - GAM 150");

	// Set bg color
	AEGfxSetBackgroundColor(0.1f, 0.0f, 0.2f);

	// Reset the system modules
	AESysReset();

	// Game Loop
	while (GameStateManagerIsRunning())
	{
		// Change in time (in seconds) since the last game loop.
		dt = (float)AEFrameRateControllerGetFrameTime();

		// Clamping prevents excessive dt values due to long load times or pausing execution in a debugger.
		dt = AEClamp(dt, 0.0f, 0.125f);

		// Informing the system about the loop's start
		AESysFrameStart();

		AESysUpdate();

		// Handling Input
		AEInputUpdate();
		result = FMOD_System_Update(FmodSystem);
		ERRCHECK(result);

		// Update the game state manager.
		GameStateManagerUpdate(dt);

		// Informing the system about the loop's end
		AESysFrameEnd();
	}

	// Shutdown the game state manager.
	GameStateManagerShutdown();

	// Free the system
	result = FMOD_Sound_Release(sound);
	ERRCHECK(result);

	// Close and Release the FMOD system
	result = FMOD_System_Close(FmodSystem);
	ERRCHECK(result);
	result = FMOD_System_Release(FmodSystem);
	ERRCHECK(result);
	AESysExit();

	return 1;
}

// ---------------------------------------------------------------------------

