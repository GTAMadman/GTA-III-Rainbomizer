#pragma once
#include "plugin.h"
#include "CStreaming.h"
#include "ModelInfo.h"
#include "CTheScripts.h"
#include <ctime>
#include <random>

class Functions
{
private:
	static std::mt19937 rngEngine;
	static int* ms_vehiclesLoaded;
public:
	static int RandomNumber(int min, int max);
	static void LoadModel(int modelID);
	static bool DoCoordinatesMatch(int x1, int y1, int z1, int x2, int y2, int z2);
	static bool IsModelLoaded(int modelID);
	static int GetNumberOfVehiclesLoaded();
	static int GetRandomLoadedVehicle();
	struct CText
	{
		char* GetText(const char* key);
	};
};