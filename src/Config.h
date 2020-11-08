#pragma once
#include "default_config.h"
#include <fstream>
#include <filesystem>
#include <sstream>


class Config
{
private:
	static std::string ConfigName;
public:
	static void Initialise();
	static struct ScriptedVehiclesRandomizer
	{
		bool Enabled;
		bool offroadEnabled;
		bool rcEnabled;
		void Read(const std::string& line);
	} script;

	static struct RCVehiclesRandomizer
	{
		bool Enabled;
		void Read(const std::string& line);
	} rc;

	static struct ParkedVehiclesRandomizer
	{
		bool Enabled;
		void Read(const std::string& line);
	} parked;

	static struct TrafficRandomizer
	{
		bool Enabled;
		bool roadblocksEnabled;
		bool deadDodo;
		bool train;
		bool airTrain;
		void Read(const std::string& line);
	} traffic;

	static struct WeaponRandomizer
	{
		bool Enabled;
		void Read(const std::string& line);
	} weapons;

	static struct ColourRandomizer
	{
		bool vehicleEnabled;
		bool textEnabled;
		bool rainbowTextEnabled;
		bool markersEnabled;
		bool pickupsEnabled;
		bool explosionsEnabled;
		void Read(const std::string& line);
	} colours;

	static struct PickupsRandomizer
	{
		bool Enabled;
		bool randomizePedDrops;
		bool weapons;
		bool health;
		bool armour;
		bool adrenaline;
		bool bribes;
		bool briefcase;
		void Read(const std::string& line);
	} pickups;

	static struct PagerRandomizer
	{
		bool Enabled;
		bool allowSubtitlesEnabled;
		void Read(const std::string& line);
	} pager;

	static struct VoiceLineRandomizer
	{
		bool Enabled;
		bool MatchSubtitles;
		void Read(const std::string& line);
	} voice;

	static struct Autosave
	{
		int slot = 8;
		bool Enabled;
		void Read(const std::string& line);
	} autosave;

	static void WriteConfig();
};