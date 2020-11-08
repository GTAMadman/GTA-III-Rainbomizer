#pragma once
#include "plugin.h"
#include "CModelInfo.h"
#include <string>

const int RC_BANDIT_MODEL = 131;
const int DODO_MODEL = 126;
const int DEAD_DODO_MODEL = 141;

class ModelInfo
{
public:
	static bool IsBlacklistedVehicle(int modelID);
	static std::string CheckVehicleModel(int modelID);
};
