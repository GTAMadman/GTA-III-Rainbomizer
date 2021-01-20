#include "Remote.h"

void Remote::GivePlayerRandomRCVehicle(float x, float y, float z, float angle, short modelId)
{
	int newModel = 0;

	// Check for vehicle pattern
	newModel = Script::GetIDBasedOnPattern(modelId, x, y, z, CTheScripts::pActiveScripts->m_szName);

	LoadModel(newModel);

	if (!IsModelLoaded(newModel))
		newModel = modelId;

	CRemote::GivePlayerRemoteControlledCar(x, y, z, angle, newModel);
}
void Remote::Initialise()
{
	if (Config::rc.Enabled)
	{
		plugin::patch::RedirectCall(0x43E04A, GivePlayerRandomRCVehicle);

		if (Script::Patterns.size() == 0)
			Script::InitialiseVehiclePatterns();
	}
}