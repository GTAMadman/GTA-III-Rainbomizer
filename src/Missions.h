#pragma once

#include <string>
#include <memory>
#include "Functions.h"
#include <queue>
#include "CWorld.h"
#include "CBridge.h"
#include "eObjective.h"
#include "CStats.h"
#include "CCutsceneMgr.h"
#include "CMessages.h"
#include "CRestart.h"
#include "CGarages.h"
#include "CClock.h"

class CRunningScript;

const int SIZE_MISSION_SCRIPT = 0x8000;
const int START_MISSIONS = 15;
const int END_MISSIONS = 79;
const int TOTAL_MISSIONS = END_MISSIONS - START_MISSIONS + 1;

class Missions : Functions
{
public:
	struct MissionEndOffset
	{
		int Start;
		int End = -1;
	};
private:

	struct SaveStructure
	{
		char signature[12] = "RAINBOMIZER";
		unsigned int randomSeed;

		SaveStructure()
		{
			memcpy(signature, "RAINBOMIZER", 12);
		};
	};

	struct MissionOrder
	{
		int Missions[TOTAL_MISSIONS];

		MissionOrder() { Reset(); }

		inline int& operator [] (int index)
		{
			if (index < START_MISSIONS || index > END_MISSIONS)
				return Missions[START_MISSIONS];

			return Missions[index - START_MISSIONS];
		};

		void Reset();
	};

	inline static struct GangThreats
	{
		int mafia = 0;
		int triads = 0;
		int diablos = 0;
		int yardies = 0;
		int yakuza = 0;
		int hoods = 0;
		int colombians = 1;
	} gang_threats;

	inline static SaveStructure mSaveStructure;
	inline static MissionOrder mMissionOrder;

	inline static int mLastOriginalMissionStarted = -1;
	inline static int mOriginalMission = -1;
	inline static int mRandomizedMission = -1;
	inline static bool mStoreNextScript = false;
	inline static bool mScriptReplaced = false;
	inline static CRunningScript* mRandomizedScript = nullptr;

	inline static std::vector<MissionEndOffset> mPostReplaceEndOffsets;
	inline static std::vector<MissionEndOffset> mPreReplaceEndOffsets;

	inline static std::unique_ptr<unsigned char[]> mTempMissionData;
	inline static std::unique_ptr<unsigned int[]> mLocalVariables;

	static void TeleportPlayerAfterMission();
	static void InitShuffledMissionOrder(SaveStructure*);

	static bool ShouldJump(CRunningScript*);

	static void MoveScriptToOriginalOffset(CRunningScript*);
	static void RestoreOriginalScriptForCleanup();

	static void __fastcall RandomizeMissionToStart(CRunningScript* script, void* edx, int* arg0, short count);
	static CRunningScript* StoreRandomizedScript(uint32_t ip);
	static char __fastcall JumpOnMissionEnd(CRunningScript*);

	static int GetRandomMission();

	static bool ProcessPreReplaceMissionEndOffsets(CRunningScript*, short opcode);
	static bool ProcessPostReplaceMissionEndOffsets(CRunningScript*, uint16_t& opcode);
	static void HandleEndThreadOpcode(CRunningScript*, short opcode);

	static void LoadMissionData(uint8_t* data, uint32_t size);
	static void SaveMissionData(uint8_t* data, uint32_t& size);

	static void __fastcall UnlockBridges(CBuilding* building, void* edx, int modelId);
	static void __fastcall RemoveCarCubes(CPathFind* path, void* edx, float x1, float y1,
	float z1, float x2, float y2, float z2, char a3);
	static void RemoveObjects(CEntity* entity);
	static void UnlockShoresideBridge();
	static void __fastcall FixRemovingExchangeMoney(CRunningScript* script, void* edx, int* arg0, short count);
	static void __fastcall FixGiveMeLibertyMovement(CRunningScript* script, void* edx, int* arg0, short count);
	static void FixWorldLoadingAfterToyminator(CVector& point);
	static void BlockExtraText(wchar_t* message, int time, short flag);
	static void __fastcall FixSalvatoresGarage(CRunningScript* script, void* edx, int* arg0, short count);
	static void DoGameSpecificStuffAfterSucessLoad();
	static void FindClosestHospitalRestartPoint(CVector& point, CVector* storedPoint, float* angle);
	static void FindClosestPoliceRestartPoint(CVector& point, CVector* storedPoint, float* angle);

	static void ShouldOverrideRestart(CVector& point, float angle);
	static void __fastcall ShouldRestartCritical(CPlayerInfo* player);

	static eLevelName GetIslandFromMission(int mission);
	static bool ShouldBuildingBeReplaced(int origModel, int newModel);
	static bool ShouldObjectBeRemoved(int model);
	static bool ShouldRemoveCarCube(float x1, float x2);
	static void SetGangHostility(bool mafia, bool triads, bool diablos, bool yardies, bool yakuza = false, bool hoods = false, bool colombians = true);
	static void SetGangHostilityBasedOnNewMission(int mission);
	static void StoreGangThreatStates();
	static void ResetGangThreatStates();
	static void OpenPortlandSafehouseDoor();
	static void FixEndOfMissions();
	static void RemoveBridgeObstacles();

public:
	static void Initialise();
};