//---------------------------------------------------------
// file:	gamestate_level3.c
// author:	Mary Khuu, Rey Rosario, Zak Stephenson
// course:	GAM100
//
// brief:	level three of the game
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "gamestate_level3.h"
#include "gamestate_level2.h"
#include "gamestate_level1.h"
#include "gamestate_hub.h"
#include "gamestate_win.h"
#include "gamestate_lose.h"
#include "map_assets.h"
#include "player.h"

CP_Image rock = NULL;
CP_Image rock2 = NULL;
CP_Image rock3 = NULL;
CP_Image level3Ship = NULL;

void drawMaze3(float xAxis, float yAxis, float multiplier)
{
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));

	/*outline of maze drawn based on given x and y position, maze is 7x6*/
	CP_Graphics_DrawLine(xAxis, yAxis, xAxis, yAxis + 6 * multiplier);
	CP_Graphics_DrawLine(xAxis, yAxis, xAxis + 7 * multiplier, yAxis);
	CP_Graphics_DrawLine(xAxis + 7 * multiplier, yAxis, xAxis + 7 * multiplier, yAxis + 6 * multiplier);
	CP_Graphics_DrawLine(xAxis, yAxis + 6 * multiplier, xAxis + 7 * multiplier, yAxis + 6 * multiplier);

	/*horizontal lines for first row from bottom*/
	CP_Graphics_DrawLine(xAxis + multiplier, yAxis + 5 * multiplier, xAxis + 4 * multiplier, yAxis + 5 * multiplier);
	CP_Graphics_DrawLine(xAxis + 6 * multiplier, yAxis + 5 * multiplier, xAxis + 7 * multiplier, yAxis + 5 * multiplier);

	CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 255));

	/*horizontal lines for second row from bottom*/
	CP_Graphics_DrawLine(xAxis + 2 * multiplier, yAxis + 4 * multiplier, xAxis + 3 * multiplier, yAxis + 4 * multiplier);
	CP_Graphics_DrawLine(xAxis + 4 * multiplier, yAxis + 4 * multiplier, xAxis + 5 * multiplier, yAxis + 4 * multiplier);

	CP_Settings_Stroke(CP_Color_Create(0, 255, 0, 255));

	/*vertical lines for second row from bottom*/
	CP_Graphics_DrawLine(xAxis + multiplier, yAxis + 3 * multiplier, xAxis + multiplier, yAxis + 5 * multiplier);
	CP_Graphics_DrawLine(xAxis + 6 * multiplier, yAxis + 3 * multiplier, xAxis + 6 * multiplier, yAxis + 5 * multiplier);

	CP_Settings_Stroke(CP_Color_Create(0, 0, 255, 255));

	/*horizontal lines for third row from bottom*/
	CP_Graphics_DrawLine(xAxis, yAxis + 3 * multiplier, xAxis + 3 * multiplier, yAxis + 3 * multiplier);

	CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 255));

	/*vertical lines for third row from bottom*/
	CP_Graphics_DrawLine(xAxis + 2 * multiplier, yAxis + 3 * multiplier, xAxis + 2 * multiplier, yAxis + 4 * multiplier);
	CP_Graphics_DrawLine(xAxis + 4 * multiplier, yAxis + 2 * multiplier, xAxis + 4 * multiplier, yAxis + 4 * multiplier);
	CP_Graphics_DrawLine(xAxis + 5 * multiplier, yAxis + 2 * multiplier, xAxis + 5 * multiplier, yAxis + 5 * multiplier);

	CP_Settings_Stroke(CP_Color_Create(0, 255, 0, 255));

	/*horizontal lines for fourth row from bottom*/
	CP_Graphics_DrawLine(xAxis + multiplier, yAxis + 2 * multiplier, xAxis + 3 * multiplier, yAxis + 2 * multiplier);
	CP_Graphics_DrawLine(xAxis + 5 * multiplier, yAxis + 2 * multiplier, xAxis + 6 * multiplier, yAxis + 2 * multiplier);

	CP_Settings_Stroke(CP_Color_Create(0, 0, 255, 255));

	/*vertical lines for fourth row from bottom*/
	CP_Graphics_DrawLine(xAxis + multiplier, yAxis + multiplier, xAxis + multiplier, yAxis + 2 * multiplier);
	CP_Graphics_DrawLine(xAxis + 6 * multiplier, yAxis, xAxis + 6 * multiplier, yAxis + 2 * multiplier);

	CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 255));

	/*horizontal lines for fifth row from bottom*/
	CP_Graphics_DrawLine(xAxis + multiplier, yAxis + multiplier, xAxis + 3 * multiplier, yAxis + multiplier);
	CP_Graphics_DrawLine(xAxis + 4 *multiplier, yAxis + multiplier, xAxis + 5 * multiplier, yAxis + multiplier);

	CP_Settings_Stroke(CP_Color_Create(0, 255, 0, 255));

	/*vertical lines for fourth row from bottom*/
	CP_Graphics_DrawLine(xAxis + multiplier, yAxis + multiplier, xAxis + multiplier, yAxis + 2 * multiplier);

	CP_Settings_Stroke(CP_Color_Create(0, 0, 255, 255));

	/*vertical lines for fifth and final row from bottom*/
	CP_Graphics_DrawLine(xAxis + 3 * multiplier, yAxis, xAxis + 3 * multiplier, yAxis + multiplier);
}

void addMazeCollision3(float xAxis, float yAxis, float multiplier)
{
	float rightSide = playerPos.x + playerWidth;
	float leftSide = playerPos.x - playerWidth;
	float topSide = playerPos.y - playerWidth;
	float botSide = playerPos.y + playerWidth;

	/*collision for outline of maze*/
	if (leftSide == xAxis)
	{
		if (CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}
	if (rightSide == xAxis + 7 * multiplier)
	{
		if (CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}
	if (topSide == yAxis)
	{
		if (CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}
	if (botSide == yAxis + 6 * multiplier)
	{
		if (CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first horizontal line, first row from bottom*/
	if ((topSide == yAxis + 5 * multiplier || botSide == yAxis + 5 * multiplier) && (playerPos.x > xAxis + multiplier && playerPos.x < xAxis + 4 * multiplier))
	{
		if (topSide == yAxis + 5 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 5 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	if ((topSide == yAxis + 5 * multiplier || botSide == yAxis + 5 * multiplier) && (playerPos.x > xAxis + 6 * multiplier && playerPos.x < xAxis + 7 * multiplier))
	{
		if (topSide == yAxis + 5 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 5 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first verticle line, second row from bottom*/
	if ((leftSide == xAxis + multiplier || rightSide == xAxis + multiplier) && (playerPos.y > yAxis + 3 * multiplier && playerPos.y < yAxis + 5 * multiplier))
	{
		if (rightSide == xAxis + multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	if ((leftSide == xAxis + 6 * multiplier || rightSide == xAxis + 6 * multiplier) && (playerPos.y > yAxis + 3 * multiplier && playerPos.y < yAxis + 5 * multiplier))
	{
		if (rightSide == xAxis + 6 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 6 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first horizontal line, second row from bottom*/
	if ((topSide == yAxis + 4 * multiplier || botSide == yAxis + 4 * multiplier) && (playerPos.x > xAxis + 2 * multiplier && playerPos.x < xAxis + 3 * multiplier))
	{
		if (topSide == yAxis + 4 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 4 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	if ((topSide == yAxis + 4 * multiplier || botSide == yAxis + 4 * multiplier) && (playerPos.x > xAxis + 4 * multiplier && playerPos.x < xAxis + 5 * multiplier))
	{
		if (topSide == yAxis + 4 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 4 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first verticle line, third row from bottom*/
	if ((leftSide == xAxis + 2 * multiplier || rightSide == xAxis + 2 * multiplier) && (playerPos.y > yAxis + 3 * multiplier && playerPos.y < yAxis + 4 * multiplier))
	{
		if (rightSide == xAxis + 2 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 2 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	if ((leftSide == xAxis + 4 * multiplier || rightSide == xAxis + 4 * multiplier) && (playerPos.y > yAxis + 2 * multiplier && playerPos.y < yAxis + 4 * multiplier))
	{
		if (rightSide == xAxis + 4 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 4 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	if ((leftSide == xAxis + 5 * multiplier || rightSide == xAxis + 5 * multiplier) && (playerPos.y > yAxis + 2 * multiplier && playerPos.y < yAxis + 5 * multiplier))
	{
		if (rightSide == xAxis + 5 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 5 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first horizontal line, third row from bottom*/
	if ((topSide == yAxis + 3 * multiplier || botSide == yAxis + 3 * multiplier) && (playerPos.x > xAxis && playerPos.x < xAxis + 3 * multiplier))
	{
		if (topSide == yAxis + 3 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 3 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first horizontal line, fourth row from bottom*/
	if ((topSide == yAxis + 2 * multiplier || botSide == yAxis + 2 * multiplier) && (playerPos.x > xAxis + multiplier && playerPos.x < xAxis + 3 * multiplier))
	{
		if (topSide == yAxis + 2 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 2 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	if ((topSide == yAxis + 2 * multiplier || botSide == yAxis + 2 * multiplier) && (playerPos.x > xAxis + 5 * multiplier && playerPos.x < xAxis + 6 * multiplier))
	{
		if (topSide == yAxis + 2 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 2 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first verticle line, fifth row from bottom*/
	if ((leftSide == xAxis + multiplier || rightSide == xAxis + multiplier) && (playerPos.y > yAxis + multiplier && playerPos.y < yAxis + 2 * multiplier))
	{
		if (rightSide == xAxis + multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first horizontal line, sixth/last row from bottom*/
	if ((topSide == yAxis + multiplier || botSide == yAxis + multiplier) && (playerPos.x > xAxis + multiplier && playerPos.x < xAxis + 3 * multiplier))
	{
		if (topSide == yAxis + multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	if ((topSide == yAxis + multiplier || botSide == yAxis + multiplier) && (playerPos.x > xAxis + 4 * multiplier && playerPos.x < xAxis + 5 * multiplier))
	{
		if (topSide == yAxis + multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first verticle line, fifth row from bottom*/
	if ((leftSide == xAxis + 3 * multiplier || rightSide == xAxis + 3 * multiplier) && (playerPos.y > yAxis && playerPos.y < yAxis + multiplier))
	{
		if (rightSide == xAxis + 3 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 3 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	if ((leftSide == xAxis + 6 * multiplier || rightSide == xAxis + 6 * multiplier) && (playerPos.y > yAxis && playerPos.y < yAxis + 2 * multiplier))
	{
		if (rightSide == xAxis + 6 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 6 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}
}


void gamestate_level3_init(void)
{
	/*images*/
	rock = CP_Image_Load("./OurAssets/volcano.png");
	rock2 = CP_Image_Load("./OurAssets/rock2.png");
	rock3 = CP_Image_Load("./OurAssets/rock3.png");
	keyX = CP_Image_Load("./OurAssets/x.png");
	level3Ship = CP_Image_Load("./OurAssets/flying_spaceship.png");

	/*initialize player*/
	playerPos.x = 300.0;
	playerPos.y = 125.0;
	moveDistance = 5.0;
	playerWidth = 15.0f;
	playerDirection = 270;

	/*initialize map assets*/
	ratio = 100.0;
	doorPos.x = 700.0f;
	doorPos.y = 150.0f;
	key1Pos.x = 200.0f;
	key1Pos.y = 225.0f;
	key2Pos.x = 200.0f;
	key2Pos.y = 425.0f;
	key3Pos.x = 100.0f;
	key3Pos.y = 425.0f;
	key4Pos.x = 500.0f;
	key4Pos.y = 425.0f;
	enemy1Pos.x = 200.0f;
	enemy1Pos.y = 525.0f;
	enemy1Low = 195.0f;
	enemy1High = 500.0f;
	enemy1Offset = 5.0f;
	enemy2Pos.x = 400.0f;
	enemy2Pos.y = 125.0f;
	enemy2Low = 395.0f;
	enemy2High = 605.0f;
	enemy2Offset = 5.0f;
	enemy3Pos.x = 600.0f;
	enemy3Pos.y = 225.0f;
	enemy3Low = 395.0f;
	enemy3High = 605.0f;
	enemy3Offset = 5.0f;
	enemy4Pos.x = 100.0f;
	enemy4Pos.y = 625.0f;
	enemy4Low = 95.0f;
	enemy4High = 700.0f;
	enemy4Offset = 5.0f;
	enemy5Pos.x = 600.0f;
	enemy5Pos.y = 325.0f;
	enemy5Low = 320.0f;
	enemy5High = 550.0f;
	enemy5Offset = 5.0f;
	circleEnemy1Pos.x = 400.0f;
	circleEnemy1Pos.y = 335.0f;
	circleEnemy1Diameter = 25.0f;
	circleEnemy1Low = 15.0f;
	circleEnemy1High = 65.0f;
	circleEnemy1Offset = 2.0f;
	circleEnemy2Pos.x = 700.0f;
	circleEnemy2Pos.y = 335.0f;
	circleEnemy2Diameter = 25.0f;
	circleEnemy2Low = 15.0f;
	circleEnemy2High = 65.0f;
	circleEnemy2Offset = 2.0f;
	wallEnemy1Pos.x = 60.0f;
	wallEnemy1Pos.y = 175.0f;
	wallEnemy1Offset = 5.0f;
	wallEnemy1Low = 125.0f;
	wallEnemy1High = 325.0f;
	wallEnemy2Pos.x = 60.0f;
	wallEnemy2Pos.y = 400.0f;
	wallEnemy2Offset = -5.0f;
	wallEnemy2Low = 400.0f;
	wallEnemy2High = 675.0f;
	hasKey = 0;
	hasKey1 = 0;
	hasKey2 = 0;
	hasKey3 = 0;
	hasKey4 = 0;

	CP_Settings_Background(CP_Color_Create(30, 30, 30, 255));
}

void gamestate_level3_update(void)
{
	/*refresh background*/
	CP_Settings_Background(CP_Color_Create(30, 30, 30, 255));
	/*drawMaze3(50.0f, 75.0f, ratio);*/

	/*adds rock walls*/
	drawBorderVertical(rock, 150.0f, 425.0f, 8, 25.0f, ratio / 2.5f);		/*first vertical line, third row from bottom*/
	drawBorderVertical(rock, 250.0f, 425.0f, 4, 25.0f, ratio / 2.5f);		/*second vertical line, third row from bottom*/
	drawBorderVertical(rock, 450.0f, 325.0f, 8, 25.0f, ratio / 2.5f);		/*third vertical line, third row from bottom*/
	drawBorderVertical(rock, 550.0f, 325.0f, 12, 25.0f, ratio / 2.5f);		/*fourth vertical line, third row from bottom*/
	drawBorderVertical(rock, 650.0f, 425.0f, 8, 25.0f, ratio / 2.5f);		/*fifth vertical line, third row from bottom*/
	drawBorderVertical(rock, 150.0f, 225.0f, 4, 25.0f, ratio / 2.5f);		/*first vertical line, fourth row from bottom*/
	drawBorderVertical(rock, 350.0f, 125.0f, 4, 25.0f, ratio / 2.5f);		/*first vertical line, last row from bottom*/
	drawBorderVertical(rock, 650.0f, 125.0f, 9, 25.0f, ratio / 2.5f);		/*second vertical line, last row from bottom*/
	drawBorderHorizontal(rock, 150.0f, 625.0f, 12, 27.0f, ratio / 2.5f);	/*first horizontal line, first row from bottom*/
	drawBorderHorizontal(rock, 650.0f, 625.0f, 4, 27.0f, ratio / 2.5f);		/*second horizontal line, first row from bottom*/
	drawBorderHorizontal(rock, 250.0f, 525.0f, 4, 27.0f, ratio / 2.5f);		/*first horizontal line, second row from bottom*/
	drawBorderHorizontal(rock, 450.0f, 525.0f, 4, 27.0f, ratio / 2.5f);		/*second horizontal line, second row from bottom*/
	drawBorderHorizontal(rock, 50.0f, 425.0f, 12, 27.0f, ratio / 2.5f);		/*first horizontal line, third row from bottom*/
	drawBorderHorizontal(rock, 150.0f, 325.0f, 8, 27.0f, ratio / 2.5f);		/*first horizontal line, fourth row from bottom*/
	drawBorderHorizontal(rock, 550.0f, 325.0f, 4, 27.0f, ratio / 2.5f);		/*second horizontal line, third row from bottom*/
	drawBorderHorizontal(rock, 150.0f, 225.0f, 8, 27.0f, ratio / 2.5f);		/*first horizontal line, fourth row from bottom*/
	drawBorderHorizontal(rock, 450.0f, 225.0f, 4, 27.0f, ratio / 2.5f);		/*second horizontal line, fourth row from bottom*/

	/*adds border*/
	drawBorderHorizontal(rock2, 60.0f, 100.0f, 11, 65.0f, ratio);
	drawBorderVertical(rock3, 40.0f, 125.0f, 13, 50.0f, ratio);
	drawBorderVertical(rock2, 775.0f, 125.0f, 13, 50.0f, ratio);
	drawBorderHorizontal(rock2, 60.0f, 750.0f, 11, 65.0f, ratio);

	addMazeCollision3(50.0f, 75.0f, ratio);

	/*remove key if collected*/
	if (hasKey1 == 0)
	{
		drawKey(key1Pos.x, key1Pos.y, ratio);
	}
	if (hasKey2 == 0)
	{
		drawKey(key2Pos.x, key2Pos.y, ratio);
	}
	if (hasKey3 == 0)
	{
		drawKey(key3Pos.x, key3Pos.y, ratio);
	}
	if (hasKey4 == 0)
	{
		drawKey(key4Pos.x, key4Pos.y, ratio);
	}

	/*draw idle spaceship*/
	if (hasKey1 == 0 || hasKey2 == 0 || hasKey3 == 0 || hasKey4 == 0)
	{
		DrawDoor(doorPos.x, doorPos.y);
	}

	/*enemy movement*/
	DrawEnemy(enemy1Pos.x -= enemy1Offset, enemy1Pos.y);
	if (enemy1Pos.x == enemy1Low)
	{
		enemy1Offset *= -1;
	}
	if (enemy1Pos.x == enemy1High)
	{
		enemy1Offset *= -1;
	}
	DrawEnemy(enemy2Pos.x -= enemy2Offset, enemy2Pos.y);
	if (enemy2Pos.x == enemy2Low)
	{
		enemy2Offset *= -1;
	}
	if (enemy2Pos.x == enemy2High)
	{
		enemy2Offset *= -1;
	}
	DrawEnemy(enemy3Pos.x -= enemy3Offset, enemy3Pos.y);
	if (enemy3Pos.x == enemy3Low)
	{
		enemy3Offset *= -1;
	}
	if (enemy3Pos.x == enemy3High)
	{
		enemy3Offset *= -1;
	}
	DrawEnemy(enemy4Pos.x -= enemy4Offset, enemy4Pos.y);
	if (enemy4Pos.x == enemy4Low)
	{
		enemy4Offset *= -1;
	}
	if (enemy4Pos.x == enemy4High)
	{
		enemy4Offset *= -1;
	}
	DrawEnemy(enemy5Pos.x, enemy5Pos.y += enemy5Offset);
	if (enemy5Pos.y == enemy5Low)
	{
		enemy5Offset *= -1;
	}
	if (enemy5Pos.y == enemy5High)
	{
		enemy5Offset *= -1;
	}
	DrawCircleEnemy(circleEnemy1Pos.x, circleEnemy1Pos.y, circleEnemy1Diameter -= circleEnemy1Offset);
	if (circleEnemy1Diameter == circleEnemy1Low)
	{
		circleEnemy1Offset *= -1;
	}
	if (circleEnemy1Diameter == circleEnemy1High)
	{
		circleEnemy1Offset *= -1;
	}
	DrawCircleEnemy(circleEnemy2Pos.x, circleEnemy2Pos.y, circleEnemy2Diameter -= circleEnemy2Offset);
	if (circleEnemy2Diameter == circleEnemy2Low)
	{
		circleEnemy2Offset *= -1;
	}
	if (circleEnemy2Diameter == circleEnemy2High)
	{
		circleEnemy2Offset *= -1;
	}

	/*wall enemies*/
	DrawWallEnemy(wallEnemy1Pos.x, wallEnemy1Pos.y -= wallEnemy1Offset);
	if (wallEnemy1Pos.y == wallEnemy1Low)
	{
		wallEnemy1Offset *= -1;
	}
	if (wallEnemy1Pos.y == wallEnemy1High)
	{
		wallEnemy1Offset *= -1;
	}
	DrawWallEnemy(wallEnemy2Pos.x, wallEnemy2Pos.y -= wallEnemy2Offset);
	if (wallEnemy2Pos.y == wallEnemy2Low)
	{
		wallEnemy2Offset *= -1;
	}
	if (wallEnemy2Pos.y == wallEnemy2High)
	{
		wallEnemy2Offset *= -1;
	}

	/*wall enemy collision*/
	if (((playerPos.x < wallEnemy1Pos.x + 25.0f) && (playerPos.x > wallEnemy1Pos.x - 25.0f)) && ((playerPos.y < wallEnemy1Pos.y + 25.0f) && (playerPos.y > wallEnemy1Pos.y - 25.0f)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
	}
	if (((playerPos.x < wallEnemy2Pos.x + 25.0f) && (playerPos.x > wallEnemy2Pos.x - 25.0f)) && ((playerPos.y < wallEnemy2Pos.y + 25.0f) && (playerPos.y > wallEnemy2Pos.y - 25.0f)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
	}

	/*key collision*/
	if (((playerPos.x < key1Pos.x + 20.0f) && (playerPos.x > key1Pos.x - 20.0f)) && ((playerPos.y < key1Pos.y + 20.0f) && (playerPos.y > key1Pos.y - 20.0f)))
	{
		if (hasKey1 == 0)
		{
			hasKey += 1;
		}
		hasKey1 = 1;
	}
	if (((playerPos.x < key2Pos.x + 20.0f) && (playerPos.x > key2Pos.x - 20.0f)) && ((playerPos.y < key2Pos.y + 20.0f) && (playerPos.y > key2Pos.y - 20.0f)))
	{
		if (hasKey2 == 0)
		{
			hasKey += 1;
		}
		hasKey2 = 1;
	}
	if (((playerPos.x < key3Pos.x + 20.0f) && (playerPos.x > key3Pos.x - 20.0f)) && ((playerPos.y < key3Pos.y + 20.0f) && (playerPos.y > key3Pos.y - 20.0f)))
	{
		if (hasKey3 == 0)
		{
			hasKey += 1;
		}
		hasKey3 = 1;
	}
	if (((playerPos.x < key4Pos.x + 20.0f) && (playerPos.x > key4Pos.x - 20.0f)) && ((playerPos.y < key4Pos.y + 20.0f) && (playerPos.y > key4Pos.y - 20.0f)))
	{
		if (hasKey4 == 0)
		{
			hasKey += 1;
		}
		hasKey4 = 1;
	}

	/*key counter*/
	if (hasKey == 0)
	{
		keyNum = CP_Image_Load("./OurAssets/numberZero.png");
	}
	if (hasKey == 1)
	{
		keyNum = CP_Image_Load("./OurAssets/numberOne.png");
	}
	if (hasKey == 2)
	{
		keyNum = CP_Image_Load("./OurAssets/numberTwo.png");
	}
	if (hasKey == 3)
	{
		keyNum = CP_Image_Load("./OurAssets/numberThree.png");
	}
	if (hasKey == 4)
	{
		keyNum = CP_Image_Load("./OurAssets/numberFour.png");
		/*draw flying spaceship*/
		CP_Image_Draw(level3Ship, doorPos.x, doorPos.y, 50.0f, 90.0f, 255);
	}

	/*bottom left key icon*/
	CP_Image_Draw(treasure, 100.0f, 760.0f, ratio, ratio, 255);
	CP_Image_Draw(keyX, 140.0f, 760.0f, ratio / 5, ratio / 5, 255);
	CP_Image_Draw(keyNum, 165.0f, 760.0f, ratio / 3, ratio / 3, 255);

	/*enemy collision*/
	if (((playerPos.x < enemy1Pos.x + 25.0f) && (playerPos.x > enemy1Pos.x - 25.0f)) && ((playerPos.y < enemy1Pos.y + 25.0f) && (playerPos.y > enemy1Pos.y - 25.0f)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
		hasKey3 = 0;
		hasKey4 = 0;
	}
	if (((playerPos.x < enemy2Pos.x + 25.0f) && (playerPos.x > enemy2Pos.x - 25.0f)) && ((playerPos.y < enemy2Pos.y + 25.0f) && (playerPos.y > enemy2Pos.y - 25.0f)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
		hasKey3 = 0;
		hasKey4 = 0;
	}
	if (((playerPos.x < enemy3Pos.x + 25.0f) && (playerPos.x > enemy3Pos.x - 25.0f)) && ((playerPos.y < enemy3Pos.y + 25.0f) && (playerPos.y > enemy3Pos.y - 25.0f)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
		hasKey3 = 0;
		hasKey4 = 0;
	}
	if (((playerPos.x < enemy4Pos.x + 25.0f) && (playerPos.x > enemy4Pos.x - 25.0f)) && ((playerPos.y < enemy4Pos.y + 25.0f) && (playerPos.y > enemy4Pos.y - 25.0f)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
		hasKey3 = 0;
		hasKey4 = 0;
	}
	if (((playerPos.x < enemy5Pos.x + 25.0f) && (playerPos.x > enemy5Pos.x - 25.0f)) && ((playerPos.y < enemy5Pos.y + 25.0f) && (playerPos.y > enemy5Pos.y - 25.0f)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
		hasKey3 = 0;
		hasKey4 = 0;
	}
	if (((playerPos.x + playerWidth >= circleEnemy1Pos.x - circleEnemy1Diameter / 2) && (playerPos.x - playerWidth <= circleEnemy1Pos.x + circleEnemy1Diameter / 2))
	   && ((playerPos.y + playerWidth >= circleEnemy1Pos.y - circleEnemy1Diameter / 2) && (playerPos.y - playerWidth <= circleEnemy1Pos.y + circleEnemy1Diameter / 2)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
		hasKey3 = 0;
		hasKey4 = 0;
	}
	if (((playerPos.x + playerWidth >= circleEnemy2Pos.x - circleEnemy2Diameter / 2) && (playerPos.x - playerWidth <= circleEnemy2Pos.x + circleEnemy2Diameter / 2))
		&& ((playerPos.y + playerWidth >= circleEnemy2Pos.y - circleEnemy2Diameter / 2) && (playerPos.y - playerWidth <= circleEnemy2Pos.y + circleEnemy2Diameter / 2)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
		hasKey3 = 0;
		hasKey4 = 0;
	}

	/*maze exit*/
	if (((playerPos.x < doorPos.x + 25.0f) && (playerPos.x > doorPos.x - 25.0f)) && ((playerPos.y < doorPos.y + 25.0f) && (playerPos.y > doorPos.y - 25.0f)) && hasKey == 4)
	{
		CP_Engine_SetNextGameState(gamestate_win_init, gamestate_win_update, gamestate_win_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
		hasKey3 = 0;
		hasKey4 = 0;
	}

	playerMovement(&playerPos.x, &playerPos.y, &playerDirection, moveDistance); 
	drawPlayer(playerPos.x, playerPos.y, playerDirection);
}

void gamestate_level3_exit(void)
{
	
}
