//---------------------------------------------------------
// file:	gamestate_level2.c
// author:	Mary Khuu, Zak Stephenson, Rey Rosario
// course:	GAM100
//
// brief:	level two of the game
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "gamestate_level2.h"
#include "gamestate_level1.h"
#include "gamestate_hub.h"
#include "map_assets.h"
#include "player.h"

/*local variables*/
CP_Image icetree = NULL;
CP_Image snowtree = NULL;
CP_Image snowcube = NULL;
CP_Image level2Ship = NULL;

void drawMaze2(float xAxis, float yAxis, float multiplier)
{
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));

	/*outline of maze drawn based on given x and y position, maze is 7x6*/
	CP_Graphics_DrawLine(xAxis, yAxis, xAxis, yAxis + 6 * multiplier);
	CP_Graphics_DrawLine(xAxis, yAxis, xAxis + 7 * multiplier, yAxis);
	CP_Graphics_DrawLine(xAxis + 7 * multiplier, yAxis, xAxis + 7 * multiplier, yAxis + 6 * multiplier);
	CP_Graphics_DrawLine(xAxis, yAxis + 6 * multiplier, xAxis + 7 * multiplier, yAxis + 6 * multiplier);

	/*vertical lines, first row from bottom*/
	CP_Graphics_DrawLine(xAxis + 2 * multiplier, yAxis + 5 * multiplier, xAxis + 2 * multiplier, yAxis + 6 * multiplier);
	CP_Graphics_DrawLine(xAxis + 3 * multiplier, yAxis + 4 * multiplier, xAxis + 3 * multiplier, yAxis + 6 * multiplier);
	CP_Graphics_DrawLine(xAxis + 4 * multiplier, yAxis + 5 * multiplier, xAxis + 4 * multiplier, yAxis + 6 * multiplier);

	/*horizontal lines, first row from bottom*/
	CP_Graphics_DrawLine(xAxis + multiplier, yAxis + 5 * multiplier, xAxis + 2 * multiplier, yAxis + 5 * multiplier);
	CP_Graphics_DrawLine(xAxis + 4 * multiplier, yAxis + 5 * multiplier, xAxis + 6 * multiplier, yAxis + 5 * multiplier);

	/*horizontal lines, second row from bottom*/
	CP_Graphics_DrawLine(xAxis + multiplier, yAxis + 4 * multiplier, xAxis + 2 * multiplier, yAxis + 4 * multiplier);
	CP_Graphics_DrawLine(xAxis + 3 * multiplier, yAxis + 4 * multiplier, xAxis + 6 * multiplier, yAxis + 4 * multiplier);

	/*vertical lines, third row from bottom*/
	CP_Graphics_DrawLine(xAxis + multiplier, yAxis + 2 * multiplier, xAxis + multiplier, yAxis + 4 * multiplier);
	CP_Graphics_DrawLine(xAxis + 2 * multiplier, yAxis + multiplier, xAxis + 2 * multiplier, yAxis + 4 * multiplier);
	CP_Graphics_DrawLine(xAxis + 6 * multiplier, yAxis + 2 * multiplier, xAxis + 6 * multiplier, yAxis + 2 * multiplier);

	/*horizontal lines, third row from bottom*/
	CP_Graphics_DrawLine(xAxis + 2 * multiplier, yAxis + 3 * multiplier, xAxis + 3 * multiplier, yAxis + 3 * multiplier);
	CP_Graphics_DrawLine(xAxis + 4 * multiplier, yAxis + 3 * multiplier, xAxis + 5 * multiplier, yAxis + 3 * multiplier);

	/*vertical lines, fourth row from bottom*/
	CP_Graphics_DrawLine(xAxis + 5 * multiplier, yAxis + multiplier, xAxis + 5 * multiplier, yAxis + 3 * multiplier);
	CP_Graphics_DrawLine(xAxis + 6 * multiplier, yAxis + 2 * multiplier, xAxis + 6 * multiplier, yAxis + 4 * multiplier);

	/*horizontal line, fourth row from bottom*/
	CP_Graphics_DrawLine(xAxis + 3 * multiplier, yAxis + 2 * multiplier, xAxis + 4 * multiplier, yAxis + 2 * multiplier);

	/*vertical line, fifth row from bottom*/
	CP_Graphics_DrawLine(xAxis + 4 * multiplier, yAxis + multiplier, xAxis + 4 * multiplier, yAxis + 2 * multiplier);

	/*horizontal lines, fifth row from bottom*/
	CP_Graphics_DrawLine(xAxis + multiplier, yAxis + multiplier, xAxis + 2 * multiplier, yAxis + multiplier);
	CP_Graphics_DrawLine(xAxis + 4 * multiplier, yAxis + multiplier, xAxis + 7 * multiplier, yAxis + multiplier);
	
	/*vertical lines, sixth and last row from bottom*/
	CP_Graphics_DrawLine(xAxis + multiplier, yAxis, xAxis + multiplier, yAxis + multiplier);
	CP_Graphics_DrawLine(xAxis + 3 * multiplier, yAxis, xAxis + 3 * multiplier, yAxis + multiplier);
}

void addMazeCollision2(float xAxis, float yAxis, float multiplier)
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

	/*first verticle line, first row from bottom*/
	if (rightSide == xAxis + 2 * multiplier && (playerPos.y > yAxis + 5 * multiplier && playerPos.y < yAxis + 6 * multiplier))
	{
		if (rightSide == xAxis + 2 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	if (leftSide == xAxis + 2 * multiplier && (playerPos.y > yAxis + 5 * multiplier && playerPos.y < yAxis + 6 * multiplier))
	{
		if (leftSide == xAxis + 2 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*second verticle line, first row from bottom*/
	if ((rightSide == xAxis + 3 * multiplier || leftSide == xAxis + 3 * multiplier) && (playerPos.y > yAxis + 4 * multiplier && playerPos.y < yAxis + 6 * multiplier))
	{
		if (rightSide == xAxis + 3 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 3 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*third verticle line, first row from bottom*/
	if ((rightSide == xAxis + 4 * multiplier || leftSide == xAxis + 4 * multiplier) && (playerPos.y > yAxis + 5 * multiplier && playerPos.y < yAxis + 6 * multiplier))
	{
		if (rightSide == xAxis + 4 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 4 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first horizontal line, first row from bottom*/
	if ((topSide == yAxis + 5 * multiplier || botSide == yAxis + 5 * multiplier) && (playerPos.x > xAxis + multiplier && playerPos.x < xAxis + 2 * multiplier))
	{
		if (topSide == yAxis + 5 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 5 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*second horizontal line, first row from bottom*/
	if ((topSide == yAxis + 5 * multiplier || botSide == yAxis + 5 * multiplier) && (playerPos.x > xAxis + 4 * multiplier && playerPos.x < xAxis + 6 * multiplier))
	{
		if (topSide == yAxis + 5 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 5 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first horizontal line, second row from bottom*/
	if ((topSide == yAxis + 4 * multiplier || botSide == yAxis + 4 * multiplier) && (playerPos.x > xAxis + multiplier && playerPos.x < xAxis + 2 * multiplier))
	{
		if (topSide == yAxis + 4 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 4 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*second horizontal line, second row from bottom*/
	if ((topSide == yAxis + 4 * multiplier || botSide == yAxis + 4 * multiplier) && (playerPos.x > xAxis + 3 * multiplier && playerPos.x < xAxis + 6 * multiplier))
	{
		if (topSide == yAxis + 4 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 4 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first vertical line, third row from bottom*/
	if ((rightSide == xAxis + multiplier || leftSide == xAxis + multiplier) && (playerPos.y > yAxis + 2 * multiplier && playerPos.y < yAxis + 4 * multiplier))
	{
		if (rightSide == xAxis + multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*second vertical line, third row from bottom*/
	if ((rightSide == xAxis + 2 * multiplier || leftSide == xAxis + 2 * multiplier) && (playerPos.y > yAxis + multiplier && playerPos.y < yAxis + 4 * multiplier))
	{
		if (rightSide == xAxis + 2 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 2 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*third vertical line, third row from bottom*/
	if ((rightSide == xAxis + 5 * multiplier || leftSide == xAxis + 5 * multiplier) && (playerPos.y > yAxis + multiplier && playerPos.y < yAxis + 3 * multiplier))
	{
		if (rightSide == xAxis + 5 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 5 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*fourth vertical line, third row from bottom*/
	if ((rightSide == xAxis + 6 * multiplier || leftSide == xAxis + 6 * multiplier) && (playerPos.y > yAxis + 2 * multiplier && playerPos.y < yAxis + 4 * multiplier))
	{
		if (rightSide == xAxis + 6 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 6 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first horizontal line, third row from bottom*/
	if ((topSide == yAxis + 3 * multiplier || botSide == yAxis + 3 * multiplier) && (playerPos.x > xAxis + 2 * multiplier && playerPos.x < xAxis + 3 * multiplier))
	{
		if (topSide == yAxis + 3 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 3 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*second horizontal line, third row from bottom*/
	if ((topSide == yAxis + 3 * multiplier || botSide == yAxis + 3 * multiplier) && (playerPos.x > xAxis + 4 * multiplier && playerPos.x < xAxis + 5 * multiplier))
	{
		if (topSide == yAxis + 3 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 3 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first horizontal line, fourth row from bottom*/
	if ((topSide == yAxis + 2 * multiplier || botSide == yAxis + 2 * multiplier) && (playerPos.x > xAxis + 3 * multiplier && playerPos.x < xAxis + 4 * multiplier))
	{
		if (topSide == yAxis + 2 * multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + 2 * multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first vertical line, fifth row from bottom*/
	if ((rightSide == xAxis + 4 * multiplier || leftSide == xAxis + 4 * multiplier) && (playerPos.y > yAxis + multiplier && playerPos.y < yAxis + 2 * multiplier))
	{
		if (rightSide == xAxis + 4 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 4 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*second vertical line, fifth row from bottom*/
	if ((rightSide == xAxis + 5 * multiplier || leftSide == xAxis + 5 * multiplier) && (playerPos.y > yAxis + multiplier && playerPos.y < yAxis + 3 * multiplier))
	{
		if (rightSide == xAxis + 5 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 5 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first horizontal line, fifth row from bottom*/
	if ((topSide == yAxis + multiplier || botSide == yAxis + multiplier) && (playerPos.x > xAxis + multiplier && playerPos.x < xAxis + 2 * multiplier))
	{
		if (topSide == yAxis + multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*second horizontal line, fifth row from bottom*/
	if ((topSide == yAxis + multiplier || botSide == yAxis + multiplier) && (playerPos.x > xAxis + 4 * multiplier && playerPos.x < xAxis + 7 * multiplier))
	{
		if (topSide == yAxis + multiplier && CP_Input_KeyDown(KEY_W))
			moveDistance = 0;
		else if (botSide == yAxis + multiplier && CP_Input_KeyDown(KEY_S))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first vertical line, sixth/last row from bottom*/
	if ((rightSide == xAxis + multiplier || leftSide == xAxis + multiplier) && (playerPos.y > yAxis && playerPos.y < yAxis + multiplier))
	{
		if (rightSide == xAxis + multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}

	/*first vertical line, sixth/last row from bottom*/
	if ((rightSide == xAxis + 3 * multiplier || leftSide == xAxis + 3 * multiplier) && (playerPos.y > yAxis && playerPos.y < yAxis + multiplier))
	{
		if (rightSide == xAxis + 3 * multiplier && CP_Input_KeyDown(KEY_D))
			moveDistance = 0;
		else if (leftSide == xAxis + 3 * multiplier && CP_Input_KeyDown(KEY_A))
			moveDistance = 0;
		else
			moveDistance = 5.0;
	}
}

void gamestate_level2_init(void)
{
	/*images*/
	snowtree = CP_Image_Load("./OurAssets/snow-tree.png");
	icetree = CP_Image_Load("./OurAssets/ice-tree.png");
	snowcube = CP_Image_Load("./OurAssets/snowcube.png");
	keyX = CP_Image_Load("./OurAssets/x.png");
	level2Ship = CP_Image_Load("./OurAssets/flying_spaceship.png");

	/*initialize player*/
	playerPos.x = 100.0; 
	playerPos.y = 100.0;
	moveDistance = 5.0;
	playerWidth = 15.0f;
	playerDirection = 180;

	/*initialize map assets*/
	ratio = 100.0;
	key1Pos.x = 200.0f;
	key1Pos.y = 425.0f;
	key2Pos.x = 400.0f;
	key2Pos.y = 625.0f;
	doorPos.x = 675.0f;
	doorPos.y = 125.0f;
	wallEnemy1Pos.x = 75.0f;
	wallEnemy1Pos.y = 475.0f;
	wallEnemy1Offset = 5.0f;
	wallEnemy1Low = 285.0f;
	wallEnemy1High = 485.0f;
	wallEnemy2Pos.x = 125.0f;
	wallEnemy2Pos.y = 295.0f;
	wallEnemy2Offset = -5.0f;
	wallEnemy2Low = 275.0f;
	wallEnemy2High = 475.0f;
	wallEnemy3Pos.x = 725.0f;
	wallEnemy3Pos.y = 275.0f;
	wallEnemy3Offset = 5.0f;
	wallEnemy3Low = 265.0f;
	wallEnemy3High = 485.0f;
	wallEnemy4Pos.x = 675.0f;
	wallEnemy4Pos.y = 470.0f;
	wallEnemy4Offset = -5.0f;
	wallEnemy4Low = 270.0f;
	wallEnemy4High = 490.0f;
	enemy1Pos.x = 300.0f;
	enemy1Pos.y = 525.0f;
	enemy1Low = 425.0f;
	enemy1High = 625.0f;
	enemy1Offset = 5.0f;
	enemy2Pos.x = 400.0f;
	enemy2Pos.y = 325.0f;
	enemy2Low = 300.0f;
	enemy2High = 500.0f;
	enemy2Offset = 4.0f;
	enemy3Pos.x = 650.0f;
	enemy3Pos.y = 225.0f;
	enemy3Low = 575.0f;
	enemy3High = 725.0f;
	enemy3Offset = 5.0f;
	hasKey = 0;
	hasKey1 = 0;
	hasKey2 = 0;
	level2Key = 0;

	CP_Settings_Background(CP_Color_Create(30, 30, 30, 255));
}


void gamestate_level2_update(void)
{
	/*refresh background*/
	CP_Settings_Background(CP_Color_Create(30, 30, 30, 255));
	/*drawMaze2(50.0f, 75.0f, ratio);*/

	/*adds walls*/
	drawBorderHorizontal(snowcube, 150.0f, 625.0f, 5, 20.0f, ratio / 2);	/*first horizontal line, first row from bottom*/
	drawBorderHorizontal(snowcube, 450.0f, 625.0f, 11, 20.0f, ratio / 2);	/*second horizontal line, first row from bottom*/
	drawBorderHorizontal(snowcube, 150.0f, 525.0f, 5, 20.0f, ratio / 2);	/*first horizontal line, second row from bottom*/
	drawBorderHorizontal(snowcube, 350.0f, 525.0f, 15, 20.0f, ratio / 2);	/*second horizontal line, second row from bottom*/
	drawBorderHorizontal(snowcube, 250.0f, 425.0f, 6, 20.0f, ratio / 2);	/*first horizontal line, third row from bottom*/
	drawBorderHorizontal(snowcube, 450.0f, 425.0f, 5, 20.0f, ratio / 2);	/*second horizontal line, third row from bottom*/
	drawBorderHorizontal(snowcube, 350.0f, 325.0f, 5, 20.0f, ratio / 2);	/*first horizontal line, fourth row from bottom*/
	drawBorderHorizontal(snowcube, 150.0f, 225.0f, 5, 20.0f, ratio / 2);	/*first horizontal line, fifth row from bottom*/
	drawBorderHorizontal(snowcube, 450.0f, 225.0f, 15, 20.0f, ratio / 2);	/*second horizontal line, fifth row from bottom*/
	drawBorderVertical(snowcube, 250.0f, 625.0f, 5, 25.0f, ratio / 2);		/*second vertical line, first row from bottom*/
	drawBorderVertical(snowcube, 350.0f, 525.0f, 10, 25.0f, ratio / 2);		/*third vertical line, first row from bottom*/
	drawBorderVertical(snowcube, 450.0f, 625.0f, 5, 25.0f, ratio / 2);		/*fourth vertical line, first row from bottom*/
	drawBorderVertical(snowcube, 150.0f, 325.0f, 8, 25.0f, ratio / 2);		/*first vertical line, third row from bottom*/
	drawBorderVertical(snowcube, 650.0f, 325.0f, 9, 25.0f, ratio / 2);		/*first vertical line, fourth row from bottom*/
	drawBorderVertical(snowcube, 250.0f, 225.0f, 13, 25.0f, ratio / 2);		/*first vertical line, fifth row from bottom*/
	drawBorderVertical(snowcube, 450.0f, 225.0f, 5, 25.0f, ratio / 2);		/*second vertical line, fifth row from bottom*/
	drawBorderVertical(snowcube, 550.0f, 225.0f, 9, 25.0f, ratio / 2);		/*third vertical line, fifth row from bottom*/
	drawBorderVertical(snowcube, 150.0f, 125.0f, 5, 25.0f, ratio / 2);		/*first vertical line, last row from bottom*/
	drawBorderVertical(snowcube, 350.0f, 125.0f, 5, 25.0f, ratio / 2);		/*second vertical line, last row from bottom*/

	/*adds snow tree border*/
	drawBorderHorizontal(icetree, 60.0f, 100.0f, 9, 84.0f, ratio);
	drawBorderHorizontal(snowtree, 100.0f, 100.0f, 8, 84.0f, ratio);
	drawBorderVertical(icetree, 40.0f, 125.0f, 5, 130.0f, ratio);
	drawBorderVertical(snowtree, 40.0f, 185.0f, 5, 130.0f, ratio);
	drawBorderVertical(icetree, 760.0f, 125.0f, 5, 130.0f, ratio);
	drawBorderVertical(snowtree, 760.0f, 185.0f, 5, 130.0f, ratio);
	drawBorderHorizontal(icetree, 60.0f, 750.0f, 9, 84.0f, ratio);
	drawBorderHorizontal(snowtree, 100.0f, 750.0f, 8, 84.0f, ratio);

	addMazeCollision2(50.0f, 75.0f, ratio);
	
	/*remove key if collected*/
	if (hasKey1 == 0)
	{
		drawKey(key1Pos.x, key1Pos.y, ratio);
	}
	if (hasKey2 == 0)
	{
		drawKey(key2Pos.x, key2Pos.y, ratio);
	}
	
	/*draw idle spaceship*/
	if (hasKey1 == 0 || hasKey2 == 0)
	{
		DrawDoor(doorPos.x, doorPos.y);
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
	DrawWallEnemy(wallEnemy3Pos.x, wallEnemy3Pos.y -= wallEnemy3Offset);
	if (wallEnemy3Pos.y == wallEnemy3Low)
	{
		wallEnemy3Offset *= -1;
	}
	if (wallEnemy3Pos.y == wallEnemy3High)
	{
		wallEnemy3Offset *= -1;
	}
	DrawWallEnemy(wallEnemy4Pos.x, wallEnemy4Pos.y -= wallEnemy4Offset);
	if (wallEnemy4Pos.y == wallEnemy4Low)
	{
		wallEnemy4Offset *= -1;
	}
	if (wallEnemy4Pos.y == wallEnemy4High)
	{
		wallEnemy4Offset *= -1;
	}
	
	/*enemies*/
	DrawEnemy(enemy1Pos.x, enemy1Pos.y -= enemy1Offset);
	if (enemy1Pos.y == enemy1Low)
	{
		enemy1Offset *= -1;
	}
	if (enemy1Pos.y == enemy1High)
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
		/*draw flying spaceship*/
		CP_Image_Draw(level2Ship, doorPos.x, doorPos.y, 50.0f, 90.0f, 255);
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
	}
	if (((playerPos.x < enemy2Pos.x + 25.0f) && (playerPos.x > enemy2Pos.x - 25.0f)) && ((playerPos.y < enemy2Pos.y + 25.0f) && (playerPos.y > enemy2Pos.y - 25.0f)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
	}
	if (((playerPos.x < enemy3Pos.x + 25.0f) && (playerPos.x > enemy3Pos.x - 25.0f)) && ((playerPos.y < enemy3Pos.y + 25.0f) && (playerPos.y > enemy3Pos.y - 25.0f)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
	}

	/*maze exit*/
	if (((playerPos.x < doorPos.x + 25.0f) && (playerPos.x > doorPos.x - 25.0f)) && ((playerPos.y < doorPos.y + 25.0f) && (playerPos.y > doorPos.y - 25.0f)) && hasKey == 2)
	{
		level2Key = 1;
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
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
	if (((playerPos.x < wallEnemy2Pos.x + 25.0f) && (playerPos.x > wallEnemy2Pos.x - 25.0f)) && ((playerPos.y < wallEnemy2Pos.y + 25.0f) && (playerPos.y > wallEnemy2Pos.y - 25.0f)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
	}
	if (((playerPos.x < wallEnemy3Pos.x + 25.0f) && (playerPos.x > wallEnemy3Pos.x - 25.0f)) && ((playerPos.y < wallEnemy3Pos.y + 25.0f) && (playerPos.y > wallEnemy3Pos.y - 25.0f)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
	}
	if (((playerPos.x < wallEnemy4Pos.x + 25.0f) && (playerPos.x > wallEnemy4Pos.x - 25.0f)) && ((playerPos.y < wallEnemy4Pos.y + 25.0f) && (playerPos.y > wallEnemy4Pos.y - 25.0f)))
	{
		CP_Engine_SetNextGameState(gamestate_hub_init, gamestate_hub_update, gamestate_hub_exit);
		hasKey = 0;
		hasKey1 = 0;
		hasKey2 = 0;
	}

	playerMovement(&playerPos.x, &playerPos.y, &playerDirection, moveDistance);
	drawPlayer(playerPos.x, playerPos.y, playerDirection);
}


void gamestate_level2_exit(void)
{
	
}
