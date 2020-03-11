#pragma once
#include "plugin.h"
#include "Functions.h"
#include "Config.h"
#include "ModelInfo.h"
#include "CPopulation.h"
#include "CAutomobile.h"
#include "CCarAI.h"
#include "eEntityStatus.h"
#include "CBoat.h"
#include "CPlane.h"
#include "CHeli.h"
#include "CTrain.h"
#include "CWorld.h"

class Traffic : Functions
{
private:
	static int ChooseModelToLoad();
	static void* RandomizeCarPeds(ePedType type, int model, CVector* posn);
	static void* __fastcall FixTrafficVehicles(CVehicle* vehicle, void* edx, int model, char createdBy);
	static int ChooseModel();
	static int ChoosePoliceModel();
	static void FixEmptyPoliceCars(CVehicle* vehicle);
	static void __fastcall PedExitCar(CPed* ped, void* edx);
	static void __fastcall PedEnterCar(CPed* ped, void* edx);
	static void ExitCar(CPed* ped);
	static void EnterCar(CPed* ped);
	static void QuitEnteringCar(CPed* ped);
	static void FixBoatSpawns(CEntity* entity);
public:
	static void Initialise();
};