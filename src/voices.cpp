#include "voices.h"

std::vector<std::string> voices::sounds;
void __fastcall voices::LoadRandomizedAudio(uint16_t* audio, void* edx, char* text)
{
	char* sound;
	int index = RandomNumber(0, sounds.size() - 1);

	strcpy(sound, sounds[index].c_str());
	PreloadMissionAudio(audio, text);
}
void voices::PreloadMissionAudio(uint16_t* audio, char* text)
{
	plugin::CallMethod<0x57CD70>(audio, text);
}
void voices::InitialiseSounds()
{
	std::vector<std::string> large_files = {"a1_sso", "a2_pp", "a3_ss", "a4_pdr", "a5_k2ft", "a6_bait",
	"a7_etg", "a8_ps", "a9_asd", "CHAT", "City", "CLASS", "COMopen", "FLASH", "GAME", "HEAD", "KJAH", 
	"LIPS", "Miscom", "MSX", "police", "RISE", "SUBopen", "Water"};

	for (auto& files : std::filesystem::directory_iterator(plugin::paths::GetGameDirRelativePathA("audio/")))
	{
		if (files.path().extension() == ".wav")
		{
			std::string sound = files.path().filename().string();

			size_t index = sound.find_last_of(".");
			std::string fileName = sound.substr(0, index);

			sounds.push_back(fileName);
		}
	}

	// Remove large files
	for (int i = 0; i < large_files.size(); i++)
	{
		sounds.erase(std::remove(sounds.begin(), sounds.end(), large_files[i]), sounds.end());
	}
}
void voices::Initialise()
{
	if (Config::VoiceLineRandomizer::Enabled)
	{
		plugin::patch::RedirectCall(0x44F268, LoadRandomizedAudio);

		if (sounds.size() == 0)
			InitialiseSounds();
	}
}