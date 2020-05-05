#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"

class voices : Functions
{
	static int GetRandomizedMissionAudioSfx (const char* name);
	
public:
	static void Initialise();
};
