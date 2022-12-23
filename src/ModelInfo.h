#pragma once
#include "plugin.h"
#include "Config.h"
#include "CModelInfo.h"

const int RC_BANDIT_MODEL = 131;
const int DODO_MODEL = 126;
const int DEAD_DODO_MODEL = 141;

class ModelInfo
{
public:
	inline static const int RC_BANDIT_MODEL = 131;
	inline static const int DODO_MODEL = 126;
	static bool IsPoliceVehicle(int modelID);
	static bool IsEmergencyVehicle(int modelID);
	static bool IsBlacklistedVehicle(int modelID);
	static bool IsMiscVehicle(int modelID);
	static std::string CheckVehicleModel(int modelID);
};