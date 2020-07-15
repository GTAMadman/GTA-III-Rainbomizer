#pragma once
#include "plugin.h"
#include "Functions.h"
#include "Config.h"
#include "scm.h"
#include "CRemote.h"
#include "CTheScripts.h"

class Remote : Functions
{
public:
	static void Initialise();
private:
	static void GivePlayerRCVehicle(float x, float y, float z, float angle, short modelId);
};