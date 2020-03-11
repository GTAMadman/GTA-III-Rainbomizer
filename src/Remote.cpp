#include "Remote.h"

void Remote::GivePlayerRCVehicle(float x, float y, float z, float angle, short modelId)
{
	int newModel = 0;

	// Check for vehicle pattern
	newModel = scm::GetIDBasedOnPattern(modelId, x, y, z, CTheScripts::pActiveScripts->m_szName);

	LoadModel(newModel);
	CRemote::GivePlayerRemoteControlledCar(x, y, z, angle, newModel);
}
void Remote::Initialise()
{
	if (Config::RCVehiclesRandomizer::Enabled)
	{
		plugin::patch::RedirectCall(0x43E04A, GivePlayerRCVehicle);
		if (scm::Patterns.size() == 0)
			scm::InitialiseVehiclePatterns();
	}
}