#include "Parked.h"

void __fastcall Parked::ParkedVehiclesRandomizer(CCarGenerator* gen)
{
	int oldModel = gen->m_nModelId;
	int newModel = RandomNumber(90, 150);

	while (ModelInfo::IsBlacklistedVehicle(newModel) || newModel == DEAD_DODO_MODEL)
	{
		newModel = RandomNumber(90, 150);
	}
	gen->m_nModelId = (eVehicleModel)newModel;

	gen->DoInternalProcessing();
}
void* __fastcall Parked::CarparkVehiclesRandomizer(CVehicle* vehicle, void* edx, int model, char createdBy)
{
	int newModel;

	while ((newModel = ms_vehiclesLoaded[RandomNumber(0, CStreaming::ms_numVehiclesLoaded - 1)],
		ModelInfo::IsBlacklistedVehicle(newModel) || newModel < 90 || newModel > 150 || newModel == ModelInfo::DEAD_DODO_MODEL));

	if (CModelInfo::IsBoatModel(newModel))
		reinterpret_cast<CBoat*>(vehicle)->CBoat::CBoat(newModel, createdBy);

	if (CModelInfo::IsPlaneModel(newModel))
		reinterpret_cast<CPlane*>(vehicle)->CPlane::CPlane(newModel, createdBy);

	if (CModelInfo::IsHeliModel(newModel))
		reinterpret_cast<CHeli*>(vehicle)->CHeli::CHeli(newModel, createdBy);

	if (CModelInfo::IsTrainModel(newModel))
		reinterpret_cast<CTrain*>(vehicle)->CTrain::CTrain(newModel, createdBy);

	if (CModelInfo::IsCarModel(newModel))
		reinterpret_cast<CAutomobile*>(vehicle)->CAutomobile::CAutomobile(newModel, createdBy);

	return vehicle;
}
void Parked::Initialise()
{
	if (Config::ParkedVehiclesRandomizer::Enabled)
	{
		plugin::patch::RedirectCall(0x542BE3, ParkedVehiclesRandomizer);
		plugin::patch::RedirectCall(0x44EE10, CarparkVehiclesRandomizer);
	}
}