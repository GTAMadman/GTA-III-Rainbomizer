#include "Parked.h"

void __fastcall Parked::ParkedVehiclesRandomizer(CCarGenerator* gen)
{
	int oldModel = gen->m_nModelId;
	int newModel;

	while ((newModel = RandomNumber(90, 150), ModelInfo::IsMiscVehicle(newModel) ||
		ModelInfo::IsBlacklistedVehicle(newModel) || newModel == 142));

	gen->m_nModelId = (eVehicleModel)newModel;

	gen->DoInternalProcessing();
	gen->m_nModelId = (eVehicleModel)oldModel;
}
void* __fastcall Parked::CarparkVehiclesRandomizer(CVehicle* vehicle, void* edx, int model, char createdBy)
{
	int newModel;

	while ((newModel = GetRandomLoadedVehicle(),ModelInfo::IsMiscVehicle(newModel) || 
		ModelInfo::IsBlacklistedVehicle(newModel) || newModel == 142 || newModel < 90 || newModel > 150));

	#ifndef __GNUC__
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
	#endif

	return vehicle;
}
void Parked::Initialise()
{
	if (Config::parked.Enabled)
	{
		plugin::patch::RedirectCall(0x542BE3, ParkedVehiclesRandomizer);
		plugin::patch::RedirectCall(0x44EE10, CarparkVehiclesRandomizer);
	}
}
