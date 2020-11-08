#include "Weapons.h"

std::vector<Weapons::Pattern> Weapons::Patterns;
int __fastcall Weapons::GiveRandomizedWeapon(CPed* ped, void* edx, int weapon, int ammo)
{
	if (ped == FindPlayerPed())
	{
		ped->GiveWeapon((eWeaponType)weapon, ammo);
		return weapon;
	}

	// Stored Coordinates
	int x = ped->GetPosition().x;
	int y = ped->GetPosition().y;
	int z = ped->GetPosition().z;

	int newWeapon = 0;

	// Check pattern
	if (ped->m_nModelIndex != 1) // Fix cops
		newWeapon = GetWeaponBasedOnPattern(weapon, x, y, z, ped->m_nModelIndex, CTheScripts::pActiveScripts->m_szName);

	// Give random weapon
	if (newWeapon == 0)
		newWeapon = RandomNumber(1, 11);

	int weaponModel = CWeaponInfo::GetWeaponInfo((eWeaponType)newWeapon)->m_nModelId;

	// Load the weapon model before setting it
	if (!IsModelLoaded(weaponModel))
		LoadModel(weaponModel);

	ped->GiveWeapon((eWeaponType)newWeapon, ammo);
	ped->m_nWepModelID = weaponModel;

	return newWeapon;
}
void __fastcall Weapons::SetCurrentWeapon(CPed* ped, void* edx, int slot)
{
	if (ped == FindPlayerPed())
	{
		ped->SetCurrentWeapon(slot);
		return;
	}
	ped->SetCurrentWeapon(GetWeaponSlotFromModelID(ped->m_nWepModelID));
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
void Weapons::ClearWeapons(CPed* ped)
{
	plugin::CallMethod<0x4CFB70, CPed*>(ped);
}
void Weapons::InitialiseWeaponPatterns()
{
	// Cipriani's Chauffeur
	Pattern pattern = { .weapon = {2}, .allowed = {2, 3}, .coords = {850, -663, 14} };
	Patterns.push_back(pattern);

	pattern = { .weapon = {2}, .allowed = {2, 3}, .coords = {850, -664, 14} };
	Patterns.push_back(pattern);

	// Gone Fishing
	pattern = { .weapon = {11}, .allowed = {11}, .pedID = {7} };
	Patterns.push_back(pattern);

	// Rumble
	pattern = { .weapon = {1}, .allowed = {1}, .pedID = {22, 23}, .thread = {"hood5"} };
	Patterns.push_back(pattern);
}
/* I've only built the pattern system to work with the necessary patterns for the main game.
   This may be changed in future. */
int Weapons::GetWeaponBasedOnPattern(int weapon, int x, int y, int z, int pedID, std::string thread)
{
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

			// Ped Check
			for (int x = 0; x < sizeof(Patterns[index].pedID); x++)
			{
				if (Patterns[index].pedID[x] == pedID)
				{
					weapons = Patterns[index].allowed;
					break;
				}
			}

			// Ped and Thread Check
			if (Patterns[index].thread != "" || Patterns[index].thread != "noname")
			{
				for (int x = 0; x < sizeof(Patterns[index].pedID); x++)
				{
					if (Patterns[index].pedID[x] == pedID && Patterns[index].thread == thread)
					{
						weapons = Patterns[index].allowed;
						break;
					}
				}
			}
			if (weapons.size() > 0)
				return weapons[RandomNumber(0, weapons.size() - 1)];
		}
	}
	return 0;
}
/* Had to create my own function for this */
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
		return 9;;
	}
	return 0;
}
void Weapons::Initialise()
{
	if (Config::weapons.Enabled)
	{
		// CPed::GiveWeapon
		for (int weaponAddresses : { 0x4211CC, 0x421201, 0x427BDC, 0x430F5C, 0x431056,
			0x4311E3, 0x4410B9, 0x441102, 0x4C1201, 0x4C1250, 0x4C1260, 0x4C12AF,
			0x4C12BF, 0x4C130B, 0x4C131B, 0x4C1328, 0x4C503F, 0x4DB768, 0x4F537E,
			0x4F5611, 0x4F562B, 0x551F98, 0x587552, 0x5882A9, 0x588377 })
			plugin::patch::RedirectCall(weaponAddresses, GiveRandomizedWeapon);

		// CPed::SetCurrentWeapon
		for (int setWepAddresses : { 0x437951, 0x44110A, 0x441337, 0x4C126B, 0x4C12CA,
			0x4C1333, 0x4C1ECE, 0x4C1F88, 0x4C2C0E, 0x4C2C79, 0x4CEF31, 0x4CF1E9,
			0x4DB771, 0x4DD2AA, 0x4DD95C, 0x4DD971, 0x4E045B, 0x4E0AB6, 0x4E0F29,
			0x4E147D, 0x4F2583, 0x4F5386, 0x4F5633, 0x4F59E9, 0x5875AA, 0x5883CF })
			plugin::patch::RedirectCall(setWepAddresses, SetCurrentWeapon);

		plugin::patch::RedirectCall(0x437951, FixRoadblockPoliceWeapons);

		if (Patterns.size() == 0)
			InitialiseWeaponPatterns();
	}
}