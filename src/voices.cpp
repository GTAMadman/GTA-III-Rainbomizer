#include "voices.h"
#include <cstdint>
#include <unordered_map>

struct MissionAudioData
{
	char* SoundName;
	uint32_t SoundId;
};

std::unordered_map<std::string, std::string> subtitles{{
		{"lib_a1", "ebal_a"}
	}};

MissionAudioData* MissionAudioNameSfxAssoc = (MissionAudioData*) 0x607094;

const int STREAMED_SOUND_MISSION_LIB_A1 = 0x5F;
const int STREAMED_SOUND_MISSION_C1 = 0xC3;

static int GetRandomizedMissionAudioSfx (const char* name)
{

	int sound = RandomNumber(STREAMED_SOUND_MISSION_LIB_A1,
				 STREAMED_SOUND_MISSION_C1);

	char* newName = MissionAudioNameSfxAssoc
		[sound - STREAMED_SOUND_MISSION_LIBA1].SoundName;

	voiceLines[sound] = newName;
	if (subtitles.count(newName))
		voiceLines[sound] = subtitles[newName];
	
	return sound;
}

char* __fastcall voices::FixSubtitles(CText* text, void* edx, char* key)
{
	if (voices.count(key))
		key = voiceLines[key];
	
	return plugin::CallMethodAndReturn<char*, 0x52C5A0, CText *>(text, key);
}

void voices::Initialise()
{
	if (Config::VoiceLineRandomizer::Enabled)
		{
			plugin::patch::RedirectCall(0x57955D, GetRandomizedMissionAudioSfx);
			plugin::patch::RedirectCall(0x43D119, voices::FixSubtitles);
		}
}
