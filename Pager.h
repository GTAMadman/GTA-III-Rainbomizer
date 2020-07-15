#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include "voices.h"

class Pager : Functions
{
public:
	static void Initialise();
private:
	static void __fastcall RandomizePagerMessages(CText* text, void* edx, char* key);
	static void AddSubtitleKeys();
	static std::vector<std::string> PagerKeys;
};