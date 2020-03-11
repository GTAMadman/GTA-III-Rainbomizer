#pragma once
#include "plugin.h"
#include "Functions.h"
#include "Config.h"
#include "CRunningScript.h"
#include "CTheScripts.h"
#include "C3dMarker.h"

class Colours : Functions
{
public:
	static void Initialise();
private:
	static void* __fastcall RandomizeColours(CRGBA* colour, void* edx, int r, int g, int b, int a);
	static void* __fastcall RandomizeMiscColours(CRGBA* colour, void* edx, int r, int g, int b, int a);
	static void __fastcall ScriptVehicleColourRandomizer(CRunningScript* thisScript, void* edx, int* arg0, short count);
	static void __fastcall ChooseVehicleColour(CVehicleModelInfo* thisInfo, void* edx, int* prim, int* sec);
	static void __fastcall RandomizeMarkerColours(C3dMarker* marker);
	static int RandomizeColourTable();
	static int GetColour(int pattern, int rgb);
	static CRGBA GetRainbowColour(int r, int g, int b);
	static void HSVtoRGB(int H, double S, double V, int output[3]);
	static struct Pattern
	{
		int ID;
		int colours[3];
	};
	static std::vector<Pattern> Patterns;
};