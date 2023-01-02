//------------------------------------------------------------------------------
/*!
\file	LevelLoadSystem.cpp
\author	Riti, Zak
\par	Copyright © 2021 DigiPen (USA) Corporation.
\brief  used as reference to learn how to use rapidJSON: https://glusoft.com/tutorials/sfml/importing-tiled-maps
*/
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------
#include "LevelLoadSystem.h"
#include "glm/vec2.hpp"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "ComponentCollider.h"
#include "ComponentTransform.h"
#include "SpriteComponent.h"
#include <sstream>
#include "JsonLoader.h"
#include "Level1.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
static int tileCounter = 1;
static int horizontalCounter = 1;
static int verticalCounter = 1;
static int CurrentLevelNo;

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
GameObjectManager* ManagerRef = 0;
ComponentGraphic** UniqueSpriteGraphicList;//unique means it never stores more than one instance of the same graphic. 
const char** CollisionTypes;// stores what kind of collision corresponds to the sprite in UniqueSpriteGraphicList. the indexes match
//this means that tile ids must be UNIQUE and go from 0 to 99
 rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>* ObjectProperties;
 bool* HasProperties;
int UniqueSpriteGraphicListCount = 0;

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
// Initialize the system.
void LevelLoadSystem::Initialize(GameObjectManager* Manager, Shader* ShaderP)
{
	ReadJSONData(&AllGameLevelData, "./TextFiles/AllGameLevelData.json");
	UniqueSpriteGraphicList = new ComponentGraphic* [100]();
	CollisionTypes = new const char * [100]();
	HasProperties = new bool[500]();
	ObjectProperties = new  rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>[500]();
	UniqueSpriteGraphicListCount = 0;
	ManagerRef = Manager;
	FILE* fp = 0;
	fopen_s(&fp, (*AllGameLevelData)["Levels"].GetArray()[CurrentLevelNo]["TilemapJson"].GetString(), "rb"); //"source":".../TileMaps/art test new.json"
	if (fp)
	{
		char* readBuffer = (char*)(calloc(100000, sizeof(char)));
		rapidjson::FileReadStream is(fp, readBuffer, 100000);

		rapidjson::Document TileMapD;
		TileMapD.ParseStream(is);
		fclose(fp);
		free(readBuffer);

		int height = TileMapD["height"].GetInt();
		int width = TileMapD["width"].GetInt();
		int tilewidth = TileMapD["tilewidth"].GetInt();//not be confused with tile size. tilewidth is the size of the tile's image in PIXELS

		glm::vec2 TopLeftTileCenterPos(-1 + (0.05), 1.2 - (0.05));//center position of the top left tile in the map in the game's coordinates.
		
		//int* TMdata = (int*)calloc((unsigned long)height * (unsigned long)width, sizeof(int));
		//int TMData[10000];

		//assuming we have all the tiles in just one tileset
		FILE* fpTileSet = 0;
		rapidjson::Document TileSetD;

		const char* TileSetName = "./TileMaps/arttestnew.json";//TileMapD["tilesets"][0]["source"].GetString();
		fopen_s(&fpTileSet, TileSetName, "rb");
		if (fpTileSet)
		{
			char* fpTileSetBuffer = (char*)(calloc(100000, sizeof(char)));
			rapidjson::FileReadStream is(fpTileSet, fpTileSetBuffer, 100000);

			TileSetD.ParseStream(is);

			free(fpTileSetBuffer);

			LoadTileSprites(TileSetD, ShaderP);

			fclose(fpTileSet);
		}

		rapidjson::Value::Array layersA = TileMapD["layers"].GetArray();
		for (size_t i = 0; i < layersA.Capacity(); i++)
		{
			rapidjson::Value& CurrentLayer = layersA[i];
			bool Collidable = false;
			bool Special = false;
			if (strcmp(CurrentLayer["name"].GetString(), "Special Layer") == 0)//this is for special layer only
			{
				Special = true;
			}
			if (strcmp(CurrentLayer["name"].GetString(), "Collision Layer") == 0)//this is for collision layer only
			{
				Collidable = true;
			}

		
			if (CurrentLayer.HasMember("data"))
			{
				int CurrentTileIndex = 0;
				for (int i = 0; i < (height * width); i++)
				{
					auto& a = CurrentLayer["data"].GetArray()[i];
					int TileID = a.GetInt();//the number that specifies what kind of tile this is
					if (TileID == 60)
					{
						TileID = 60;
					}
					int CurrentTileXIndex = CurrentTileIndex % width;
					int CurrentTileYIndex = CurrentTileIndex / width;
					glm::vec2 CurrentTileCenter(0, 0);
					CurrentTileCenter.x = TopLeftTileCenterPos.x + (CurrentTileXIndex * (2 * TileSize));
					CurrentTileCenter.y = TopLeftTileCenterPos.y - (CurrentTileYIndex * (2 * TileSize));
					if (Special && TileID != 0)
					{
						if (HasProperties[TileID - 1])
						{
							SpawnSpecial(glm::vec3(CurrentTileCenter, 1), TileID, &ObjectProperties[TileID - 1]);
						}
						else
						{
							SpawnSpecial(glm::vec3(CurrentTileCenter, 1), TileID, 0);

						}
					}
					else
					{
						CreateTile(CurrentTileCenter, TileID, TileSize, TileSetD, Collidable);
					}
					CurrentTileIndex++;
				}
			}
		}

	}
}

// Update the system each game loop.
void LevelLoadSystem::Update(float dt)
{
}


void LevelLoadSystem::Render()//currently just draws the debug boxes and lines around tiles
{

}

void LevelLoadSystem::LoadTileSprites(rapidjson::Document& TileSetDoc, Shader* ShaderP)
{

	int VBO = 0;
	int VAO = 0;
	int EBO = 0;

	int NumTileSprites = TileSetDoc["tiles"].Capacity();

	//graphics stuff
	for (int i = 0; i < NumTileSprites; i++)
	{
		const char* CurrentSpritePath = TileSetDoc["tiles"][i]["image"].GetString();
		int CurrentSpriteID = TileSetDoc["tiles"][i]["id"].GetInt();
		ComponentSprite TempSprite;
		TempSprite.Set_MeshPath("./TextFiles/TileMesh.txt");//its the same mesh for every tile
		ComponentGraphics* TileGraphic = new ComponentGraphics(VAO, VBO, EBO);
		TileGraphic->SetIndices(TempSprite.GetIndecies());
		TileGraphic->SetVertices(TempSprite.GetVertices());
		//its CurrentSpritePath +  1 instead of CurrentSpritePath because we want to remove the first dot from the file path
		TileGraphic->CreateSquareFromFileName(VAO, VBO, EBO, CurrentSpritePath + 1, *ShaderP);
		UniqueSpriteGraphicList[CurrentSpriteID] = TileGraphic;//stores it based on ID so that we can get it based on ID
		if(TileSetDoc["tiles"][i].HasMember("properties"))
		{
			if (strcmp(TileSetDoc["tiles"][i]["properties"][0]["name"].GetString(), "c") == 0)
			{
				CollisionTypes[CurrentSpriteID] = TileSetDoc["tiles"][i]["properties"][0]["value"].GetString();
			}
			ObjectProperties[CurrentSpriteID] = TileSetDoc["tiles"][i]["properties"];
			HasProperties[CurrentSpriteID] = true;
		}
		else
		{
			HasProperties[CurrentSpriteID] = false;

		}
		
		UniqueSpriteGraphicListCount++;
	}
}

float LevelLoadSystem::GetTileSize()
{
	return TileSize;

}

void LevelLoadSystem::CreateTile(glm::vec2 CurrentTileCenter, int TileID, float TileSize, rapidjson::Document& TileSetDoc, bool CreateCollisionWalls)
{
	if (TileID == 0)
	{
		return;
	}
	GameObject* NewTile = new GameObject();
	ComponentTransform* TileTransform = NewTile->GetTransform();
	//glm::vec3 StartPos(0.5, 0.65, 1);
	glm::vec3 TilePos(CurrentTileCenter.x, CurrentTileCenter.y, 1);
	glm::vec3 TileScale(TileSize, TileSize, 1);//sqauredraw 4x4 uses a mesh of 0.1 * 0.1
	std::stringstream name;
	name << "Tile ";
	name << tileCounter;
	NewTile->SetName(name.str());
	tileCounter++;
	TileTransform->SetPosition(&TilePos);
	TileTransform->SetScale(&TileScale);
	GameObjectManagerAdd(ManagerRef, NewTile);
	if (CreateCollisionWalls)
	{
		CreateTileWalls(CurrentTileCenter, TileID, TileSize);
	}
	if (TileID == 26)
	{
	  SpawnGoal(glm::vec3 (CurrentTileCenter,1));
	}
	AssignTileSprite(TileID, NewTile);

}


//this function os for placing colliding walls on the tiles
void LevelLoadSystem::CreateTileWalls(glm::vec2 CurrentTileCenter, int TileID, float TileSize)
{
	std::stringstream horizontalName;
	std::stringstream verticalName;
	/*remember that the ID in the json is equal to the ID in tiled + 1*/
	if (TileID == 0)
	{
		return;
	}
	//int CollisionType = TileID % 9;
	const char* CollisionType = CollisionTypes[TileID - 1];
	float WallSize = TileSize ;
	float WallShrinkByTopBot =  0.03;
	float WallShrinkByLeftRight = 0.03;
	float WallPlacementShrinkByTopBot = 0.02;
	float WallPlacementShrinkByLeftRight = 0.02;


	//float 
	GameObject* TileWallHorizontal = 0;
	ComponentTransform* TileWallHorizontalTran = 0;


	GameObject* TileWallVertical = 0;
	ComponentTransform* TileWallVerticalTran = 0;

	bool CreateVert = false;
	bool CreateHor = false;
	float VertWallPlacement = 0;
	float HorizWallPlacement = 0;

	if (strcmp(CollisionType, "TL") == 0)
	{
		CreateVert = true;
		CreateHor = true;
		VertWallPlacement = CurrentTileCenter.x - (WallSize - WallPlacementShrinkByLeftRight);
		HorizWallPlacement = CurrentTileCenter.y + (WallSize - WallPlacementShrinkByTopBot);
	}
	if (strcmp(CollisionType, "TM") == 0)
	{
		CreateVert = false;
		CreateHor = true;
		HorizWallPlacement = CurrentTileCenter.y + (WallSize - WallPlacementShrinkByTopBot);
	}
	if (strcmp(CollisionType, "TR") == 0)
	{
		CreateVert = true;
		CreateHor = true;
		VertWallPlacement = CurrentTileCenter.x + (WallSize - WallPlacementShrinkByLeftRight);
		HorizWallPlacement = CurrentTileCenter.y + (WallSize - WallPlacementShrinkByTopBot);
	}
	if (strcmp(CollisionType, "ML") == 0)
	{
		CreateVert = true;
		CreateHor = false;

		VertWallPlacement = CurrentTileCenter.x - (WallSize - WallPlacementShrinkByLeftRight);
	}
	if (strcmp(CollisionType, "MM") == 0)
	{
		CreateVert = false;
		CreateHor = false;
	}
	if (strcmp(CollisionType, "MR") == 0)
	{
		CreateVert = true;
		CreateHor = false;

		VertWallPlacement = CurrentTileCenter.x + (WallSize - WallPlacementShrinkByLeftRight);
	}
	if (strcmp(CollisionType, "BL") == 0)
	{
		CreateVert = true;
		CreateHor = true;
		VertWallPlacement = CurrentTileCenter.x - (WallSize  - WallPlacementShrinkByLeftRight);
		HorizWallPlacement = CurrentTileCenter.y - (WallSize - WallPlacementShrinkByTopBot);
	}
	if (strcmp(CollisionType, "BM") == 0)
	{
		CreateVert = false;
		CreateHor = true;
		HorizWallPlacement = CurrentTileCenter.y - (WallSize - WallPlacementShrinkByTopBot);
	}
	if (strcmp(CollisionType, "BR") == 0)
	{
		CreateVert = true;
		CreateHor = true;
		VertWallPlacement = CurrentTileCenter.x + (WallSize - WallPlacementShrinkByLeftRight);
		HorizWallPlacement = CurrentTileCenter.y - (WallSize - WallPlacementShrinkByTopBot);
	}
	

	if (CreateHor)
	{
		TileWallHorizontal = new GameObject();
		horizontalName << "Horizontal Wall ";
		horizontalName << horizontalCounter;
		TileWallHorizontal->SetName(horizontalName.str());
		horizontalCounter++;
		TileWallHorizontalTran = TileWallHorizontal->GetTransform();
		glm::vec3 StartPosWall(CurrentTileCenter.x, HorizWallPlacement, 1);
		glm::vec3 StartScaleWall(WallSize - WallShrinkByTopBot, WallSize, 1);

		//the collider box is 1x1. if the transform is scaled, the collider box will also be scaled by that much
		TileWallHorizontal->SetCollider(new ComponentCollider('h', 1.0f));

		TileWallHorizontalTran->SetPosition(&StartPosWall);
		TileWallHorizontalTran->SetScale(&StartScaleWall);
		GameObjectManagerAdd(ManagerRef, TileWallHorizontal);

	}

	if (CreateVert)
	{
		TileWallVertical = new GameObject();
		verticalName << "Vertical Wall ";
		verticalName << verticalCounter;
		TileWallVertical->SetName(verticalName.str());
		verticalCounter++;
		TileWallVerticalTran = TileWallVertical->GetTransform();
		glm::vec3 StartPosWall(VertWallPlacement, CurrentTileCenter.y, 1);
		glm::vec3 StartScaleWall(WallSize, WallSize - WallShrinkByLeftRight, 1);

		//the collider box is 1x1. if the transform is scaled, the collider box will also be scaled by that much
		TileWallVertical->SetCollider(new ComponentCollider('v', 1.0f));

		TileWallVerticalTran->SetPosition(&StartPosWall);
		TileWallVerticalTran->SetScale(&StartScaleWall);
		GameObjectManagerAdd(ManagerRef, TileWallVertical);

	}

}

void LevelLoadSystem::AssignTileSprite(int TileID, GameObject* Tile)
{
	Tile->SetGraphic(UniqueSpriteGraphicList[TileID - 1]);
}

void LevelLoadSystem::DrawLevel()
{
}
void LevelLoadSystem::UnloadLevelData()
{
	if (UniqueSpriteGraphicList && CollisionTypes)
	{
		for (int i = 0; i < 100; i++)
		{
			delete UniqueSpriteGraphicList[i];
		}
		delete[] UniqueSpriteGraphicList;
		delete[] CollisionTypes;
		delete[] ObjectProperties;
		delete[] HasProperties;

		UniqueSpriteGraphicList = 0;
		CollisionTypes = 0;
	}
}

 int LevelLoadSystem::GetCurrentLevel()
{
		return CurrentLevelNo;
}

 void LevelLoadSystem::SetCurrentLevel(int i)
 {
	  CurrentLevelNo = i;
 }

