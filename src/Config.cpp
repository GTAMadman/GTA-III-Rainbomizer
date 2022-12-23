#include "Config.h"

std::string Config::ConfigName = Functions::GetRainbomizerDir() + "config.cfg";
void ReadConfigBool(const std::string& key, const std::string& data, bool& value)
{
	if (data.find(key) != std::string::npos)
		value = data.find("true") != std::string::npos;
}
void ReadConfigInt(const std::string& key, const std::string& data, int& value)
{
	if (data.find(key) != std::string::npos)
	{
		std::stringstream stream;
		stream << data;

		std::string str;
		int val;

		while (!stream.eof())
		{
			stream >> str;
			if (std::stringstream(str) >> val)
			{
				value = val;
				break;
			}
		}
	}
}
void ReadConfigString(const std::string& key, const std::string& data, std::string& value)
{
	if (data.find(key) != std::string::npos)
	{
		std::stringstream stream;
		std::string output;

		stream << data;

		std::getline(stream, output, '\"');
		while (!stream.eof())
		{
			std::getline(stream, output, '\"');
			stream.ignore(256, '\"');
		}
		value = output;
	}
}
void Config::General::Read(const std::string& line)
{
	ReadConfigBool("DisableReplays", line, replays);
	ReadConfigBool("ModifyCredits", line, credits);
	ReadConfigBool("EnableEasterEggs", line, easterEggs);
}
void Config::ScriptedVehiclesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("ScriptVehiclesRandomizer", line, Enabled);

	ReadConfigBool("OffroadMissions", line, offroadEnabled);
	ReadConfigBool("RCMissions", line, rcEnabled);

	ReadConfigInt("ForcedScriptVehicle", line, forcedVehicle);
}
void Config::RCVehiclesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("RandomizeRCVehicles", line, Enabled);
}
void Config::ParkedVehiclesRandomizer::Read(const std::string& line)
{
	ReadConfigBool("ParkedVehiclesRandomizer", line, Enabled);
	ReadConfigInt("ForcedParkedVehicle", line, forcedVehicle);
}
void Config::ColourRandomizer::Read(const std::string& line)
{
	ReadConfigBool("RandomizeVehicleColours", line, vehicleEnabled);
	ReadConfigBool("RandomizeHUDColours", line, textEnabled);
	ReadConfigBool("RandomizeMarkerColours", line, markersEnabled);

	ReadConfigBool("RandomizePickupColours", line, pickupsEnabled);
	ReadConfigBool("RandomizeExplosionColours", line, explosionsEnabled);

	ReadConfigBool("RainbowHUDColours", line, rainbowTextEnabled);
	ReadConfigBool("StaticMarkerColours", line, staticMarkerColours);
	ReadConfigBool("StaticPickupColours", line, staticPickupColours);
	ReadConfigBool("StaticExplosionColours", line, staticExplosionColours);
}
void Config::TrafficRandomizer::Read(const std::string& line)
{
	ReadConfigBool("TrafficRandomizer", line, Enabled);
	ReadConfigBool("RandomizeRoadblocks", line, roadblocksEnabled);

	ReadConfigBool("EnableCars", line, cars);
	ReadConfigBool("EnableBoats", line, boats);

	ReadConfigBool("EnableDeadDodo", line, deadDodo);
	ReadConfigBool("EnableTrain", line, train);
	ReadConfigBool("EnableAirTrain", line, airTrain);
	ReadConfigBool("EnableDodo", line, dodo);
	ReadConfigBool("EnableRCBandit", line, RCBandit);

	ReadConfigInt("ForcedTrafficVehicle", line, forcedVehicle);
}
void Config::WeaponRandomizer::Read(const std::string& line)
{
	ReadConfigBool("WeaponRandomizer", line, Enabled);

	ReadConfigBool("RandomizePlayerWeapons", line, randomizePlayerWeapons);
	ReadConfigBool("RandomizeRampageWeapons", line, randomizeRampageWeapons);

	ReadConfigInt("ForcedWeapon", line, forcedWeapon);
}
void Config::PickupsRandomizer::Read(const std::string& line)
{
	ReadConfigBool("PickupsRandomizer", line, Enabled);
	ReadConfigBool("RandomizePedWeaponDrops", line, randomizePedDrops);

	ReadConfigBool("EnableWeapons", line, weapons);
	ReadConfigBool("EnableHealth", line, health);
	ReadConfigBool("EnableArmour", line, armour);
	ReadConfigBool("EnableAdrenaline", line, adrenaline);
	ReadConfigBool("EnableBribes", line, bribes);
	ReadConfigBool("EnableBriefcase", line, briefcase);

	ReadConfigBool("MoneyInBriefcase", line, briefcaseMoney);
	ReadConfigString("PickupsCustomSeed", line, seed);

	ReadConfigInt("ForcedPickup", line, forcedPickup);

	if (seed != "")
		usingSeed = true;
}
void Config::CutsceneRandomizer::Read(const std::string& line)
{
	ReadConfigBool("CutsceneRandomizer", line, Enabled);
}
void Config::PlayerRandomizer::Read(const std::string& line)
{
	ReadConfigBool("PlayerRandomizer", line, Enabled);

	ReadConfigBool("RandomizePlayerOutfits", line, playerOutfits);
	ReadConfigBool("IncludeSpecialModels", line, specialModels);

	ReadConfigString("ForcedPlayerModel", line, forcedModel);
}
void Config::PedRandomizer::Read(const std::string& line)
{
	ReadConfigBool("PedRandomizer", line, Enabled);

	ReadConfigBool("RandomizeGenericPeds", line, genericPeds);
	ReadConfigBool("RandomizeCopPeds", line, copPeds);

	ReadConfigInt("ForcedPedModel", line, forcedPed);
}
void Config::PagerRandomizer::Read(const std::string& line)
{
	ReadConfigBool("PagerRandomizer", line, Enabled);
	ReadConfigBool("AllowSubtitleMessages", line, allowSubtitlesEnabled);
}
void Config::MissionRandomizer::Read(const std::string& line)
{
	ReadConfigBool("MissionRandomizer", line, Enabled);
	ReadConfigString("MissionCustomSeed", line, seed);
	ReadConfigInt("ForcedMission", line, forcedMission);

	if (seed != "")
		usingSeed = true;
}
void Config::VoiceLineRandomizer::Read(const std::string& line)
{
	ReadConfigBool("VoiceLineRandomizer", line, Enabled);
	ReadConfigBool("MatchSubtitles", line, MatchSubtitles);
}
void Config::Autosave::Read(const std::string& line)
{
	ReadConfigBool("Autosave", line, Enabled);
	ReadConfigInt("Slot", line, slot);

	if (slot < 1 || slot > 8)
		slot = 8;
}
void Config::WriteConfig()
{
	std::ofstream config;
	config.open(ConfigName);
	config << default_config;
	config.close();
}
void Config::Initialise()
{
	if (!std::filesystem::exists(Functions::GetRainbomizerDir()))
		return;

	if (!std::filesystem::exists(ConfigName))
		WriteConfig();

	std::ifstream config;
	config.open(ConfigName);

	for (std::string str; std::getline(config, str); )
	{
		script.Read(str);
		rc.Read(str);
		parked.Read(str);
		traffic.Read(str);
		weapons.Read(str);
		colours.Read(str);
		autosave.Read(str);
		voice.Read(str);
		pickups.Read(str);
		pager.Read(str);
		cutscene.Read(str);
		player.Read(str);
		ped.Read(str);
		mission.Read(str);
		general.Read(str);
	}
}