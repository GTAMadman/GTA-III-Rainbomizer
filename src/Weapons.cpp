#include "Weapons.h"

std::vector<Weapons::Pattern> Weapons::Patterns;
int __fastcall Weapons::GiveRandomizedWeapon(CPed* ped, void* edx, eWeaponType weapon, int ammo)
{
	if (!Config::weapons.randomizePlayerWeapons && (ped == FindPlayerPed()) || weapon == 12)
	{
		ped->GiveWeapon(weapon, ammo);
		return weapon;
	}

	// Stored Coordinates
	int x = ped->GetPosition().x;
	int y = ped->GetPosition().y;
	int z = ped->GetPosition().z;

	int newWeapon = ProcessWeaponChange(weapon, x, y, z, false, false, GetMissionThread());
	int weaponModel = CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_nModelId;

	// Load the weapon model before setting it
	LoadModel(weaponModel);
	if (!IsModelLoaded(weaponModel))
		newWeapon = weapon;

	ped->GiveWeapon((eWeaponType)newWeapon, ammo);

	if (Config::weapons.randomizePlayerWeapons && ped == FindPlayerPed())
	{
		player_weapon = newWeapon;
		return newWeapon;
	}
	ped->m_nWepModelID = weaponModel;

	return newWeapon;
}
void __fastcall Weapons::SetCurrentWeapon(CPed* ped, void* edx, int slot)
{
	if (ped == FindPlayerPed())
		ped->SetCurrentWeapon(slot);
	else
		ped->SetCurrentWeapon(GetWeaponSlotFromModelID(ped->m_nWepModelID));
}
void __fastcall Weapons::SetPlayerCurrentWeapon(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	int& weapon = CTheScripts::ScriptParams[1].iParam;

	if (weapon != 12)
	{
		if (player_weapon > -1)
			weapon = player_weapon;
		else
			weapon = 0;
	}
}
void Weapons::GiveRandomWeaponForRampage(int weapon, int time, short kill, int modelId0, unsigned short* text,
	int modelId2, int modelId3, int modelId4, bool standardSound, bool needHeadshot)
{
	int newWeapon = ProcessWeaponChange(weapon, 0, 0, 0, true, needHeadshot, GetMissionThread());
	int weaponModel = CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_nModelId;

	LoadModel(weaponModel);
	if (!IsModelLoaded(weaponModel))
		newWeapon = weapon;

	StartFrenzy(newWeapon, time, kill, modelId0, text, modelId2, modelId3, modelId4, standardSound, needHeadshot);
}
void __fastcall Weapons::FixRoadblockPoliceWeapons(CPed* ped, void* edx, int slot)
{
	ClearWeapons(ped);
	int weapon = 2;

	LoadModel(CWeaponInfo::GetWeaponInfo((eWeaponType)weapon)->m_nModelId);

	ped->GiveWeapon((eWeaponType)weapon, 1000);
	ped->m_nWepModelID = CWeaponInfo::GetWeaponInfo((eWeaponType)weapon)->m_nModelId;

	ped->SetCurrentWeapon(GetWeaponSlotFromModelID(ped->m_nWepModelID));
}
void Weapons::InitialiseWeaponPatterns()
{
	// Cipriani's Chauffeur
	Pattern pattern = { .weapon = {2}, .allowed = {2, 3}, .coords = {850, -663, 14} };
	Patterns.push_back(pattern);

	pattern = { .weapon = {2}, .allowed = {2, 3}, .coords = {850, -664, 14} };
	Patterns.push_back(pattern);

	// Gone Fishing
	pattern = { .weapon = {11}, .allowed = {11}, .thread = {"ray4"} };
	Patterns.push_back(pattern);

	// Rumble
	pattern = { .weapon = {1}, .allowed = {1}, .thread = {"hood5"} };
	Patterns.push_back(pattern);

	// Silence the Sneak
	pattern = { .weapon = {11}, .allowed = {11, 8}, .thread = {"ray1"} };
	Patterns.push_back(pattern);

	// Uzi Rider
	pattern = { .weapon = {3}, .allowed = {3}, .thread = {"yard2"} };
	Patterns.push_back(pattern);


	/* RAMPAGES */


	// Drive-By
	pattern = { .weapon = {19}, .is_rampage = {true}, .allowed = {19} };
	Patterns.push_back(pattern);

	// Run-Over
	pattern = { .weapon = {17}, .is_rampage = {true}, .allowed = {17} };
	Patterns.push_back(pattern);

	// M16 - Destroy Vehicles
	pattern = { .weapon = {6}, .is_rampage = {true}, .allowed = {6, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} };
	Patterns.push_back(pattern);

	// M16 - Need Headshot
	pattern = { .weapon = {6}, .is_rampage = {true}, .need_headshot = {true}, .allowed = {6, 7} };
	Patterns.push_back(pattern);

	// Uzi
	pattern = { .weapon = {3}, .is_rampage = {true}, .allowed = {3, 2, 4, 5, 6, 7, 8, 9, 10, 11} };
	Patterns.push_back(pattern);

	// RPG
	pattern = { .weapon = {8}, .is_rampage = {true}, .allowed = {8, 2, 3, 4, 5, 6, 7, 9, 10, 11} };
	Patterns.push_back(pattern);

	// Shotgun
	pattern = { .weapon = {4}, .is_rampage = {true}, .allowed = {4, 2, 3, 5, 6, 7, 8, 9, 10, 11} };
	Patterns.push_back(pattern);

	// Grenades
	pattern = { .weapon = {11}, .is_rampage = {true}, .allowed = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} };
	Patterns.push_back(pattern);

	// Molotovs
	pattern = { .weapon = {10}, .is_rampage = {true}, .allowed = {10, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} };
	Patterns.push_back(pattern);

	// AK47
	pattern = { .weapon = {5}, .is_rampage = {true}, .allowed = {5, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} };
	Patterns.push_back(pattern);

	// Flamethrower
	pattern = { .weapon = {9}, .is_rampage = {true}, .allowed = {9, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11} };
	Patterns.push_back(pattern);

	// Sniper
	pattern = { .weapon = {7}, .is_rampage = {true}, .need_headshot = {true}, .allowed = {7, 6} };
	Patterns.push_back(pattern);

}
int Weapons::ProcessWeaponChange(int weapon, int x, int y, int z, bool is_rampage, bool need_headshot, std::string thread)
{
	if (Config::weapons.forcedWeapon >= 1 && Config::weapons.forcedWeapon <= 12)
		return Config::weapons.forcedWeapon;

	for (int i = 0; i < Patterns.size(); i++)
	{
		int index = i;
		std::vector<int> weapons;

		if (Patterns[index].weapon == weapon)
		{
			// Check for more than one weapon of same type in pattern by using coords
			for (int a = 0; a < Patterns.size(); a++)
			{
				if (DoCoordinatesMatch(Patterns[a].coords[0], Patterns[a].coords[1], Patterns[a].coords[2], x, y, z))
				{
					index = a;
					break;
				}
			}

			// Coordinate Check
			if (DoCoordinatesMatch(Patterns[index].coords[0], Patterns[index].coords[1], Patterns[index].coords[2], x, y, z))
				weapons = Patterns[index].allowed;

			// Thread Check
			if (Patterns[index].thread != "" || Patterns[index].thread != "noname")
			{
				if (Patterns[index].thread == thread)
					weapons = Patterns[index].allowed;
			}
			// Rampages Check
			if (Patterns[index].is_rampage && Patterns[index].need_headshot == need_headshot)
				weapons = Patterns[index].allowed;

			if (weapons.size() > 0)
				return weapons[RandomNumber(0, weapons.size() - 1)];
		}
	}
	return RandomNumber(1, 11);
}
int Weapons::GetWeaponSlotFromModelID(int modelID)
{
	switch (modelID)
	{
	case 170:
		return 11;
	case 171:
		return 5;
	case 172:
		return 1;
	case 173:
		return 2;
	case 174:
		return 10;
	case 175:
		return 8;
	case 176:
		return 4;
	case 177:
		return 7;
	case 178:
		return 3;
	case 180:
		return 6;
	case 181:
		return 9;
	case 182:
		return 12;
	}
	return 0;
}
void Weapons::Initialise()
{
	if (Config::weapons.Enabled)
	{
		for (int addr : {0x4410B9, 0x441102, 0x4C1201, 0x4C1250, 
			0x4C1260, 0x4C12AF, 0x4C12BF, 0x4C130B,0x4C131B, 
			0x4C1328, 0x4C503F, 0x4DB768, 0x4F537E, 0x4F5611, 
			0x4F562B, 0x551F98, 0x587552, 0x5882A9, 0x588377})
			plugin::patch::RedirectCall(addr, GiveRandomizedWeapon);

		for (int addr : {0x44110A, 0x441337, 0x4C126B, 0x4C12CA, 0x4C1333, 
			0x4C1ECE, 0x4C1F88, 0x4C2C0E, 0x4C2C79, 0x4CEF31, 0x4CF1E9,
			0x4DB771, 0x4DD2AA, 0x4DD95C, 0x4DD971, 0x4E045B, 0x4E0AB6,
			0x4E0F29, 0x4E147D, 0x4F2583, 0x4F5386, 0x4F5633, 0x4F59E9, 
			0x5875AA, 0x5883CF })
			plugin::patch::RedirectCall(addr, SetCurrentWeapon);

		if (Config::weapons.randomizePlayerWeapons)
		{
			plugin::patch::RedirectCall(0x4412AA, SetPlayerCurrentWeapon);
			if (Config::weapons.randomizeRampageWeapons)
			{
				plugin::patch::RedirectCall(0x442BD2, GiveRandomWeaponForRampage);
				plugin::patch::RedirectCall(0x44B9FE, GiveRandomWeaponForRampage);
			}
		}
		plugin::patch::RedirectCall(0x437951, FixRoadblockPoliceWeapons);

		if (Patterns.size() == 0)
			InitialiseWeaponPatterns();
	}
}