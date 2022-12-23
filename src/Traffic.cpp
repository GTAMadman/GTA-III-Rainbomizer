#include "Traffic.h"

int Traffic::ChooseModelToLoad()
{
	int model;

	// Forced vehicles
	if (Config::traffic.forcedVehicle >= 90 && Config::traffic.forcedVehicle <= 150)
		return Config::traffic.forcedVehicle;

	while ((model = RandomNumber(90, 150)), !IsVehicleAllowed(model) && !IsModelLoaded(model));

	return model;
}
int Traffic::RandomizeTraffic()
{
	int model;

	// Forced vehicles
	if (Config::traffic.forcedVehicle >= 90 && Config::traffic.forcedVehicle <= 150)
	{
		model = Config::traffic.forcedVehicle;
		if (!IsModelLoaded(model))
			LoadModel(model);

		return model;
	}
	for (int i = 0; i < 21; i++)
	{
		model = GetRandomLoadedVehicle();
		if (!IsVehicleAllowed(model) || ModelInfo::IsBlacklistedVehicle(model)
			|| model < 90 || model > 150)
			continue;

		return model;
	}

	/* Sometimes it will run this function before ChooseModelToLoad,
	so I fix this by forcing an allowed vehicle and loading it */
	while ((model = RandomNumber(90, 150)), !IsVehicleAllowed(model));

	if (!IsModelLoaded(model))
		LoadModel(model);

	return model;
}
int Traffic::RandomizePoliceTraffic()
{
	int model;

	if (Config::traffic.forcedVehicle >= 90 && Config::traffic.forcedVehicle <= 150)
	{
		model = Config::traffic.forcedVehicle;
		if (!IsModelLoaded(model))
			LoadModel(model);

		return model;
	}

	while ((model = GetRandomLoadedVehicle(), ModelInfo::IsMiscVehicle(model) ||
		ModelInfo::IsBlacklistedVehicle(model)) || model < 90 || model > 150);

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
void* __fastcall Traffic::RandomizeRoadblocks(CVehicle* vehicle, void* edx, int model, char createdBy)
{
	int newModel;
	while ((newModel = GetRandomLoadedVehicle()), ModelInfo::IsMiscVehicle(newModel) ||
		ModelInfo::IsBlacklistedVehicle(newModel));

	if (Config::traffic.forcedVehicle >= 90 && Config::traffic.forcedVehicle <= 150)
		newModel = Config::traffic.forcedVehicle;

	if (!IsModelLoaded(newModel))
		newModel = model;

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
	
	vehicle->m_nState = eEntityStatus::STATUS_PHYSICS;

	return vehicle;
}
void* __fastcall Traffic::FixTrafficVehicles(CVehicle* vehicle, void* edx, int model, char createdBy)
{
	#ifndef __GNUC__
	if (ModelInfo::IsMiscVehicle(model))
	{
		reinterpret_cast<CBoat*>(vehicle)->CBoat::CBoat(model, createdBy);

		// Give train and Dead Dodo more health to stop them from instantly exploding
		if (model == 124 || model == 141)
			vehicle->m_fHealth = 10000;

		return vehicle;
	}
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

	if (vehicle->m_nModelIndex == 116)
	{
		vehicle->ChangeLawEnforcerState(1);
		vehicle->m_nDoorLock = 5;
	}

	return vehicle;
}
int Traffic::ChoosePoliceVehicle(int model)
{
	if (ModelInfo::IsPoliceVehicle(model))
		return model;
	return 116;
}
void Traffic::FixEmptyPoliceCars(CVehicle* vehicle)
{
	int origModel = vehicle->m_nModelIndex;
	vehicle->m_nModelIndex = ChoosePoliceVehicle(origModel);

	CCarAI::AddPoliceCarOccupants(vehicle);
	vehicle->m_nModelIndex = origModel;
}
void __fastcall Traffic::PedEnterCar(CPed* ped)
{
	if (ped->m_pVehicle->m_nModelIndex == ModelInfo::RC_BANDIT_MODEL)
	{
		QuitEnteringCar(ped);
		FindPlayerPed()->SetObjective((eObjective)0);
		CPad::GetPad(CWorld::PlayerInFocus)->Clear(true);
	}
	else
	EnterCar(ped);
}
void __fastcall Traffic::PedExitCar(CPed* ped)
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
void Traffic::FixBoatSpawns(CEntity* entity)
{
	if (CModelInfo::IsBoatModel(entity->m_nModelIndex) || ModelInfo::IsEmergencyVehicle(entity->m_nModelIndex)
		&& entity->m_nModelIndex != 97) // Don't need to give Firetuck's real physics
		entity->m_nState = eEntityStatus::STATUS_PHYSICS;

	CWorld::Add(entity);
}
bool Traffic::IsVehicleAllowed(int model)
{
	if (model < 90 || model > 150)
		return false;

	if (model == 124 && Config::traffic.train)
		return true;

	if (model == 140 && Config::traffic.airTrain)
		return true;

	if (model == RC_BANDIT_MODEL && Config::traffic.RCBandit)
		return true;

	if (model == DEAD_DODO_MODEL && Config::traffic.deadDodo)
		return true;

	if (model == DODO_MODEL && Config::traffic.dodo)
		return true;

	if (CModelInfo::IsBoatModel(model) && Config::traffic.boats)
		return true;

	if (CModelInfo::IsCarModel(model) && model != 131 &&
		model != 126 && model != 141 && Config::traffic.cars)
		return true;

	return false;
}
bool Traffic::AllVehiclesDisabled()
{
	if (Config::traffic.cars)
		return false;
	if (Config::traffic.airTrain)
		return false;
	if (Config::traffic.boats)
		return false;
	if (Config::traffic.deadDodo)
		return false;
	if (Config::traffic.dodo)
		return false;
	if (Config::traffic.RCBandit)
		return false;
	if (Config::traffic.train)
		return false;
	if (Config::traffic.forcedVehicle >= 90 && Config::traffic.forcedVehicle <= 150)
		return false;

	return true;
}
void Traffic::FixBoatPeds(CPed* ped){}
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
	if (Config::traffic.Enabled)
	{
		if (AllVehiclesDisabled())
			return;

		plugin::patch::RedirectCall(0x4167DB, RandomizeTraffic);
		plugin::patch::RedirectCall(0x4167AD, RandomizePoliceTraffic);
		plugin::patch::RedirectCall(0x417FDE, RandomizePoliceTraffic);
		plugin::patch::RedirectCall(0x40AFF2, ChooseModelToLoad);
		plugin::patch::RedirectCall(0x4F59CD, RandomizeCarPeds);
		plugin::patch::RedirectCall(0x416C9E, FixTrafficVehicles);
		plugin::patch::RedirectCall(0x417CE8, FixEmptyPoliceCars);
		plugin::patch::RedirectCall(0x4B1EBB, PedEnterCar);
		plugin::patch::RedirectCall(0x4B1EDB, PedExitCar);
		plugin::patch::RedirectCall(0x417CD7, FixBoatSpawns);
		plugin::patch::RedirectCall(0x4DB1F2, FixBoatPeds);

		if (Config::traffic.roadblocksEnabled)
			plugin::patch::RedirectCall(0x43749C, RandomizeRoadblocks);
	}
}