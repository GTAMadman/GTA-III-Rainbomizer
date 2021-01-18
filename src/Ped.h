#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include "CCivilianPed.h"
#include "CCopPed.h"

class Ped : Functions
{
public:
	static void Initialise();
private:
	static void* __fastcall RandomizeGenericPeds(CCivilianPed* ped, void* edx, ePedType type, int model);
	static void* __fastcall RandomizeCopPeds(CCopPed* ped, void* edx, eCopType type);
	static void* __fastcall FixPedsInReplays(CCivilianPed* ped, void* edx, ePedType type, int model);
	static bool IsSpecialModel(int model);
	static bool IsGangMemberForMission(int model);
};