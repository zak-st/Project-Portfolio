//------------------------------------------------------------------------------
// Project Name		:	Nook		
// File Name		:	Particle.c
// Author(s)		:	Primary: Zak Stephenson | Secondary: Justin W Li
// Creation Date	:	11 March 2021
// Purpose			:	Implementation for Particle.c
// History			:
// - 11 March 2021	:	- initial implementation
// All content © 2021 DigiPen (USA) Corporation, all rights reserved.
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "framework.h"
#include "AEEngine.h"
#include <fmod.h>
#include <stdlib.h>
#include "GameStateManager.h"
#include "Particle.h"
#include "object_data.h"
#include <time.h>
#include "map.h"
//------------------------------------------------------------------------------
// Private Consts:
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
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
void ParticleCreate(game_obj* obj)
{
	if (obj->type == PLAYER || obj->type == ENEMY_1 || obj->type == ENEMY_2 || obj->type == ENEMY_3 || obj->type == ENEMY_4)
	{
		if (container == NULL)
		{
			container = (ParticleSystem*)malloc(sizeof(ParticleSystem));
			if (container == NULL)
			{
				AESysPrintf("System Creation Failed!!");
				return;
			}
		}
		else
		{
			ParticleSystem* temp;
			temp = (ParticleSystem*)malloc(container, sizeof(ParticleSystem) * numSystems + 1);
			if (temp == NULL)
			{
				AESysPrintf("System realloc Failed!!\n");
				return;
			}

			/*copy over old system*/
			for (int i = 0; i < numSystems; ++i)
			{
				temp[i] = container[i];
			}
			free(container);
			container = temp;
		}
		switch (obj->type)
		{
		case PLAYER:
			container[numSystems].ParticleCount = 25;
			break;
		case ENEMY_1:
		case ENEMY_2:
		case ENEMY_3:
		case ENEMY_4:
			container[numSystems].ParticleCount = 50;
			break;
		default:
			container[numSystems].ParticleCount = 10;
			break;
		}
		container[numSystems].ParticleList = (Particle*)malloc(sizeof(Particle) * container[numSystems].ParticleCount);
		if (container[numSystems].ParticleList == NULL)
		{
			AESysPrintf("Particle Creation Failed!!");
		}
		/*create seed*/
		srand(time(0));
		for (int i = 0; i < container[numSystems].ParticleCount; i++)
		{
			switch (obj->type)
			{
			case PLAYER:
				container[numSystems].ParticleList[i].velocity.x = (float)((rand() % (PlayerDustParticleVelocityMax - PlayerDustParticleVelocityMin + 1) + PlayerDustParticleVelocityMin));
																					 //* ((rand() % 2) ? 1 : -1)); /*50/50 to be positive or negative*/
				container[numSystems].ParticleList[i].velocity.y = (float)(rand() % (PlayerDustParticleVelocityMax - PlayerDustParticleVelocityMin + 1) + PlayerDustParticleVelocityMin);
				container[numSystems].ParticleList[i].lifetime = (float)(rand() % (PlayerDustParticleLifetimeMax - PlayerDustParticleLifetimeMin + 1) + PlayerDustParticleLifetimeMin);
				container[numSystems].ParticleList[i].scale = (float)(rand() % (PlayerDustParticleScaleMax - PlayerDustParticleScaleMin  + 1) + PlayerDustParticleScaleMin) / 10;
				container[numSystems].ParticleList[i].alive = 1;
				container[numSystems].ParticleList[i].position.x = obj->pos.x;
				container[numSystems].ParticleList[i].position.y = obj->pos.y - obj->height * tile_dim / 2;
				container[numSystems].ParticleList[i].type = PLAYER;
				break;
			case ENEMY_1:
				container[numSystems].ParticleList[i].velocity.x = (float)(rand() % EnemyParticleVelocityMax - EnemyParticleVelocityMin);
				container[numSystems].ParticleList[i].velocity.y = (float)(rand() % EnemyParticleVelocityMax - EnemyParticleVelocityMin);
				container[numSystems].ParticleList[i].lifetime = (float)(rand() % EnemyParticleLifetimeMax - EnemyParticleLifetimeMin);
				container[numSystems].ParticleList[i].scale = (float)(rand() % EnemyParticleScaleMax - EnemyParticleScaleMin);
				container[numSystems].ParticleList[i].alive = 1;
				container[numSystems].ParticleList[i].position.x = obj->pos.x;
				container[numSystems].ParticleList[i].position.y = obj->pos.y;
				container[numSystems].ParticleList[i].type = ENEMY_1;
				break;
			case ENEMY_2:
				container[numSystems].ParticleList[i].velocity.x = (float)(rand() % EnemyParticleVelocityMax - EnemyParticleVelocityMin);
				container[numSystems].ParticleList[i].velocity.y = (float)(rand() % EnemyParticleVelocityMax - EnemyParticleVelocityMin);
				container[numSystems].ParticleList[i].lifetime = (float)(rand() % EnemyParticleLifetimeMax - EnemyParticleLifetimeMin);
				container[numSystems].ParticleList[i].scale = (float)(rand() % EnemyParticleScaleMax - EnemyParticleScaleMin);
				container[numSystems].ParticleList[i].alive = 1;
				container[numSystems].ParticleList[i].position.x = obj->pos.x;
				container[numSystems].ParticleList[i].position.y = obj->pos.y;
				container[numSystems].ParticleList[i].type = ENEMY_2;
				break;
			case ENEMY_3:
				container[numSystems].ParticleList[i].velocity.x = (float)(rand() % EnemyParticleVelocityMax - EnemyParticleVelocityMin);
				container[numSystems].ParticleList[i].velocity.y = (float)(rand() % EnemyParticleVelocityMax - EnemyParticleVelocityMin);
				container[numSystems].ParticleList[i].lifetime = (float)(rand() % EnemyParticleLifetimeMax - EnemyParticleLifetimeMin);
				container[numSystems].ParticleList[i].scale = (float)(rand() % EnemyParticleScaleMax - EnemyParticleScaleMin);
				container[numSystems].ParticleList[i].alive = 1;
				container[numSystems].ParticleList[i].position.x = obj->pos.x;
				container[numSystems].ParticleList[i].position.y = obj->pos.y;
				container[numSystems].ParticleList[i].type = ENEMY_3;
				break;
			case ENEMY_4:
				container[numSystems].ParticleList[i].velocity.x = (float)(rand() % EnemyParticleVelocityMax - EnemyParticleVelocityMin);
				container[numSystems].ParticleList[i].velocity.y = (float)(rand() % EnemyParticleVelocityMax - EnemyParticleVelocityMin);
				container[numSystems].ParticleList[i].lifetime = (float)(rand() % EnemyParticleLifetimeMax - EnemyParticleLifetimeMin);
				container[numSystems].ParticleList[i].scale = (float)(rand() % EnemyParticleScaleMax - EnemyParticleScaleMin);
				container[numSystems].ParticleList[i].alive = 1;
				container[numSystems].ParticleList[i].position.x = obj->pos.x;
				container[numSystems].ParticleList[i].position.y = obj->pos.y;
				container[numSystems].ParticleList[i].type = ENEMY_4;
				break;
			default:
				break;
			}
		}
		numSystems++;
	}
	else
	{
		AESysPrintf("Invalid Object Type!!");
		return;
	}
}



void ParticleUpdate(float dt)
{
	if (container == NULL)
	{
		return;
	}
	int deadParticles = 0;
	for (int systemIndex = 0; systemIndex < numSystems; systemIndex++)
	{
		for (int particleIndex = 0; particleIndex < container[systemIndex].ParticleCount; particleIndex++)
		{
			/*if particles are alive*/
			if (container[systemIndex].ParticleList[particleIndex].lifetime > 0)
			{
				container[systemIndex].ParticleList[particleIndex].lifetime--;
				container[systemIndex].ParticleList[particleIndex].position.x += container[systemIndex].ParticleList[particleIndex].velocity.x * dt;
				container[systemIndex].ParticleList[particleIndex].position.y += container[systemIndex].ParticleList[particleIndex].velocity.y * dt;
			}
			else
			{
				/*mark particles as dead*/
				container[systemIndex].ParticleList[particleIndex].alive = 0;
				deadParticles++;
			}
		}
		if (deadParticles == container[systemIndex].ParticleCount)
		{
			DestroySystem(systemIndex);
		}
	}
}

void DestroySystem(int systemNum)
{
	ParticleSystem* temp;

	if (container[systemNum].ParticleList != NULL)
	{
		free(container[systemNum].ParticleList);
		container[systemNum].ParticleList = NULL;
		container[systemNum].ParticleCount = 0;
	}
	--numSystems;

	if (numSystems)
	{
		/*copy over all systems to temp container except for deleted row*/
		temp = (ParticleSystem*)malloc(sizeof(ParticleSystem) * numSystems);
		for (int i = 0; i < systemNum; ++i)	temp[i] = container[i];
		for (int i = systemNum; i < numSystems; ++i) temp[i] = container[i + 1];

		/*replace container with temp*/
		free(container);
		container = temp;
	}
	else
	{
		free(container);
		container = NULL;
	}
}

void DestroyContainer(void)
{
	for (int i = 0; i < numSystems; i++)
	{
		DestroySystem(i);
	}
	container = NULL;
	numSystems = 0;
}

void ParticleDraw(AEGfxTexture* texture, AEGfxVertexList* mesh, int type)
{
	if (container == NULL)
	{
		return;
	}
	if (texture == NULL || mesh == NULL)
	{
		AESysPrintf("Missing texture or Mesh!!");
		return;
	}
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	for (int systemIndex = 0; systemIndex < numSystems; systemIndex++)
	{
		if (container[systemIndex].ParticleList != NULL && container[systemIndex].ParticleList[0].type == type)
		{
			for (int particleIndex = 0; particleIndex < container[systemIndex].ParticleCount; particleIndex++)
			{
				if (container[systemIndex].ParticleList[particleIndex].alive)
				{
					AEGfxSetFullTransform(container[systemIndex].ParticleList[particleIndex].position.x,
						container[systemIndex].ParticleList[particleIndex].position.y, 0.0f,
						container[systemIndex].ParticleList[particleIndex].scale,
						container[systemIndex].ParticleList[particleIndex].scale);
					AEGfxTextureSet(texture, 0.0f, 0.0f);
					AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
				}
			}
		}
	}
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------