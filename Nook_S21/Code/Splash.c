// ---------------------------------------------------------------------------
// Project Name		:	Nook
// File Name		:	Splash.c
// Author			:	Zak Stephenson
// Creation Date	:	22 Feb 2021
// Purpose			:	Splash Screen
//
// All content © 2021 DigiPen (USA) Corporation, all rights reserved.
// ---------------------------------------------------------------------------

#include "framework.h"
#include "AEEngine.h"
#include "Audio.h"
#include "GameStateManager.h"
#include "object_data.h"
#include "Sprite.h"

#include "Splash.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static AEGfxVertexList* logoMesh;
static AEGfxVertexList* fmodMesh;
static AEGfxVertexList* creditMesh;
static AEGfxTexture* logoTexture;
static AEGfxTexture* fmodTexture;
static AEGfxTexture* creditTexture;

static float splashTimer = 0.0f;
static vec2 logoSize = { 1026.0f, 249.0f };
static vec2 fmodSize = { 728.0f, 192.0f };
static vec2 creditSize = { 600.0f, 100.0f };

static TextureOffset fontOffsets[30];
static int* currentfontOffset = 0;
static int currfontFrame = 0;
static float* fontTime;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void SplashLoad()
{
    logoMesh = createQuadMesh(logoSize.x / 3, logoSize.y / 3, 1.0f, 1.0f, "logoMesh");
    AE_ASSERT_MESG(logoMesh, "Failed to create logoMesh!");
    
    fmodMesh = createQuadMesh(fmodSize.x / 3, fmodSize.y / 3, 1.0f, 1.0f, "logoMesh");
    AE_ASSERT_MESG(fmodMesh, "Failed to create fmodMesh!");
    
    creditMesh = createQuadMesh(creditSize.x / 3, creditSize.y / 3, 1.0f, 1.0f, "logoMesh");
    AE_ASSERT_MESG(creditMesh, "Failed to create fmodMesh!");

    logoTexture = AEGfxTextureLoad("Assets/DigiPen_RED.png");
    AE_ASSERT_MESG(logoTexture, "Failed to create logoTexture!");

    fmodTexture = AEGfxTextureLoad("Assets/FModLogo.png");
    AE_ASSERT_MESG(fmodTexture, "Failed to create fmodTexture!");

    creditTexture = AEGfxTextureLoad("Assets/FModCredit.png");
    AE_ASSERT_MESG(creditTexture, "Failed to create texture!");

    
}

void SplashInit()
{
    splashTimer = 0.0f;
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
    
    AudioInit();
    playSoundAdvanced("Assets/Sounds/DigiPenSplashTrack.mp3", 0.1f);
}

void SplashUpdate(float dt)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    if (splashTimer >= 0.0f && splashTimer <= 2.5f)
    {
        AEGfxSetPosition(0.0f, 0.0f);
        AEGfxTextureSet(logoTexture, 1.0f, 1.0f);
        AEGfxSetTransparency(1.0f);
        AEGfxMeshDraw(logoMesh, AE_GFX_MDM_TRIANGLES);
    }
    if (splashTimer >= 2.5f && splashTimer <= 5.0f)
    {
        AEGfxSetPosition(0.0f, 0.0f);
        AEGfxTextureSet(fmodTexture, 1.0f, 1.0f);
        AEGfxMeshDraw(fmodMesh, AE_GFX_MDM_TRIANGLES);

        AEGfxSetPosition(0.0f, -150.0f);
        AEGfxTextureSet(creditTexture, 1.0f, 1.0f);
        AEGfxMeshDraw(creditMesh, AE_GFX_MDM_TRIANGLES);
    }
    if (splashTimer >= 5.0f)
    {
        GameStateManagerSetNextState(Menu);
    }
    splashTimer += dt;
}

void SplashShutdown()
{
    AudioCleanup();
}

void SplashUnload()
{
    AEGfxTextureUnload(logoTexture);
    AEGfxMeshFree(logoMesh);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------