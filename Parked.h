#pragma once
#include "plugin.h"
#include "Functions.h"
#include "Config.h"
#include "CBoat.h"
#include "CPlane.h"
#include "CHeli.h"
#include "ModelInfo.h"
#include "CCarGenerator.h"

class Parked : Functions, ModelInfo
{
public:
	static void Initialise();
	static void __fastcall ParkedVehiclesRandomizer(CCarGenerator* gen);
	static void* __fastcall CarparkVehiclesRandomizer(CVehicle* vehicle, void* edx, int model, char createdBy);
};