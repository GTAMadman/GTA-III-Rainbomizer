#pragma once
#include "plugin.h"
#include "Config.h"
#include "Functions.h"
#include "CStreaming.h"
#include "extensions/ScriptCommands.h"
#include "CAnimBlendClumpData.h"
#include "CAnimBlendAssociation.h"
#include "common.h"
#include "rw/rwplcore.h"
#include <array>

class Player : Functions
{
public:
	static void Initialise();
private:
	static const std::array<std::string, 2> player_outfits;
	static const std::array<std::string, 35> special_models;
	inline static std::vector<std::string> all_outfits;
	static void RandomizeOutfit(uint32_t modelId, const char* modelName, uint32_t flags);
	static void GivePlayerRandomOutfit();
	static void RandomizeOutfitOnFade();
	static void ChangePlayerModel(const char* modelName);
	inline static CAnimBlendAssociation* association = nullptr;
};