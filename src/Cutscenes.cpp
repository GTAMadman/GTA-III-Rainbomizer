#include "Cutscenes.h"
#include "plugin.h"
#include "CModelInfo.h"

const char* Cutscenes::GetRandomModel(const char* model)
{
	for (const auto& i : mModels)
	{
		if (DoesElementExist(i, model))
			return GetRandomElement(i).c_str();
	}

	return model;
}

void Cutscenes::RandomizeSpecialModelToLoad(int modelId, const char* modelName, int flags)
{
	const char* model = GetRandomModel(modelName);
	CStreaming::RequestSpecialModel(modelId, model, flags);

	CStreaming::LoadAllRequestedModels(false);
	strncpy(CModelInfo::GetModelInfo(modelId)->m_szName, modelName, 24);
}

bool Cutscenes::InitialiseModelData()
{
	std::string fileDir = GetRainbomizerDir() + "CutsceneModels.txt";

	FILE* modelsFile = fopen(fileDir.c_str(), "r");
	mModels.clear();

	if (!modelsFile)
		return false;

	char line[512] = { 0 };
	mModels.push_back({});
	while (fgets(line, 512, modelsFile))
	{
		if (strlen(line) < 2)
		{
			mModels.push_back({});
			continue;
		}

		line[strcspn(line, "\n")] = 0;
		mModels.back().push_back(line);
	}

	return true;
}
void Cutscenes::Initialise()
{
	if (Config::cutscene.Enabled && InitialiseModelData())
	{
		plugin::patch::RedirectCall(0x40ADB2, RandomizeSpecialModelToLoad);
		plugin::patch::RedirectCall(0x4474C4, RandomizeSpecialModelToLoad);
	}
}