#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"

class Pickups : Functions
{
public:
	static void Initialise();
private:
	static int RandomizePickups(CVector posn, int modelID, int arg3, int ammo);
	static int GenerateNewOne(CVector posn, int modelID, int arg3, int ammo);
	static int GetRandomUsingCustomSeed(int min, int max);
	static bool GiveMoneyForBriefcase(unsigned short model, int plrIndex);
	static bool GivePlayerGoodiesWithPickUpMI(unsigned short model, int plrIndex);
	static std::vector<int> original_pickups;
	static std::vector<int> allowed_pickups;
};