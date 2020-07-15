#include "Autosave.h"

bool Autosave::ShouldSave = false;
void __fastcall Autosave::RequestAutosave(CRunningScript* script, void* edx, int opcode)
{
	ProcessCommands0to99(script, opcode);

	if (opcode == 78 && script->m_bIsMission && ShouldSave)
	{
		int slot = Config::autosave.slot;
		bool inVehicle = FindPlayerPed()->m_bInVehicle;

		script->m_bIsActive = false;

		if (FindPlayerVehicle())
			FindPlayerPed()->m_bInVehicle = false;

		char* file = MakeValidSaveName(slot - 1);
		int handle = CFileMgr::OpenFile(file, "wb");

		GenericSave(handle);
		CFileMgr::CloseFile(handle);

		ShouldSave = false;
		FindPlayerPed()->m_bInVehicle = inVehicle;
	}
}
void __fastcall Autosave::IncreaseMissionsPassed(CRunningScript* script, void* edx, int* arg0, short count)
{
	script->CollectParameters(arg0, count);
	ShouldSave = true;
}
char* Autosave::MakeValidSaveName(int slot)
{
	return plugin::CallAndReturnDynGlobal<char*>(0x591B10, slot);
}
void Autosave::GenericSave(int fileHandle)
{
	plugin::CallAndReturn<int, 0x58F8D0>(fileHandle);
}
char Autosave::ProcessCommands0to99(CRunningScript* script, int opcode)
{
	return plugin::CallMethodAndReturn<char, 0x439650>(script, opcode);
}
void Autosave::Initialise()
{
	if (Config::autosave.Enabled)
	{
		plugin::patch::RedirectCall(0x439552, RequestAutosave);
		plugin::patch::RedirectCall(0x447D88, IncreaseMissionsPassed);
	}
}