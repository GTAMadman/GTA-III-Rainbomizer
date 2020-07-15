#include "ModelInfo.h"

std::string ModelInfo::CheckVehicleModel(int modelID)
{
	if (IsBlacklistedVehicle(modelID))
		return "unknown";

	if (modelID == RC_BANDIT_MODEL)
		return "rc";

	if (CModelInfo::IsBoatModel(modelID))
		return "boat";

	if (modelID == DODO_MODEL)
		return "dodo";

	if (CModelInfo::IsCarModel(modelID))
		return "car";

	return "unknown";
}
bool ModelInfo::IsEmergencyVehicle(int modelID)
{
	switch (modelID)
	{
	case 97:
	case 106:
	case 107:
	case 116:
	case 117:
	case 122:
	case 123:
		return true;
	}
	return false;
}
bool ModelInfo::IsMiscVehicle(int modelID)
{
	switch (modelID)
	{
	case 141:
	case 124:
	case 140:
		return true;
	}
	return false;
}
bool ModelInfo::IsBlacklistedVehicle(int modelID)
{
	switch (modelID)
	{
	case 141:
		if (Config::traffic.deadDodo)
			return false;
	case 124:
		if (Config::traffic.train)
			return false;
	case 140:
		if (Config::traffic.airTrain)
			return false;
	case 125:
	case 147:
		return true;
	}
	return false;
}