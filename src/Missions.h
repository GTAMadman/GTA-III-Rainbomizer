#pragma once

#include <string>
#include <memory>
#include "Functions.h"

class CRunningScript;

const int SIZE_MISSION_SCRIPT = 0x8000;

class Missions : Functions
{
	inline static int mOriginalMission = -1;
	inline static int mRandomizedMission = -1;
	inline static bool mStoreNextScript = false;
	inline static bool mScriptReplaced = false;
	inline static CRunningScript* mRandomizedScript = nullptr;
	
	inline static std::unique_ptr<unsigned char[]> mTempMissionData;
	inline static std::unique_ptr<unsigned int[]> mLocalVariables;

	static void TeleportPlayerAfterMission ();
	
	static bool ShouldJump (CRunningScript*);
	static void MoveScriptToOriginalOffset (CRunningScript*);
	
	static void __fastcall RandomizeMissionToStart (CRunningScript* script, void* edx, int* arg0, short count);
        static CRunningScript *StoreRandomizedScript (uint32_t ip);
	static char __fastcall JumpOnMissionEnd (CRunningScript*);

        static int GetRandomMission ();

	static void HandleReturnOpcode (CRunningScript*, short opcode);
	static void HandleEndThreadOpcode (CRunningScript*, short opcode);
	
public:
	static void Initialise();
};
