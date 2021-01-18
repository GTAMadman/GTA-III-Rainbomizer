#pragma once
#include "plugin.h"
#include "Functions.h"
#include "Config.h"
#include "Script.h"
#include "CRemote.h"
#include "CTheScripts.h"

class Remote : Functions
{
public:
	static void Initialise();
private:
	static void GivePlayerRandomRCVehicle(float x, float y, float z, float angle, short modelId);
};