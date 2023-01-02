//------------------------------------------------------------------------------
/*!
\file	Audio.cpp
\author	Zak (zak.s), Hemie (hemie.choi)
\par	Copyright © 2021 DigiPen (USA) Corporation.
\brief
*/
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Audio.h"
#include "Trace.h"
#include "Stream.h"
#include "Options.h"

//SYSTEM_PTR soundsystem;

CHANNEL_PTR channel1 = 0;
bool isMuted = false;


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

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// initializing 
Audio::Audio(void) : result(), volume(1.0f)
{
    soundsystem = 0;
    // creating main system object
    result = FMOD::System_Create(&soundsystem);
    ERRORCHECK(result);

    // initializing FMOD
    result = soundsystem->init(32, FMOD_INIT_NORMAL, 0);
    ERRORCHECK(result);
}

// shutting down
Audio::~Audio(void)
{
    // example of releasing sounds
    /*if (sound1)
    {
        result = sound1->release();
        ERRORCHECK(result);
    }*/

    // closing and releasing the FMOD system 
    if (soundsystem)
    {
        result = soundsystem->close();
        ERRORCHECK(result);

        result = soundsystem->release();
        ERRORCHECK(result);
    }
    soundsystem = 0;
}


// dt is the change in time(sec) since the last game loop
void Audio::Update(float dt)
{
    result = soundsystem->update();
    ERRORCHECK(result);
}


void Audio::Play(SOUND_PTR sound, CHANNEL_PTR* channel) 
{

    // checks the null pointer
    if (!sound)
    {
        TraceSetActiveChannel("Audio");
        TraceMessage("Audio", "NULL pointer passed in to Play().");
        return;
    }

    // plays the sound
    result = soundsystem->playSound(sound, nullptr, isMuted, channel);
    ERRORCHECK(result);

    result = (*channel)->setVolume(1.0f);
}

/* FMOD_DEFAULT as mode for default and FMOD_LOOP_NORMAL for looping audio */
SOUND_PTR Audio::Load(Stream stream, FMOD_MODE mode)
{
    sound1 = 0;
    // creates sound taked from the file input
    const char* buffer = StreamReadString(stream);
    soundsystem->createSound(buffer, mode, NULL, &sound1);

    // returns sound pointer
    return sound1;
}

// Use this function for pausing channel. DOES NOT turn off all channel
void Audio::Pause(bool paused, CHANNEL_PTR channel)
{
    if (!channel) return;
    result = channel->setPaused(paused);
    ERRORCHECK(result);
}

void Audio::Mute(bool mute)
{
    isMuted = mute;
}

void Audio::ChangeVolume(CHANNEL_PTR channel, float _volume)
{
    volume = _volume;
    result = channel->setVolume(volume);
    ERRORCHECK(result);
}

void Audio::Free(SOUND_PTR* sound)
{
    result = (*sound)->release();
    *sound = nullptr;
    ERRORCHECK(result);
}

void Audio::IncreaseVolume(CHANNEL_PTR channel)
{
    if (channel)
    {
        volume += 0.1f;
        channel->setVolume(volume);
    }
}

void Audio::DecreaseVolume(CHANNEL_PTR channel)
{
    if (channel) 
    {
        volume -= 0.1f;
        channel->setVolume(volume);
    }
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

void Audio::ERRORCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        //exit(-1);
    }
}
