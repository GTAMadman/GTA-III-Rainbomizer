#pragma once
#include "default_config.h"
#include <fstream>
#include <filesystem>
#include <iterator>
#include <string>
#include <vector>

class Config
{
private:
	static std::string ConfigName;
public:
	static void Initialise();
	struct ScriptedVehiclesRandomizer
	{
		std::string Name = "ScriptVehiclesRandomizer";
		static bool Enabled;
		void Read();
	};
	struct RCVehiclesRandomizer
	{
		std::string Name = "RandomizeRCVehicles";
		static bool Enabled;
		void Read();
	};
	struct ParkedVehiclesRandomizer
	{
		std::string Name = "ParkedVehiclesRandomizer";
		static bool Enabled;
		void Read();
	};
	struct TrafficRandomizer
	{
		std::string Name = "TrafficRandomizer";
		static bool Enabled;
		void Read();
	};
	struct WeaponRandomizer
	{
		std::string Name = "WeaponRandomizer";
		static bool Enabled;
		void Read();
	};
	struct ColourRandomizer
	{
		std::string vehicleName = "RandomizeVehicleColours";
		std::string textName = "RandomizeTextColours";
		std::string rainbowTextName = "RainbowTextColours";
		std::string markersName = "RandomizeMarkerColours";
		static bool vehicleEnabled;
		static bool textEnabled;
		static bool rainbowTextEnabled;
		static bool markersEnabled;
		void Read();
	};
	struct VoiceLineRandomizer
	{
		std::string Name = "VoiceLineRandomizer";
		static bool Enabled;
		void Read();
	};
	struct Autosave
	{
		std::string autosaveName = "Autosave =";
		std::string slotName = "Slot";
		static int slot;
		static bool Enabled;
		void Read();
	};
	static void WriteConfig();
};