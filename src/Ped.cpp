#include "Ped.h"

void* __fastcall Ped::RandomizeGenericPeds(CCivilianPed* ped, void* edx, ePedType type, int model)
{
	int newModel = RandomNumber(0, 82);

	if (Config::ped.forcedPed >= 0 && Config::ped.forcedPed <= 82)
		newModel = Config::ped.forcedPed;

	if (IsSpecialModel(newModel) && !IsModelLoaded(newModel)
		|| IsSpecialModel(model) || IsRampageRunning() || IsGangMemberForMission(model))
		newModel = model;

	LoadModel(newModel);

	if (!IsModelLoaded(newModel))
		newModel = model;

	ped->CCivilianPed::CCivilianPed(type, newModel);

	return ped;
}
void* __fastcall Ped::FixPedsInReplays(CCivilianPed* ped, void* edx, ePedType type, int model)
{
	int newModel = RandomNumber(0, 82);

	if (!IsModelLoaded(newModel) || IsSpecialModel(newModel))
		newModel = model;

	ped->CCivilianPed::CCivilianPed(type, newModel);
	return ped;
}
void* __fastcall Ped::RandomizeCopPeds(CCopPed* ped, void* edx, eCopType type)
{
	eCopType newType;
	int random = RandomNumber(1, 4);

	switch (random)
	{
	case 1:
		newType = eCopType::COP_TYPE_COP;
		break;
	case 2:
		newType = eCopType::COP_TYPE_SWAT;
		break;
	case 3:
		newType = eCopType::COP_TYPE_FBI;
		break;
	case 4:
		newType = eCopType::COP_TYPE_ARMY;
		break;
	}

	LoadModel(random);

	if (!IsModelLoaded(random))
		newType = type;

	ped->CCopPed::CCopPed(newType);

	return ped;
}
bool Ped::IsGangMemberForMission(int model)
{
	// Mssion fixes
	if (model == 14 || model == 15)
	{
		if (IsMission("yard2"))
			return true;
	}
	if (model == 22 || model == 23)
	{
		if (IsMission("hood1"))
			return true;
	}

	return false;
}
bool Ped::IsSpecialModel(int model)
{
	switch (model)
	{
	case 26:
	case 27:
	case 28:
	case 29:
		return true;
	}
	return false;
}
void Ped::Initialise()
{
	if (Config::ped.Enabled)
	{
		if (Config::ped.genericPeds)
		{
			for (int addr : {0x43BB20, 0x43E67F, 0x441A2F, 0x44C0D3, 0x4F52BB,
				0x4F554B, 0x4F5655, 0x585C51, 0x5872FC})
				plugin::patch::RedirectCall(addr, RandomizeGenericPeds);

			plugin::patch::RedirectCall(0x5955DF, FixPedsInReplays);
		}

		if (Config::ped.copPeds)
		{
			for (int addr : {0x437926, 0x437946, 0x43BAC6,
				0x43E627, 0x4419D6, 0x4F53A7})
				plugin::patch::RedirectCall(addr, RandomizeCopPeds);
		}
	}
}