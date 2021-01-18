#pragma once
#include "default_config.h"
#include "Functions.h"
#include <fstream>
#include <filesystem>
#include <sstream>


class Config
{
private:
	static std::string ConfigName;
public:
	static void Initialise();
	inline static struct General
	{
		bool replays;
		bool credits;
		void Read(const std::string& line);
	} general;

	inline static struct ScriptedVehiclesRandomizer
	{
		bool Enabled;
		bool offroadEnabled;
		bool rcEnabled;
		void Read(const std::string& line);
	} script;

	inline static struct RCVehiclesRandomizer
	{
		bool Enabled;
		void Read(const std::string& line);
	} rc;

	inline static struct ParkedVehiclesRandomizer
	{
		bool Enabled;
		void Read(const std::string& line);
	} parked;

	inline static struct TrafficRandomizer
	{
		bool Enabled;
		bool roadblocksEnabled;
		bool deadDodo;
		bool train;
		bool airTrain;

		bool cars;
		bool RCBandit;
		bool boats;
		bool dodo;
		bool forceVehicle;
		int forcedVehicleID = 0;
		void Read(const std::string& line);
	} traffic;

	inline static struct WeaponRandomizer
	{
		bool Enabled;
		void Read(const std::string& line);
	} weapons;

	inline static struct ColourRandomizer
	{
		bool vehicleEnabled;
		bool textEnabled;
		bool rainbowTextEnabled;
		bool markersEnabled;
		bool pickupsEnabled;
		bool explosionsEnabled;
		bool staticMarkerColours;
		bool staticPickupColours;
		bool staticExplosionColours;
		void Read(const std::string& line);
	} colours;

	inline static struct PickupsRandomizer
	{
		bool Enabled;
		bool randomizePedDrops;
		bool weapons;
		bool health;
		bool armour;
		bool adrenaline;
		bool bribes;
		bool briefcase;
		bool briefcaseMoney;
		void Read(const std::string& line);
	} pickups;

	inline static struct PagerRandomizer
	{
		bool Enabled;
		bool allowSubtitlesEnabled;
		void Read(const std::string& line);
	} pager;

	inline static struct PlayerRandomizer
	{
		bool Enabled;
		bool playerOutfits;
		bool specialModels;
		void Read(const std::string& line);
	} player;

	inline static struct PedRandomizer
	{
		bool Enabled;
		bool genericPeds;
		bool copPeds;
		void Read(const std::string& line);
	} ped;

	inline static struct CutsceneRandomizer
	{
		bool Enabled;
		void Read(const std::string& line);
	} cutscene;

	inline static struct MissionRandomizer
	{
		bool Enabled;
		bool usingSeed;
		std::string seed;
		int forcedMission;
		void Read(const std::string& line);
	} mission;

	inline static struct VoiceLineRandomizer
	{
		bool Enabled;
		bool MatchSubtitles;
		void Read(const std::string& line);
	} voice;

	inline static struct Autosave
	{
		int slot = 8;
		bool Enabled;
		void Read(const std::string& line);
	} autosave;

	static void WriteConfig();
};