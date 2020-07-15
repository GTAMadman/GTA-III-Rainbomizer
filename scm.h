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

class scm : Functions, ModelInfo
{
private:
	static void __fastcall ScriptVehicleRandomizer(CRunningScript* script, void* edx, int* arg0, short count);
	static void __fastcall FixForcedPlayerVehicle(CRunningScript* script, void* edx, int* arg0, short count);
	static void* __fastcall RandomizeADITODeadDodo(CPlane* plane, void* edx, int model, char createdBy);
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
		int doors = 0;
	};
	static std::vector<int> ProcessVehicleTypes(Pattern pattern);
public:
	static void Initialise();
	static std::vector<Pattern> Patterns;
	static void InitialiseVehiclePatterns();
	static int GetIDBasedOnPattern(int origModel, int x, int y, int z, char* thread);
};