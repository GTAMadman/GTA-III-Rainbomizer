#pragma once
#include "plugin.h"
#include "CStreaming.h"
#include "ModelInfo.h"
#include "CTheScripts.h"
#include "CCamera.h"
#include "CCollision.h"
#include "CGame.h"
#include "cMusicManager.h"
#include "CCutsceneMgr.h"
#include "eObjective.h"
#include "CWorld.h"
#include <ctime>
#include <random>

class Functions
{
private:
	static std::mt19937 rngEngine;
	static int* ms_vehiclesLoaded;
public:
	static int RandomNumber(int min, int max);
	static void LoadModel(int modelID);
	static bool DoCoordinatesMatch(int x1, int y1, int z1, int x2, int y2, int z2);
	static std::string GetRainbomizerDir();
	static bool IsModelLoaded(int modelID);
	static int GetNumberOfVehiclesLoaded();
	static int GetRandomLoadedVehicle();
	static bool IsRampageRunning();
	static void PlayAudioForCredits();
	static void UnfreezePlayer();
	struct CText
	{
		char* GetText(const char* key);
	};
	static void TeleportPlayer(CVector& pos, eLevelName level);

	template <typename T> static auto& GetRandomElement(T& container)
	{
		auto it = std::begin(container);
		std::advance(it, RandomNumber(0, std::size(container) - 1));

		return *it;
	}

	template <typename T, typename V>
	static bool DoesElementExist(const T& container, const V val)
	{
		return std::find(std::begin(container), std::end(container),
			val)
			!= std::end(container);
	}
};