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
public:
	static int RandomNumber(unsigned int min, unsigned int max);
	static void LoadModel(int modelID);
	static int* ms_vehiclesLoaded;
	static bool DoCoordinatesMatch(int x1, int y1, int z1, int x2, int y2, int z2);
	static bool IsModelLoaded(int modelID);
};

