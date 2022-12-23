#include "Functions.h"

int* Functions::ms_vehiclesLoaded = reinterpret_cast<int*>(0x773560);

/* Initialised the random engine and given it a seed */
std::mt19937 Functions::rngEngine{ (unsigned int)time(0) };

char* Functions::CText::GetText(const char* key)
{
	return plugin::CallMethodAndReturn<char*, 0x52C5A0, CText*>(this, key);
}
bool Functions::DoCoordinatesMatch(int x1, int y1, int z1, int x2, int y2, int z2)
{
	if (x1 == x2 && y1 == y2 && z1 == z2)
		return true;
	return false;
}
void Functions::LoadModel(int modelID)
{
	if (CStreaming::ms_aInfoForModel[modelID].m_nLoadState != 1)
	{
		CStreaming::RequestModel(modelID, 0);
		CStreaming::LoadAllRequestedModels(false);
	}
}
bool Functions::IsModelLoaded(int modelID)
{
	return CStreaming::ms_aInfoForModel[modelID].m_nLoadState == 1 ? true : false;
}
bool Functions::IsMission(std::string thread)
{
	return CTheScripts::pActiveScripts->m_szName == thread;
}
std::string Functions::GetMissionThread()
{
	return CTheScripts::pActiveScripts->m_szName;
}
void Functions::PlayAudioForCredits()
{
	gMusicManager.ChangeMusicMode(0);
	gMusicManager.PlayFrontEndTrack(RandomNumber(0, 7), 1);
}
int Functions::GetNumberOfVehiclesLoaded()
{
	return *ms_vehiclesLoaded;
}
int Functions::GetRandomLoadedVehicle()
{
	return ms_vehiclesLoaded[RandomNumber(0, CStreaming::ms_numVehiclesLoaded - 1)];
}
std::string Functions::GetRainbomizerDir()
{
	return std::string(plugin::paths::GetGameDirPathA()) + "rainbomizer/";
}
bool Functions::IsRampageRunning()
{
	return injector::ReadMemory<short>(0x95CCB4) == 1 ? true : false;
}
bool Functions::IsRCMission()
{
	return IsMission("rc1") || IsMission("rc2") || IsMission("rc3") || IsMission("rc4");
}
void Functions::ClearWeapons(CPed* ped)
{
	plugin::CallMethod<0x4CFB70, CPed*>(ped);
}
void Functions::StartFrenzy(int weapon, int time, short kill, int modelId0, unsigned short* text,
	int modelId2, int modelId3, int modelId4, bool standardSound, bool needHeadshot)
{
	plugin::Call<0x4210E0>(weapon, time, kill, modelId0, text, modelId2, 
		modelId3, modelId4, standardSound, needHeadshot);
}
short Functions::QueryModelsKilledByPlayer(int modelId)
{
	return plugin::CallAndReturn<short, 0x421370>(modelId);
}
void Functions::UnfreezePlayer()
{
	injector::WriteMemory<int>(0x95CD95, 1);
	CCutsceneMgr::DeleteCutsceneData();
	FindPlayerPed()->SetObjective(eObjective::OBJECTIVE_NONE);
	CPad::GetPad(CWorld::PlayerInFocus)->Clear(true);
}
int Functions::RandomNumber(int min, int max)
{
	std::uniform_int_distribution random(min, max);
	return random(rngEngine);
}
void Functions::TeleportPlayer(CVector& pos, eLevelName level)
{
	CStreaming::ms_disableStreaming = 0;

	CGame::currLevel = level;
	CCollision::SortOutCollisionAfterLoad();
	CStreaming::RequestIslands(level);

	CStreaming::StreamZoneModels(pos);
	CStreaming::LoadScene(pos);
	CStreaming::LoadAllRequestedModels(false);

	FindPlayerEntity()->Teleport(pos);
}