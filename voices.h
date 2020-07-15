#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include "CTheScripts.h"
#include <string>
#include <cstdint>
#include <unordered_map>
#include <algorithm>
#include <cctype>

class voices : Functions
{
	static std::unordered_map<std::string, std::string> voiceLines;
	static int raySound;
	static char* __fastcall FixSubtitles(CText* text, void* edx, char* key);
	static char* __fastcall FixPaydayForRaySubtitles(CText* text, void* edx, char* key);
	static int GetRandomizedMissionAudioSfx(const char* name);
public:
	static void Initialise();
	static std::unordered_map<std::string, std::string> subtitles;
};