#pragma once
#include "plugin.h"
#include "Functions.h"
#include "CModelInfo.h"
#include "CCutsceneObject.h"
#include <vector>
#include <string>

struct CCutsceneObject_vftable;

class Cutscenes : Functions
{
	static void RandomizeSpecialModelToLoad(int	modelId, const char* modelName, int flags);
	static const char* Cutscenes::GetRandomModel(const char* model);
	inline static std::vector<std::vector<std::string>> mModels;
	static bool InitialiseModelData();
public:
	static void Initialise();
};