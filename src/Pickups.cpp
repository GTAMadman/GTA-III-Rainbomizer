#include "Pickups.h"

std::vector<int> Pickups::allowed_pickups;
std::vector<int> Pickups::original_pickups = { 170, 171, 172, 173, 174, 175, 176, 177,
178, 180, 181, 1362, 1363, 1364, 1383, 1319, 1361 };
int Pickups::RandomizePickups(CVector posn, int modelID, int arg3, int ammo)
{
	int newPickup = modelID;

	for (int i = 0; i < original_pickups.size(); i++)
	{
		if (modelID == original_pickups[i])
		{
			if (Config::pickups.usingSeed)
				newPickup = allowed_pickups[GetRandomUsingCustomSeed(0, allowed_pickups.size() - 1)];
			else
				newPickup = allowed_pickups[RandomNumber(0, allowed_pickups.size() - 1)];

			if (IsMission("cat1") && modelID == 175 && (int)posn.x == -1149 && 
				(int)posn.y == 347 && (int)posn.z == 30)
			{
				newPickup = modelID;
				ammo = 1;
			}
			break;
		}
	}

	if (Config::pickups.forcedPickup > 0)
		newPickup = Config::pickups.forcedPickup;

	return GenerateNewOne(posn, newPickup, arg3, ammo);
}
bool Pickups::GiveMoneyForBriefcase(unsigned short model, int plrIndex)
{
	if (model == 1319)
	{
		if (FindPlayerPed())
			FindPlayerPed()->GetPlayerInfoForThisPlayerPed()->m_nMoney += RandomNumber(1, 500);
	}
	return GivePlayerGoodiesWithPickUpMI(model, plrIndex);
}
int Pickups::GenerateNewOne(CVector posn, int modelID, int arg3, int ammo)
{
	return plugin::CallAndReturn<int, 0x4304B0>(posn, modelID, arg3, ammo);
}
bool Pickups::GivePlayerGoodiesWithPickUpMI(unsigned short model, int plrIndex)
{
	return plugin::CallAndReturn<bool, 0x4339F0>(model, plrIndex);
}
int Pickups::GetRandomUsingCustomSeed(int min, int max)
{
	static std::mt19937 pickupsEngine{ std::hash<std::string>{}(Config::pickups.seed) };
	std::uniform_int_distribution<int> random(min, max);
	return random(pickupsEngine);
}
void Pickups::Initialise()
{
	if (Config::pickups.Enabled)
	{
		if (Config::pickups.weapons)
			for (int i = 0; i < 11; i++)
				allowed_pickups.push_back(original_pickups[i]);
		if (Config::pickups.health)
			allowed_pickups.push_back(1362);
		if (Config::pickups.armour)
			allowed_pickups.push_back(1364);
		if (Config::pickups.adrenaline)
			allowed_pickups.push_back(1363);
		if (Config::pickups.bribes)
			allowed_pickups.push_back(1383);
		if (Config::pickups.briefcase)
			allowed_pickups.push_back(1319);

		if (allowed_pickups.size() == 0)
			return;

		for (int addr : {0x44336B, 0x446C58, 0x446F88, 0x447333,
			0x44740C, 0x448AEF, 0x44AFBC, 0x4DDE91})
			plugin::patch::RedirectCall(addr, RandomizePickups);

		if (Config::pickups.randomizePedDrops)
			plugin::patch::RedirectCall(0x430682, RandomizePickups);

		if (Config::pickups.briefcaseMoney)
		{
			for (int addr : {0x430F2E, 0x430FF7, 0x431186})
				plugin::patch::RedirectCall(addr, GiveMoneyForBriefcase);
		}
	}
}