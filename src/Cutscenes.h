#pragma once
#include "CCutsceneObject.h"
#include <vector>
#include <string>
#include "Functions.h"

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