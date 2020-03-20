#include "scm.h"

std::vector<scm::Pattern> scm::Patterns;
void __fastcall scm::ScriptVehicleRandomizer(CRunningScript* thisScript, void* edx, int* arg0, short count)
{
	thisScript->CollectParameters(arg0, count);

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
		newModel = GetIDBasedOnPattern(origModel, x, y, z, thisScript->m_szName);

	// Attempt to load the vehicle
	LoadModel(newModel);

	// If the vehicle isn't loaded, return the original
	if (!IsModelLoaded(newModel))
		newModel = origModel;

	CTheScripts::ScriptParams[0].iParam = newModel;
}
void __fastcall scm::FixForcedPlayerVehicle(CRunningScript* thisScript, void* edx, int* arg0, short count)
{
	thisScript->CollectParameters(arg0, count);
	int origModel = CTheScripts::ScriptParams[1].iParam;

	// Blow Fish Fix - Open the gate for any vehicle
	if (thisScript->m_szName == (std::string)"fsh_gte" && origModel == 98)
	{ 
		if (FindPlayerVehicle())
			CTheScripts::ScriptParams[1].iParam = FindPlayerVehicle()->m_nModelIndex;
	}
}
void scm::InitialiseVehiclePatterns()
{
	/* General Patterns */
	Pattern pattern = { .gVehicle = {"car"}, .allowedType = {"car", "dodo"} };
	Patterns.push_back(pattern);

	pattern = { .gVehicle = {"boat"}, .allowedType = {"boat"} };
	Patterns.push_back(pattern);

	pattern = { .gVehicle = {"rc"}, .allowedType = {"rc", "car", "dodo"} };
	Patterns.push_back(pattern);

	/* Script Vehicle Patterns */

	// Dead Dodo
	pattern = { .vehicle = {DEAD_DODO_MODEL}, .allowed = {DEAD_DODO_MODEL} };
	Patterns.push_back(pattern);

	// Dodo
	pattern = { .vehicle = {DODO_MODEL}, .allowed = {DODO_MODEL}, .allowedType = {"car"} };
	Patterns.push_back(pattern);

	// RC Bandit
	pattern = { .vehicle = {131}, .allowed = {131}, .allowedType = {"rc", "car", "dodo"} };
	Patterns.push_back(pattern);

	// Mr. Whoopie
	pattern = { .vehicle = {113}, .allowed = {113}, .thread = {"diablo2"} };
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

	// The Thieves
	pattern = { .vehicle = {95}, .denied = {97, 106, 116, 117}, .coords = { 1190, -796, 13 },
	.doors = {4} };
	Patterns.push_back(pattern);

	// Stinger - Grand Theft Auto
	pattern = { .vehicle = {92}, .denied = { 93, 97, 98, 99, 103, 104, 106, 108, 112, 117, 118, 122, 123, 126,
	127, 130, 132, 133, 139, 144, 145, 146, 149}, .allowedType = {"car"}, .thread = {"kenji2"} };
	Patterns.push_back(pattern); // Denied all larger vehicles

	// Infurnus - Grand Theft Auto
	pattern = { .vehicle = {101}, .denied = {93, 97, 98, 99, 103, 104, 106, 108, 112, 117, 118, 122, 123, 126,
	127, 130, 132, 133, 139, 144, 145, 146, 149},.allowedType = {"car"}, .thread = {"kenji2"} };
	Patterns.push_back(pattern); // Denied all larger vehicles

	// Infurnus - Rigged To Blow
	pattern = { .vehicle = {101},.denied = {93, 97, 98, 99, 103, 104, 106, 108, 112, 117, 118, 122, 123, 126,
	127, 130, 132, 133, 139, 144, 145, 146, 149},.allowedType = {"car"},.thread = {"hood3"} };
	Patterns.push_back(pattern); // Denied all larger vehicles

	// Cheetah - Grand Theft Auto
	pattern = { .vehicle = {105},.denied = {93, 97, 98, 99, 103, 104, 106, 108, 112, 117, 118, 122, 123, 126,
	127, 130, 132, 133, 139, 144, 145, 146, 149},.allowedType = {"car"}, .thread = {"kenji2"} };
	Patterns.push_back(pattern); // Denied all larger vehicles

	// Stallion - Don't Spank...
	pattern = { .vehicle = {129}, .denied = {97, 106, 116, 117, 122, 123, 126}, .allowedType = {"car"}, 
	.coords = { 1396, -837, -100 } };
	Patterns.push_back(pattern); 

	// Mike Lips' Last Lunch
	pattern = { .vehicle = {91}, .denied = {93, 98, 104, 113, 122, 123, 127, 132, 133, 145, 146},
	.coords = {1336, -460, -100} }; // Removed some large vehicles
	Patterns.push_back(pattern);

	// Cipriani's Chauffeur
	pattern = { .vehicle = {134}, .denied = {93, 98, 104, 113, 122, 123, 127, 132, 133, 145, 146}, 
	.allowedType = {"car"}, .coords = {1189, -864, 14} }; // Removed some large vehicles
	Patterns.push_back(pattern);
}
/* I've only built the pattern system to work with the necessary patterns for the main game.
   This may be changed in future. */
int scm::GetIDBasedOnPattern(int origModel, int x, int y, int z, char* thread)
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
				if (DoCoordinatesMatch(Patterns[a].coords[0], Patterns[a].coords[1], Patterns[a].coords[2], x, y, z))
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
			{
				return vehicles[RandomNumber(0, vehicles.size() - 1)];
			}
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
std::vector<int> scm::ProcessVehicleTypes(Pattern pattern)
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
					if (CModelInfo::IsCarModel(model) && model != RC_BANDIT_MODEL && model != DEAD_DODO_MODEL)
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
void scm::Initialise()
{
	if (Config::ScriptedVehiclesRandomizer::Enabled)
	{
		plugin::patch::RedirectCall(0x43C47E, ScriptVehicleRandomizer);
		plugin::patch::RedirectCall(0x43DA21, FixForcedPlayerVehicle);
		plugin::patch::SetChar(0x52CF7A, 1); // Unlock police vehicles

		if (Patterns.size() == 0)
			InitialiseVehiclePatterns();
	}
}