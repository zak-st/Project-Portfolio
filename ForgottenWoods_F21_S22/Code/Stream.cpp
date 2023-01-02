//------------------------------------------------------------------------------
/*!
\file	Stream.cpp
\author	Zak (zak.s)
\par	Copyright © 2021 DigiPen (USA) Corporation.
\brief
*/
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Stream.h"
#include "framework.h"
#include "Trace.h"

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
static FILE* file;
static char stringBuffer[1024];
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
Stream StreamOpen(const char* filename)
{
	fopen_s(&file, filename, "rt");
	char errorMsg[256];
	strerror_s(errorMsg, 256, errno);

	if (file == NULL)
	{
		TraceSetActiveChannel("ERROR");
		TraceMessage("ERROR", "StreamOpen could not open file %s; %s", filename, errorMsg);
		return NULL;
	}
	else
	{
		return file;
	}
}
void StreamClose(Stream* stream)
{
	if (stream != NULL)
	{
		fclose(*stream);
	}
}
bool StreamReadBool(Stream stream)
{
	if (stream != NULL)
	{
		int scanBool;
		fscanf_s(stream, "%i", &scanBool);
		return scanBool;
	}
	else
	{
		return 0;
	}
}
int StreamReadInt(Stream stream)
{
	if (stream != NULL)
	{
		int scanInt;
		fscanf_s(stream, "%i", &scanInt);
		return scanInt;
	}
	else
	{
		return 0;
	}
}
float StreamReadFloat(Stream stream)
{
	if (stream != NULL)
	{
		float scanFloat;
		fscanf_s(stream, "%f", &scanFloat);
		return scanFloat;
	}
	else
	{
		return 0;
	}
}
const char* StreamReadString(Stream stream)
{
	stringBuffer[0] = 0;
	if (stream != NULL)
	{
		fscanf_s(stream, "%s", &stringBuffer, sizeof(stringBuffer));
	}
	return stringBuffer;
}

void StreamRead2DVec(Stream stream, vec2* vector)
{
	if (stream != NULL && vector != NULL)
	{
		// Fill the vector with two float values (x & y).
		float scanFloat = StreamReadFloat(stream);
		vector->x = scanFloat;
		scanFloat = StreamReadFloat(stream);
		vector->y = scanFloat;
	}
	else
	{
		TraceSetActiveChannel("ERROR");
		TraceMessage("ERROR", "Stream and/or vec2 pointer are not valid.", "Stream");
	}
}
void StreamRead3DVec(Stream stream, vec3* vector)
{
	if (stream != NULL && vector != NULL)
	{
		// Fill the vector with two float values (x & y).
		float scanFloat = StreamReadFloat(stream);
		vector->x = scanFloat;
		scanFloat = StreamReadFloat(stream);
		vector->y = scanFloat;
		scanFloat = StreamReadFloat(stream);
		vector->z = scanFloat;
	}
	else
	{
		TraceSetActiveChannel("ERROR");
		TraceMessage("ERROR", "Stream and/or vec3 pointer are not valid.", "Stream");
	}
}

void StreamReadVector2D(Stream stream, Vector2D* vector) {
	if (stream == NULL) {
		return;
	}
	float x = StreamReadFloat(stream);
	float y = StreamReadFloat(stream);
	vector->x = x;
	vector->y = y;

}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------