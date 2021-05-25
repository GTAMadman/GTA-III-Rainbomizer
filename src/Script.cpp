#include "Script.h"

std::vector<Script::Pattern> Script::Patterns;
void __fastcall Script::ScriptVehicleRandomizer(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);

	int origModel = CTheScripts::ScriptParams[0].iParam;
	int newModel = 0;

	// Stored coordinates
	int x = CTheScripts::ScriptParams[1].fParam;
	int y = CTheScripts::ScriptParams[2].fParam;
	int z = CTheScripts::ScriptParams[3].fParam;

	// Any added vehicles will return the same ID
	if (origModel > 150)
		newModel = origModel;

	if (newModel != origModel)
		newModel = GetIDBasedOnPattern(origModel, x, y, z, script->m_szName);

	// Attempt to load the vehicle
	LoadModel(newModel);

	// If the vehicle isn't loaded, return the original
	if (!IsModelLoaded(newModel))
		newModel = origModel;

	CTheScripts::ScriptParams[0].iParam = newModel;
}
void __fastcall Script::FixForcedPlayerVehicle(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	int origModel = CTheScripts::ScriptParams[1].iParam;

	// Blow Fish Fix - Open the gate for any vehicle
	if (script->m_szName == std::string("fsh_gte") && origModel == 98)
	{ 
		if (FindPlayerVehicle())
			CTheScripts::ScriptParams[1].iParam = FindPlayerVehicle()->m_nModelIndex;
	}

	// I Scream, You Scream
	if (script->m_szName == std::string("diablo2") && origModel == 113)
	{
		if (FindPlayerVehicle())
		{
			int model = FindPlayerVehicle()->m_nModelIndex;
			if (IsEmergencyVehicle(model) || model == 113 && model != 122 && model != 123)
				CTheScripts::ScriptParams[1].iParam = FindPlayerVehicle()->m_nModelIndex;
		}
	}

	if (Config::script.offroadEnabled)
	{
		if (origModel == 90 || origModel == 96 || origModel == 129)
			if (FindPlayerVehicle())
				CTheScripts::ScriptParams[1].iParam = FindPlayerVehicle()->m_nModelIndex;
	}
	if (Config::script.rcEnabled)
	{
		if (origModel == 149)
			if (FindPlayerVehicle())
				CTheScripts::ScriptParams[1].iParam = FindPlayerVehicle()->m_nModelIndex;
	}
}
void* __fastcall Script::RandomizeADITODeadDodo(CPlane* plane, void* edx, int model, char createdBy)
{
	int newModel = GetIDBasedOnPattern(model, plane->GetPosition().x, plane->GetPosition().y,
		plane->GetPosition().z, CTheScripts::pActiveScripts->m_szName);

	LoadModel(newModel);

	if (!IsModelLoaded(newModel))
		newModel = model;

	reinterpret_cast<CPlane*>(plane)->CPlane::CPlane(newModel, createdBy);
	return plane;
}
void Script::FixUziRiderDriveToCoords(CVehicle* vehicle, CVector coords, bool arg2)
{
	if (CTheScripts::pActiveScripts->m_szName == std::string("yard2") &&
		coords.x == 113 && coords.y == -272)
	{
		coords.x = 111;
	}
	CCarCtrl::JoinCarWithRoadSystemGotoCoors(vehicle, coords, arg2);
}
void Script::InitialiseVehiclePatterns()
{
	/* General Patterns */
	Pattern pattern = { .gVehicle = {"car"}, .allowedType = {"car", "dodo"} };
	Patterns.push_back(pattern);

	pattern = { .gVehicle = {"boat"}, .allowedType = {"boat"} };
	Patterns.push_back(pattern);

	pattern = { .gVehicle = {"rc"}, .allowedType = {"rc", "car", "dodo"} };
	Patterns.push_back(pattern);

	/* Script Vehicle Patterns */

	// Dead Dodo - A Drop In The Ocean
	pattern = { .vehicle = {141}, .allowed = {141, 124, 125, 147}, .allowedType = {"car", "dodo", 
	"boat", "rc"}, .thread = {"love3"} };
	Patterns.push_back(pattern);

	// Dodo
	pattern = { .vehicle = {DODO_MODEL}, .allowed = {DODO_MODEL}, .allowedType = {"car"} };
	Patterns.push_back(pattern);

	// RC Bandit
	pattern = { .vehicle = {131}, .allowed = {131}, .allowedType = {"rc", "car", "dodo"} };
	Patterns.push_back(pattern);

	// Mr. Whoopie - I Scream, You Scream
	pattern = { .vehicle = {113}, .allowed = {113, 97, 106, 107, 116, 117}, .thread = {"diablo2"} };
	Patterns.push_back(pattern);

	// Predator
	pattern = { .vehicle = {120}, .allowed = {120} };
	Patterns.push_back(pattern);

	// Stretch - Salvatore's Called a Meeting
	pattern = { .vehicle = {99}, .coords = {1187, -860, 14}, .doors = {4}, };
	Patterns.push_back(pattern);

	// Perennial - Uzi Rider
	pattern = { .vehicle = {94}, .allowed = {127}, .coords = {4, -310, 16}, .doors = {4} };
	Patterns.push_back(pattern);

	// The Crook
	pattern = { .vehicle = {94},.denied = {97, 98, 102, 118, 121, 122, 126}, 
	.allowedType = {"car"}, .thread = {"meat1"} };
	Patterns.push_back(pattern);

	// Dead Skunk In the Trunk
	pattern = { .vehicle = {115}, .denied = {97, 98, 102, 118, 121, 122, 126},
	.allowedType = {"car"}, .thread = {"joey5"} };
	Patterns.push_back(pattern);

	// The Thieves
	pattern = { .vehicle = {95}, .denied = {97, 106, 116, 117}, .coords = { 1190, -796, 13 }, .doors = {4} };
	Patterns.push_back(pattern);

	// Stinger - Grand Theft Auto
	pattern = { .vehicle = {92}, .denied = { 93, 97, 98, 99, 103, 104, 106, 108, 112, 113, 117, 118, 121, 122, 123,
	127, 130, 132, 133, 138, 139, 144, 145, 146, 149}, .allowedType = {"car"}, .thread = {"kenji2"} };
	Patterns.push_back(pattern); // Denied all larger vehicles

	// Infurnus - Grand Theft Auto
	pattern = { .vehicle = {101}, .denied = {93, 97, 98, 99, 103, 104, 106, 108, 112, 113, 117, 118, 121, 122, 123,
	127, 130, 132, 133, 138, 139, 144, 145, 146, 149}, .allowedType = {"car"}, .thread = {"kenji2"} };
	Patterns.push_back(pattern); // Denied all larger vehicles

	// Cheetah - Grand Theft Auto
	pattern = { .vehicle = {105},.denied = {93, 97, 98, 99, 103, 104, 106, 108, 112, 113, 117, 118, 121, 122, 123,
	127, 130, 132, 133, 138, 139, 144, 145, 146, 149},.allowedType = {"car"},.thread = {"kenji2"} };
	Patterns.push_back(pattern); // Denied all larger vehicles

	// Infurnus - Rigged To Blow
	pattern = { .vehicle = {101}, .denied = {93, 97, 98, 99, 103, 104, 106, 108, 112, 113, 117, 118, 121, 122, 123,
	127, 130, 132, 133, 139, 144, 145, 146, 149}, .allowedType = {"car"}, .thread = {"hood3"} };
	Patterns.push_back(pattern); // Denied all larger vehicles

	// Deal Steal
	pattern = { .vehicle = {138}, .denied = {121, 127}, .allowedType = {"car", "dodo"}, .thread = {"kenji3"} };
	Patterns.push_back(pattern);

	// Toyminator
	pattern = { .vehicle = {118}, .denied = {122}, .allowedType = {"car", "dodo"}, .thread = {"hood2"} };
	Patterns.push_back(pattern);

	// Stallion - Don't Spank...
	pattern = { .vehicle = {129}, .denied = {93, 97, 98, 99, 104, 106, 113, 116, 117, 118, 121, 122, 123,
	126, 127, 132, 133, 145, 146}, .allowedType = {"car"}, .coords = { 1396, -837, -100 } };
	Patterns.push_back(pattern);

	// Mike Lips' Last Lunch
	pattern = { .vehicle = {91}, .denied = {93, 98, 104, 106, 113, 121, 122, 123, 126, 127, 132, 133, 145, 146},
	.allowedType = {"car"}, .coords = {1336, -460, -100} }; // Removed some large vehicles
	Patterns.push_back(pattern);

	// Cipriani's Chauffeur
	pattern = { .vehicle = {134}, .denied = {93, 98, 104, 113, 122, 123, 126, 127, 132, 133, 145, 146},
	.allowedType = {"car"}, .coords = {1189, -864, 14} }; // Removed some large vehicles
	Patterns.push_back(pattern);
}
/* I've only built the pattern system to work with the necessary patterns for the main game.
   This may be changed in future. */
int Script::GetIDBasedOnPattern(int origModel, int x, int y, int z, char* thread)
{
	// Scripted Vehicle Patterns
	for (int i = 0; i < Patterns.size(); i++)
	{
		int index = i;
		if (Patterns[index].vehicle == origModel)
		{
			// Check for more than one vehicle in pattern (checking using coordinates)
			// This will allow multiple vehicles to be used in the patterns - as long as they have coords!
			for (int a = 0; a < Patterns.size(); a++)
			{
				if (DoCoordinatesMatch(Patterns[a].coords[0], Patterns[a].coords[1], Patterns[a].coords[2], x, y, z)
					&& Patterns[a].vehicle == origModel)
				{
					index = a;
					break;
				}
			}
			std::vector<int> vehicles;

			if (DoCoordinatesMatch(Patterns[index].coords[0], Patterns[index].coords[1], Patterns[index].coords[2], 0, 0, 0))
				vehicles = Patterns[index].allowed;

			std::vector<int> deniedVehicles = Patterns[index].denied;

			// Coordinate check only
			if (DoCoordinatesMatch(Patterns[index].coords[0], Patterns[index].coords[1], Patterns[index].coords[2], x, y, z))
			{
				vehicles = Patterns[index].allowed;
				std::vector<int> newVehicles = ProcessVehicleTypes(Patterns[index]);
				for (int a = 0; a < newVehicles.size(); a++)
					vehicles.push_back(newVehicles[a]);
			}
			// Thread check only
			if (Patterns[index].thread == thread)
			{
				vehicles = Patterns[index].allowed;
				std::vector<int> newVehicles = ProcessVehicleTypes(Patterns[index]);
				for (int a = 0; a < newVehicles.size(); a++)
					vehicles.push_back(newVehicles[a]);
			}
			// Coordinate and door check
			if (DoCoordinatesMatch(Patterns[index].coords[0], Patterns[index].coords[1], Patterns[index].coords[2], x, y, z) &&
				Patterns[index].doors > 0)
			{
				vehicles = Patterns[index].allowed;
				for (int model = 90; model < 151; model++)
				{
					if (CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(model) == Patterns[index].doors - 1)
						vehicles.push_back(model);
				}
			}
			// Any other check that uses allowed types
			if (Patterns[index].allowedType.size() > 0)
			{
				// If this pattern has coordinates or a thread check, don't run this
				if (DoCoordinatesMatch(Patterns[index].coords[0], Patterns[index].coords[1], Patterns[index].coords[2], 0, 0, 0)
					&& Patterns[index].thread == "")
				{
					vehicles = Patterns[index].allowed;
					std::vector<int> newVehicles = ProcessVehicleTypes(Patterns[index]);
					for (int a = 0; a < newVehicles.size(); a++)
						vehicles.push_back(newVehicles[a]);
				}
			}
			// Remove any denied vehicles
			if (Patterns[index].denied.size() > 0)
			{
				for (int x = 0; x < Patterns[index].denied.size(); x++)
				{
					vehicles.erase(std::remove(vehicles.begin(), vehicles.end(),
						Patterns[index].denied[x]), vehicles.end());
				}
			}
			if (vehicles.size() > 0)
				return vehicles[RandomNumber(0, vehicles.size() - 1)];
		}
	}

	/* General Vehicle Patterns */

	// Added this as a safety precaution
	if (CheckVehicleModel(origModel) == "unknown")
	{
		int newModel = 0;
		while (!CModelInfo::IsCarModel(newModel))
			newModel = RandomNumber(90, 150);

		return newModel;
	}

	std::vector<int> vehicles;
	for (int i = 0; i < Patterns.size(); i++)
	{
		if (Patterns[i].gVehicle == CheckVehicleModel(origModel))
		{
			vehicles = ProcessVehicleTypes(Patterns[i]);
			break;
		}
	}
	if (vehicles.size() > 0)
		return vehicles[RandomNumber(0, vehicles.size() - 1)];
	return origModel; // Return original
}
std::vector<int> Script::ProcessVehicleTypes(Pattern pattern)
{
	std::vector<int> output;

	if (pattern.allowedType.size() > 0)
	{
		for (int i = 0; i < pattern.allowedType.size(); i++)
		{
			if (pattern.allowedType[i] == "car")
			{
				for (int model = 90; model < 151; model++)
				{
					if (CModelInfo::IsCarModel(model) && model != RC_BANDIT_MODEL && model != DODO_MODEL &&
						model != 141)
						output.push_back(model);
				}
			}
			if (pattern.allowedType[i] == "boat")
			{
				for (int model = 90; model < 151; model++)
				{
					if (CModelInfo::IsBoatModel(model))
						output.push_back(model);
				}
			}
			if (pattern.allowedType[i] == "dodo")
			{
				output.push_back(DODO_MODEL);
			}
			if (pattern.allowedType[i] == "rc")
			{
				output.push_back(RC_BANDIT_MODEL);
			}
		}
	}
	return output;
}
void Script::Initialise()
{
	if (Config::script.Enabled)
	{
		plugin::patch::RedirectCall(0x43C47E, ScriptVehicleRandomizer);
		plugin::patch::RedirectCall(0x43DA21, FixForcedPlayerVehicle);
		plugin::patch::RedirectCall(0x54E1A8, RandomizeADITODeadDodo);
		plugin::patch::SetChar(0x52CF7A, 1); // Unlock police vehicles

		if (Patterns.size() == 0)
			InitialiseVehiclePatterns();
	}
	if (Config::script.Enabled || Config::mission.Enabled)
		plugin::patch::RedirectCall(0x43C8EA, FixUziRiderDriveToCoords);
}