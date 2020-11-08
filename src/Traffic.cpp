#include "Traffic.h"

int Traffic::ChooseModelToLoad()
{
	int newModel = RandomNumber(90, 150);

	while (ModelInfo::IsBlacklistedVehicle(newModel))
		newModel = RandomNumber(90, 150);

	return newModel;
}
int Traffic::ChooseModel()
{
	int model;
	while ((model = ms_vehiclesLoaded[RandomNumber(0, CStreaming::ms_numVehiclesLoaded - 1)], 
		ModelInfo::IsBlacklistedVehicle(model) || model < 90 || model > 150));

	if (!IsModelLoaded(model))
		return -1;

	return model;
}
int Traffic::ChoosePoliceModel()
{
	int model;
	while ((model = ms_vehiclesLoaded[RandomNumber(0, CStreaming::ms_numVehiclesLoaded - 1)],
		ModelInfo::IsBlacklistedVehicle(model) || model < 90 || model > 150));

	if (!IsModelLoaded(model))
		return 116;

	return model;
}
void* Traffic::RandomizeCarPeds(ePedType type, int model, CVector* posn)
{
	switch (type)
	{
	case 16:
		model = 5;
		break;
	case 17:
		model = 6;
		break;
	}

	switch (model)
	{
	case 1:
	case 3:
		model = 0;
		break;
	}
	int loadModel = model;

	if (!IsModelLoaded(model))
		LoadModel(loadModel);

	return CPopulation::AddPed(type, model, posn);
}
void* __fastcall Traffic::FixTrafficVehicles(CVehicle* vehicle, void* edx, int model, char createdBy)
{
	#ifndef __GNUC__
	if (CModelInfo::IsBoatModel(model))
		reinterpret_cast<CBoat*>(vehicle)->CBoat::CBoat(model, createdBy);
	
	if (CModelInfo::IsPlaneModel(model))
		reinterpret_cast<CPlane*>(vehicle)->CPlane::CPlane(model, createdBy);

	if (CModelInfo::IsHeliModel(model))
		reinterpret_cast<CHeli*>(vehicle)->CHeli::CHeli(model, createdBy);

	if (CModelInfo::IsTrainModel(model))
		reinterpret_cast<CTrain*>(vehicle)->CTrain::CTrain(model, createdBy);

	if (CModelInfo::IsCarModel(model))
		reinterpret_cast<CAutomobile*>(vehicle)->CAutomobile::CAutomobile(model, createdBy);
	#endif

	return vehicle;
}
void Traffic::FixEmptyPoliceCars(CVehicle* vehicle)
{
	int origModel = vehicle->m_nModelIndex;
	vehicle->m_nModelIndex = 116;

	CCarAI::AddPoliceCarOccupants(vehicle);
	vehicle->m_nModelIndex = origModel;
}
void __fastcall Traffic::PedExitCar(CPed* ped, void* edx)
{
	if (ped->m_pVehicle->m_nModelIndex == RC_BANDIT_MODEL)
	{
		// Teleporting the ped out crashes, so I just remove them :P
		ped->m_bInVehicle = false;
		CWorld::Remove(ped);
	}
	else
		ExitCar(ped);
}
void __fastcall Traffic::PedEnterCar(CPed* ped, void* edx)
{
	ped->m_pVehicle->m_nModelIndex == RC_BANDIT_MODEL ? QuitEnteringCar(ped) : EnterCar(ped);
}
void Traffic::FixBoatSpawns(CEntity* entity)
{
	if (CModelInfo::IsBoatModel(entity->m_nModelIndex))
		entity->m_nState = eEntityStatus::STATUS_PHYSICS;

	CWorld::Add(entity);
}
void Traffic::ExitCar(CPed* ped)
{
	plugin::Call<0x4E18D0>(ped);
}
void Traffic::EnterCar(CPed* ped)
{
	plugin::Call<0x4E0D30>(ped);
}
void Traffic::QuitEnteringCar(CPed* ped)
{
	plugin::Call<0x4E0E00>(ped);
}
void Traffic::Initialise()
{
	if (Config::TrafficRandomizer::Enabled)
	{
		plugin::patch::RedirectCall(0x4167DB, ChooseModel);
		plugin::patch::RedirectCall(0x4167AD, ChoosePoliceModel);
		plugin::patch::RedirectCall(0x417FDE, ChoosePoliceModel);
		plugin::patch::RedirectCall(0x40AFF2, ChooseModelToLoad);
		plugin::patch::RedirectCall(0x4F59CD, RandomizeCarPeds);
		plugin::patch::RedirectCall(0x416C9E, FixTrafficVehicles);
		plugin::patch::RedirectCall(0x417CE8, FixEmptyPoliceCars);
		plugin::patch::RedirectCall(0x4B1EDB, PedExitCar);
		plugin::patch::RedirectCall(0x4B1EBB, PedEnterCar);
		plugin::patch::RedirectCall(0x417CD7, FixBoatSpawns);
	}
}
