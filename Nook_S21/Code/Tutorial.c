// ---------------------------------------------------------------------------
// Project Name		:	Nook
// File Name		:	Tutorial.c
// Author			:	Primary: Justin Li | Secondary: Rey Rosario, Mary Khuu, Zak Stephenson, Caleb Hurlbert
// Creation Date	:	19 March 2021
// Purpose			:	Game state for tutorial level
// History			:
// - 19 March 2021	:	- initial implementation
//
// All content © 2021 DigiPen (USA) Corporation, all rights reserved.
// ---------------------------------------------------------------------------

#include "framework.h"
#include "Audio.h"
#include "GameStateManager.h"
#include "Tutorial.h"
#include "AEEngine.h"
#include "map.h"
#include "collision.h"
#include "Enemy.h"
#include "object_data.h"
#include "Player.h"
#include "camera.h"
#include "Sprite.h"
#include "hook.h"
#include "Particle.h"
#include "debug_logger.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

AEGfxVertexList* pMesh1;
AEGfxVertexList* pMesh2;
AEGfxVertexList* pMesh3;
AEGfxVertexList* pMesh4;
AEGfxVertexList* pMesh5;
AEGfxVertexList* pMesh6;
AEGfxVertexList* pMesh7;

AEGfxTexture* pTexR;   /*Red*/
AEGfxTexture* pTexO;   /*Orange*/
AEGfxTexture* pTexY;   /*Yellow*/
AEGfxTexture* pTexG;   /*Green*/
AEGfxTexture* pTexB;   /*Blue*/
AEGfxTexture* pTexP;   /*Purple*/
AEGfxTexture* pTexI;   /*Indigo*/
AEGfxTexture* pTexBl;   /*Black*/
AEGfxTexture* pTexW;   /*White*/
AEGfxTexture* pTexGr;  /*Gray*/

/*Textures: pixel art*/
AEGfxTexture* tileTexture; /*tile*/
AEGfxTexture* spikeTexture; /*spike*/
AEGfxTexture* hookTexture; /*hook*/
AEGfxTexture* hookableTexture; /*hookable_target*/
AEGfxTexture* playerIdleTexture; /*player in idle*/
AEGfxTexture* playerJumpTexture; /*player jumping*/
AEGfxTexture* playerWalkTexture; /*player walking*/
AEGfxTexture* playerDeathTexture; /*player death*/
AEGfxTexture* playerHeartOn; /*red heart*/
AEGfxTexture* playerHeartAnimation; /*heart spritesheet*/
AEGfxTexture* playerHeartOff; /*grey heart*/
AEGfxTexture* ghostTexture; /*enemy_1*/
AEGfxTexture* enemy2Texture; /*enemy_2*/
AEGfxTexture* enemy3Texture; /*enemy_3*/
AEGfxTexture* enemy4Texture; /*enemy_4*/
AEGfxTexture* enemyDeadTexture; /*enemy dies*/
AEGfxTexture* checkpointTexture; /*checkpoint*/
AEGfxTexture* checkpointTexture2; /*checkpoint*/
AEGfxTexture* finalcheckTexture; /*checkpoint*/
AEGfxTexture* bgTexture; /*background*/
AEGfxTexture* signTexture; /*sign*/

/*ghost animation variables*/
TextureOffset heartOffsets[9];
int* tutorialCurrentHeartOffset = 0;
int tutorialCurrHeartFrame = 0;
float* heartTime;

/*player animation variables*/
TextureOffset playerOffsets[4];
int* tutorialCurrentPlayerOffset = 0;
int tutorialCurrPlayerFrame = 0;
float* playerTime;

/*ghost animation variables*/
TextureOffset ghostOffsets[2];
int* tutorialCurrentGhostOffset = 0;
int tutorialCurrGhostFrame = 0;
float* ghostTime;

/*enemy2 animation variables*/
TextureOffset enemy2Offsets[3];
int* tutorialCurrentEnemy2Offset = 0;
int tutorialCurrEnemy2Frame = 0;
float* enemy2Time;

/*enemy3 animation variables*/
TextureOffset enemy3Offsets[2];
int* tutorialCurrentEnemy3Offset = 0;
int tutorialCurrEnemy3Frame = 0;
float* enemy3Time;

/*enemy4 animation variables*/
TextureOffset enemy4Offsets[2];
int* tutorialCurrentEnemy4Offset = 0;
int tutorialCurrEnemy4Frame = 0;
float* enemy4Time;

signed long tutorialMousePosX, tutorialMousePosY;
float tutorialMouseWorldPosX, tutorialMouseWorldPosY;
float tutorialCamX, tutorialCamY;

int tutorialLastPlayerDir = 0;

int tutorialNumLives = 9; /*number to be decrimented*/
const int tutorialMaxLives = 9; /*constant max*/
int tutorialDustCounter = 60;

Player* tutorialPlayer;
static char* debug_filename;

static float bgMusicTimer;

/*metrics data*/
unsigned int tutorialStart_frame = 0;          /*frame on which gameplay was started*/
unsigned int tutorialGhosts_killed = 0;        /*number of ghosts killed*/
unsigned int tutorialCheckpoints_lit = 0;      /*number of checkpoints hit*/
float tutorialDistance_run = 0;                /*total distance run by player*/

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static float isWalking = 0.0f;
static float deathTimer;
static int hookTrigger;
static int movementTrigger;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void TutorialLoad()
{
	map_create("Assets/tutorial_map.txt");

	unsigned char colors[10][4];    /*array of colors*/

	if (!debug_filename) debug_filename = create_log(173); /*TODO -- update revision number*/

	pMesh1 = createEqualQuadMesh(0.5f, 0.0f, "Mesh1x1");
	pMesh2 = createQuadMesh(0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1_texture");
	pMesh3 = createQuadMesh(0.5f, 0.5f, 1.0f / 2, 1.0f / 1, "Mesh1x2_texture");
	pMesh4 = createQuadMesh(0.5f, 0.5f, 1.0f / 3, 1.0f / 1, "Mesh3x1_texture");
	pMesh5 = createQuadMesh(1670.0f, 564.0f, 1.0f, 1.0f, "Background_texture");
	pMesh6 = createQuadMesh(0.5f, 0.5f, 1.0f / 2, 1.0f / 2, "Mesh2x2_texture");
	pMesh7 = createQuadMesh(0.5f, 0.5f, 1.0f / 3, 1.0f / 3, "Mesh3x3_texture");

	/*initialize colors*/
	colors[0][0] = 255; colors[0][1] = 0;   colors[0][2] = 0;   colors[0][3] = 255; /*red*/
	colors[1][0] = 255; colors[1][1] = 165; colors[1][2] = 0;   colors[1][3] = 255; /*orange*/
	colors[2][0] = 255; colors[2][1] = 255; colors[2][2] = 0;   colors[2][3] = 255; /*yellow*/
	colors[3][0] = 0;   colors[3][1] = 255; colors[3][2] = 0;   colors[3][3] = 255; /*green*/
	colors[4][0] = 0;   colors[4][1] = 0;   colors[4][2] = 255; colors[4][3] = 255; /*blue*/
	colors[5][0] = 128; colors[5][1] = 0;   colors[5][2] = 128; colors[5][3] = 255; /*purple*/
	colors[6][0] = 65;  colors[6][1] = 0;   colors[6][2] = 128; colors[6][3] = 255; /*indigo*/
	colors[7][0] = 0;   colors[7][1] = 0;   colors[7][2] = 0;   colors[7][3] = 255; /*black*/
	colors[8][0] = 255; colors[8][1] = 255; colors[8][2] = 255; colors[8][3] = 255; /*white*/
	colors[9][0] = 128; colors[9][1] = 128; colors[9][2] = 128; colors[9][3] = 255; /*gray*/

	/*create textures*/
	pTexR = AEGfxTextureLoadFromMemory(colors[0], 1, 1);
	pTexO = AEGfxTextureLoadFromMemory(colors[1], 1, 1);
	pTexY = AEGfxTextureLoadFromMemory(colors[2], 1, 1);
	pTexG = AEGfxTextureLoadFromMemory(colors[3], 1, 1);
	pTexB = AEGfxTextureLoadFromMemory(colors[4], 1, 1);
	pTexP = AEGfxTextureLoadFromMemory(colors[5], 1, 1);
	pTexI = AEGfxTextureLoadFromMemory(colors[6], 1, 1);
	pTexBl = AEGfxTextureLoadFromMemory(colors[7], 1, 1);
	pTexW = AEGfxTextureLoadFromMemory(colors[8], 1, 1);
	pTexGr = AEGfxTextureLoadFromMemory(colors[9], 1, 1);

	/*textures: pixel art*/
	tileTexture = AEGfxTextureLoad("Assets/NoirTile.png");
	AE_ASSERT_MESG(tileTexture, "Failed to create tileTexture!!");

	spikeTexture = AEGfxTextureLoad("Assets/NookSpike.png");
	AE_ASSERT_MESG(spikeTexture, "Failed to create spikeTexture!!");

	hookTexture = AEGfxTextureLoad("Assets/NoirYarn2.png");
	AE_ASSERT_MESG(hookTexture, "Failed to create hookTexture!!");

	hookableTexture = AEGfxTextureLoad("Assets/NoirYarn.png");
	AE_ASSERT_MESG(hookableTexture, "Failed to create hookableTexture!!");

	playerIdleTexture = AEGfxTextureLoad("Assets/NoirCat_Idle.png");
	AE_ASSERT_MESG(playerIdleTexture, "Failed to create playerIdleTexture!!");

	playerJumpTexture = AEGfxTextureLoad("Assets/NoirCat_Idle.png");
	AE_ASSERT_MESG(playerJumpTexture, "Failed to create playerJumpTexture!!");

	playerWalkTexture = AEGfxTextureLoad("Assets/NoirCat_Walk.png");
	AE_ASSERT_MESG(playerWalkTexture, "Failed to create playerWalkTexture!!");

	playerOffsets[0].mX = 0.0f;			playerOffsets[0].mY = 0.0f;
	playerOffsets[1].mX = 0.0f;			playerOffsets[1].mY = 0.5f;

	playerOffsets[2].mX = 0.5f;			playerOffsets[2].mY = 0.0f;
	playerOffsets[3].mX = 0.5f;			playerOffsets[3].mY = 0.5f;

	playerDeathTexture = AEGfxTextureLoad("Assets/NoirCat_Death.png");
	AE_ASSERT_MESG(playerDeathTexture, "Failed to create playerDeathTexture!!");

	playerHeartOn = AEGfxTextureLoad("Assets/NookHeart.png");
	AE_ASSERT_MESG(playerHeartOn, "Failed to create playerHeartOn!!");

	playerHeartAnimation = AEGfxTextureLoad("Assets/NookHeart_spritesheet.png");
	AE_ASSERT_MESG(playerHeartAnimation, "Failed to create playerHeartAnimation!!");

	heartOffsets[0].mX = 0.0f;			heartOffsets[0].mY = 0.0f / 3;
	heartOffsets[1].mX = 0.0f;			heartOffsets[1].mY = 1.0f / 3;
	heartOffsets[2].mX = 0.0f;			heartOffsets[2].mY = 2.0f / 3;

	heartOffsets[3].mX = 1.0f;			heartOffsets[3].mY = 0.0f / 3;
	heartOffsets[4].mX = 1.0f;			heartOffsets[4].mY = 1.0f / 3;
	heartOffsets[5].mX = 1.0f;			heartOffsets[5].mY = 2.0f / 3;

	heartOffsets[6].mX = 2.0f;			heartOffsets[6].mY = 0.0f / 3; //gray heart
	heartOffsets[7].mX = 2.0f;			heartOffsets[7].mY = 1.0f / 3; //empty
	heartOffsets[8].mX = 2.0f;			heartOffsets[8].mY = 2.0f / 3; //empty

	playerHeartOff = AEGfxTextureLoad("Assets/NookNoHeart.png");
	AE_ASSERT_MESG(playerHeartOff, "Failed to create playerHeartOff!!");

	ghostTexture = AEGfxTextureLoad("Assets/ghost_powerup_spriteSheet.png");
	AE_ASSERT_MESG(ghostTexture, "Failed to create ghostTexture!!");

	ghostOffsets[0].mX = 0.0f;			ghostOffsets[0].mY = 0.0f;
	ghostOffsets[1].mX = 0.5f;			ghostOffsets[1].mY = 0.0f;

	enemy2Texture = AEGfxTextureLoad("Assets/ghost_test.png");
	AE_ASSERT_MESG(enemy2Texture, "Failed to create enemy2Texture!!");

	enemy2Offsets[0].mX = 0.0f;			enemy2Offsets[0].mY = 0.0f;
	enemy2Offsets[1].mX = 0.33f;		enemy2Offsets[1].mY = 0.0f;
	enemy2Offsets[2].mX = 0.66f;		enemy2Offsets[2].mY = 0.0f;

	enemy3Texture = AEGfxTextureLoad("Assets/GhostPlaceholder1.png");
	AE_ASSERT_MESG(enemy3Texture, "Failed to create enemy2Texture!!");

	enemy3Offsets[0].mX = 0.0f;			enemy3Offsets[0].mY = 0.0f;
	enemy3Offsets[1].mX = 0.5f;			enemy3Offsets[1].mY = 0.0f;

	enemy4Texture = AEGfxTextureLoad("Assets/GhostPlaceholder2.png");
	AE_ASSERT_MESG(enemy4Texture, "Failed to create enemy4Texture!!");

	enemy4Offsets[0].mX = 0.0f;			enemy4Offsets[0].mY = 0.0f;
	enemy4Offsets[1].mX = 0.5f;			enemy4Offsets[1].mY = 0.0f;

	enemyDeadTexture = AEGfxTextureLoad("Assets/NoirPuff.png");
	AE_ASSERT_MESG(enemyDeadTexture, "Failed to create enemy2Texture!!");

	checkpointTexture = AEGfxTextureLoad("Assets/NoirStreetLights_off.png");
	AE_ASSERT_MESG(checkpointTexture, "Failed to create checkpointTexture!!");

	checkpointTexture2 = AEGfxTextureLoad("Assets/NoirStreetLights_on.png");
	AE_ASSERT_MESG(checkpointTexture2, "Failed to create checkpointTexture2!!");

	finalcheckTexture = AEGfxTextureLoad("Assets/telephoneBooth.png");
	AE_ASSERT_MESG(finalcheckTexture, "Failed to create finalcheckTexture!!");

	signTexture = AEGfxTextureLoad("Assets/NoirStreetSign.png");
	AE_ASSERT_MESG(signTexture, "Failed to create signTexture!!");

	bgTexture = AEGfxTextureLoad("Assets/CityscapeLoop.png");
	AE_ASSERT_MESG(bgTexture, "Failed to create bgTexture!!");
}

void TutorialInit()
{
	AudioInit();
	bgMusicTimer = 1638.0f; // Roughly 27 seconds

	tutorialStart_frame = AEFrameRateControllerGetFrameCount();

	deathTimer = 2.0f;
	hookTrigger = 1;
	movementTrigger = 1;

	/*green bg*/
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	/*set blend mode*/
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	/*init player*/
	tutorialPlayer = (Player*)(malloc(sizeof(Player)));
	create_player(tutorialPlayer);

	/*init number of objects to zero*/
	object_list = NULL;
	num_objects = 0;
	objects_created = 0;

	tutorialNumLives = 9;

	/*create objects*/
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_width; j++)
		{
			if (object_map[i][j] > SPIKES)
			{
				if (create_object(object_map[i][j], j, i) == NULL)
				{
					AESysPrintf("Failed to create object at %d, %d\n", j, i);
					write_to_log(debug_filename, "Failed to create object\n");
					AESysExit();
				}
			}
		}
	}

	cameraInit();

	//game_obj* player = find_object(PLAYER, 0);
	//player->oldpos = player->pos;
}

void TutorialUpdate(float dt)
{
	update_log(debug_filename);

	AudioUpdate();

	/*play bg music*/
	if (bgMusicTimer == 1638.0f)
	{
		playSoundAdvanced("Assets/Sounds/Level2Track.mp3", 0.1f);
	}

	/*reset time for bg music loop*/
	if (bgMusicTimer == 0.0f)
	{
		bgMusicTimer = 1638.0f;
	}
	else
	{
		bgMusicTimer--;
	}

	/*breakpoint button*/
	if (AEInputCheckTriggered('K'))
	{
		write_to_log(debug_filename, "Breakpoint triggered!\n");
		AESysPrintf("Breakpoint triggered!\n");
	}

	int i, j, k;
	game_obj* curr;
	game_obj* curr2;
	game_obj* player = find_object(PLAYER, 0);
	game_obj* hook;

	AEInputGetCursorPosition(&tutorialMousePosX, &tutorialMousePosY);
	AEGfxConvertScreenCoordinatesToWorld(tutorialMousePosX, tutorialMousePosY, &tutorialMouseWorldPosX, &tutorialMouseWorldPosY);

	/*throw hook*/
	if (AEInputCheckTriggered(RI_MOUSE_LEFT_BUTTON_DOWN) && hookTrigger == 1)
	{
		playSoundAdvanced("Assets/Sounds/hook_shoot.wav", 0.4f);
		hook_throw(player, tutorialMouseWorldPosX, tutorialMouseWorldPosY);
	}

	/*play sound for jump*/
	if (AEInputCheckTriggered(' ') || AEInputCheckTriggered('W'))
	{
		playSoundAdvanced("Assets/Sounds/player_jump.wav", 0.4f);
	}

	hook = find_object(HOOK, 0); /*now that hook exists, assign pointer*/

	/*update game object data*/
	if (object_list)
	{
		curr = object_list;

		i = 0;
		while (i < num_objects)
		{

			curr2 = object_list;
			switch (curr->type)
			{
			case PLAYER:
				//curr->oldpos = curr->pos;

				/*Update player position*/
				if (movementTrigger == 1)
				{
					player_move(curr, tutorialPlayer, dt);
				}

				/*check map collision; snap if out of bounds*/
				curr->coll_flag = hotspot_check(curr);

				/*check spike collision; kill player if true*/
				if (spike_check(curr))
				{
					/*
					curr->isAlive = 0; //player dies
					tutorialNumLives--;
					player_reset(curr);
					if (tutorialNumLives != 0)
					{
						curr->pos = curr->checkpointPos;
						curr->isAlive = 1; //player isAlive after respawn

						//reset player vel
						player->vel.x = 0;
						player->vel.y = 0;
					}
					else if (tutorialNumLives == 0)
					{
						GameStateManagerSetNextState(Lose);
					}
					*/

					if (curr->isAlive == 1)
					{
						playSound(false, "Assets/Sounds/spike_death.wav");
						playSound(false, "Assets/Sounds/cat_yelp.wav");
					}
					curr->oldpos = curr->pos;
					curr->isAlive = 0; //player dies
					
					if (tutorialNumLives != 0)
					{
						if (curr->isAlive == 0)
						{
							deathTimer -= dt;
							hookTrigger = 0; //disable the hook
							movementTrigger = 0; //disable movement
							//player_reset(curr);
						}

						if (deathTimer <= 0)
						{
							tutorialNumLives--;
							curr->pos = curr->checkpointPos;
							curr->isAlive = 1; //player isAlive after respawn
							hookTrigger = 1; //enable hook
							movementTrigger = 1; //enable movement
							deathTimer = 2.0f; //reset timer because we're alive

						}
					}
					else
					{
						GameStateManagerSetNextState(Lose);
					}
					break;
				}
				tutorialDistance_run += (player->vel.x > 0 ? player->vel.x : -player->vel.x);
				if (curr->coll_flag) snap(curr, curr->coll_flag);
				//create dust particles
				if (tutorialDustCounter > 15)
				{
					if (player->oldpos.x != player->pos.x && (player->coll_flag & 8))
					{
						tutorialDustCounter = 0;
						ParticleCreate(player);
						player->oldpos = player->pos;
					}
				}
				tutorialDustCounter++;
				/*update camera*/
				cameraUpdate();

				/*check against other objects*/
				j = 0;
				while (j < num_objects)
				{
					/*if player collides with something...*/
					if ((curr2->type != PLAYER) && bounding_box_check(curr, curr2))
					{
						switch (curr2->type)
						{
							/*player dies*/
						case ENEMY_1:
						case ENEMY_2:
						case ENEMY_3:
						case ENEMY_4:
						{
							
							/*
							//player dies
							curr->isAlive = 0;
							if (tutorialNumLives != 0)
							{
								if (curr->isAlive == 0)
								{
									deathTimer -= 0.01f;

									AESysPrintf(" "); //timer never runs without this line?
								}

								if (deathTimer <= 0)
								{
									tutorialNumLives--;
									deathCounter++;
									curr->pos = curr->checkpointPos;
									curr->isAlive = 1; //player isAlive after respawn
								}

								deathTimer = 100.0f;
								deathTimer *= deathCounter;

								//reset player vel
								player->vel.x = 0;
								player->vel.y = 0;
							}
							else
							{
								GameStateManagerSetNextState(Lose);
							}
							*/
							if (curr->isAlive == 1)
							{
								playSound(false, "Assets/Sounds/player_dies_to_ghost.wav");
								playSound(false, "Assets/Sounds/cat_yelp.wav");
							}
							
							curr->oldpos = curr->pos;
							curr->isAlive = 0; //player dies
							if (tutorialNumLives != 0)
							{
								if (curr->isAlive == 0)
								{
									deathTimer -= dt;

									curr->pos = curr2->pos; //set player to position of enemy
									hookTrigger = 0; //disable the hook
									//player_reset(curr);
								}

								if (deathTimer <= 0)
								{
									tutorialNumLives--;
									curr->pos = curr->checkpointPos;
									curr->isAlive = 1; //player isAlive after respawn
									hookTrigger = 1; //enable hook
									deathTimer = 2.0f; //reset timer because we're alive
								}
							}
							else
							{
								GameStateManagerSetNextState(Lose);
							}
							break;
						}
						case CHECKPOINT:
							if (curr->isAlive == 1 && curr2->isAlive == 1)
							{
								tutorialCheckpoints_lit++;
								playSound(false, "Assets/Sounds/lantern_switch.wav");
								curr2->isAlive = 0; /*turn on light*/
								curr->checkPoint = curr2->id;
								curr->checkpointPos.x = curr2->pos.x;
								curr->checkpointPos.y = curr2->pos.y - 20.0f; /*adjustment places player on ground*/
							}
							break;
							/*player wins*/
						case FINALCHECK:
						{
							/*print metrics*/
							tutorialCheckpoints_lit++;
							AESysPrintf("Time elapsed since start of level: %f seconds\n", (float)(AEFrameRateControllerGetFrameCount() - tutorialStart_frame) * AEFrameRateControllerGetFrameTime());
							AESysPrintf("Ghosts killed: %d\nCheckpoints touched: %d\n", tutorialGhosts_killed, tutorialCheckpoints_lit);
							AESysPrintf("Total distance run: %f\n", tutorialDistance_run);

							GameStateManagerSetNextState(Demo);
							break;
						}
						case SIGN:
						{
							if (curr2->isAlive == 1)
							{
								playSound(false, "Assets/Sounds/final_checkpoint.wav");
								curr2->isAlive = 0; /*can only ring sign once*/
							}
							break;
						}
						default:break;
						}
					}
					curr2 = curr2->next;
					j++;
				}
				break;
			case ENEMY_1: Enemy1Update(curr, dt); break;
			case ENEMY_2: Enemy2Update(curr, dt); break;
			case ENEMY_3: Enemy3Update(curr, dt); break;
			case ENEMY_4: Enemy4Update(curr, dt); break;
			case HOOK:
			{
				/*update hook*/
				hook->pos.x += hook->vel.x;
				hook->pos.y += hook->vel.y;

				/*destroy hook if it gets too far from player*/
				if (((hook->pos.x - player->pos.x) * (hook->pos.x - player->pos.x) +
					(hook->pos.y - player->pos.y) * (hook->pos.y - player->pos.y)) > 90000)
				{
					/*check that hook is not attached to target*/
					k = num_instances(HOOK_TARGET);
					for (j = 0; j < k; ++j)
					{
						curr2 = find_object(HOOK_TARGET, j);
						if (curr2->pos.x == curr->pos.x && curr2->pos.y == curr->pos.y)
							break;
					}

					if (j == k)
					{
						destroy_object(hook->id);
						curr = object_list;
						break;
					}
				}

				curr2 = object_list;
				j = 0;
				while (j < num_objects)
				{
					/*if hook hits something...*/
					if (bounding_box_check(curr, curr2))
					{
						switch (curr2->type)
						{
							/*enemy - destroy enemy and hook*/
						case ENEMY_1:
						case ENEMY_2:
						case ENEMY_3:
						{
							ParticleCreate(curr2);
							playSound(false, "Assets/Sounds/ghost_death.wav");
							tutorialGhosts_killed++;
							destroy_object(curr->id);
							destroy_object(curr2->id);
							curr = object_list;
							curr2 = object_list;
							break;
						}
						case ENEMY_4:
						{
							ParticleCreate(curr2);
							playSound(false, "Assets/Sounds/ghost_death.wav");
							tutorialGhosts_killed++;
							destroy_object(curr->id);
							curr2->type = HOOK_TARGET;
							curr = object_list;
							break;
						}
						default: break;
						}
					}
					curr2 = curr2->next;
					j++;
				}

				break;
			}
			default: break;
			}

			/*move to next object*/
			curr = curr->next;
			i++;
		}
	}

#if 1
	if (hook)
	{
		/*check collision between hook, targets*/
		int num_targets = num_instances(HOOK_TARGET);
		i = 0;
		game_obj* curr_target = find_object(HOOK_TARGET, 0);
		/*precalculate distance between two circles, then add buffer*/
		float min_distance = (hook->width / 2 * tile_dim + curr_target->width / 2 * tile_dim);
		min_distance += 30;

		while (i < num_targets)
		{
			curr_target = find_object(HOOK_TARGET, i);
			/*check grappling hook distance from other target*/
			if (circle_circle_check(hook, curr_target, min_distance))
			{
				/*hook if hook isn't hooked already*/
				if (!hook->hooked) hook->hooked = 1;

				/*set hook position to target position*/
				hook->pos = curr_target->pos;

				/*swing!*/
				hook_swing(player, curr_target);

				/*check that player will not collide with terrain on next frame; destroy if true*/
				/*todo -- work on a better way to do this*/
				player->pos.x += player->vel.x;
				player->pos.y += player->vel.y;
				if (hotspot_check(player) || !AEInputCheckCurr(RI_MOUSE_BUTTON_1_DOWN) /*AEInputCheckTriggered(RI_MOUSE_BUTTON_1_DOWN)*/)
				{
					destroy_object(hook->id);
					hook = NULL;
					break;
				}
				player->pos.x -= player->vel.x;   /*reset player position*/
				player->pos.y -= player->vel.y;
				break;
			}
			++i;
		}
	}
#endif 

	/*update particles*/
	ParticleUpdate(dt);

	/*---------------
	  drawing objects
	  ---------------*/

	  /*render textures*/
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetTransparency(1.0f);

	/* draw bg */
	AEGfxTextureSet(bgTexture, 0.0f, 0.0f);
	AEGfxSetPosition(0.0f, -100.0f);
	AEGfxMeshDraw(pMesh5, AE_GFX_MDM_TRIANGLES);
	/* temporary loop until new bg */
	AEGfxSetPosition(3340.0f, -100.0f);
	AEGfxMeshDraw(pMesh5, AE_GFX_MDM_TRIANGLES);
	AEGfxSetPosition(3340.0f * 2, -100.0f);
	AEGfxMeshDraw(pMesh5, AE_GFX_MDM_TRIANGLES);
	AEGfxSetPosition(3340.0f * 3, -100.0f);
	AEGfxMeshDraw(pMesh5, AE_GFX_MDM_TRIANGLES);
	AEGfxSetPosition(3340.0f * 4, -100.0f);
	AEGfxMeshDraw(pMesh5, AE_GFX_MDM_TRIANGLES);
	AEGfxSetPosition(3340.0f * 5, -100.0f);
	AEGfxMeshDraw(pMesh5, AE_GFX_MDM_TRIANGLES);

	/*draw each tile based on relative position on tilemap*/
	for (i = 0; i < map_height; ++i)
	{
		for (j = 0; j < map_width; ++j)
		{
			/*set transform*/
			AEGfxSetFullTransform((f32)((j + 0.5) * tile_dim - SCREEN_WIDTH / 2),
				(f32)(SCREEN_HEIGHT / 2 - (i + 0.5) * tile_dim), /*account for downward y-axis*/
				0.0f, tile_dim, tile_dim);

			/*set texture color*/
			switch (object_map[i][j])
			{
			case UNCOLLIDABLE_TERRAIN: AEGfxTextureSet(pTexBl, 0.0f, 0.0f); break;
			case COLLIDABLE_TERRAIN: 
				AEGfxTextureSet(tileTexture, 0.0f, 0.0f); break;
			case SPIKES:
				AEGfxTextureSet(spikeTexture, 0.0f, 0.0f);
				break;
			default: break;
			}

			/*draw mesh*/
			if (object_map[i][j] == UNCOLLIDABLE_TERRAIN)
			{
				AEGfxSetTransparency(0.0f);
				AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);
			}
			else if (object_map[i][j] == COLLIDABLE_TERRAIN)
			{
				AEGfxSetTransparency(1.0f);
				AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);
			}
			else if (object_map[i][j] == SPIKES)
			{
				AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);
			}
		}
	}

	/*draw particles*/
	ParticleDraw(pTexW, pMesh1, PLAYER);
	ParticleDraw(pTexP, pMesh1, ENEMY_1);
	ParticleDraw(pTexG, pMesh1, ENEMY_2);
	ParticleDraw(pTexB, pMesh1, ENEMY_3);
	ParticleDraw(pTexY, pMesh1, ENEMY_4);

	/*draw objects if there are any to draw*/
	if (object_list)
	{
		curr = object_list;
		i = 0;
		while (i < num_objects)
		{
			/*set transform*/
			AEGfxSetFullTransform(curr->pos.x, curr->pos.y, 0.0f, (float)curr->width * tile_dim, (float)curr->height * tile_dim);

			/*set texture color*/
			switch (curr->type)
			{
			case HOOK_TARGET: 
				AEGfxTextureSet(hookableTexture, 0.0f, 0.0f);
				AEGfxSetTransparency(1.0f);
				break;
			case PLAYER:
				if (curr->isAlive == 1)
				{
					//player is moving left
					if (player_moving_left() != 0)
					{
						//set texture: Moving
						AEGfxTextureSet(playerWalkTexture, 0.0f, 0.0f);
						AEGfxSetFullTransform(curr->pos.x, curr->pos.y, 0.0f, -(curr->width * tile_dim), curr->height * tile_dim);

						animateFrames(&tutorialCurrentPlayerOffset, &playerTime, 1, dt);
						checkEndFrames(&tutorialCurrentPlayerOffset, 4);
						tutorialCurrPlayerFrame = tutorialCurrentPlayerOffset;
						AEGfxTextureSet(playerWalkTexture, playerOffsets[tutorialCurrPlayerFrame].mX, ghostOffsets[tutorialCurrPlayerFrame].mY);

						tutorialLastPlayerDir = 1;
						isWalking = 1;
					}
					//player is moving right
					else if (player_moving_right() != 0)
					{
						//set texture: Moving
						//AEGfxTextureSet(playerIdleTexture, 0.0f, 0.0f);

						//set texture: Moving
						AEGfxTextureSet(playerWalkTexture, 0.0f, 0.0f);
						AEGfxSetFullTransform(curr->pos.x, curr->pos.y, 0.0f, curr->width * tile_dim, curr->height * tile_dim);

						animateFrames(&tutorialCurrentPlayerOffset, &playerTime, 1, dt);
						checkEndFrames(&tutorialCurrentPlayerOffset, 4);
						tutorialCurrPlayerFrame = tutorialCurrentPlayerOffset;
						AEGfxTextureSet(playerWalkTexture, playerOffsets[tutorialCurrPlayerFrame].mX, ghostOffsets[tutorialCurrPlayerFrame].mY);

						tutorialLastPlayerDir = 0;
						isWalking = 1;
					}
					//player is jumping
					else if (player_jumping() != 0)
					{
						//set texture: Jumping
						AEGfxTextureSet(playerJumpTexture, 0.0f, 0.0f);
						isWalking = 0;
					}
					else
					{
						AEGfxTextureSet(playerIdleTexture, 0.0f, 0.0f);
						isWalking = 0;
					}

					//if the last time player moved was left
					if (!AEInputCheckCurr("A") && tutorialLastPlayerDir == 1 && isWalking == 0)
					{
						//flip the sprite
						AEGfxTextureSet(playerIdleTexture, 0.0f, 0.0f);
						AEGfxSetFullTransform(curr->pos.x, curr->pos.y, 0.0f, -(curr->width * tile_dim), curr->height * tile_dim);
						isWalking = 0;
					}
				}
				else
				{
					AEGfxTextureSet(playerDeathTexture, 0.0f, 0.0f);
					AEGfxSetFullTransform(curr->pos.x, curr->pos.y, 0.0f, curr->width* tile_dim, -(curr->height * tile_dim));
					isWalking = 0;
				}
				break;
			case ENEMY_1:
				if (curr->vel.x != -5.0f)
				{
					AEGfxSetFullTransform(curr->pos.x, curr->pos.y, 0.0f, -(curr->width * tile_dim), curr->height * tile_dim);
				}
				animateFrames(&tutorialCurrentGhostOffset, &ghostTime, 2, dt);
				checkEndFrames(&tutorialCurrentGhostOffset, 2);
				tutorialCurrGhostFrame = tutorialCurrentGhostOffset;
				AEGfxTextureSet(ghostTexture, ghostOffsets[tutorialCurrGhostFrame].mX, ghostOffsets[tutorialCurrGhostFrame].mY);
				AEGfxSetTransparency(1.0f);
				break;
			case ENEMY_2:
				if (curr->vel.y != -5.0f)
				{
					AEGfxSetFullTransform(curr->pos.x, curr->pos.y, 0.0f, -(curr->width * tile_dim), curr->height * tile_dim);
				}
				animateFrames(&tutorialCurrentEnemy2Offset, &enemy2Time, 2, dt);
				checkEndFrames(&tutorialCurrentEnemy2Offset, 2);
				tutorialCurrEnemy2Frame = tutorialCurrentEnemy2Offset;
				AEGfxTextureSet(enemy2Texture, enemy2Offsets[tutorialCurrEnemy2Frame].mX, enemy2Offsets[tutorialCurrEnemy2Frame].mY);
				AEGfxSetTransparency(1.0f);
				break;
			case ENEMY_3:
				if (curr->vel.x != -2.5f)
				{
					AEGfxSetFullTransform(curr->pos.x, curr->pos.y, 0.0f, -(curr->width * tile_dim), curr->height * tile_dim);
				}
				animateFrames(&tutorialCurrentEnemy3Offset, &enemy3Time, 2, dt);
				checkEndFrames(&tutorialCurrentEnemy3Offset, 2);
				tutorialCurrEnemy3Frame = tutorialCurrentEnemy3Offset;
				AEGfxTextureSet(enemy3Texture, enemy3Offsets[tutorialCurrEnemy3Frame].mX, enemy3Offsets[tutorialCurrEnemy3Frame].mY);
				AEGfxSetTransparency(1.0f);
				break;
			case ENEMY_4:
				if (curr->vel.y != -2.5f)
				{
					AEGfxSetFullTransform(curr->pos.x, curr->pos.y, 0.0f, -(curr->width * tile_dim), curr->height * tile_dim);
				}
				animateFrames(&tutorialCurrentEnemy4Offset, &enemy4Time, 2, dt);
				checkEndFrames(&tutorialCurrentEnemy4Offset, 2);
				tutorialCurrEnemy4Frame = tutorialCurrentEnemy4Offset;
				AEGfxTextureSet(enemy4Texture, enemy4Offsets[tutorialCurrEnemy4Frame].mX, enemy4Offsets[tutorialCurrEnemy4Frame].mY);
				AEGfxSetTransparency(1.0f);
				break;
			case CHECKPOINT:
				if (curr->isAlive == 1)
				{
					AEGfxTextureSet(checkpointTexture, 0.0f, 0.0f); /*draw off light*/
					AEGfxSetTransparency(1.0f);
				}
				else if (curr->isAlive == 0)
				{
					AEGfxTextureSet(checkpointTexture2, 0.0f, 0.0f); /*draw on light*/
					AEGfxSetTransparency(1.0f);
				}

				break;
			case HOOK:
				AEGfxTextureSet(hookTexture, 0.0f, 0.0f);
				AEGfxSetTransparency(1.0f);
				break;
			case FINALCHECK: 
				AEGfxTextureSet(finalcheckTexture, 0.0f, 0.0f);
				AEGfxSetTransparency(1.0f); 
				break;
			case SIGN: 
				AEGfxTextureSet(signTexture, 0.0f, 0.0f);
				AEGfxSetTransparency(1.0f); 
				break;
			default:
				AESysPrintf("Invalid object type! Object id is %d\n", curr->id);
				write_to_log(debug_filename, "Breakpoint triggered!\n");
				break;
			}


			/*draw mesh*/
			if (curr->type == HOOK_TARGET || (curr->type == PLAYER && isWalking == 0.0f)|| curr->type == CHECKPOINT || curr->type == HOOK || curr->type == FINALCHECK || curr->type == SIGN)
			{
				AEGfxMeshDraw(pMesh2, AE_GFX_MDM_TRIANGLES);
			}
			else if ((curr->type == PLAYER) && (isWalking == 1.0f))
			{
				AEGfxMeshDraw(pMesh6, AE_GFX_MDM_TRIANGLES);
			}
			else if (curr->type == ENEMY_1 || curr->type == ENEMY_3 || curr->type == ENEMY_4)
			{
				AEGfxMeshDraw(pMesh3, AE_GFX_MDM_TRIANGLES);
			}
			else if (curr->type == ENEMY_2)
			{
				AEGfxMeshDraw(pMesh4, AE_GFX_MDM_TRIANGLES);
			}
			else
			{
				AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);
			}

			/*move to next object*/
			curr = curr->next;
			i++;
		}

	}
	LivesDraw(tutorialMaxLives, tutorialNumLives, playerHeartOn, pMesh2);

	/*draw lines*/
	if (object_list)
	{
		curr = object_list;
		i = 0;
		while (i < num_objects)
		{
			switch (curr->type)
			{
			case PLAYER:
				curr2 = object_list;
				j = 0;
				while (j < num_objects)
				{
					switch (curr2->type)
					{
					case HOOK:

						/*create line*/
						AEGfxMeshStart();

						AEGfxVertexAdd(curr->pos.x, curr->pos.y, 0xFF0000FF, 0.0f, 0.0f);
						AEGfxVertexAdd(curr2->pos.x, curr2->pos.y, 0xFF0000FF, 0.0f, 0.0f);

						AEGfxVertexList* meshLine = AEGfxMeshEnd();
						AE_ASSERT_MESG(meshLine, "Failed to create line!");

						/*draw line*/
						AEGfxSetRenderMode(AE_GFX_RM_COLOR);
						AEGfxSetPosition(0.0f, 0.0f);
						AEGfxMeshDraw(meshLine, AE_GFX_MDM_LINES_STRIP);
						AEGfxMeshFree(meshLine);

						break;
					default: break;
					}
					curr2 = curr2->next;
					j++;
				}
				break;
			default: break;
			}

			/*move to next object*/
			curr = curr->next;
			i++;
		}
	}
}

void TutorialShutdown()
{
	/*free map*/
	maps_destroy();

	// TODO free(debug_filename);

	/*reset metrics data*/
	tutorialStart_frame = 0;
	tutorialGhosts_killed = 0;
	tutorialCheckpoints_lit = 0;
	tutorialDistance_run = 0;

	DestroyContainer();
	// Free all objects.
	destroy_objects_all();
	free(tutorialPlayer);

	AudioCleanup();
}

void TutorialUnload()
{
	// TODO free(debug_filename);

	// Unload all textures.
	AEGfxTextureUnload(pTexR);
	AEGfxTextureUnload(pTexO);
	AEGfxTextureUnload(pTexY);
	AEGfxTextureUnload(pTexG);
	AEGfxTextureUnload(pTexB);
	AEGfxTextureUnload(pTexP);
	AEGfxTextureUnload(pTexI);
	AEGfxTextureUnload(pTexBl);
	AEGfxTextureUnload(pTexW);
	AEGfxTextureUnload(pTexGr);

	AEGfxTextureUnload(tileTexture);
	AEGfxTextureUnload(spikeTexture);
	AEGfxTextureUnload(hookTexture);
	AEGfxTextureUnload(hookableTexture);
	AEGfxTextureUnload(playerIdleTexture);
	AEGfxTextureUnload(playerJumpTexture);
	AEGfxTextureUnload(playerWalkTexture);
	AEGfxTextureUnload(playerDeathTexture);
	AEGfxTextureUnload(playerHeartOn);
	AEGfxTextureUnload(playerHeartAnimation);
	AEGfxTextureUnload(playerHeartOff);
	AEGfxTextureUnload(ghostTexture);
	AEGfxTextureUnload(checkpointTexture);
	AEGfxTextureUnload(checkpointTexture2);
	AEGfxTextureUnload(signTexture);

	// Free all meshes.
	AEGfxMeshFree(pMesh1);
	AEGfxMeshFree(pMesh2);
	AEGfxMeshFree(pMesh3);
	AEGfxMeshFree(pMesh4);
	AEGfxMeshFree(pMesh5);
	AEGfxMeshFree(pMesh6);
	AEGfxMeshFree(pMesh7);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

