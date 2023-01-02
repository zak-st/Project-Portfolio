//------------------------------------------------------------------------------
// Project Name		:	Nook		
// File Name		:	Enemy.c
// Author(s)		:	Zak Stephenson
// Creation Date	:	19 Feb 2021
// Purpose			:	Manages the enemy functions
// History			:
// - 19 Feb 2021	:	- initial implementation
// All content © 2021 DigiPen (USA) Corporation, all rights reserved.
// -----------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "framework.h"
#include <stdlib.h>
#include "AEEngine.h"
#include <fmod.h>
#include "GameStateManager.h"
#include "Enemy.h"
#include "object_data.h"
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
void EnemyTimerInit(game_obj* enemy)
{
	if (enemy != NULL)
	{
		enemy->timer = 0;
	}
}
void Enemy1Update(game_obj* enemy, float dt)
{
	enemy->timer += dt;
	enemy->pos.x += enemy->vel.x;
	if (enemy->timer >= 1.0f)
	{
		enemy->vel.x *= -1;
		enemy->timer = 0.0f;
	}
}

void Enemy2Update(game_obj* enemy, float dt)
{
	enemy->timer += dt;
	enemy->pos.y += enemy->vel.y;
	if (enemy->timer >= 1.0f)
	{
		enemy->vel.y *= -1;
		enemy->timer = 0.0f;
	}
}

void Enemy3Update(game_obj* enemy, float dt)
{
	enemy->timer += dt;
	enemy->pos.x += enemy->vel.x;
	if (enemy->timer >= 2.0f)
	{
		enemy->vel.x *= -1;
		enemy->timer = 0.0f;
	}
}

void Enemy4Update(game_obj* enemy, float dt)
{
	enemy->timer += dt;
	enemy->pos.y += enemy->vel.y;
	if (enemy->timer >= 0.75f)
	{
		enemy->vel.y *= -1;
		enemy->timer = 0.0f;
	}
}


float DistanceCheck(vec2 p1, vec2 p2)
{
	float xDiff = (p2.x - p1.x) * (p2.x - p1.x);
	float yDiff = (p2.y - p1.y) * (p2.y - p1.y);
	return xDiff + yDiff;
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------