//------------------------------------------------------------------------------
/*!
\file	BunBun.cpp
\main author	Hemie, Zak, Riti 
\par	Copyright © 2021 DigiPen (USA) Corporation.
\brief
*/
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------
#include "BunBun.h"
#include "glm/vec3.hpp"
#include "GameObjectManager.h"
#include "Level1.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
static const float PlayerDeathDuration = 4.0f;
const glm::vec3 velocity = { 1,1,1 };
 glm::vec3 gravity(0, 0, 0);

 Audio* playerSoundHolder = 0;
 SOUND_PTR jump = 0;
 SOUND_PTR playerTakingDamage = 0;
 SOUND_PTR playerDeath = 0;
 CHANNEL_PTR playerSoundChannel = 0; // channel for background musics

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
 void BehaviorBunBun::HandleLeftOrRightPressed(glm::vec3* PlayerVel, glm::vec3* PlayerScale, bool LeftKey)
 {
     float SpeedToBeUsed = moveSpeed;
     if (LeftKey)
     {
         SpeedToBeUsed *= -1;;
     }
     // player regular speed
     if (glfwGetKey(GetWindow(), GLFW_KEY_LEFT_CONTROL) != GLFW_PRESS)
     {
         isDashing = false;
         if (canJump && IsThePlayerInAShootingAnimation("Walking") == false)//on the ground and walking
         {
             getParent()->SetCurrentAnimation(1);//play the normal walking animation
         }
         // moving speed slightly decreases while jumping. This is to avoid letting the player jumping multiple platforms at once
         if (isJumping)
         {
             PlayerVel->x = SpeedToBeUsed * 0.75;
         }

         // regular moving speed
         else
         {
             PlayerVel->x = SpeedToBeUsed;
         }
     }

     // player dashing speed when holds pressing the key
     else
     {
         isDashing = true;

         // moving speed slightly decreases while jumping. This is to avoid letting the player jumping multiple platforms at once
         if (isJumping)
         {
             PlayerVel->x = SpeedToBeUsed * (*playerDoc)["Properties"]["DashMuliplierJump"].GetFloat();
         }

         // regular dashing speed
         else
         {
             if (canJump && IsThePlayerInAShootingAnimation("Dashing") == false)//on the ground and walking
             {
                 getParent()->SetCurrentAnimation(11);
             }
             PlayerVel->x = SpeedToBeUsed * (*playerDoc)["Properties"]["DashMuliplierRun"].GetFloat();
         }
     }

     // animation when the player is not jumping
     if (canJump /* && getParent()->GetAnimation()->GetDone() && !getParent()->GetAnimation()->GetLooping()*/)
     {
         //getParent()->SetCurrentAnimation(1);
     }


     if (LeftKey)
     {
         PlayerScale->x = -1 * abs(PlayerScale->x);
     }
     else
     {
         PlayerScale->x = abs(PlayerScale->x);
     }
 }

 bool BehaviorBunBun::IsThePlayerInAShootingAnimation(const char* PlayerCurrentStatus)
 {
     int CurrentAni = getParent()->GetCurrentAnimationIndexInList();
     if ((CurrentAni == 5  || CurrentAni == 7 || CurrentAni == 8)&& strcmp(PlayerCurrentStatus,"Idle") == 0)
     {
         if (getParent()->GetAnimation()->GetDone() == false)
         {
             return true;
         }
     }
     if ((CurrentAni == 12 || CurrentAni == 13 || CurrentAni == 14) && strcmp(PlayerCurrentStatus, "Walking")== 0)
     {
         if (getParent()->GetAnimation()->GetDone() == false)
         {
             return true;
         }
     }
     if ((CurrentAni == 3 || CurrentAni == 9 || CurrentAni == 10) && strcmp(PlayerCurrentStatus, "Dashing") == 0)
     {
         if (getParent()->GetAnimation()->GetDone() == false)
         {
             return true;
         }
     }
     if ((CurrentAni == 6) && strcmp(PlayerCurrentStatus, "Jumping") == 0)
     {
         if (getParent()->GetAnimation()->GetDone() == false)
         {
             return true;
         }
     }
     return false;

 }
BehaviorBunBun::BehaviorBunBun(ImageManager* imgManager, Shader* cameraShader) : ComponentBehavior()
{
    ReadJSONData(&playerDoc, "./TextFiles/PlayerBehavior.json");

		stateNext = (int)PlayerStates::PlayerIdle;
		gravity.y = (*playerDoc)["Properties"]["Gravity"].GetFloat();
		GameObjectPtr thisIsPlayer = GetPlayer();
		thisIsPlayer->SetBehavior(this);		getParent()->SetName("Player");
		playerPhysics = new ComponentPhysics();
		playerTransform = getParent()->GetTransform();
		playerPhysics->SetAcceleration(&gravity);
		playerKnockBackDuration = (*playerDoc)["Properties"]["PlayerKnockBackDuration"].GetFloat();
		playerMaxLives = (*playerDoc)["Properties"]["PlayerMaxLives"].GetInt();
		playerLives = playerMaxLives;
		minimumTimeIntervalPlayerHurt = (*playerDoc)["Properties"]["MinimumTimeIntervalPlayerHurt"].GetFloat();
		playerTimeSinceLastHurt = minimumTimeIntervalPlayerHurt;

		glm::vec3 startPos((*playerDoc)["Properties"]["PlayerSpawnPosX"].GetFloat(), (*playerDoc)["Properties"]["PlayerSpawnPosY"].GetFloat(), 1);
		glm::vec3 startScale((*playerDoc)["Properties"]["PlayerScaleX"].GetFloat(), (*playerDoc)["Properties"]["PlayerScaleY"].GetFloat(), 1);

		//playerCollider = new ComponentCollider((*playerDoc)["Properties"]["PlayerColliderScaleX"].GetFloat(), (*playerDoc)["Properties"]["PlayerColliderScaleY"].GetFloat(), true, true, true);
		playerCollider = new ComponentCollider((*playerDoc)["Properties"]["PlayerColliderScaleX"].GetFloat(), (*playerDoc)["Properties"]["PlayerColliderScaleY"].GetFloat(), true, true, true, false);
		//the collider box is 1x1. if the transform is scaled, the collider box will also be scaled by that much
		getParent()->SetCollider(playerCollider);
		playerCollider->SetParent(getParent());
		playerCollider->ComponentColliderBoxSetContactWithGroundFunction(ResetJump);

		playerTransform->SetPosition(&startPos);
		playerTransform->SetScale(&startScale);

		getParent()->SetPhysics(playerPhysics);

		
		getParent()->CreateAndAddAnimation((*playerDoc)["Idle"]["AnimationFile"].GetString(), (*playerDoc)["Idle"]["SpriteSourceFile"].GetString(), imgManager, cameraShader);//0 = idle
		getParent()->CreateAndAddAnimation((*playerDoc)["Walk"]["AnimationFile"].GetString(), (*playerDoc)["Walk"]["SpriteSourceFile"].GetString(), imgManager, cameraShader);//1 = walk
		getParent()->CreateAndAddAnimation((*playerDoc)["Jump"]["AnimationFile"].GetString(), (*playerDoc)["Jump"]["SpriteSourceFile"].GetString(), imgManager, cameraShader);//2 = jump
        getParent()->CreateAndAddAnimation((*playerDoc)["Shooting Idle"]["AnimationFile"].GetString(), (*playerDoc)["Shooting Idle"]["SpriteSourceFile"].GetString(), imgManager, cameraShader); //3 =  shooting dashing
        getParent()->CreateAndAddAnimation((*playerDoc)["Death"]["AnimationFile"].GetString(), (*playerDoc)["Death"]["SpriteSourceFile"].GetString(), imgManager, cameraShader); // 4 = death
        getParent()->CreateAndAddAnimation((*playerDoc)["Shooting Moving"]["AnimationFile"].GetString(), (*playerDoc)["Shooting Moving"]["SpriteSourceFile"].GetString(), imgManager, cameraShader); //5 shooting idle
        getParent()->CreateAndAddAnimation((*playerDoc)["Shooting Jump"]["AnimationFile"].GetString(), (*playerDoc)["Shooting Jump"]["SpriteSourceFile"].GetString(), imgManager, cameraShader); //6 shooting jumping
        getParent()->CreateAndAddAnimation((*playerDoc)["Shooting Up Idle"]["AnimationFile"].GetString(), (*playerDoc)["Shooting Up Idle"]["SpriteSourceFile"].GetString(), imgManager, cameraShader); //7 shooting up idle
        getParent()->CreateAndAddAnimation((*playerDoc)["Shooting Down Idle"]["AnimationFile"].GetString(), (*playerDoc)["Shooting Down Idle"]["SpriteSourceFile"].GetString(), imgManager, cameraShader); //8 shooting down idle
        getParent()->CreateAndAddAnimation((*playerDoc)["Shooting Up Moving"]["AnimationFile"].GetString(), (*playerDoc)["Shooting Up Moving"]["SpriteSourceFile"].GetString(), imgManager, cameraShader); //9 shooting up dashing
        getParent()->CreateAndAddAnimation((*playerDoc)["Shooting Down Moving"]["AnimationFile"].GetString(), (*playerDoc)["Shooting Down Moving"]["SpriteSourceFile"].GetString(), imgManager, cameraShader); //10 shooting down dashing
        getParent()->CreateAndAddAnimation((*playerDoc)["Run"]["AnimationFile"].GetString(), (*playerDoc)["Run"]["SpriteSourceFile"].GetString(), imgManager, cameraShader); //11 dash/run
        getParent()->CreateAndAddAnimation((*playerDoc)["Shooting Walk"]["AnimationFile"].GetString(), (*playerDoc)["Shooting Walk"]["SpriteSourceFile"].GetString(), imgManager, cameraShader); //12 shooting walk neutral
        getParent()->CreateAndAddAnimation((*playerDoc)["Shooting Up Walk"]["AnimationFile"].GetString(), (*playerDoc)["Shooting Up Walk"]["SpriteSourceFile"].GetString(), imgManager, cameraShader); //13 shooting walk up
        getParent()->CreateAndAddAnimation((*playerDoc)["Shooting Down Walk"]["AnimationFile"].GetString(), (*playerDoc)["Shooting Down Walk"]["SpriteSourceFile"].GetString(), imgManager, cameraShader); //14 shooting walk down
        getParent()->CreateAndAddAnimation((*playerDoc)["Hurt"]["AnimationFile"].GetString(), (*playerDoc)["Hurt"]["SpriteSourceFile"].GetString(), imgManager, cameraShader); //15 player getting hurt

        //Player Walk: 
		getParent()->SetCurrentAnimation(0);

		// animation
		playerAnimation = new Animation;
		char playerAnimationName[FILENAME_MAX] = "";
		sprintf_s(playerAnimationName, _countof(playerAnimationName), "./TextFiles/playerAni.txt");
		Stream PlayerAnimStream = StreamOpen(playerAnimationName);
		playerAnimation->ReadAni(PlayerAnimStream);
		playerAnimation->Parent(getParent());

		// sprite
		playerSpriteSource = new SpriteSource(9, 3, playerGraphics->get_texture());
		playerSprite->SetSpriteSource(playerSpriteSource);

		playerAnimation->Play();

    // set player's data from the file
    jumpSpeed = (*playerDoc)["Properties"]["JumpVel"].GetFloat();
    moveSpeed = (*playerDoc)["Properties"]["HorizontalVel"].GetFloat();

    playerStats = { 0,0,0,0,0 };

    canJump = true;
    canDoubleJump = true;
    isJumping = false;
    isDashing = false;
    playerSoundChannel = 0;

    // audio
    char audio_path[FILENAME_MAX] = "";

    playerSoundHolder = new Audio();

    // audio for player jump
    sprintf_s(audio_path, _countof(audio_path), (*playerDoc)["Audio"]["Jump"].GetString());
    Stream bushesSound = StreamOpen(audio_path);
    jump = playerSoundHolder->Load(bushesSound, FMOD_DEFAULT);

    sprintf_s(audio_path, _countof(audio_path), (*playerDoc)["Audio"]["TakingDamage"].GetString());
    Stream damageSound = StreamOpen(audio_path);
    playerTakingDamage = playerSoundHolder->Load(damageSound, FMOD_DEFAULT);

    sprintf_s(audio_path, _countof(audio_path), (*playerDoc)["Audio"]["Death"].GetString());
    Stream deathSound = StreamOpen(audio_path);
    playerDeath = playerSoundHolder->Load(deathSound, FMOD_DEFAULT);
}

BehaviorBunBun::~BehaviorBunBun(void)
{
    if (playerSoundHolder)
    {
        delete(playerSoundHolder);
        playerSoundHolder = 0;
    }
}

void BehaviorBunBun::onInit()
{
    playerDead = false;

		if (stateCurr == (int)PlayerStates::PlayerInvalid)
		{
		}
		else if (stateCurr == (int)PlayerStates::PlayerDead)
		{
				timeDelta = PlayerDeathDuration;

				getParent()->GetSprite()->SetAlpha(0.25f);

				getParent()->GetPhysics()->SetVelocity(&velocity);
		}
}

void BehaviorBunBun::onUpdate(float dt)
{
    checkPlayerInput(dt);
    
}

void BehaviorBunBun::onExit()
{
}

void BehaviorBunBun::checkPlayerInput(float dt)
{
    if (!playerDead)
    {
        // make sure if the player exists 
        if (getParent()->GetPhysics())
        {
            glm::vec3 LocalVel(0, 0, 0);
            glm::vec3 LocalScale(0, 0, 0);

            glm::vec3* PlayerVelLocalCopy = &LocalVel;
            glm::vec3* PlayerScaleLocalCopy = &LocalScale;

            // getting player data fromt the game object
            *PlayerVelLocalCopy = *(getParent()->GetPhysics()->GetVelocity());
            *PlayerScaleLocalCopy = *(getParent()->GetTransform()->GetScale());

            // when the game is playing
            if (GetLevelOnePause() == false)
            {
                //not in knockback
                if (playerTimeSinceLastHurt > playerKnockBackDuration)
                {
                    // player JUMP
                    if (glfwGetKey(GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && canJump)
                    {
                        TraceMessage("Input", "space pressed down");
                        //keyPSystem->Emit(keyPPattern);
                        // regular jumping speed for the first jump
                        if (PlayerNoClip == false)
                        {
                            PlayerVelLocalCopy->y = jumpSpeed;
                        }
                        canJump = false;
                        isJumping = true;

                        playerStats.numJumps++;

                        // PLAY THE SOUND OF THE PLAYER JUMPING HERE
                        playerSoundHolder->Play(jump, &playerSoundChannel);
                        playerSoundHolder->ChangeVolume(playerSoundChannel, 1.0f);
                    }


                    // only checks for the next "w" key check when the player is currently jumping
                    if (isJumping)
                    {
                        isDashing = false;
                        // start jumping timer
                        jumpDT += dt;
                        // makes sure this is the second jump
                        if (glfwGetKey(GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && jumpDT > 0.5f && canJump == false && canDoubleJump == true)
                        {
                            canDoubleJump = false;

                            playerStats.numDoubleJumps++;

                            // sets it to a non-jumping animation just for sec so that jump animation starts over 
                            getParent()->SetCurrentAnimation(0);

                            // slightly increase the jumping speed for the double jump
                            if (PlayerNoClip == false)
                            {
                                PlayerVelLocalCopy->y = jumpSpeed * 1.1;
                            }

                            // makes another jumping sound
                            playerSoundHolder->Play(jump, &playerSoundChannel);
                            playerSoundHolder->ChangeVolume(playerSoundChannel, 1.0f);
                        }
                    }

                    // player moving LEFT
                    if (glfwGetKey(GetWindow(), GLFW_KEY_A) == GLFW_PRESS /*|| glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS*/)
                    {
                        TraceMessage("Input", "a pressed down");

                        // starts holding key timer
                        pressingAdt += dt;

                        HandleLeftOrRightPressed(PlayerVelLocalCopy, PlayerScaleLocalCopy, true);
                        //soundHolder->Play(walking, channelOne);
                    }

                    // player moving RIGHT
                    else if (glfwGetKey(GetWindow(), GLFW_KEY_D) == GLFW_PRESS /*| glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS */)
                    {
                        TraceMessage("Input", "d pressed down");

                        // starts holding key timer
                        pressingDdt += dt;

                        HandleLeftOrRightPressed(PlayerVelLocalCopy, PlayerScaleLocalCopy, false);

                    }

                    // player NOT moving
                    else
                    {
                        PlayerVelLocalCopy->x = 0;
                        //if standing on the ground
                        if (canJump /* && getParent()->GetAnimation()->GetDone() && !getParent()->GetAnimation()->GetLooping() */)
                        {

                            if (IsThePlayerInAShootingAnimation("Idle") == false)
                            {
                                getParent()->SetCurrentAnimation(0);
                            }
                        }
                    }

                    // resets "D" holding timer when the key is released
                    if (glfwGetKey(GetWindow(), GLFW_KEY_D) == GLFW_RELEASE)
                    {
                        pressingDdt = 0.0f;
                    }

                    // resets "A" holding timer when the key is released
                    {
                        pressingAdt = 0.0f;
                    }

                    if (glfwGetKey(GetWindow(), GLFW_KEY_A) == GLFW_RELEASE && glfwGetKey(GetWindow(), GLFW_KEY_D) == GLFW_RELEASE)
                    {
                        isDashing = false;
                    }

                    // setting JUMP animation 
                    if (!canJump || !canDoubleJump)
                    {
                        if (IsThePlayerInAShootingAnimation("Jumping") == false)
                        {
                            getParent()->SetCurrentAnimation(2);
                        }
                    }

                    // update new playermvelocity and scale
                    getParent()->GetPhysics()->SetVelocity(PlayerVelLocalCopy);
                    getParent()->GetTransform()->SetScale(PlayerScaleLocalCopy);

                    // check player's death
                    if (playerLives == 0)
                    {
                        playerSoundHolder->Play(playerDeath, &playerSoundChannel);
                        playerDead = true;
                        getParent()->SetCurrentAnimation(4);
                    }
                }
                else //the player is currently in knockbach
                {
                    playerSoundHolder->Play(playerTakingDamage, &playerSoundChannel);
                    getParent()->SetCurrentAnimation(15);//getting hurt animation
                }
            }
        }
    }
    else
    {
        if (getParent()->GetAnimation()->GetDone())
        {
            playerStats.numDeaths++;
            playerDead = true;
            GameStateManagerSetNextState(GameStates::GsLose);
        }
    }
}

rapidjson::Document* BehaviorBunBun::getPlayerDoc()
{
    return playerDoc;
}

BehaviorBunBun::PlayerStats BehaviorBunBun::getPlayerStat()
{
    return playerStats;
}
