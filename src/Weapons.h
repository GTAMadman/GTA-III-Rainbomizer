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
	static int __fastcall GiveRandomizedWeapon(CPed* ped, void* edx, eWeaponType weapon, int ammo);
	static void __fastcall SetCurrentWeapon(CPed* ped, void* edx, int slot);
	static void __fastcall SetPlayerCurrentWeapon(CRunningScript* script, void* edx, int* arg0, short count);
	static void GiveRandomWeaponForRampage(int weapon, int time, short kill, int modelId0, unsigned short* text,
		int modelId2, int modelId3, int modelId4, bool standardSound, bool needHeadshot);
	static void __fastcall FixRoadblockPoliceWeapons(CPed* ped, void* edx, int slot);
	static int ProcessWeaponChange(int weapon, int x, int y, int z, bool is_rampage, bool need_headshot, std::string thread);
	static int GetWeaponSlotFromModelID(int modelID);
	struct Pattern
	{
		int weapon = 0;
		bool is_rampage = false;
		bool need_headshot = false;
		std::vector<int> allowed = {};
		int coords[3] = { -1, -1, -1 };
		std::string thread = "";
	};
	inline static int player_weapon = -1;
	static std::vector<Pattern> Patterns;
	static void InitialiseWeaponPatterns();
};