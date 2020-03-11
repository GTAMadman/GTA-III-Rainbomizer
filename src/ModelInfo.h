#pragma once
#include "plugin.h"
#include "CModelInfo.h"
#include <string>

class ModelInfo
{
public:
	static const int RC_BANDIT_MODEL = 131;
	static const int DODO_MODEL = 126;
	static const int DEAD_DODO_MODEL = 141;
	static bool IsBlacklistedVehicle(int modelID);
	static std::string CheckVehicleModel(int modelID);
};