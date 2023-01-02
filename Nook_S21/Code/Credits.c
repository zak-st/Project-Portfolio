// ---------------------------------------------------------------------------
// Project Name		:	Nook
// File Name		:	Credits.c
// Author			:	Zak Stephenson
// Creation Date	:	22 Feb 2021
// Purpose			:	Credits Screen
// All content © 2021 DigiPen (USA) Corporation, all rights reserved.
// ---------------------------------------------------------------------------

#include "framework.h"
#include "AEEngine.h"
#include "Audio.h"
#include "GameStateManager.h"
#include "object_data.h"
#include "Sprite.h"

#include "Credits.h"

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

static vec2 backgroundSize = { 1670.0f, 564.0f };
static vec2 backButtonSize = { 20.0f, 20.0f };
static signed long mouseX, mouseY;
static float mouseInWorldX, mouseInWorldY;

static AEGfxVertexList* buttonMesh;
static AEGfxVertexList* bgMesh;
static AEGfxVertexList* fontMesh;
static AEGfxVertexList* arrowMesh;
static AEGfxVertexList* backButtonMesh;
static AEGfxVertexList* numMesh;

static AEGfxTexture* bgTexture;
static AEGfxTexture* buttonTexture;
static AEGfxTexture* fontTexture;
static AEGfxTexture* arrowTexture;
static AEGfxTexture* backButtonTexture;
static AEGfxTexture* numTexture;

static TextureOffset numOffsets[10];
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

void CreditsLoad()
{
    /*mesh for bg*/
    AEGfxMeshStart();

    AEGfxTriAdd(
        -backgroundSize.x, -backgroundSize.y, 0xFF00FF00, 0.0f, 1.0f,
        backgroundSize.x, -backgroundSize.y, 0xFF00FF00, 1.0f, 1.0f,
        -backgroundSize.x, backgroundSize.y, 0xFF00FF00, 0.0f, 0.0f);

    AEGfxTriAdd(
        backgroundSize.x, -backgroundSize.y, 0xFF00FF00, 1.0f, 1.0f,
        backgroundSize.x, backgroundSize.y, 0xFF00FF00, 1.0f, 0.0f,
        -backgroundSize.x, backgroundSize.y, 0xFF00FF00, 0.0f, 0.0f);

    bgMesh = AEGfxMeshEnd();
    AE_ASSERT_MESG(bgMesh, "Failed to create button!");

    bgTexture = AEGfxTextureLoad("Assets/CityscapeGrey.png");
    AE_ASSERT_MESG(bgTexture, "Failed to create pTex!!");

    /*mesh for back button*/
    backButtonMesh = createEqualQuadMesh(20.0f, 1.0f, "backButton");

    backButtonTexture = AEGfxTextureLoad("Assets/NoirBackButton.png");
    AE_ASSERT_MESG(backButtonTexture, "Failed to create texture!");

    /*mesh for text*/
    fontMesh = createQuadMesh(15.0f, 15.0f, 1.0f / 5, 1.0f / 6, "alphabets");

    fontTexture = AEGfxTextureLoad("Assets/NookFontSheet_alphabet.png");
    AE_ASSERT_MESG(fontTexture, "Failed to create texture!");

    fontOffsets[0].mX = 0.0f;			    fontOffsets[0].mY = 0.0f / 6;  //A
    fontOffsets[1].mX = 1.0f / 5;		    fontOffsets[1].mY = 0.0f / 6;  //B
    fontOffsets[2].mX = 2.0f / 5;			fontOffsets[2].mY = 0.0f / 6;  //C
    fontOffsets[3].mX = 3.0f / 5;			fontOffsets[3].mY = 0.0f / 6;  //D
    fontOffsets[4].mX = 4.0f / 5;			fontOffsets[4].mY = 0.0f / 6;  //E

    fontOffsets[5].mX = 0.0f;			    fontOffsets[5].mY = 1.0f / 6;  //F
    fontOffsets[6].mX = 1.0f / 5;		    fontOffsets[6].mY = 1.0f / 6;  //G
    fontOffsets[7].mX = 2.0f / 5;			fontOffsets[7].mY = 1.0f / 6;  //H
    fontOffsets[8].mX = 3.0f / 5;			fontOffsets[8].mY = 1.0f / 6;  //I
    fontOffsets[9].mX = 4.0f / 5;			fontOffsets[9].mY = 1.0f / 6;  //J

    fontOffsets[10].mX = 0.0f;			    fontOffsets[10].mY = 2.0f / 6;  //K
    fontOffsets[11].mX = 1.0f / 5;		    fontOffsets[11].mY = 2.0f / 6;  //L
    fontOffsets[12].mX = 2.0f / 5;			fontOffsets[12].mY = 2.0f / 6;  //M
    fontOffsets[13].mX = 3.0f / 5;			fontOffsets[13].mY = 2.0f / 6;  //N
    fontOffsets[14].mX = 4.0f / 5;			fontOffsets[14].mY = 2.0f / 6;  //O

    fontOffsets[15].mX = 0.0f;			    fontOffsets[15].mY = 3.0f / 6;  //P
    fontOffsets[16].mX = 1.0f / 5;		    fontOffsets[16].mY = 3.0f / 6;  //Q
    fontOffsets[17].mX = 2.0f / 5;			fontOffsets[17].mY = 3.0f / 6;  //R
    fontOffsets[18].mX = 3.0f / 5;			fontOffsets[18].mY = 3.0f / 6;  //S
    fontOffsets[19].mX = 4.0f / 5;			fontOffsets[19].mY = 3.0f / 6;  //T

    fontOffsets[20].mX = 0.0f;			    fontOffsets[20].mY = 4.0f / 6;  //U
    fontOffsets[21].mX = 1.0f / 5;		    fontOffsets[21].mY = 4.0f / 6;  //V
    fontOffsets[22].mX = 2.0f / 5;			fontOffsets[22].mY = 4.0f / 6;  //W
    fontOffsets[23].mX = 3.0f / 5;			fontOffsets[23].mY = 4.0f / 6;  //X
    fontOffsets[24].mX = 4.0f / 5;			fontOffsets[24].mY = 4.0f / 6;  //Y


    fontOffsets[25].mX = 0.0f;			    fontOffsets[25].mY = 5.0f / 6;  //Z  
    fontOffsets[26].mX = 1.0f / 5;		    fontOffsets[26].mY = 5.0f / 6;  //Left Parenthesis
    fontOffsets[27].mX = 2.0f / 5;			fontOffsets[27].mY = 5.0f / 6;  //Right Parenthesis
    fontOffsets[28].mX = 3.0f / 5;			fontOffsets[28].mY = 5.0f / 6;  //blank
    fontOffsets[29].mX = 4.0f / 5;			fontOffsets[29].mY = 5.0f / 6;  //blank

        /*mesh for numbers*/
    numMesh = createQuadMesh(15.0f, 15.0f, 1.0 / 3, 1.0f / 4, "numbers");

    numTexture = AEGfxTextureLoad("Assets/NookFontSheet_numbers.png");
    AE_ASSERT_MESG(numTexture, "Failed to create texture!");

    numOffsets[0].mX = 0.0f;			    numOffsets[0].mY = 0.0f / 4;  //0
    numOffsets[1].mX = 1.0f / 3;		    numOffsets[1].mY = 0.0f / 4;  //1
    numOffsets[2].mX = 2.0f / 3;			numOffsets[2].mY = 0.0f / 4;  //2

    numOffsets[3].mX = 0.0f;			    numOffsets[3].mY = 1.0f / 4;  //3
    numOffsets[4].mX = 1.0f / 3;			numOffsets[4].mY = 1.0f / 4;  //4
    numOffsets[5].mX = 2.0f / 3;			numOffsets[5].mY = 1.0f / 4;  //5

    numOffsets[6].mX = 0.0f;		        numOffsets[6].mY = 2.0f / 4;  //6
    numOffsets[7].mX = 1.0f / 3;			numOffsets[7].mY = 2.0f / 4;  //7
    numOffsets[8].mX = 2.0f / 3;			numOffsets[8].mY = 2.0f / 4;  //8

    numOffsets[9].mX = 0.0f / 3;			numOffsets[9].mY = 3.0f / 4;  //9
}

void CreditsInit()
{
    AEGfxSetBackgroundColor(0.55f, 0.55f, 0.55f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
}

void CreditsUpdate(float dt)
{
    UNREFERENCED_PARAMETER(dt);
    /*AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetPosition(0, 0);
    AEGfxTextureSet(bgTexture, 0, 0);
    AEGfxSetTransparency(1.0f);
    AEGfxSetPosition(0.0f, 0.0f);
    AEGfxMeshDraw(bgMesh, AE_GFX_MDM_TRIANGLES);*/

    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetPosition(AEGfxGetWinMinX() + 40.0f, AEGfxGetWinMaxY() - 30.0f);
    AEGfxTextureSet(backButtonTexture, 1.0f, 1.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(backButtonMesh, AE_GFX_MDM_TRIANGLES);

    /*get the mouse position*/
    AEInputGetCursorPosition(&mouseX, &mouseY);
    AEGfxConvertScreenCoordinatesToWorld(mouseX, mouseY, &mouseInWorldX, &mouseInWorldY);

    /*if backButton is hovered*/
    if ((mouseInWorldX > (AEGfxGetWinMinX() + 40.0f - 20.0f) && mouseInWorldX < (AEGfxGetWinMinX() + 40.0f + 20.0f)) &&
        (mouseInWorldY > (AEGfxGetWinMaxY() - 30.0f - 20.0f) && mouseInWorldY < (AEGfxGetWinMaxY() - 30.0f + 20.0f)))
    {
        // Hover texture

        if (AEInputCheckTriggered(RI_MOUSE_LEFT_BUTTON_DOWN))
        {
            GameStateManagerSetNextState(Menu);
        }
    }

    /*Team Names*/
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    /*Caleb*/
    AEGfxSetPosition(- 180.0f, 255.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[2].mX, fontOffsets[2].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(- 150.0f, 255.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(- 120.0f, 255.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[11].mX, fontOffsets[11].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-90.0f, 255.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(- 60.0f, 255.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[1].mX, fontOffsets[1].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetPosition(0.0f, 255.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[7].mX, fontOffsets[7].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(30.0f, 255.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[20].mX, fontOffsets[20].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);
    
    AEGfxSetPosition(60.0f, 255.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(90.0f, 255.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[11].mX, fontOffsets[11].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(120.0f, 255.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[1].mX, fontOffsets[1].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(150.0f, 255.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(180.0f, 255.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(210.0f, 255.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    /*Mary*/

    AEGfxSetPosition(0.0f - 120.0f, 220.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[12].mX, fontOffsets[12].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f - 90.0f, 220.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f - 60.0f, 220.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f - 30.0f, 220.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[24].mX, fontOffsets[24].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetPosition(0.0f + 30.0f, 220.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[10].mX, fontOffsets[10].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f + 60.0f, 220.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[7].mX, fontOffsets[7].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f + 90.0f, 220.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[20].mX, fontOffsets[20].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f + 120.0f, 220.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[20].mX, fontOffsets[20].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    /*Justin*/

    AEGfxSetPosition(-120.0f, 185.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[9].mX, fontOffsets[9].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-90.0f, 185.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[20].mX, fontOffsets[20].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-60.0f, 185.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[18].mX, fontOffsets[18].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-30.0f, 185.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f, 185.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(30.0f, 185.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetPosition(90.0f, 185.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[11].mX, fontOffsets[11].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(120.0f, 185.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    /*Rey*/

    AEGfxSetPosition(-150.0f, 155.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-120.0f, 155.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-90.0f, 155.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[24].mX, fontOffsets[24].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetPosition(-30.0f, 155.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f, 155.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[14].mX, fontOffsets[14].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(30.0f, 155.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[18].mX, fontOffsets[18].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(60.0f, 155.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(90.0f, 155.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(120.0f, 155.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(150.0f, 155.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[14].mX, fontOffsets[14].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    /*Zak*/

    AEGfxSetPosition(-180.0f, 120.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[25].mX, fontOffsets[25].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-150.0f, 120.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-120.0f, 120.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[10].mX, fontOffsets[10].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetPosition(-60.0f, 120.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[18].mX, fontOffsets[18].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-30.0f, 120.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f, 120.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(30.0f, 120.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[15].mX, fontOffsets[15].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(60.0f, 120.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[7].mX, fontOffsets[7].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(90.0f, 120.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(120.0f, 120.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(150.0f, 120.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[18].mX, fontOffsets[18].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(180.0f, 120.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[14].mX, fontOffsets[14].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(210.0f, 120.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    /*Instructors*/

    AEGfxSetPosition(-150.0f, 65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-120.0f, 65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-90.0f, 65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[18].mX, fontOffsets[18].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-60.0f, 65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-30.0f, 65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f, 65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(30.0f, 65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[2].mX, fontOffsets[2].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(60.0f, 65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(90.0f, 65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[14].mX, fontOffsets[14].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(120.0f, 65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(150.0f, 65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[18].mX, fontOffsets[18].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    /*Justin Chambers*/

    AEGfxSetPosition(-210.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[9].mX, fontOffsets[9].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-180.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[20].mX, fontOffsets[20].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-150.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[18].mX, fontOffsets[18].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-120.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-90.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-60.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetPosition(0.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[2].mX, fontOffsets[2].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(30.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[7].mX, fontOffsets[7].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(60.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(90.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[12].mX, fontOffsets[12].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(120.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[1].mX, fontOffsets[1].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(150.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(180.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(210.0f, 25.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[18].mX, fontOffsets[18].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    /*Matthew Picioccio*/

    AEGfxSetPosition(-240.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[12].mX, fontOffsets[12].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-210.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-180.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-150.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-120.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-90.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[22].mX, fontOffsets[22].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetPosition(-30.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[15].mX, fontOffsets[15].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(30.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[2].mX, fontOffsets[2].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(60.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(90.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[14].mX, fontOffsets[14].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(120.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[2].mX, fontOffsets[2].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(150.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[2].mX, fontOffsets[2].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(180.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(210.0f, -10.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[14].mX, fontOffsets[14].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    /*Special Thanks*/

    AEGfxSetPosition(-210.0f, -65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[18].mX, fontOffsets[18].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-180.0f, -65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[15].mX, fontOffsets[15].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-150.0f, -65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-120.0f, -65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[2].mX, fontOffsets[2].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-90.0f, -65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-60.0f, -65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-30.0f, -65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[11].mX, fontOffsets[11].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetPosition(30.0f, -65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(60.0f, -65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[7].mX, fontOffsets[7].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(90.0f, -65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(120.0f, -65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(150.0f, -65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[10].mX, fontOffsets[10].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(180.0f, -65.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[18].mX, fontOffsets[18].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    /*Rhianna Pinkerton*/

    AEGfxSetPosition(-240.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-210.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[7].mX, fontOffsets[7].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-180.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-150.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-120.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-90.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-60.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetPosition(0.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[15].mX, fontOffsets[15].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(30.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(60.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(90.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[10].mX, fontOffsets[10].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(120.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(150.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(180.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(210.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[14].mX, fontOffsets[14].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(240.0f, -105.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    /*Bennett Ewanchyna*/

    AEGfxSetPosition(-240.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[1].mX, fontOffsets[1].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-210.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-180.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-150.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-120.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-90.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-60.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetPosition(0.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(30.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[22].mX, fontOffsets[22].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(60.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(90.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(120.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[2].mX, fontOffsets[2].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(150.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[7].mX, fontOffsets[7].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(180.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[24].mX, fontOffsets[24].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(210.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(240.0f, -140.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    /*Benjamin Fox*/

    AEGfxSetPosition(-180.0f, -175.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[1].mX, fontOffsets[1].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-150.0f, -175.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-120.0f, -175.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-90.0f, -175.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[9].mX, fontOffsets[9].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-60.0f, -175.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(-30.0f, -175.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[12].mX, fontOffsets[12].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(0.0f, -175.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(30.0f, -175.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetPosition(90.0f, -175.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[5].mX, fontOffsets[5].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(120.0f, -175.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[14].mX, fontOffsets[14].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetPosition(150.0f, -175.0f);
    AEGfxTextureSet(fontTexture, fontOffsets[23].mX, fontOffsets[23].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    /*Copyright*/

    AEGfxSetFullTransform(-345.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-330.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[11].mX, fontOffsets[11].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-315.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[11].mX, fontOffsets[11].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetFullTransform(-285.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[2].mX, fontOffsets[2].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-269.5f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[14].mX, fontOffsets[14].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-254.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-238.5f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-223.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-207.5f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-186.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetFullTransform(-165.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[26].mX, fontOffsets[26].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-150.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[2].mX, fontOffsets[2].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-135.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[27].mX, fontOffsets[27].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetFullTransform(-105.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(numTexture, numOffsets[2].mX, numOffsets[2].mY);
    AEGfxMeshDraw(numMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-90.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(numTexture, numOffsets[0].mX, numOffsets[0].mY);
    AEGfxMeshDraw(numMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-75.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(numTexture, numOffsets[2].mX, numOffsets[2].mY);
    AEGfxMeshDraw(numMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-62.5f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(numTexture, numOffsets[1].mX, numOffsets[1].mY);
    AEGfxMeshDraw(numMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetFullTransform(-30.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[3].mX, fontOffsets[3].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-15.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(0.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[6].mX, fontOffsets[6].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(15.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(30.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[15].mX, fontOffsets[15].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(45.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(60.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[11].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetFullTransform(90.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[26].mX, fontOffsets[26].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(105.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[20].mX, fontOffsets[20].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(120.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[18].mX, fontOffsets[18].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(135.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(150.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[27].mX, fontOffsets[27].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetFullTransform(180.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[2].mX, fontOffsets[2].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(198.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[14].mX, fontOffsets[14].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(216.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(228.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[15].mX, fontOffsets[15].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(244.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[14].mX, fontOffsets[14].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(262.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(276.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(292.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(308.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(324.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[14].mX, fontOffsets[14].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(342.0f, -250.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[13].mX, fontOffsets[13].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    /*All Right Reserved*/

    AEGfxSetFullTransform(-120.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[0].mX, fontOffsets[0].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-105.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[11].mX, fontOffsets[11].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-90.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[11].mX, fontOffsets[11].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetFullTransform(-60.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-45.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[8].mX, fontOffsets[8].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-30.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[6].mX, fontOffsets[6].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(-15.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[7].mX, fontOffsets[7].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(0.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[19].mX, fontOffsets[19].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(15.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[18].mX, fontOffsets[18].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);



    AEGfxSetFullTransform(45.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(60.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(75.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[18].mX, fontOffsets[18].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(90.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(105.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[17].mX, fontOffsets[17].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(120.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[21].mX, fontOffsets[21].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(135.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[4].mX, fontOffsets[4].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);

    AEGfxSetFullTransform(150.0f, -280.0f, 0.0f, 0.6f, 0.6f);
    AEGfxTextureSet(fontTexture, fontOffsets[3].mX, fontOffsets[3].mY);
    AEGfxMeshDraw(fontMesh, AE_GFX_MDM_TRIANGLES);


}

void CreditsShutdown()
{
    AudioCleanup();
}

void CreditsUnload()
{
    // Free all sprite sources.

    // Unload all textures.
    AEGfxTextureUnload(buttonTexture);
    AEGfxTextureUnload(fontTexture);
    AEGfxTextureUnload(bgTexture);
    AEGfxTextureUnload(backButtonTexture);
    // Free all meshes.
    AEGfxMeshFree(buttonMesh);
    AEGfxMeshFree(fontMesh);
    AEGfxMeshFree(bgMesh);
    AEGfxMeshFree(backButtonMesh);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------