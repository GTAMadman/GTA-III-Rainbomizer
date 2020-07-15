#pragma once
#include "plugin.h"
#include "Config.h"
#include "CModelInfo.h"

class ModelInfo
{
public:
	static const int RC_BANDIT_MODEL = 131;
	static const int DODO_MODEL = 126;
	static bool IsEmergencyVehicle(int modelID);
	static bool IsBlacklistedVehicle(int modelID);
	static bool IsMiscVehicle(int modelID);
	static std::string CheckVehicleModel(int modelID);
};