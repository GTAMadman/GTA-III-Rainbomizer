#pragma once
#include "plugin.h"
#include "Functions.h"
#include "Config.h"
#include "ModelInfo.h"
#include "CStreaming.h"
#include "CRunningScript.h"
#include "CTheScripts.h"
#include "CVehicleModelInfo.h"
#include "CBoat.h"
#include "CPlane.h"
#include "CHeli.h"
#include "CCarCtrl.h"

class Script : Functions, ModelInfo
{
private:
	static void __fastcall ScriptVehicleRandomizer(CRunningScript* script, void* edx, int* arg0, short count);
	static void __fastcall FixForcedPlayerVehicle(CRunningScript* script, void* edx, int* arg0, short count);
	static void* __fastcall RandomizeADITODeadDodo(CPlane* plane, void* edx, int model, char createdBy);
	static void FixUziRiderDriveToCoords(CVehicle* vehicle, CVector coords, bool arg2);
	struct Pattern
	{
		int vehicle = 0;
		std::string gVehicle = "";
		std::vector<int> allowed = {};
		std::vector<int> denied = {};
		std::vector<std::string> allowedType = {};
		int coords[3] = { 0, 0, 0 };
		int move[3] = { 0, 0, 0 };
		std::string thread = "";
		bool door_check = false;
	};
	static std::vector<int> ProcessVehicleTypes(Pattern pattern);
public:
	static void Initialise();
	static std::vector<Pattern> Patterns;
	static void InitialiseVehiclePatterns();
	static int ProcessScriptVehicleChange(int origModel, int x, int y, int z, std::string thread);
};