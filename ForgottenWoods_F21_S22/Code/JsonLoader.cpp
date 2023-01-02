//------------------------------------------------------------------------------
/*!
\file	JsonLoader.cpp
\author	Riti (r.bhatwal), Zak (zak.s)
\par	Copyright © 2021 DigiPen (USA) Corporation.
\brief
*/
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------
#include "JsonLoader.h"

void ReadJSONData(rapidjson::Document** DocPointer, const char* FilePath)
{
    FILE* PlayerFile;
    fopen_s(&PlayerFile, FilePath, "rb"); 
    if (PlayerFile)
    {
        char* readBuffer = new char[100000];
        rapidjson::FileReadStream InStream(PlayerFile, readBuffer, 100000);
        *DocPointer = new rapidjson::Document();
        (*DocPointer)->ParseStream(InStream);
        delete[]readBuffer;
        fclose(PlayerFile);


    }

}
