#pragma once
#include "plugin.h"
#include "Functions.h"
#include "Config.h"
#include "CWeaponInfo.h"
#include "CTheScripts.h"

class Weapons : Functions
{
public:
	static void Initialise();
private:
	static int __fastcall GiveRandomizedWeapon(CPed* ped, void* edx, int weapon, int ammo);
	static void __fastcall SetCurrentWeapon(CPed* ped, void* edx, int slot);
	static void __fastcall FixRoadblockPoliceWeapons(CPed* ped, void* edx, int slot);
	static void ClearWeapons(CPed* ped);
	static int GetWeaponBasedOnPattern(int weapon, int x, int y, int z, int pedID, std::string thread);
	static int GetWeaponSlotFromModelID(int modelID);
	struct Pattern
	{
		int weapon = 0;
		std::vector<int> allowed = {};
		int coords[3] = { 0, 0, 0 };
		std::string thread = "";
	};
	static std::vector<Pattern> Patterns;
	static void InitialiseWeaponPatterns();
};