#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include <filesystem>

class voices : Functions
{
public:
	static void Initialise();
private:
	static void __fastcall LoadRandomizedAudio(uint16_t* audio, void* edx, char* text);
	static void PreloadMissionAudio(uint16_t* audio, char* text);
	static void InitialiseSounds();
	static std::vector<std::string> sounds;
};