#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include <string>
#include <unordered_map>

class CText;

class voices : Functions
{
	static std::unordered_map<std::string, std::string> voiceLines;
	static char* __fastcall FixSubtitles(CText* t, void* edx, char* key);
	
public:
	static void Initialise();
};
