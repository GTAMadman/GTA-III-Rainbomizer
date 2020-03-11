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
bool ModelInfo::IsBlacklistedVehicle(int modelID)
{
	switch (modelID)
	{
	case 124:
	case 125:
	case 140:
	case 141:
	case 147:
		return true;
	}
	return false;
}