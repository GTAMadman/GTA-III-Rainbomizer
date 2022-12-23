#include "Remote.h"

void Remote::GivePlayerRandomRCVehicle(float x, float y, float z, float angle, short modelId)
{
	int newModel = Script::ProcessScriptVehicleChange(modelId, x, y, z, GetMissionThread());

	LoadModel(newModel);
	if (!IsModelLoaded(newModel))
		newModel = modelId;

	CRemote::GivePlayerRemoteControlledCar(x, y, z, angle, newModel);
}
short Remote::FixRCMissions(int modelId)
{
	if (IsRCMission())
	{
		for (CVehicle* vehicle : CPools::ms_pVehiclePool)
		{
			if (vehicle->m_nModelIndex == modelId && vehicle->m_fHealth < 250.0f
				&& vehicle->m_nState != eEntityStatus::STATUS_WRECKED)
				vehicle->BlowUpCar(FindPlayerEntity());
		}
	}
	return QueryModelsKilledByPlayer(modelId);
}
void Remote::Initialise()
{
	if (Config::rc.Enabled)
	{
		plugin::patch::RedirectCall(0x43E04A, GivePlayerRandomRCVehicle);
		plugin::patch::RedirectCall(0x444D21, FixRCMissions);

		if (Script::Patterns.size() == 0)
			Script::InitialiseVehiclePatterns();
	}
}