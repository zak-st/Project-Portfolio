//------------------------------------------------------------------------------
/*!
\file	Level1.cpp
\author	Ash (a.blankenship), Mary (m.khuu), Riti (r.bhatwal), Zak (zak.s)
    Hemie (hemie.choi), Rey (rey.rosario)
\par	Copyright © 2021 DigiPen (USA) Corporation.
\brief
*/
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------
#include "PlayerLivesDisplay.h"
#include "PauseButtonDisplay.h"
#include "KeyDisplay.h"
#include "BehaviorKeyEnd.h"
#include "stdafx.h"
#include "Audio.h"
#include "GameStateManager.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/mat3x3.hpp"
#include "glm/vec3.hpp"
#include "GameObject.h"
#include "Gui.h"
#include "Level1.h"
#include "Mesh.h"
#include "PhysicsSystem.h"
#include "ComponentParticleSystem.h"
#include "Resource.h"
#include "Shader.h"
#include "GameObjectManager.h"
#include "MeshManager.h"
#include "stb_image.h"
#include "System.h"
#include "Trace.h"
#include "DebugDraw.h"
#include "LevelLoadSystem.h"
#include "BehaviorKey.h"
#include "BehaviorEnemy.h"
#include "BehaviorBigEnemy.h"
#include "BunBun.h"
#include <sstream>
#include "JsonLoader.h"
#include "BehaviorSystem.h"
#include "AnimationSystem.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "ImageManager.h"
#include "BehaviorIceBullet.h"
#include "PhysicsParticleGenerator.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
bool  LevelActiveFlag;
bool pause = false;
bool quitTrigger = false;
glm::vec3 previous = glm::vec3(0);

///////// PLAYER variables ////////////
GameObjectPtr TestGameObject = 0;
BehaviorBunBunPtr PlayerBehavior = 0;
PlayerLivesDisplay* LivesDisplay = 0;
///////////////////////////////////////

glm::mat3x3 RedRectTran;
bool ShowRedRect;
GameObjectManager ObjectManager;
ComponentGraphics* myBackground = 0;
ComponentGraphics* myParallax1 = 0;
ComponentGraphics* myParallax2 = 0;
ComponentGraphics* myParallax3 = 0;

//Pause Button 
PauseButtonDisplay* PauseDisplay = 0;
bool musicOn = true;

static SpriteSourcePtr randomani;
ComponentGraphics* testan = 0;
ComponentSprite* Testani = 0;

SpriteSource* SpriteSourceEnemy;

//KEY KEY
GameObjectPtr Key;
BehaviorKey* KeyBehavior;
GameObjectPtr KeyMid;
BehaviorKeyMid* KeyMidBehavior;
GameObjectPtr KeyEnd;
BehaviorKeyEnd* KeyEndBehavior;
static const float WinTransitionTime = 4.0f;
ComponentGraphics* bKeyH = 0;
ComponentGraphics* bKeyM = 0;
ComponentGraphics* bKeyB = 0;
GameObject* WinTrans = 0;
PhysicsParticleEmitter* Em = 0;

rapidjson::Document* LevelDoc;
rapidjson::Document* EnemyDoc;
rapidjson::Document* flyingEnemyDoc;
rapidjson::Document* BigEnemyDoc;
rapidjson::Document* RotatingPlatformDoc;
rapidjson::Document* BulletDoc;
rapidjson::Document* SoundEffectDoc;
rapidjson::Document* AnimatedMenuDoc;
rapidjson::Document* WinTransDoc;
rapidjson::Document* KeyEffectDoc;

ComponentSprite* Background = 0;
ComponentSprite* Parallax1 = 0;
ComponentSprite* Parallax2 = 0;
ComponentSprite* Parallax3 = 0;
ComponentSprite* MainMenuButton = 0;
ComponentSprite* ResumeButton = 0;
ComponentSprite* QuitButton = 0;
ComponentSprite* YesButton = 0;
ComponentSprite* YesHover = 0;
ComponentSprite* NoButton = 0;
ComponentSprite* NoHover = 0;
ComponentGraphics* LoadingImg = 0;
GameObject* MenuBackgroundAnimated = 0;
PhysicsEmmiterManager* EmmiterManager;
float TimeSinceLastShot;
ImageManager* ImgManager = 0;
unsigned int VBO, VAO, EBO;
unsigned int texture;                                   // For textures
int width, height, nrChannels;                          // For textures

//ComponentParticleSystemPtr tempWalkSystem;

GLFWwindow* window;

ComponentParticleSystemPtr keyPSystem;
ParticlePattern keyPPattern;
glm::vec2 particleScaleLevel1 = { 0.1f, 0.1f };
bool keyPSystemPlayback = true;

// Testing Enemy Object 
glm::vec3 enemy_previous = glm::vec3(0);
glm::vec3 PlayerGravity;
// health
int specialCounter = 1;

// mode state
bool GodMode = false;

// dash effect
ComponentGraphics* dash_graphics = 0;
ComponentSprite* dash_sprite = 0;
/////////////////////////////////////////

GameObject* GoalObject = 0;
ComponentTransform* GoalObjTransform = 0;
ComponentCollider* GoalObjBox = 0;

bool ShowGraphics = 0;
bool ShowDebugDraw = 0;

PhysicsSystem PhySystem;
DebugDraw DebugDrawSys;
LevelLoadSystem LevelLoadSys;

bool PlayingWinEffect = false;
float WinAnimationDuration = 4.5;
float TimeSinceWin = 0;

//------------------------ Audio testing//
Audio* soundHolder = 0;

SOUND_PTR music;
SOUND_PTR backgroundMusic;
SOUND_PTR walking;
SOUND_PTR landing;
SOUND_PTR takingDamage;
SOUND_PTR dies;
SOUND_PTR shootingIce;
SOUND_PTR pickingUpKey;
SOUND_PTR pickingUpKey1;
SOUND_PTR doorOpening;

CHANNEL_PTR channelOne = 0; // channel for sound effects with trigger
CHANNEL_PTR channelTwo = 0; // channel for background musics
CHANNEL_PTR channelThree = 0; // channel for player sound effects

bool playKeySound = false;
//--------------------------------------//

ComponentCamera* camera1 = 0;
Shader* CameraShader;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static bool GUIToggle = false;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
void checkInput(GLFWwindow* window, float dt);
void WhilePlayerTouchingDoor(GameObject* Obj, ComponentBehavior* OtherB);
void setNextLevel();
void ShootBullet(float dt);
void GoToMainMenu();
void GoToResume();
void GoToQuit();
void GoToControls();
void GoToOptions();
void GoToExit();
void GoToMM();
void GoToPause();
void GoToMusicOn();
void GoToMusicOff();
void FullScreenClicked();
void WindowedClicked();
void MainMenuButtonHover(glm::mat3x3 ButtonTransform);
void MainMenuButtonLeave();
void ResumeButtonLeave();
void ControlsButtonLeave();
void OptionsButtonLeave();
void QuitButtonLeave();
void YesButtonLeave();
void NoButtonLeave();
void BackButtonLeave();
void OnButtonLeave();
void OffButtonLeave();
void OnFullScreenButtonLeave();
void OnWindowedButtonLeave();
void OptionsButtonHover(glm::mat3x3 ButtonTransform);
void ControlsButtonHover(glm::mat3x3 ButtonTransform);
void QuitButtonHover(glm::mat3x3 ButtonTransform);
void ResumeButtonHover(glm::mat3x3 ButtonTransform);
void YesButtonHover(glm::mat3x3 ButtonTransform);
void NoButtonHover(glm::mat3x3 ButtonTransform);
void BackButtonHover(glm::mat3x3 ButtonTransform);
void OnButtonHover(glm::mat3x3 ButtonTransform);
void OffButtonHover(glm::mat3x3 ButtonTransform);
void OnFullScreenButtonHover(glm::mat3x3 ButtonTransform);
void OnWindowedButtonHover(glm::mat3x3 ButtonTransform);


//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
void WhilePlayerTouchingDoor(GameObject* Obj, ComponentBehavior* OtherB)//this is a function that will be called by goal's collider when it touches the player
{
    bool kh = KeyBehavior->AtDoor(TestGameObject);
    bool km = KeyMidBehavior->AtDoor(TestGameObject);
    bool ke = KeyEndBehavior->AtDoor(TestGameObject);
     if (kh == true && km && ke)
    {
         if (!PlayingWinEffect)
         {
             WinTrans->SetVisible(true);
             GameObjectManagerSpriteDrawSingleObject(WinTrans, &ObjectManager);
             WinTrans->GetAnimation()->Play();
             PhysicsParticleEmitter* Em = EmmiterManager->AddPhysicsParticleEmitter(GoalObject->GetTransform(), "./TextFiles/PhysicsParticleGenerators/VictoryParticleGenerator.json");
             Em->Start();
             //soundHolder->Pause(true, channelTwo);
             //soundHolder->Pause(false, channelOne);
             PlayingWinEffect = true;
         }
    }
}

GameObject* GetPlayer()
{
    return TestGameObject;
}

bool LevelActive()
{
    return LevelActiveFlag;
}
//this is a function that will be called by player's collider when it is resting on a surface
void ResetJump(GameObject* Wall)
{
    // resets player jumping data
    if (!PlayerBehavior->canJump)
    {
        PlayerBehavior->canJump = true;
        PlayerBehavior->canDoubleJump = true;
        PlayerBehavior->isJumping = false;
        PlayerBehavior->jumpDT = 0.0f;
        TestGameObject->SetCurrentAnimation(0);

        //PLAY THE SOUND OF THE PLAYER LANDING HERE
        soundHolder->Play(landing, &channelThree);
        soundHolder->ChangeVolume(channelThree, 0.4f);

    }
}
static void	WindowFocus(GLFWwindow* w, int state)
{
    pause = true;
}
void Level1Load()
{
    // GLFW initialize and configure
    ReadJSONData(&LevelDoc, "./TextFiles/LevelData.json");
    ReadJSONData(&RotatingPlatformDoc, "./TextFiles/RotatingPlatform.json");
    ReadJSONData(&EnemyDoc, "./TextFiles/EnemyBehavior.json");
    ReadJSONData(&flyingEnemyDoc, "./TextFiles/flyingEnemyBehavior.json");
    ReadJSONData(&BigEnemyDoc, "./TextFiles/BigBehaviorEnemyData/EnemyBehavior.json");
    ReadJSONData(&BulletDoc, "./TextFiles/BulletData/Bullet.json");
    ReadJSONData(&KeyEffectDoc, "./TextFiles/KeyEffectData/KeyEffect.json");
    ReadJSONData(&SoundEffectDoc, "./TextFiles/SoundEffects.json");
    ReadJSONData(&AnimatedMenuDoc, "./TextFiles/PauseMenuData/AnimatedMenu.json");
    ReadJSONData(&WinTransDoc, "./TextFiles/PauseMenuData/AniWinTrans.json");
    GodMode = false;

  // GLFW window creation
    window = GetWindow();//glfwCreateWindow(1920, 1080, "Level1", NULL, NULL);
    glfwSetWindowFocusCallback(window, WindowFocus);
    //public void windowFocusChanged(boolean focused) { /* snipped */ }
    int a, b;

    glfwGetWindowSize(window, & a, &b);
    if (window == NULL)
    {
        TraceSetActiveChannel("ERROR");
        TraceMessage("ERROR", "Failed to create GLFW window");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    ShowGraphics = true;

    // imGUI initialize
    GuiInitialize(window);
    TimeSinceWin = 0;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
void Level1Init()
{
    bool quitTrigger = false;

    PhysicsSystem PhySystem;
    PhySystem.Initialize();
    GameObjectManagerInit(&ObjectManager, &PhySystem);
    CameraShader = new Shader("Shaders/camera.vs", "Shaders/camera.fs");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    VBO = 0;
    VAO = 0;
    EBO = 0;

    //graphics stuff
    myBackground = new ComponentGraphics(VAO, VBO, EBO);
    Background = new ComponentSprite();
    char pathName[FILENAME_MAX] = "";
    sprintf_s(pathName, _countof(pathName), "./TextFiles/background/background.txt");
    Stream i = StreamOpen(pathName);
    Background->ReadSprite(i);
    myBackground->SetSprite(Background);
    DebugDrawSys.Initialize();
    myBackground->SetIndices(Background->GetIndecies());
    myBackground->SetVertices(Background->GetVertices());
    myBackground->CreateSquare(VAO, VBO, EBO, i, *CameraShader);
    myBackground->setBackgroundSpeedFromFile(i);
    myBackground->setPosFromFile(i);

    Parallax1 = new ComponentSprite();
    sprintf_s(pathName, _countof(pathName), "./TextFiles/background/parallaxbackground1.txt");
    Stream parallaxStream1 = StreamOpen(pathName);
    Parallax1->ReadSprite(parallaxStream1);
    myParallax1 = new ComponentGraphics(VAO, VBO, EBO);
    myParallax1->SetIndices(Background->GetIndecies());
    myParallax1->SetVertices(Background->GetVertices());
    myParallax1->CreateSquare(VAO, VBO, EBO, parallaxStream1, *CameraShader);
    myParallax1->setBackgroundSpeedFromFile(parallaxStream1);
    myParallax1->setPosFromFile(parallaxStream1);

    Parallax2 = new ComponentSprite();
    sprintf_s(pathName, _countof(pathName), "./TextFiles/background/parallaxbackground2.txt");
    Stream parallaxStream2 = StreamOpen(pathName);
    Parallax2->ReadSprite(parallaxStream2);
    myParallax2 = new ComponentGraphics(VAO, VBO, EBO);
    myParallax2->SetIndices(Background->GetIndecies());
    myParallax2->SetVertices(Background->GetVertices());
    myParallax2->CreateSquare(VAO, VBO, EBO, parallaxStream2, *CameraShader);
    myParallax2->setBackgroundSpeedFromFile(parallaxStream2);
    myParallax2->setPosFromFile(parallaxStream2);

    Parallax3 = new ComponentSprite();
    sprintf_s(pathName, _countof(pathName), "./TextFiles/background/parallaxbackground3.txt");
    Stream parallaxStream3 = StreamOpen(pathName);
    Parallax3->ReadSprite(parallaxStream3);
    myParallax3 = new ComponentGraphics(VAO, VBO, EBO);
    myParallax3->SetIndices(Background->GetIndecies());
    myParallax3->SetVertices(Background->GetVertices());
    myParallax3->CreateSquare(VAO, VBO, EBO, parallaxStream3, *CameraShader);
    myParallax3->setBackgroundSpeedFromFile(parallaxStream3);
    myParallax3->setPosFromFile(parallaxStream3);

   

    LoadingImg = new ComponentGraphics(VAO, VBO, EBO);
    ComponentSprite* LoadingSpr = new ComponentSprite();
    sprintf_s(pathName, _countof(pathName), "./TextFiles/loading.txt");
    Stream loadingHoverStream = StreamOpen(pathName);
    LoadingSpr->ReadSprite(loadingHoverStream);
    LoadingImg->SetSprite(LoadingSpr);
    LoadingImg->SetIndices(LoadingSpr->GetIndecies());
    LoadingImg->SetVertices(LoadingSpr->GetVertices());
    LoadingImg->CreateSquare(VAO, VBO, EBO, loadingHoverStream, *CameraShader);
    LoadingImg->setPosFromFile(loadingHoverStream);
    delete(LoadingSpr);

    //black key head 
    bKeyH = new ComponentGraphics(VAO, VBO, EBO);
    ComponentSprite* bKeyHS = new ComponentSprite();
    sprintf_s(pathName, _countof(pathName), "./TextFiles/KeyData/BKeyHead.txt");
    Stream bkh = StreamOpen(pathName);
    bKeyHS->ReadSprite(bkh);
    bKeyH->SetSprite(bKeyHS);
    bKeyH->SetIndices(bKeyHS->GetIndecies());
    bKeyH->SetVertices(bKeyHS->GetVertices());
    bKeyH->CreateSquare(VAO, VBO, EBO, bkh, *CameraShader);
    bKeyH->setPosFromFile(bkh);

    //black key mid 
    bKeyM = new ComponentGraphics(VAO, VBO, EBO);
    ComponentSprite* bKeyMS = new ComponentSprite();
    sprintf_s(pathName, _countof(pathName), "./TextFiles/KeyData/BKeyMid.txt");
    bkh = StreamOpen(pathName);
    bKeyMS->ReadSprite(bkh);
    bKeyM->SetSprite(bKeyMS);
    bKeyM->SetIndices(bKeyMS->GetIndecies());
    bKeyM->SetVertices(bKeyMS->GetVertices());
    bKeyM->CreateSquare(VAO, VBO, EBO, bkh, *CameraShader);
    bKeyM->setPosFromFile(bkh);
    

    //black key bottom 
    bKeyB = new ComponentGraphics(VAO, VBO, EBO);
    ComponentSprite* bKeyBS = new ComponentSprite();
    sprintf_s(pathName, _countof(pathName), "./TextFiles/KeyData/BKeyEnd.txt");
    bkh = StreamOpen(pathName);
    bKeyBS->ReadSprite(bkh);
    bKeyB->SetSprite(bKeyBS);
    bKeyB->SetIndices(bKeyBS->GetIndecies());
    bKeyB->SetVertices(bKeyBS->GetVertices());
    bKeyB->CreateSquare(VAO, VBO, EBO, bkh, *CameraShader);
    bKeyB->setPosFromFile(bkh);

    soundHolder = GetGlobalSoundHolder();

    ImgManager = new ImageManager(CameraShader, window, SoundEffectDoc,soundHolder);
    GameObjectManagerSetImgManager(ImgManager);


    MenuBackgroundAnimated = new GameObject();
    
    glm::vec3 MenuS((*AnimatedMenuDoc)["ScaleX"].GetFloat(), (*AnimatedMenuDoc)["ScaleY"].GetFloat(), 1);
    glm::vec3 MenuPosition((*AnimatedMenuDoc)["PositionX"].GetFloat(), (*AnimatedMenuDoc)["PositionY"].GetFloat(), 1);
    MenuBackgroundAnimated->SetName("MenuBackAnimated");
    MenuBackgroundAnimated->GetTransform()->SetScale(&MenuS);
    MenuBackgroundAnimated->GetTransform()->SetPosition(&MenuPosition);
     
    MenuBackgroundAnimated->SetDrawInUISpace(true);//draws this object in screen space instead of world space
    MenuBackgroundAnimated->CreateAndAddAnimation((*AnimatedMenuDoc)["AnimationFile"].GetString(), (*AnimatedMenuDoc)["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//0 = idle
    MenuBackgroundAnimated->SetCurrentAnimation(0);
    MenuBackgroundAnimated->GetAnimation()->Play();
    MenuBackgroundAnimated->SetVisible(false);

    WinTrans = new GameObject();

    glm::vec3 Ts((*WinTransDoc)["ScaleX"].GetFloat(), (*WinTransDoc)["ScaleY"].GetFloat(), 1);
    glm::vec3 Tp((*WinTransDoc)["PositionX"].GetFloat(), (*WinTransDoc)["PositionY"].GetFloat(), 1);
    WinTrans->SetName("WinTransition");
    WinTrans->GetTransform()->SetScale(&Ts);
    WinTrans->GetTransform()->SetPosition(&Tp);

    WinTrans->SetDrawInUISpace(true);//draws this object in screen space instead of world space
    WinTrans->CreateAndAddAnimation((*WinTransDoc)["AnimationFile"].GetString(), (*WinTransDoc)["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//0 = idle
    WinTrans->SetCurrentAnimation(0);
  //  WinTrans->GetAnimation()->Play();
    WinTrans->SetVisible(false);

    //Pause Screen Init
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0, 0), "./TextFiles/PauseMenuData/PauseBg.json", "PauseBG", false, false);

	//Controls Screen Init
	ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0, 0), "./TextFiles/ControlsMenuData/ControlsBg.json", "ControlsBG", false, false);

    //hover buttons
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.0, .25)* AffineScaleMatrix(.30, .10), "./TextFiles/PauseMenuData/MainMenuButton.json", "MainMenuButton", true, false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.0, .05)* AffineScaleMatrix(.30, .10), "./TextFiles/PauseMenuData/ResumeButton.json", "ResumeButton", true, false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.0, -.15)* AffineScaleMatrix(.3, .1), "./TextFiles/PauseMenuData/ControlsButton.json", "ControlsButton", true, false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.0, -.35)* AffineScaleMatrix(.3, .1), "./TextFiles/PauseMenuData/OptionsButton.json", "OptionsButton", true, false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.0, -.55)* AffineScaleMatrix(.3, .1), "./TextFiles/PauseMenuData/QuitButton.json", "QuitButton", true, false);

    //board
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0.0, -0.3)* AffineScaleMatrix(.02,.02), "./TextFiles/PauseMenuData/Board.json", "Board", false, false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0.0, 0.3)* AffineScaleMatrix(.15,.1), "./TextFiles/PauseMenuData/SoundTitle.json", "Sound", false, false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.15, -0.3)* AffineScaleMatrix(.3,.10), "./TextFiles/PauseMenuData/FSTitle.json", "FullScreen", false, false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.15, -0.50)* AffineScaleMatrix(.3,.10), "./TextFiles/PauseMenuData/WTitle.json", "Windowed", false, false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0.0, .50)* AffineScaleMatrix(.5, 1)* AffineScaleMatrix(1, .28), "./TextFiles/PauseMenuData/Name.json", "Name", true, false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0.0, .50)* AffineScaleMatrix(.5, 1)* AffineScaleMatrix(1, .28), "./TextFiles/PauseMenuData/ConfirmQuit.json", "QuitConfirm", true, false);
    ImgManager->SetImageVisibleInSystem("QuitConfirm", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0.0, .50)* AffineScaleMatrix(.5, 1)* AffineScaleMatrix(1, .28), "./TextFiles/PauseMenuData/ConfirmMM.json", "MMConfirm", true, false);
    ImgManager->SetImageVisibleInSystem("MMConfirm", false);
    //yes and no
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(.20, -0.50)* AffineScaleMatrix(.30,.10), "./TextFiles/PauseMenuData/YesButton.json", "YesButton", true, false);
    ImgManager->SetImageVisibleInSystem("YesButton", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(.20, -0.50)* AffineScaleMatrix(.30, .10), "./TextFiles/PauseMenuData/YesButton.json", "YesButtonM", true, false);
    ImgManager->SetImageVisibleInSystem("YesButtonM", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.20, -.50)* AffineScaleMatrix(.30, .10), "./TextFiles/PauseMenuData/NoButton.json", "NoButton", true, false);
    ImgManager->SetImageVisibleInSystem("NoButton", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(.20, -0.50)* AffineScaleMatrix(.30, .10), "./TextFiles/PauseMenuData/YesHoverButton.json", "YesHoverButton", true, false);
    ImgManager->SetImageVisibleInSystem("YesHoverButton", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.20, -.50)* AffineScaleMatrix(.30, .10), "./TextFiles/PauseMenuData/NoHoverButton.json", "NoHoverButton", true, false);
    ImgManager->SetImageVisibleInSystem("NoHoverButton", false);

    //on and off
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.25, 0.15)* AffineScaleMatrix(.15,.10), "./TextFiles/PauseMenuData/OnButton.json", "OnButton", true, false);
    ImgManager->SetImageVisibleInSystem("OnButton", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.25, -.05)* AffineScaleMatrix(.15, .10), "./TextFiles/PauseMenuData/OffButton.json", "OffButton", true, false);
    ImgManager->SetImageVisibleInSystem("OffButton", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0.2, -0.30)* AffineScaleMatrix(.05, .05), "./TextFiles/PauseMenuData/FullscreenButton.json", "FullscreenButton", true, false);
    ImgManager->SetImageVisibleInSystem("FullscreenButton", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0, -.20)* AffineScaleMatrix(.15, .10), "./TextFiles/PauseMenuData/FullscreenHoverButton.json", "FullscreenButtonHover", true, false);
    ImgManager->SetImageVisibleInSystem("FullscreenButtonHover", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0.2, -.50)* AffineScaleMatrix(.05, .05), "./TextFiles/PauseMenuData/WindowedButton.json", "WindowedButton", true, false);
    ImgManager->SetImageVisibleInSystem("WindowedButton", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0, -.60)* AffineScaleMatrix(.15, .10), "./TextFiles/PauseMenuData/WindowedHoverButton.json", "WindowedButtonHover", true, false);
    ImgManager->SetImageVisibleInSystem("WindowedButtonHover", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.03, -.7)* AffineScaleMatrix(.20, .10), "./TextFiles/PauseMenuData/BackButton.json", "BackButton", true, false);
    ImgManager->SetImageVisibleInSystem("BackButton", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.25, -.05)* AffineScaleMatrix(.15, .10), "./TextFiles/PauseMenuData/BackButtonHover.json", "BackHoverButton", true, false);
    ImgManager->SetImageVisibleInSystem("BackHoverButton", false);

    //buttons for on off
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0.2, .15)* AffineScaleMatrix(.05, .05), "./TextFiles/PauseMenuData/OnSquareButton.json", "OnSquareButton", true, false);
    ImgManager->SetImageVisibleInSystem("OnSquareButton", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0.20, -.05)* AffineScaleMatrix(.05, .05), "./TextFiles/PauseMenuData/OffSquareButton.json", "OffSquareButton", true, false);
    ImgManager->SetImageVisibleInSystem("OffSquareButton", false);

    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(.20, .15)* AffineScaleMatrix(.05, .05), "./TextFiles/PauseMenuData/OnHoverButton.json", "OnHoverButton", true, false);
    ImgManager->SetImageVisibleInSystem("OnHoverButton", false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0.20, -.05)* AffineScaleMatrix(.05, .05), "./TextFiles/PauseMenuData/OffHoverButton.json", "OffHoverButton", true, false);
    ImgManager->SetImageVisibleInSystem("OffHoverButton", false);

    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(0.0, .60)* AffineScaleMatrix(.3, .8)* AffineScaleMatrix(1, .28), "./TextFiles/PauseMenuData/OptionsTitle.json", "OptionsTitle", true, false);
    ImgManager->SetImageVisibleInSystem("OptionsTitle", false);


    //buttons
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.0, -.10)* AffineScaleMatrix(.3, .1), "./TextFiles/PauseMenuData/ResumeHoverButton.json", "ResumeHoverButton", true, false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.0, -.30)* AffineScaleMatrix(.3, 1), "./TextFiles/PauseMenuData/ControlsHoverButton.json", "ControlsHoverButton", true, false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.0, -.50)* AffineScaleMatrix(.3, 1), "./TextFiles/PauseMenuData/OptionsHoverButton.json", "OptionsHoverButton", true, false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.0, -.70)* AffineScaleMatrix(.3, 1), "./TextFiles/PauseMenuData/QuitHoverButton.json", "QuitHoverButton", true, false);
    ImgManager->AddImageToDrawingSystem(false, AffineTranslationMatrix(-0.0, .10)* AffineScaleMatrix(.3, .1), "./TextFiles/PauseMenuData/MainMenuHoverButton.json", "MainMenuHoverButton", true, false);
    ImgManager->SetImageVisibleInSystem("MainMenuHoverButton", false);
    ImgManager->SetImageVisibleInSystem("ControlsHoverButton", false);
    ImgManager->SetImageVisibleInSystem("OptionsHoverButton", false);
    ImgManager->SetImageVisibleInSystem("ResumeHoverButton", false);
    ImgManager->SetImageVisibleInSystem("QuitHoverButton", false);

    
    ImgManager->SetButtonClick("MainMenuButton", GoToMainMenu);
    ImgManager->SetButtonClick("ResumeButton", GoToResume);
    ImgManager->SetButtonClick("QuitButton", GoToQuit);
    ImgManager->SetButtonClick("ControlsButton", GoToControls);
    ImgManager->SetButtonClick("OptionsButton", GoToOptions);
    ImgManager->SetButtonClick("YesButton", GoToExit);
    ImgManager->SetButtonClick("YesButtonM", GoToMM);
    ImgManager->SetButtonClick("NoButton", GoToPause);
    ImgManager->SetButtonClick("BackButton", GoToPause);
    ImgManager->SetButtonClick("OnSquareButton", GoToMusicOn);
    ImgManager->SetButtonClick("OffSquareButton", GoToMusicOff);
    ImgManager->SetButtonClick("FullscreenButton", FullScreenClicked);
    ImgManager->SetButtonClick("WindowedButton", WindowedClicked);



    ImgManager->SetButtonHover("MainMenuButton", MainMenuButtonHover);
    ImgManager->SetButtonHover("ResumeButton", ResumeButtonHover);
    ImgManager->SetButtonHover("ControlsButton", ControlsButtonHover);
    ImgManager->SetButtonHover("OptionsButton", OptionsButtonHover);
    ImgManager->SetButtonHover("QuitButton", QuitButtonHover);
    ImgManager->SetButtonHover("YesButton", YesButtonHover);
    ImgManager->SetButtonHover("YesButtonM", YesButtonHover);
    ImgManager->SetButtonHover("NoButton", NoButtonHover);
    ImgManager->SetButtonHover("FullscreenButton", OnFullScreenButtonHover);
    ImgManager->SetButtonHover("WindowedButton", OnWindowedButtonHover);
    ImgManager->SetButtonHover("BackButton", BackButtonHover);
    ImgManager->SetButtonHover("OnSquareButton", OnButtonHover);
    ImgManager->SetButtonHover("OffSquareButton", OffButtonHover);


    ImgManager->SetButtonLeave("MainMenuButton", MainMenuButtonLeave);
    ImgManager->SetButtonLeave("ControlsButton", ControlsButtonLeave);
    ImgManager->SetButtonLeave("OptionsButton", OptionsButtonLeave);
    ImgManager->SetButtonLeave("QuitButton", QuitButtonLeave);
    ImgManager->SetButtonLeave("ResumeButton", ResumeButtonLeave);
    ImgManager->SetButtonLeave("YesButton", YesButtonLeave);
    ImgManager->SetButtonLeave("YesButtonM", YesButtonLeave);
    ImgManager->SetButtonLeave("NoButton", NoButtonLeave);
    ImgManager->SetButtonLeave("BackButton", BackButtonLeave);
    ImgManager->SetButtonLeave("OnSquareButton", OnButtonLeave);
    ImgManager->SetButtonLeave("OffSquareButton", OffButtonLeave);
    ImgManager->SetButtonLeave("FullscreenButton", OnFullScreenButtonLeave);
    ImgManager->SetButtonLeave("WindowedButton", OnWindowedButtonLeave);

    //ImgManager->SetButtonHover("YesButton", PauseButtonHover);
    //ImgManager->SetButtonHover("NoButton", PauseButtonHover);

    //ImgManager->AddImageToDrawingSystem(false, AffineScaleMatrix(1, 1) * AffineTranslationMatrix(0, 0), "./TextFiles/button/buttonspriteJson.json", "Duplicate Resume", true, false);
    //key init!!
    Key = new GameObject();
    Key->SetName("Key");
    KeyBehavior = new BehaviorKey(SoundEffectDoc);

    Key->SetBehavior(KeyBehavior);
    Key->GetBehavior()->onInit();
    Key->GetGraphic()->CreateSquareFromFileName(VAO, VBO, EBO, KeyBehavior->GetFilename(), *CameraShader);

    //mid of key init
    KeyMid = new GameObject();
    KeyMid->SetName("KeyMiddle");
    KeyMidBehavior = new BehaviorKeyMid(SoundEffectDoc);

    KeyMid->SetBehavior(KeyMidBehavior);
    KeyMid->GetBehavior()->onInit();
    KeyMid->GetGraphic()->CreateSquareFromFileName(VAO, VBO, EBO, KeyMidBehavior->GetFilename(), *CameraShader);

    //mid of key init
    KeyEnd = new GameObject();
    KeyEnd->SetName("KeyEnd");
    KeyEndBehavior = new BehaviorKeyEnd(SoundEffectDoc);

    KeyEnd->SetBehavior(KeyEndBehavior);
    KeyEnd->GetBehavior()->onInit();
    KeyEnd->GetGraphic()->CreateSquareFromFileName(VAO, VBO, EBO, KeyEndBehavior->GetFilename(), *CameraShader);

    //key particle init

    GameObject* KeyEffect = new GameObject();
    glm::vec3 EffectSize((*KeyEffectDoc)["VFX"]["EffectSizeX"].GetFloat(), (*KeyEffectDoc)["VFX"]["EffectSizeY"].GetFloat(), 1);
    KeyEffect->SetName("KeyEffect");
    KeyEffect->GetTransform()->SetScale(&EffectSize);
    KeyEffect->CreateAndAddAnimation((*KeyEffectDoc)["VFX"]["AnimationFile"].GetString(), (*KeyEffectDoc)["VFX"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//0 = idle
    KeyEffect->SetCurrentAnimation(0);
    KeyEffect->SetParent(Key);
    KeyEffect->GetAnimation()->Play();

    //key head effect
    GameObject* KeyHeadEffect = new GameObject();
    glm::vec3 EffectSizeH((*KeyEffectDoc)["VFX"]["EffectSizeX"].GetFloat(), (*KeyEffectDoc)["VFX"]["EffectSizeY"].GetFloat(), 1);
    KeyHeadEffect->SetName("KeyHeadEffect");
    KeyHeadEffect->GetTransform()->SetScale(&EffectSizeH);
    KeyHeadEffect->CreateAndAddAnimation((*KeyEffectDoc)["VFX"]["AnimationFile"].GetString(), (*KeyEffectDoc)["VFX"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//0 = idle
    KeyHeadEffect->SetCurrentAnimation(0);
    KeyHeadEffect->SetParent(KeyMid);
    KeyHeadEffect->GetAnimation()->Play();

    //key tail effect
    GameObject* KeyEndEffect = new GameObject();
    glm::vec3 EffectSizeB((*KeyEffectDoc)["VFX"]["EffectSizeX"].GetFloat(), (*KeyEffectDoc)["VFX"]["EffectSizeY"].GetFloat(), 1);
    KeyEndEffect->SetName("KeyEndEffect");
    KeyEndEffect->GetTransform()->SetScale(&EffectSizeB);
    KeyEndEffect->CreateAndAddAnimation((*KeyEffectDoc)["VFX"]["AnimationFile"].GetString(), (*KeyEffectDoc)["VFX"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//0 = idle
    KeyEndEffect->SetCurrentAnimation(0);
    KeyEndEffect->SetParent(KeyEnd);
    KeyEndEffect->GetAnimation()->Play();

   

    GameObjectManagerAdd(&ObjectManager, Key);
    GameObjectManagerAdd(&ObjectManager, KeyMid);
    GameObjectManagerAdd(&ObjectManager, KeyEnd);
    GameObjectManagerAdd(&ObjectManager, KeyEffect);
    GameObjectManagerAdd(&ObjectManager, KeyHeadEffect);
    GameObjectManagerAdd(&ObjectManager, KeyEndEffect);

    ////////////////////////// Initializing BunBun Information ///////////////////////////////////////
    TestGameObject = new GameObject();

    // attach behavior component to the player gameObject
    // this will also attach all other components to it
    PlayerBehavior = new BehaviorBunBun(ImgManager, CameraShader);
    EmmiterManager = new PhysicsEmmiterManager(&ObjectManager, ImgManager);
    //level must be loaded after the player behaviour gets initialized because it needs to be able to set the player's transform according to the "spawn tile"
    LevelLoadSys.Initialize(&ObjectManager, CameraShader);
    // !!! Audio codes must come after player behavior has been initialized !!!
    // Audio --------------- Initializes audio and loads sound from file---//
    char audio_path[FILENAME_MAX] = "";

    // audio played when pressed 'M'
    sprintf_s(audio_path, _countof(audio_path), "./Audio Text Files/death.txt");
    Stream deathSound = StreamOpen(audio_path);
    music = soundHolder->Load(deathSound, FMOD_DEFAULT);

    // audio for player landing
    sprintf_s(audio_path, _countof(audio_path), (*PlayerBehavior->getPlayerDoc())["Audio"]["Land"].GetString());
    Stream landingSound = StreamOpen(audio_path);
    landing = soundHolder->Load(landingSound, FMOD_DEFAULT);

    // audio for player walk
    sprintf_s(audio_path, _countof(audio_path), (*PlayerBehavior->getPlayerDoc())["Audio"]["Walk"].GetString());
    Stream bushesSound2 = StreamOpen(audio_path);
    walking = soundHolder->Load(bushesSound2, FMOD_DEFAULT);

    //taking damage sound effect
    sprintf_s(audio_path, _countof(audio_path), (*SoundEffectDoc)["BunBun"]["TakingDamage"].GetString());
    Stream takingDamageSound = StreamOpen(audio_path);
    takingDamage = soundHolder->Load(takingDamageSound, FMOD_DEFAULT);

    //taking damage sound effect
    sprintf_s(audio_path, _countof(audio_path), (*SoundEffectDoc)["BunBun"]["Death"].GetString());
    Stream diesSound = StreamOpen(audio_path);
    dies = soundHolder->Load(diesSound, FMOD_DEFAULT);

    //shooting sound effect
    sprintf_s(audio_path, _countof(audio_path), (*SoundEffectDoc)["Ice"]["ShootingIce"].GetString());
    Stream shootingIceSound = StreamOpen(audio_path);
    shootingIce = soundHolder->Load(shootingIceSound, FMOD_DEFAULT);

    //picking up key part sound effect
    sprintf_s(audio_path, _countof(audio_path), (*SoundEffectDoc)["Key"]["PickUp"].GetString());
    Stream keySound = StreamOpen(audio_path);
    pickingUpKey = soundHolder->Load(keySound, FMOD_DEFAULT);

    sprintf_s(audio_path, _countof(audio_path), (*SoundEffectDoc)["Key"]["PickUp"].GetString());
    Stream keySound1 = StreamOpen(audio_path);
    pickingUpKey1 = soundHolder->Load(keySound1, FMOD_LOOP_NORMAL);

    //door opening at end of level sound effect
    sprintf_s(audio_path, _countof(audio_path), (*SoundEffectDoc)["Door"]["Unlocking"].GetString());
    Stream doorOpeningSound = StreamOpen(audio_path);
    doorOpening = soundHolder->Load(doorOpeningSound, FMOD_DEFAULT);

    // looping background audio 
    sprintf_s(audio_path, _countof(audio_path), (*LevelDoc)["AudioBackground"].GetString());
    Stream backSound = StreamOpen(audio_path);
    backgroundMusic = soundHolder->Load(backSound, FMOD_LOOP_NORMAL);

    // Sets the background music one time when level loads
    soundHolder->Play(backgroundMusic, &channelTwo);

    //---------------------------------------------------------------------//

    // dash effect
    Stream dash_Stream;
    dash_graphics = new ComponentGraphics(VAO, VBO, EBO);
    dash_sprite = new ComponentSprite();
    sprintf_s(pathName, _countof(pathName), "./TextFiles/dash.txt");
    dash_Stream = StreamOpen(pathName);
    dash_sprite->ReadSprite(dash_Stream);
    dash_graphics->SetSprite(dash_sprite);
    dash_graphics->SetIndices(dash_sprite->GetIndecies());
    dash_graphics->SetVertices(dash_sprite->GetVertices());
    dash_graphics->CreateSquare(VAO, VBO, EBO, dash_Stream, *CameraShader);
    dash_graphics->setPosFromFile(dash_Stream);
    ////////////////////////////////////////////////////////////////////////////////////////////


    keyPSystem = new ComponentParticleSystem(CameraShader);
    keyPPattern.position = { -2.0f, -0.5f };
    keyPPattern.velocity = { 1.0f, 1.0f };
    keyPPattern.velocityRange = { 1.0f, 1.0f };
    keyPPattern.lifetime = 1.5f;
    keyPPattern.num_per = 20;

    // Testing Enemy

    //SpecialObject->SetAnimation(EnemyAnimation);

    GameObjectManagerAdd(&ObjectManager, TestGameObject);
    if (GoalObject)
    {
        GameObjectManagerAdd(&ObjectManager, GoalObject);
    }
    GameObjectManagerAdd(&ObjectManager, MenuBackgroundAnimated);
    GameObjectManagerAdd(&ObjectManager, WinTrans);

    camera1 = new ComponentCamera();

    glm::vec3 CamInitPos(-0.5, 0.0, 1);
    glm::vec3 CamInitSize(1920.0f / 600.0f, 1080.0f / 600.0f, 1);
    glm::vec3 CamBoundariesMin((*LevelDoc)["CamMinX"].GetFloat(), (*LevelDoc)["CamMinY"].GetFloat(), 1.0f);
    glm::vec3 CamBoundariesMax((*LevelDoc)["CamMaxX"].GetFloat(), (*LevelDoc)["CamMaxY"].GetFloat(), 1.0f);

    camera1->setCameraBoundariesMin(CamBoundariesMin);
    camera1->setCameraBoundariesMax(CamBoundariesMax);
    camera1->setCameraPosition(CamInitPos);
    camera1->setCameraSize(CamInitSize);

    //SpawnEnemy(glm::vec3 (0.5f,0.35f,1.0f), 't');
    //SpawnEnemy(glm::vec3(1.0f, 0.35f, 1.0f), 't');

    LivesDisplay = new PlayerLivesDisplay(VAO, VBO, EBO, CameraShader, window, camera1);
    //translation * scale
    //ImgManager->AddImageToDrawingSystem(false,  AffineTranslationMatrix(0, 0) * AffineScaleMatrix(0.5f, 0.5f),  "./TextFiles/FreezeImgSprite.json", "ice", true, false);
    
    //display pause button 
    PauseDisplay = new PauseButtonDisplay(VAO, VBO, EBO, CameraShader, window, camera1);
    GameObjectManagerSetRenderData(&ObjectManager, window, CameraShader, camera1);
    EmmiterManager->StartAllEmmiters();
    LevelActiveFlag = true;

    PlayingWinEffect = false;
    TimeSinceWin = 0;
}

// Update
void Level1Update(float dt)
{
    glm::vec3 CamCurrSize(GetWinWidthPix()/  600.0f, GetWinHeightPix() / 600.0f, 1);

    camera1->setCameraSize(CamCurrSize);

    if (musicOn == false) {
        soundHolder->Pause(true, channelOne);
        soundHolder->Pause(true, channelTwo);
        soundHolder->Pause(true, channelThree);
    }
    glm::vec3 current = camera1->getCameraPosition();
    glm::vec3 diff = current - previous;

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        ImageManager::SetClickHandled(false);
    }
    //double xCursor = 720;
    //double yCursor = 540;
    //glfwSetCursorPos(window, xCursor, yCursor);

    if (keyPSystemPlayback)
    {
        keyPSystem->Emit(keyPPattern);
        keyPSystemPlayback = false;
    }

    // input
    checkInput(window, dt);
    if (pause == false)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        UpdateBehaviorsOnAllGameObjects(&ObjectManager, dt);
        UpdateAnimationsOnAllGameObjects(&ObjectManager, dt);
        EmmiterManager->UpdateAllEmmiters(dt);
        GameObjectManagerClearDestroyedObjects(&ObjectManager);
    }
    // render
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (PlayingWinEffect)
    {
        glm::vec3 stop = glm::vec3(0);
        PlayerBehavior->getParent()->GetPhysics()->SetVelocity(&stop);

        if (TimeSinceWin >= WinAnimationDuration)
        {
            GameStateManagerSetNextState(GameStates::GsWin);
        }
        TimeSinceWin += dt;
    }
    if (ShowGraphics)
    {
        //myBackground->UpdateWithTransformation(dt, window, *CameraShader, camera1, ConvertTo4x4Affine(AffineScaleMatrix(2.0f, 2.0f) * AffineTranslationMatrix(0.0, 0.5)));
        myBackground->UpdateBackground(window, *CameraShader, camera1, diff);
        myParallax1->UpdateBackground(window, *CameraShader, camera1, diff);
        myParallax2->UpdateBackground(window, *CameraShader, camera1, diff);
        myParallax3->UpdateBackground(window, *CameraShader, camera1, diff);

        bKeyH->UpdateGraphics(dt, window, *CameraShader, NULL, ConvertTo4x4Affine(AffineTranslationMatrix(0.85, 0.85) * AffineScaleMatrix(0.05, 0.1)), "NoCam");
        bKeyM->UpdateGraphics(dt, window, *CameraShader, NULL, ConvertTo4x4Affine(AffineTranslationMatrix(0.85, 0.72) * AffineScaleMatrix(0.05, 0.1)), "NoCam");
        bKeyB->UpdateGraphics(dt, window, *CameraShader, NULL, ConvertTo4x4Affine(AffineTranslationMatrix(0.85, .61) * AffineScaleMatrix(0.05, 0.1)), "NoCam");

        if (KeyBehavior->GetKeyFound())
        {
            Key->GetGraphic()->UpdateGraphics(dt, window, *CameraShader, NULL, ConvertTo4x4Affine(AffineTranslationMatrix(0.85, 0.85) * AffineScaleMatrix(0.05, 0.1)), "NoCam");
        }
        if (KeyMidBehavior->GetKeyFound())
        {
            KeyMid->GetGraphic()->UpdateGraphics(dt, window, *CameraShader, NULL, ConvertTo4x4Affine(AffineTranslationMatrix(0.85, 0.72) * AffineScaleMatrix(0.05, 0.1)), "NoCam");
        }
        if (KeyEndBehavior->GetKeyFound())
        {
            KeyEnd->GetGraphic()->UpdateGraphics(dt, window, *CameraShader, NULL, ConvertTo4x4Affine(AffineTranslationMatrix(0.85, .61) * AffineScaleMatrix(0.05, 0.1)), "NoCam");
        }
        
        // imGui
        GuiUpdate(window, GUIToggle, &ObjectManager);

        keyPSystem->Update(dt);
        keyPSystem->Render(dt, window, *CameraShader, camera1, particleScaleLevel1);
        //keyPSystem->Render(dt, window, *CameraShader, camera1);
        GameObjectManagerSpriteDraw(&ObjectManager);
    }
    //keeps audio unpaused
    //soundHolder->Pause(false, channelOne);
    //soundHolder->Pause(false, channelTwo);
    //soundHolder->Pause(false, channelThree);

    // dash effect
    /*if (PlayerBehavior->isDashing)
    {
        // player is facing right
        glm::vec3 dashPos(*(TestGameObject->GetTransform()->GetPosition()));
        if (TestGameObject->GetTransform()->GetScale()->x > 0.0f)
        {
            dash_graphics->UpdateGraphics(dt, window, *CameraShader, camera1, ConvertTo4x4Affine(AffineTranslationMatrix(dashPos.x - 0.1f, dashPos.y) * AffineScaleMatrix(1.1f, 1.5f)), "Transform");
        }
        else
        {
            dash_graphics->UpdateGraphics(dt, window, *CameraShader, camera1, ConvertTo4x4Affine(AffineTranslationMatrix(dashPos.x + 0.1f, dashPos.y) * AffineScaleMatrix(-1.1f, 1.5f)), "Transform");
        }
    }*/

    if (pause == true)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        MenuBackgroundAnimated->SetVisible(true);
        MenuBackgroundAnimated->GetAnimation()->Update(dt);
        //pause the audio
        soundHolder->Pause(true, channelOne);
        soundHolder->Pause(true, channelTwo);
        soundHolder->Pause(true, channelThree);
        soundHolder->Pause(true, channelThree);

        if (quitTrigger == false)
        {

            //make a black background
            ImgManager->DrawImage(camera1, dt,"PauseBG");
            GameObjectManagerSpriteDrawSingleObject(MenuBackgroundAnimated, &ObjectManager);
            ImgManager->DrawImagesInSystem(camera1, dt);
            ImgManager->CheckUserClick(camera1);
            glm::vec3 camPosition = camera1->getCameraPosition();

            //handles all the buttons, it seems
               if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !ImageManager::IsClickHandled()) 
                {
                    ImageManager::SetClickHandled(true);
                }
        }

        if (quitTrigger == true)
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            ImgManager->SetImageVisibleInSystem("YesButton", true);
            ImgManager->SetImageVisibleInSystem("NoButton", true);
            ImgManager->SetImageVisibleInSystem("MainMenuButton", false);
            ImgManager->SetImageVisibleInSystem("ResumeButton", false);
            ImgManager->SetImageVisibleInSystem("ControlsButton", false);
            ImgManager->SetImageVisibleInSystem("OptionsButton", false);
            ImgManager->SetImageVisibleInSystem("QuitButton", false);
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !ImageManager::IsClickHandled())
                {
                    ImageManager::SetClickHandled(true);
                    //quit game
                    GameStateManagerSetNextState(GameStates::GsQuit);
                }

 
            //if player click no, go back to options menu
            if ((float)xpos <= 1500.0f &&
                (float)xpos >= 1200.0f &&
                (float)ypos <= 1020.0f &&
                (float)ypos >= 900.0f)
            {
              if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !ImageManager::IsClickHandled())
                {
                    ImageManager::SetClickHandled(true);
                    quitTrigger = false;
                }
            }
        }
    }
    else
    {
        MenuBackgroundAnimated->SetVisible(false);
    }

    if (ShowDebugDraw)
    {
        DebugDrawSys.DebugDrawAllGameObjects(&ObjectManager, camera1);
        if (ShowRedRect)
        {
            DebugDrawSys.DrawRectColor(RedRectTran, camera1, 1, 0, 0);
            ShowRedRect = false;
        }
    }

    if (pause == false)
    {
        PhySystem.Update(&ObjectManager, dt);//fake value for dt
    }

    camera1->UpdateCamera(window, *CameraShader, *(TestGameObject->GetTransform()->GetPosition()));

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    if (!PlayingWinEffect) {
        if (pause == false) {
            LivesDisplay->DisplayHealth(dt, PlayerBehavior->playerLives);
        }
    }
    if (GodMode)
    {
        DebugDrawSys.DebugDrawGameObject(TestGameObject, camera1);
    }

    //pause button display 
    if (!PlayingWinEffect) {
        if (pause == false) {
            PauseDisplay->DisplayPause(dt);
        }
    }
    if (PauseDisplay->CheckPaused(xpos, ypos, window) == true || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        pause = true;
    }

    if(glfwGetWindowAttrib(window, GLFW_ICONIFIED))
    {
        pause = true;
    }
    //GetPlayer()->GetGraphic()->UpdateWithTransformation(dt, window, *CameraShader, camera1, ConvertTo4x4Affine(AffineTranslationMatrix(0,0)* AffineScaleMatrix(0.1,0.1)));
//    ImgManager->DrawImages(camera1, dt);
    glfwSwapBuffers(window);
    glfwPollEvents();

    previous = current;

    KillPlaneCheck();
    PlayerBehavior->playerTimeSinceLastHurt += dt;

    if (PlayerBehavior->playerDead)
    {
       // LoadingImg->UpdateGraphics(dt, window, *CameraShader, camera1, AffineScaleMatrix(3.0f, 3.0f), "Transform");
    }

    TimeSinceLastShot += dt;
   
}

// Shutdown
void Level1Shutdown()
{
    GuiShutdown();
    //glfwTerminate
    soundHolder->Free(&music);
    soundHolder->Free(&backgroundMusic);
    soundHolder->Free(&walking);
    soundHolder->Free(&landing);
    soundHolder->Free(&takingDamage);
    soundHolder->Free(&dies);
    soundHolder->Free(&shootingIce);
    soundHolder->Free(&pickingUpKey);
    soundHolder->Free(&pickingUpKey1);
    soundHolder->Free(&doorOpening);
}

// Unload
void Level1Unload()
{
    LevelActiveFlag = false;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    CameraShader->deleteShader();
    //delete(TestGameObject);
    delete(CameraShader);

    // Test Enemy

    delete(LevelDoc);
    delete(EnemyDoc);
    delete(flyingEnemyDoc);
    delete(BigEnemyDoc);
    delete(BulletDoc);
    delete(AnimatedMenuDoc);
    delete(SoundEffectDoc);
    delete(RotatingPlatformDoc);
    delete(KeyEffectDoc);
    delete(WinTransDoc);
    KeyBehavior->Shutdown();
    KeyMidBehavior->Shutdown();
    delete(LivesDisplay);
    delete(PauseDisplay);
    GameObjectShutdown(&ObjectManager);
    PhySystem.Shutdown();
    LevelLoadSys.UnloadLevelData();

    delete(myBackground);
    delete(myParallax1);
    delete(myParallax2);
    delete(myParallax3);
    
   // if (soundHolder)
    //{
       // delete(soundHolder);
        //soundHolder = 0;
    //}
    

    delete(Background);
    delete(Parallax1);
    delete(Parallax2);
    delete(Parallax3);
    delete(MainMenuButton);
    delete(ResumeButton);
    delete(QuitButton);
    delete (YesButton);
    delete (YesHover);
    delete (NoButton);
    delete(NoHover);
    delete(dash_graphics);
    delete(dash_sprite);
    delete(keyPSystem);
    delete(camera1);

    delete(ImgManager);
    delete(EmmiterManager);
}

void checkInput(GLFWwindow* window, float dt)
{
    DebugDrawSys.GS_Switcher(window);
    TraceSetActiveChannel("Input");

	/*
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        pause = true;
    }*/

    // Makes sound when M key is pressed
	/*
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        TraceMessage("Input", "m pressed down");
        soundHolder->Play(music, &channelOne);
    }*/

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        ShowGraphics = true;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        ShowGraphics = false;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        GUIToggle = false;
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        GUIToggle = true;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        ShowDebugDraw = true;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        ShowDebugDraw = false;
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    {
        if (!GodMode)
        {
            GodMode = true;
            PlayerGravity = *(GetPlayer()->GetPhysics()->GetAcceleration());
            glm::vec3 Zero(0, 0, 0);
            GetPlayer()->GetPhysics()->SetAcceleration(&Zero);
            GetPlayer()->GetPhysics()->SetVelocity(&Zero);
            PhySystem.SetNoClipMode(true);
            PlayerBehavior->PlayerNoClip = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        if (GodMode)
        {
            GodMode = false;
            GetPlayer()->GetPhysics()->SetAcceleration(&PlayerGravity);
            PhySystem.SetNoClipMode(false);
            PlayerBehavior->PlayerNoClip = false;
        }

    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        FreezeAll(&ObjectManager);     
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {

        UnFreezeAll(&ObjectManager);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        GameStateManagerSetNextState(GameStates::GsWin);
    }
    
    float ZoomFactor = 1.01;
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)//zoom in
    {
        camera1->setCameraSize(camera1->getCameraSize() / ZoomFactor);
        //soundHolder->Pause(true, channelOne); //pauses audio
        //soundHolder->Pause(true, channelTwo);
        //soundHolder->Pause(true, channelThree);
    }

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)//zoom out
    {
          camera1->setCameraSize(camera1->getCameraSize() * ZoomFactor);
        //soundHolder->Pause(false, channelOne); //unpauses audio
       // soundHolder->Pause(false, channelTwo);
        //soundHolder->Pause(false, channelThree);
    }    
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        if ((TimeSinceLastShot >= (*BulletDoc)["Properties"]["ShotInterval"].GetFloat()))
        {
            if (PlayerBehavior->canJump == false)//the player is in the air
            {
                TestGameObject->SetCurrentAnimation(6);
            }
            else
            {
                if (!(glfwGetKey(GetWindow(), GLFW_KEY_A) == GLFW_PRESS) && !(glfwGetKey(GetWindow(), GLFW_KEY_D) == GLFW_PRESS))
                {
                    if (glfwGetKey(GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
                    {
                        TestGameObject->SetCurrentAnimation(7);//idle up shoot
                    }
                    else if (glfwGetKey(GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
                    {
                        TestGameObject->SetCurrentAnimation(8);//idle down shoot
                    }
                    else
                    {
                        TestGameObject->SetCurrentAnimation(5);//idle normal shoot
                    }
                }
                else if (PlayerBehavior->isDashing == false)//player walking
                {
                    if (glfwGetKey(GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
                    {
                        TestGameObject->SetCurrentAnimation(13);
                    }
                    else if (glfwGetKey(GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
                    {
                        TestGameObject->SetCurrentAnimation(14);
                    }
                    else
                    {
                        TestGameObject->SetCurrentAnimation(12);
                    }
                }
                else if (PlayerBehavior->isDashing == true)//player dashing
                {
                    if (glfwGetKey(GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
                    {
                        TestGameObject->SetCurrentAnimation(9);
                    }
                    else if (glfwGetKey(GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
                    {
                        TestGameObject->SetCurrentAnimation(10);
                    }
                    else
                    {
                        TestGameObject->SetCurrentAnimation(3);
                    }
                }
            }
            ShootBullet(dt);

        }

    }
}


void KillPlaneCheck()
{
    glm::vec3 TestObjectPosition(0, 0, 0);

    TestObjectPosition = *(TestGameObject->GetTransform()->GetPosition());
    if (TestObjectPosition.y < -2)
    {
        //soundHolder->Play(dies, &channelThree);
        GameStateManagerSetNextState(GameStates::GsLose);
    }
}


void SpawnSpecial(glm::vec3 SpawnPos, int SpawnType, rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>* Properties)
{
    //for enemies, rotating platforms, tiles that are bigger than 1x1...this is for anything on the special layer
    glm::vec3 Gravity(0, -2.65f, 0);
    glm::vec3 FlyingGravity(0, 0, 0);

    GameObject* SpecialObject = new GameObject();
    std::stringstream name;
    name << "Special ";
    name << specialCounter;
    ComponentPhysics* SpecialObjectPhy = new ComponentPhysics();

    if (SpawnType == 50 || SpawnType == 51 || SpawnType == 53 || SpawnType == 68 || SpawnType == 65 || SpawnType == 66)
    {
        name << " Enemy A ";

        ComponentTransform* SpecialObjectTransform = SpecialObject->GetTransform();
        ComponentCollider* SpecialObjectBox;
        BehaviorEnemy* EnemyBehaviour;
        ComponentFreeze* EnemFreeze;
        SpecialObject->SetName(name.str());

        if (SpawnType == 53 || SpawnType == 68)
        {
            SpecialObjectPhy->SetAcceleration(&Gravity);
            glm::vec3 EnemyStartScale((*flyingEnemyDoc)["Properties"]["EnemyScaleX"].GetFloat(), (*flyingEnemyDoc)["Properties"]["EnemyScaleY"].GetFloat(), 1);
            SpecialObjectTransform->SetScale(&EnemyStartScale);
            SpecialObjectBox = new ComponentCollider((*flyingEnemyDoc)["Properties"]["EnemyColliderScaleX"].GetFloat(), (*flyingEnemyDoc)["Properties"]["EnemyColliderScaleY"].GetFloat(), true, true, true, true);
            SpecialObject->SetCollider(SpecialObjectBox);

            EnemyBehaviour = new BehaviorEnemy(flyingEnemyDoc);
            EnemFreeze = new ComponentFreeze((*flyingEnemyDoc)["Properties"]["EnemyIceBlockScaleX"].GetFloat(), (*flyingEnemyDoc)["Properties"]["EnemyIceBlockScaleY"].GetFloat());

            //EnemyIdle
            SpecialObject->CreateAndAddAnimation((*flyingEnemyDoc)["Idle"]["AnimationFile"].GetString(), (*flyingEnemyDoc)["Idle"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//0 = fly
            //Enemy walk:
            SpecialObject->CreateAndAddAnimation((*flyingEnemyDoc)["Walk"]["AnimationFile"].GetString(), (*flyingEnemyDoc)["Walk"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//1 = idle
            //Enemy run:
            SpecialObject->CreateAndAddAnimation((*flyingEnemyDoc)["Run"]["AnimationFile"].GetString(), (*flyingEnemyDoc)["Run"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//2 = take-off

            EnemyBehaviour->SetType('e');
        }
        else
        {
            SpecialObjectPhy->SetAcceleration(&FlyingGravity);
            SpecialObjectBox = new ComponentCollider((*EnemyDoc)["Properties"]["EnemyColliderScaleX"].GetFloat(), (*EnemyDoc)["Properties"]["EnemyColliderScaleY"].GetFloat(), true, true, true, true);
            SpecialObject->SetCollider(SpecialObjectBox);
            EnemyBehaviour = new BehaviorEnemy(EnemyDoc);
            EnemFreeze = new ComponentFreeze((*EnemyDoc)["Properties"]["EnemyIceBlockScaleX"].GetFloat(), (*EnemyDoc)["Properties"]["EnemyIceBlockScaleY"].GetFloat());

            if (SpawnType == 50 || SpawnType == 65)
            {
                glm::vec3 EnemyStartScale((*EnemyDoc)["Properties"]["EnemyScaleX"].GetFloat(), (*EnemyDoc)["Properties"]["EnemyScaleY"].GetFloat(), 1);
                SpecialObjectTransform->SetScale(&EnemyStartScale);

                //EnemyIdle
                SpecialObject->CreateAndAddAnimation((*EnemyDoc)["Idle"]["AnimationFile"].GetString(), (*EnemyDoc)["Idle"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//0 = idle
                //Enemy walk:
                SpecialObject->CreateAndAddAnimation((*EnemyDoc)["Walk"]["AnimationFile"].GetString(), (*EnemyDoc)["Walk"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//1 = walk
                //Enemy run:
                SpecialObject->CreateAndAddAnimation((*EnemyDoc)["Run"]["AnimationFile"].GetString(), (*EnemyDoc)["Run"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//2 = run
                //Enemy attack:
                SpecialObject->CreateAndAddAnimation((*EnemyDoc)["Attack"]["AnimationFile"].GetString(), (*EnemyDoc)["Attack"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//3 = attack
            }
            else if (SpawnType == 51 || SpawnType == 66)
            {
                glm::vec3 EnemyStartScale((*BigEnemyDoc)["Properties"]["EnemyScaleX"].GetFloat(), (*BigEnemyDoc)["Properties"]["EnemyScaleY"].GetFloat(), 1);
                SpecialObjectTransform->SetScale(&EnemyStartScale);

                //EnemyIdle
                SpecialObject->CreateAndAddAnimation((*BigEnemyDoc)["Idle"]["AnimationFile"].GetString(), (*BigEnemyDoc)["Idle"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//0 = idle
                //Enemy walk:
                SpecialObject->CreateAndAddAnimation((*BigEnemyDoc)["Walk"]["AnimationFile"].GetString(), (*BigEnemyDoc)["Walk"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//1 = walk
                //Enemy run:
                SpecialObject->CreateAndAddAnimation((*BigEnemyDoc)["Run"]["AnimationFile"].GetString(), (*BigEnemyDoc)["Run"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//2 = run
                //Enemy attack:
                SpecialObject->CreateAndAddAnimation((*EnemyDoc)["Attack"]["AnimationFile"].GetString(), (*EnemyDoc)["Attack"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//3 = attack
            }
            if (SpawnType == 50)
                EnemyBehaviour->SetType('c');

            else if (SpawnType == 51)
                EnemyBehaviour->SetType('d');
        }

        SpecialObjectBox->SetParent(SpecialObject);
        SpecialObjectTransform->SetPosition(&SpawnPos);
        SpecialObject->SetPhysics(SpecialObjectPhy);
        SpecialObjectPhy->SetAcceleration(&Gravity);
        SpecialObject->SetBehavior(EnemyBehaviour);
        SpecialObject->SetFreeze(EnemFreeze);
        ComponentOverlaySprites* OverlaySprites = new ComponentOverlaySprites();
        SpecialObject->SetOverlaySprites(OverlaySprites);
        SpecialObject->SetCurrentAnimation(1);

        GameObjectManagerAdd(&ObjectManager, SpecialObject);

        bool SpawnAsFrozen = (*Properties)[1]["value"].GetBool();
        if (SpawnAsFrozen)
        {
            FreezeObject(SpecialObject);
        }

    }
    
    else if (SpawnType == 52 || SpawnType == 67)
    {
        name << " Enemy B ";

        // Ash's enemy
        SpecialObject->SetName(name.str());

        SpecialObjectPhy->SetAcceleration(&Gravity);
        ComponentTransform* SpecialObjectTransform = SpecialObject->GetTransform();
        if (SpawnType == 52)
        {
            glm::vec3 EnemyStartScale((*BigEnemyDoc)["Properties"]["EnemyScaleX"].GetFloat(), (*BigEnemyDoc)["Properties"]["EnemyScaleY"].GetFloat(), 1);
            SpecialObjectTransform->SetScale(&EnemyStartScale);
        }
        else if (SpawnType == 53)
        {
            glm::vec3 EnemyStartScale(.15, .15, 1);
            SpecialObjectTransform->SetScale(&EnemyStartScale);
        }
        //ComponentCollider* SpecialObjectBox = new ComponentCollider((*BigEnemyDoc)["Properties"]["EnemyColliderScaleX"].GetFloat(), (*BigEnemyDoc)["Properties"]["EnemyColliderScaleY"].GetFloat(), true, true, false);
        ComponentCollider* SpecialObjectBox = new ComponentCollider((*BigEnemyDoc)["Properties"]["EnemyColliderScaleX"].GetFloat(), (*BigEnemyDoc)["Properties"]["EnemyColliderScaleY"].GetFloat(), true, true, false, true);
        SpecialObject->SetCollider(SpecialObjectBox);
        SpecialObjectBox->SetParent(SpecialObject);
        SpecialObjectTransform->SetPosition(&SpawnPos);

        SpecialObject->SetPhysics(SpecialObjectPhy);
        SpecialObjectPhy->SetAcceleration(&Gravity);
        BehaviorBigEnemy* EnemyBehaviour = new BehaviorBigEnemy(BigEnemyDoc);
        SpecialObject->SetBehavior(EnemyBehaviour);

        if (SpawnType == 52 || SpawnType == 67)
        {
            EnemyBehaviour->SetType('e');
        }

        else if (SpawnType == 53 || SpawnType == 68)
        {
            EnemyBehaviour->SetType('f');
        }
        //EnemyIdle
        SpecialObject->CreateAndAddAnimation((*BigEnemyDoc)["Idle"]["AnimationFile"].GetString(), (*BigEnemyDoc)["Idle"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//0 = idle
        //Enemy walk:
        SpecialObject->CreateAndAddAnimation((*BigEnemyDoc)["Walk"]["AnimationFile"].GetString(), (*BigEnemyDoc)["Walk"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//1 = walk
        //Enemy run:
        SpecialObject->CreateAndAddAnimation((*BigEnemyDoc)["Run"]["AnimationFile"].GetString(), (*BigEnemyDoc)["Run"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//2 = run


        SpecialObject->SetCurrentAnimation(1);

        ComponentFreeze* EnemFreeze = new ComponentFreeze((*BigEnemyDoc)["Properties"]["EnemyIceBlockScaleX"].GetFloat(), (*BigEnemyDoc)["Properties"]["EnemyIceBlockScaleY"].GetFloat());
        SpecialObject->SetFreeze(EnemFreeze);
        ComponentOverlaySprites* OverlaySprites = new ComponentOverlaySprites();
        SpecialObject->SetOverlaySprites(OverlaySprites);

        GameObjectManagerAdd(&ObjectManager, SpecialObject);
        bool SpawnAsFrozen = (*Properties)[1]["value"].GetBool();
        if (SpawnAsFrozen)
        {
            FreezeObject(SpecialObject);
        }
    }
     else if (SpawnType == 62)
     {
        Key->GetTransform()->SetPosition(&SpawnPos);
     }
      else if (SpawnType == 74)
     {
        KeyMid->GetTransform()->SetPosition(&SpawnPos);
     }
      else if (SpawnType == 75)
     {
     KeyEnd->GetTransform()->SetPosition(&SpawnPos);
     }
     else if (SpawnType == 63)
     {
     TestGameObject->GetTransform()->SetPosition(&SpawnPos);
     //TestGameObject->EmmitLight(0.4, 1);
    
     }
    else if (Properties != 0 && strcmp((*Properties)[0]["value"].GetString(), "RP") == 0)//rotating platform
    {
        float StartAngle = (*Properties)[1]["value"].GetFloat();
        float Length = (*Properties)[2]["value"].GetFloat();
        float SpinSpeed = (*Properties)[3]["value"].GetFloat();
        //this is for spawning rotating platforms
        name << " Rotating Platform";
        SpecialObject->SetName(name.str());

        SpecialObjectPhy->SetRotationalVelocity(SpinSpeed);
        ComponentTransform* RotatingPlatformTransform = SpecialObject->GetTransform();
        glm::vec3 PlatformScale(Length, (*RotatingPlatformDoc)["Thickness"].GetFloat(), 1);
        ComponentCollider* NonAxisAlignedBox = new ComponentCollider(
            (*RotatingPlatformDoc)["Rotational Inertia"].GetFloat(),
            true,
            (*RotatingPlatformDoc)["ColliderX"].GetFloat(),
            (*RotatingPlatformDoc)["ColliderY"].GetFloat());
        SpecialObject->SetCollider(NonAxisAlignedBox);
        NonAxisAlignedBox->SetParent(SpecialObject);
        RotatingPlatformTransform->SetPosition(&SpawnPos);
        RotatingPlatformTransform->SetScale(&PlatformScale);
        SpecialObject->SetPhysics(SpecialObjectPhy);
        SpecialObject->GetTransform()->SetRotation(StartAngle);
        ImageData* Data = ImgManager->GetImageFromDrawingSystem("RotatingPlatImg");
        if (!Data)
        {
            Data = ImgManager->AddImageToDrawingSystem(true, "./TextFiles/rotatingPlatSprite.json", "RotatingPlatImg", false, false);
            

        }

        SpecialObject->SetGraphic(Data->Graphic);

        GameObjectManagerAdd(&ObjectManager, SpecialObject);

    }
    else if (Properties != 0 && strcmp((*Properties)[0]["value"].GetString(), "Multitile") == 0)//multi tile object- props that are bigger than a single tile
    {
        name << " " << "Multitile";
        
        ComponentTransform* Transform = SpecialObject->GetTransform();
        float TilesWidth = (*Properties)[1]["value"].GetFloat();
        float TilesHeight = (*Properties)[2]["value"].GetFloat();
        float TileSize = LevelLoadSys.GetTileSize();
        vec3 MultileScale(TileSize * TilesWidth, TileSize  * TilesHeight, 1);
        vec3 TilePosOffset(TileSize* (TilesWidth - 1), TileSize* (TilesHeight - 1), 1);
        vec3 SpawnPlace = SpawnPos +TilePosOffset;
        Transform->SetPosition(&SpawnPlace);
        Transform->SetScale(&MultileScale);
        LevelLoadSys.AssignTileSprite(SpawnType, SpecialObject);
        GameObjectManagerAdd(&ObjectManager, SpecialObject);

        if (SpawnType == 76)
        {
            vec3 TilePosOffset(0, -0.025, 1); //move it down so it touches the floor
            vec3 SpawnPlaceMovedDown = SpawnPlace + TilePosOffset;
            Transform->SetPosition(&SpawnPlaceMovedDown);
        }

    }
    else if (Properties != 0 && strcmp((*Properties)[0]["value"].GetString(), "Mu") == 0)//multi tile object- props that are bigger than a single tile
    {
    name << " " << "Prop";

    ComponentTransform* Transform = SpecialObject->GetTransform();
    float TileSize = LevelLoadSys.GetTileSize();
    vec3 TilePosOffset(0, -0.05, 1);
    vec3 SpawnPlace = SpawnPos + TilePosOffset;
    Transform->SetPosition(&SpawnPlace);
    vec3 PropScale(TileSize * 0.75, TileSize * 0.75, 1);
    Transform->SetScale(&PropScale);
    LevelLoadSys.AssignTileSprite(SpawnType, SpecialObject);
    GameObjectManagerAdd(&ObjectManager, SpecialObject);

    }
    else if (Properties != 0 && strcmp((*Properties)[0]["value"].GetString(), "CloudGenerator") == 0)//multi tile object- props that are bigger than a single tile
    {
       name << " " << "CloudGenSpot";
       SpecialObject->GetTransform()->SetPosition(&SpawnPos);
       SpecialObject->SetName(name.str());
       GameObjectManagerAdd(&ObjectManager, SpecialObject);
       EmmiterManager->AddPhysicsParticleEmitter(SpecialObject->GetTransform(), "./TextFiles/PhysicsParticleGenerators/CloudGenerator.json");

       //
    }
    else if (Properties != 0 && strcmp((*Properties)[0]["value"].GetString(), "Light") == 0)//multi tile object- props that are bigger than a single tile
    {
    name << " " << "LightSourceSpot";
    SpecialObject->GetTransform()->SetPosition(&SpawnPos);
    SpecialObject->SetName(name.str());
    SpecialObject->EmmitLight(0.3, 1);
    
    GameObjectManagerAdd(&ObjectManager, SpecialObject);
    }
    if (SpawnType == 76)
    {
        name << " " << "BigMushroom";
        SpecialObject->SetName(name.str());
        SpecialObject->EmmitLight(0.3, 1);
        //GameObjectManagerAdd(&ObjectManager, SpecialObject);
        //EmmiterManager->AddPhysicsParticleEmitter(SpecialObject->GetTransform(), "./TextFiles/PhysicsParticleGenerators/MushroomGenerator.json");

    }
    SpecialObject->SetName(name.str());

    specialCounter++;

}

void ShootBullet(float dt)
{
    if (TimeSinceLastShot >= (*BulletDoc)["Properties"]["ShotInterval"].GetFloat())
    {
        TimeSinceLastShot = 0;
        //physics, sprite
        // 
        // 
        //create gameobject
        GameObject* bullet = new GameObject();
        bullet->SetName("b");
        //collider
        //ComponentCollider(float xsize, float ysize, bool CollideWithWalls, bool CollideWithBoxes, bool CollideWithNABoxes, bool PushableByBoxes);
        ComponentCollider* collider = new ComponentCollider((*BulletDoc)["Properties"]["ColliderScaleX"].GetFloat(), (*BulletDoc)["Properties"]["ColliderScaleY"].GetFloat(), true, true, true, true);

        ComponentPhysics* physics = new ComponentPhysics();
        glm::vec3 vectorSpeed ((*BulletDoc)["Properties"]["Speedx"].GetFloat(), (*BulletDoc)["Properties"]["Speedy"].GetFloat(), 0.0);
        glm::vec3 vectorSpeedDown ((*BulletDoc)["Properties"]["Speedx_down"].GetFloat(), (*BulletDoc)["Properties"]["Speedy_down"].GetFloat(), 0.0);
        glm::vec3 vectorSpeedUp ((*BulletDoc)["Properties"]["Speedx_up"].GetFloat(), (*BulletDoc)["Properties"]["Speedy_up"].GetFloat(), 0.0);
        float BulletEffectDirection = 1;
        if (TestGameObject->GetTransform()->GetScale()->x < 0.0f) //the player is facing left
        {
            vectorSpeedUp.x *= -1;
            vectorSpeed.x *= -1;
            vectorSpeedDown.x *= -1;
            BulletEffectDirection *= -1;
        }

        //higher angle
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            physics->SetVelocity(&vectorSpeedUp);
        }
        //lower angle
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            physics->SetVelocity(&vectorSpeedDown);
        }
        //straight
        else
        {
            physics->SetVelocity(&vectorSpeed);
        }

        const glm::vec3 vectorGravity(0.0, (*BulletDoc)["Properties"]["Gravity"].GetFloat(), 0.0);
        physics->SetAcceleration(&vectorGravity);

        bullet->SetPhysics(physics);
        bullet->SetCollider(collider);
        
        BehaviorIceBullet* BulletBehavior = new BehaviorIceBullet(BulletDoc);
        bullet->SetBehavior(BulletBehavior);

        ComponentTransform* initialTransform = bullet->GetTransform();
        glm::vec3 BulletStartScale((*BulletDoc)["Properties"]["ScaleX"].GetFloat(), (*BulletDoc)["Properties"]["ScaleY"].GetFloat(), 1);

        initialTransform->SetPosition(GetPlayer()->GetTransform()->GetPosition());
        initialTransform->SetScale(&BulletStartScale);

        /********************shooting ice audio**********************/
        soundHolder->Play(shootingIce, &channelOne);
        soundHolder->ChangeVolume(channelOne, 0.3);

        /********************ice bullet graphics**********************/

        GameObject* IceEffect = new GameObject();
        glm::vec3 EffectSize((*BulletDoc)["VFX"]["EffectSizeX"].GetFloat() * BulletEffectDirection, (*BulletDoc)["VFX"]["EffectSizeY"].GetFloat(), 1);
        IceEffect->SetName("IceEffect");
        IceEffect->GetTransform()->SetScale(&EffectSize);
        IceEffect->CreateAndAddAnimation((*BulletDoc)["VFX"]["AnimationFile"].GetString(), (*BulletDoc)["VFX"]["SpriteSourceFile"].GetString(), ImgManager, CameraShader);//0 = idle
        IceEffect->SetCurrentAnimation(0);
        IceEffect->SetParent(bullet);
        IceEffect->GetAnimation()->Play();

  
        EmmiterManager->AddPhysicsParticleEmitter(bullet->GetTransform(), "./TextFiles/PhysicsParticleGenerators/BulletParticleGenerator.json");

        GameObjectManagerAdd(&ObjectManager, bullet);
        GameObjectManagerAdd(&ObjectManager, IceEffect);
    }
}

void  CallLevel1DebugDraw(glm::mat3x3 Tran)
{
    ShowRedRect = true;
    RedRectTran = Tran;
}


void SpawnGoal(glm::vec3 GoalPos)
{
    GoalObject = new GameObject();
    GoalObject->SetName("Goal");
    GoalObjTransform = GoalObject->GetTransform();
    //glm::vec3 StartPos(0.5, 0.65, 1);
   // glm::vec3 Pos(1.5, 0.85, 1);
    glm::vec3 Scale(0.075, 0.075, 1);//sqauredraw 4x4 uses a mesh of 0.1 * 0.1

    //GoalObjBox = new ComponentCollider(1.0f, 1.0f, false, true, false);
    GoalObjBox = new ComponentCollider(1.0f, 1.0f, false, true, false, true);
    GoalObjBox->ComponentColliderBoxSetOnCollisionWithBoxFunction(WhilePlayerTouchingDoor);


    //the collider box is 1x1. if the transform is scaled, the collider box will also be scaled by that much
    GoalObject->SetCollider(GoalObjBox);
    GoalObjBox->SetParent(GoalObject);

    GoalObjTransform->SetPosition(&GoalPos);
    GoalObjTransform->SetScale(&Scale);

}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
void PlayerLooseLife(GameObject* Enemy)
{
    if (Enemy->GetFreeze() && Enemy->GetFreeze()->GetFrozen())
    {
        return;
    }

    if (!GodMode)
    {
        if (PlayerBehavior->playerTimeSinceLastHurt > PlayerBehavior->minimumTimeIntervalPlayerHurt)
        {
            soundHolder->Play(takingDamage, &channelThree);
            (PlayerBehavior->playerLives)--;
            PlayerBehavior->playerTimeSinceLastHurt = 0;
            bool EnemyOnPlayerLeft = Enemy->GetTransform()->GetPosition()->x < GetPlayer()->GetTransform()->GetPosition()->x;
            glm::vec3 KnockVel(-1, 1, 0);
            if (EnemyOnPlayerLeft)
            {
                KnockVel.x *= -1;// this makes knock vel x positive, which would move the player to the right
            }
            TestGameObject->GetPhysics()->SetVelocity(&KnockVel);
            soundHolder->Play(landing, &channelThree);
        }
    }
}

ImageManager* GetImageManager()
{
    return ImgManager;
}

GameObjectManager* GetObjectManager()
{
    return &ObjectManager;
}
bool GetLevelOnePause()
{
    return pause;
}

void setNextLevel()
{
    LevelLoadSystem::SetCurrentLevel(LevelLoadSystem::GetCurrentLevel() + 1);
    // restarting the same gamestate but with a new level's tile setup
    GameStateManagerSetNextState(GameStates::GsRestart);

}

void increaseBGVolume()
{
    soundHolder->IncreaseVolume(channelTwo);
}

void decreaseBGVolume()
{
    soundHolder->DecreaseVolume(channelTwo);
}

void GoToMainMenu()
{
        ImgManager->SetImageVisibleInSystem("YesButtonM", true);
        ImgManager->SetImageVisibleInSystem("NoButton", true);
        ImgManager->SetImageVisibleInSystem("MainMenuButton", false);
        ImgManager->SetImageVisibleInSystem("MainMenuHoverButton", false);
        ImgManager->SetImageVisibleInSystem("QuitHoverButton", false);
        ImgManager->SetImageVisibleInSystem("ResumeButton", false);
        ImgManager->SetImageVisibleInSystem("ControlsButton", false);
        ImgManager->SetImageVisibleInSystem("OptionsButton", false);
        ImgManager->SetImageVisibleInSystem("QuitButton", false);
        ImgManager->SetImageVisibleInSystem("Board", false);
        ImgManager->SetImageVisibleInSystem("Name", false);
        ImgManager->SetImageVisibleInSystem("OffSquareButton", false);
        ImgManager->SetImageVisibleInSystem("OnSquareButton", false);
        ImgManager->SetImageVisibleInSystem("MenuBackgroundAnimated", false);
        MenuBackgroundAnimated->SetVisible(false);
        ImgManager->SetImageVisibleInSystem("MMConfirm", true);


        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !ImageManager::IsClickHandled())
        {
            ImageManager::SetClickHandled(true);
            //go back to title
            GameStateManagerSetNextState(GameStates::GsMainMenu);
        }
}
void GoToResume(){
    pause = false;
    //pause the audio
    soundHolder->Pause(false, channelOne);
    soundHolder->Pause(false, channelTwo);
    soundHolder->Pause(false, channelThree);
}

void GoToQuit() {
    quitTrigger == true;
    ImgManager->SetImageVisibleInSystem("YesButton", true);
    ImgManager->SetImageVisibleInSystem("NoButton", true);
    ImgManager->SetImageVisibleInSystem("MainMenuButton", false);
    ImgManager->SetImageVisibleInSystem("QuitHoverButton", false);
    ImgManager->SetImageVisibleInSystem("ResumeButton", false);
    ImgManager->SetImageVisibleInSystem("ControlsButton", false);
    ImgManager->SetImageVisibleInSystem("OptionsButton", false);
    ImgManager->SetImageVisibleInSystem("QuitButton", false);
    ImgManager->SetImageVisibleInSystem("Board", false);
    ImgManager->SetImageVisibleInSystem("Name", false);
    ImgManager->SetImageVisibleInSystem("OffSquareButton", false);
    ImgManager->SetImageVisibleInSystem("OnSquareButton", false);
    ImgManager->SetImageVisibleInSystem("MenuBackgroundAnimated", false);
    MenuBackgroundAnimated->SetVisible(false);
    ImgManager->SetImageVisibleInSystem("QuitConfirm", true);


    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !ImageManager::IsClickHandled())
    {
        ImageManager::SetClickHandled(true);
        //quit game
        GameStateManagerSetNextState(GameStates::GsQuit);
    }
}



void GoToControls() {
    //pause = false;
    //go back to title
	ImgManager->SetImageVisibleInSystem("ControlsBG", true);

	ImgManager->SetImageVisibleInSystem("MainMenuButton", false);
	ImgManager->SetImageVisibleInSystem("ResumeButton", false);
	ImgManager->SetImageVisibleInSystem("ControlsButton", false);
	ImgManager->SetImageVisibleInSystem("OptionsButton", false);
	ImgManager->SetImageVisibleInSystem("ControlsHoverButton", false);
	ImgManager->SetImageVisibleInSystem("Board", false);
	ImgManager->SetImageVisibleInSystem("Name", false);
	ImgManager->SetImageVisibleInSystem("QuitButton", false);
	ImgManager->SetImageVisibleInSystem("BackButton", true);

    //GameStateManagerSetNextState(GameStates::GsControls);
}

void GoToOptions() {
    //make an options pop up menu 

    ImgManager->SetImageVisibleInSystem("MainMenuButton", false);
    ImgManager->SetImageVisibleInSystem("OptionsHoverButton", false);
    ImgManager->SetImageVisibleInSystem("ResumeButton", false);
    ImgManager->SetImageVisibleInSystem("ControlsButton", false);
    ImgManager->SetImageVisibleInSystem("OptionsButton", false);
    ImgManager->SetImageVisibleInSystem("QuitButton", false);
    ImgManager->SetImageVisibleInSystem("Board", false);
    ImgManager->SetImageVisibleInSystem("Name", false);
    ImgManager->SetImageVisibleInSystem("Sound", true);

    ImgManager->SetImageVisibleInSystem("OnButton", true);
    ImgManager->SetImageVisibleInSystem("OptionsTitle", true);
    ImgManager->SetImageVisibleInSystem("BackButton", true);
    ImgManager->SetImageVisibleInSystem("OffButton", true);
    ImgManager->SetImageVisibleInSystem("OffSquareButton", true);
    ImgManager->SetImageVisibleInSystem("OnSquareButton", true);
    ImgManager->SetImageVisibleInSystem("FullscreenButton", true);
    ImgManager->SetImageVisibleInSystem("FullScreen", true);
    ImgManager->SetImageVisibleInSystem("WindowedButton", true);
    ImgManager->SetImageVisibleInSystem("Windowed", true);

}

void GoToExit() {
    //quit game
    GameStateManagerSetNextState(GameStates::GsQuit);
}

void GoToMM() {
    //quit game
    GameStateManagerSetNextState(GameStates::GsMainMenu);
}

void GoToPause() {
    //pause game
    pause == true;
    ImgManager->SetImageVisibleInSystem("YesButton", false);
    ImgManager->SetImageVisibleInSystem("YesButtonM", false);
    ImgManager->SetImageVisibleInSystem("MMConfirm", false);
    ImgManager->SetImageVisibleInSystem("NoButton", false);
    ImgManager->SetImageVisibleInSystem("YesHoverButton", false);
    ImgManager->SetImageVisibleInSystem("NoHoverButton", false);
    ImgManager->SetImageVisibleInSystem("QuitConfirm", false);
    ImgManager->SetImageVisibleInSystem("MainMenuButton", true);
    ImgManager->SetImageVisibleInSystem("ResumeButton", true);
    ImgManager->SetImageVisibleInSystem("ControlsButton", true);
    ImgManager->SetImageVisibleInSystem("OptionsButton", true);
    ImgManager->SetImageVisibleInSystem("Name", true);
    ImgManager->SetImageVisibleInSystem("QuitButton", true);
    ImgManager->SetImageVisibleInSystem("OnButton", false);
    ImgManager->SetImageVisibleInSystem("FullscreenButton", false);
    ImgManager->SetImageVisibleInSystem("FullScreen", false);
    ImgManager->SetImageVisibleInSystem("WindowedButton", false);
    ImgManager->SetImageVisibleInSystem("Windowed", false);
    ImgManager->SetImageVisibleInSystem("Sound", false);


    ImgManager->SetImageVisibleInSystem("NoButton", false);
    ImgManager->SetImageVisibleInSystem("OffButton", false);
    ImgManager->SetImageVisibleInSystem("OnHoverButton", false);
    ImgManager->SetImageVisibleInSystem("OffHoverButton", false);
    ImgManager->SetImageVisibleInSystem("OffSquareButton", false);
    ImgManager->SetImageVisibleInSystem("OnSquareButton", false);
    ImgManager->SetImageVisibleInSystem("BackButton", false);
    ImgManager->SetImageVisibleInSystem("BackHoverButton", false);
    ImgManager->SetImageVisibleInSystem("OptionsTitle", false);
	ImgManager->SetImageVisibleInSystem("ControlsBG", false);
}

//main menu hover calls
void MainMenuButtonHover(glm::mat3x3 ButtonTransform)
{
    ImgManager->SetImageVisibleInSystem("MainMenuHoverButton", true);
    ImgManager->SetImageTransform("MainMenuHoverButton",   ButtonTransform);
}

void MainMenuButtonLeave()
{
    ImgManager->SetImageVisibleInSystem("MainMenuHoverButton", false);

}

//options hover calls 
void OptionsButtonHover(glm::mat3x3 ButtonTransform)
{
    ImgManager->SetImageVisibleInSystem("OptionsHoverButton", true);
    ImgManager->SetImageTransform("OptionsHoverButton", ButtonTransform);
}

void OptionsButtonLeave()
{
    ImgManager->SetImageVisibleInSystem("OptionsHoverButton", false);

}

//controls hover calls
void ControlsButtonHover(glm::mat3x3 ButtonTransform)
{
    ImgManager->SetImageVisibleInSystem("ControlsHoverButton", true);
    ImgManager->SetImageTransform("ControlsHoverButton", ButtonTransform);
}

void ControlsButtonLeave()
{
    ImgManager->SetImageVisibleInSystem("ControlsHoverButton", false);

}

//quit hover calls
void QuitButtonHover(glm::mat3x3 ButtonTransform)
{
    ImgManager->SetImageVisibleInSystem("QuitHoverButton", true);
    ImgManager->SetImageTransform("QuitHoverButton", ButtonTransform);
}

void QuitButtonLeave()
{
    ImgManager->SetImageVisibleInSystem("QuitHoverButton", false);

}

//resume hover calls
void ResumeButtonHover(glm::mat3x3 ButtonTransform)
{
    ImgManager->SetImageVisibleInSystem("ResumeHoverButton", true);
    ImgManager->SetImageTransform("ResumeHoverButton", ButtonTransform);
}
void ResumeButtonLeave()
{
    ImgManager->SetImageVisibleInSystem("ResumeHoverButton", false);

}

//resume hover calls
void YesButtonHover(glm::mat3x3 ButtonTransform)
{
    ImgManager->SetImageVisibleInSystem("YesHoverButton", true);
    ImgManager->SetImageTransform("YesHoverButton", ButtonTransform);
}
void YesButtonLeave()
{
    ImgManager->SetImageVisibleInSystem("YesHoverButton", false);

}
void FullScreenClicked()
{

    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    glfwSetWindowAttrib(window, GLFW_MAXIMIZED, GLFW_TRUE);
    int Count = 1;
    GLFWmonitor* M = glfwGetMonitors(&Count)[0];
    const GLFWvidmode* mode = glfwGetVideoMode(M);
    glfwWindowHint(GLFW_FLOATING, false);
    glfwSetWindowMonitor(window, M, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);

    int Real_W, Real_H;
    glfwGetWindowSize(window, &Real_W, &Real_H);
    TraceSetActiveChannel("call back");

    TraceMessage("call back", "Full Screen");

    UpdateWinDimensions(Real_W, Real_H);
}
void WindowedClicked()
{
    ImgManager->SetImageVisibleInSystem("FullscreenButtonHover", true);
    ImgManager->SetImageVisibleInSystem("WindowButtonHover", false);
    int Count = 1;
    GLFWmonitor* M = glfwGetMonitors(&Count)[0];
    const GLFWvidmode* mode = glfwGetVideoMode(M);
    glfwWindowHint(GLFW_FLOATING, true);
    glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_TRUE);
    glfwSetWindowAttrib(window, GLFW_MAXIMIZED, GLFW_FALSE);
    glfwSetWindowMonitor(window, NULL, 50, 50, mode->width, mode->height, GLFW_DONT_CARE);
    glfwSetWindowSize(window, 1400, 870);

    int Real_W, Real_H;
    glfwGetWindowSize(window, &Real_W, &Real_H);
    TraceSetActiveChannel("call back");

    TraceMessage("call back", "Windowed Screen");

    UpdateWinDimensions(Real_W, Real_H);
}
//resume hover calls
void NoButtonHover(glm::mat3x3 ButtonTransform)
{
    ImgManager->SetImageVisibleInSystem("NoHoverButton", true);
    ImgManager->SetImageTransform("NoHoverButton", ButtonTransform);
}
void NoButtonLeave()
{
    ImgManager->SetImageVisibleInSystem("NoHoverButton", false);
}

void OnFullScreenButtonHover(glm::mat3x3 ButtonTransform)
{
    ImgManager->SetImageVisibleInSystem("FullscreenButtonHover", true);
    ImgManager->SetImageTransform("FullscreenButtonHover", ButtonTransform);
}
void OnFullScreenButtonLeave()
{
    ImgManager->SetImageVisibleInSystem("FullscreenButtonHover", false);
}

void OnWindowedButtonHover(glm::mat3x3 ButtonTransform)
{
    ImgManager->SetImageVisibleInSystem("WindowedButtonHover", true);
    ImgManager->SetImageTransform("WindowedButtonHover", ButtonTransform);
}
void OnWindowedButtonLeave()
{
    ImgManager->SetImageVisibleInSystem("WindowedButtonHover", false);
}
//setting the options 
void GoToMusicOn() {
  // turn on music 
     //pause the audio
    soundHolder->Pause(false, channelOne);
    soundHolder->Pause(false, channelTwo);
    soundHolder->Pause(false, channelThree);
    musicOn = true;
    ImgManager->SetImageVisibleInSystem("OnHoverButton", true);
}

void GoToMusicOff() {
    //turn off music
     //pause the audio
    soundHolder->Pause(true, channelOne);
    soundHolder->Pause(true, channelTwo);
    soundHolder->Pause(true, channelThree);
    musicOn = false;
    ImgManager->SetImageVisibleInSystem("OffHoverButton", true);
}

//on off hover calls
void OnButtonHover(glm::mat3x3 ButtonTransform)
{
    ImgManager->SetImageVisibleInSystem("OnHoverButton", true);
    ImgManager->SetImageTransform("OnHoverButton", ButtonTransform);
}

void OnButtonLeave()
{
    if (ImageManager::IsClickHandled()) {
        ImgManager->SetImageVisibleInSystem("OnHoverButton", true);
    }

    ImgManager->SetImageVisibleInSystem("OnHoverButton", false);
}

void OffButtonHover(glm::mat3x3 ButtonTransform)
{
    ImgManager->SetImageVisibleInSystem("OffHoverButton", true);
    ImgManager->SetImageTransform("OffHoverButton", ButtonTransform);
}

void OffButtonLeave()
{
    if (ImageManager::IsClickHandled()) {
        ImgManager->SetImageVisibleInSystem("OffHoverButton", true);
    }
    ImgManager->SetImageVisibleInSystem("OffHoverButton", false);
}

//back hover calls
void BackButtonHover(glm::mat3x3 ButtonTransform)
{
    ImgManager->SetImageVisibleInSystem("BackHoverButton", true);
    ImgManager->SetImageTransform("BackHoverButton", ButtonTransform);
}
void BackButtonLeave()
{
    ImgManager->SetImageVisibleInSystem("BackHoverButton", false);

}
