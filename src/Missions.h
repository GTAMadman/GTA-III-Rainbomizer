#pragma once

#include <string>
#include <memory>
#include "Functions.h"
#include <queue>

class CRunningScript;

const int SIZE_MISSION_SCRIPT = 0x8000;

class Missions : Functions
{
public:
	struct MissionEndOffset
	{
		int Start;
		int End = -1;
	};	
private:
	
	inline static int mOriginalMission = -1;
	inline static int mRandomizedMission = -1;
	inline static bool mStoreNextScript = false;
	inline static bool mScriptReplaced = false;
	inline static CRunningScript* mRandomizedScript = nullptr;

	inline static std::vector<MissionEndOffset> mPostReplaceEndOffsets;
	inline static std::vector<MissionEndOffset> mPreReplaceEndOffsets;
	
	inline static std::unique_ptr<unsigned char[]> mTempMissionData;
	inline static std::unique_ptr<unsigned int[]> mLocalVariables;

	static void TeleportPlayerAfterMission ();
	
	static bool ShouldJump (CRunningScript*);
	
	static void MoveScriptToOriginalOffset (CRunningScript*);
	static void RestoreOriginalScriptForCleanup ();
	
	static void __fastcall RandomizeMissionToStart (CRunningScript* script, void* edx, int* arg0, short count);
        static CRunningScript *StoreRandomizedScript (uint32_t ip);
	static char __fastcall JumpOnMissionEnd (CRunningScript*);

        static int GetRandomMission ();

	static bool ProcessPreReplaceMissionEndOffsets (CRunningScript*, short opcode);
	static bool ProcessPostReplaceMissionEndOffsets (CRunningScript*, uint16_t &opcode);
	static void HandleEndThreadOpcode (CRunningScript*, short opcode);
	
public:
	static void Initialise();
};
