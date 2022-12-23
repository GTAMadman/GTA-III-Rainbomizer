#include "Player.h"

const std::array<std::string, 2> Player::player_outfits = { "PLAYER",  "PLAYERP" };
const std::array<std::string, 35> Player::special_models =
{ "SAM",    "CAT",   "COLROB",	 "MIGUEL", "PLAYERX", "EIGHT",
   "OJG_P",  "COL1",  "COL2",	 "EIGHT2", "MICKY",   "LUIGI",
   "MISTY",  "JOEY",  "LIPS",	 "CHUNKY", "S_GUARD", "TONY",
   "ROBBER", "JOEY2", "FRANKIE", "MARIA",  "CURLY",   "ASUKA",
   "DONKY",  "KENJI", "RAY",	 "TANNER", "KEEPER",  "DEALER",
   "LOVE2",  "OJG",   "LOVE",	 "OJG2",   "BOMBER" };

auto GetAnimBlendClumpData(RpClump* clump)
{
	return *((CAnimBlendClumpData **)(((uint8_t*)clump) + injector::ReadMemory<uint32_t>(0x8F1B84)));
}
auto RpAnimBlendClumpExtractAssociations(RpClump* clump)
{
	auto data = GetAnimBlendClumpData(clump);
	auto ret = data->m_associationsList.link.next;
	data->m_associationsList.link.next = nullptr;
	ret->prev = nullptr;

	return (CAnimBlendAssociation*)ret;
}
auto RpAnimBlendClumpGiveAssociations(RpClump* clump, CAnimBlendAssociation* association)
{
	if (!association)
		return;

	auto data = GetAnimBlendClumpData(clump);
	auto assoc = &data->m_associationsList.link;
	auto baseAssoc = &data->m_associationsList.link;

	while (assoc->next)
	{
		auto next = assoc->next;
		((CAnimBlendAssociation*)(((uint8_t*)assoc->next) - 4))->~CAnimBlendAssociation();
		assoc = next;
	}

	baseAssoc->next = (RwLLLink*)association;
	((RwLLLink*)association)->prev = baseAssoc;
}
void Player::RandomizeOutfit(uint32_t modelId, const char* modelName, uint32_t flags)
{
	std::string newModel = GetRandomElement(all_outfits);

	if (Config::player.forcedModel != "")
		newModel = Config::player.forcedModel;

	CStreaming::RequestSpecialModel(modelId, newModel.c_str(), flags);
	CStreaming::LoadAllRequestedModels(false);
	strcpy(CModelInfo::GetModelInfo(modelId)->m_szName, modelName);
}
void Player::GivePlayerRandomOutfit()
{
	std::string newModel = GetRandomElement(all_outfits);

	if (Config::player.forcedModel != "")
		newModel = Config::player.forcedModel;

	ChangePlayerModel(newModel.c_str());
}
void Player::RandomizeOutfitOnFade()
{
	static int prevFadeValue = -1;
	int fadeValue = injector::ReadMemory<uint8_t>(0x95CD68);

	if (prevFadeValue != fadeValue && fadeValue == 255)
	{
		if (FindPlayerPed())
			GivePlayerRandomOutfit();
	}
	prevFadeValue = fadeValue;
	plugin::Call<0x48D120>();
}
void Player::ChangePlayerModel(const char* modelName)
{
	CPed* ped = FindPlayerPed();
	auto animGroup = ped->m_nAnimGroupId;
	if (!ped->m_bInVehicle)
	{
		association = RpAnimBlendClumpExtractAssociations(ped->m_pRwClump);

		plugin::Command<eScriptCommands::COMMAND_UNDRESS_CHAR>(ped, CModelInfo::GetModelInfo(0)->m_szName);
		CStreaming::LoadAllRequestedModels(false);
		plugin::Command<eScriptCommands::COMMAND_DRESS_CHAR>(ped);

		RpAnimBlendClumpGiveAssociations(ped->m_pRwClump, association);
		association = nullptr;

		ped->m_nAnimGroupId = animGroup;
	}
}
void Player::Initialise()
{
	if (Config::player.Enabled)
	{
		if (Config::player.playerOutfits)
			for (const std::string& item : player_outfits)
				all_outfits.push_back(item);

		if (Config::player.specialModels)
			for (const std::string& item : special_models)
				all_outfits.push_back(item);

		if (all_outfits.size() == 0)
			return;

		plugin::patch::RedirectCall(0x44AB88, RandomizeOutfit);
		plugin::patch::RedirectCall(0x48E6D5, RandomizeOutfitOnFade);
	}
}