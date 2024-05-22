#include "CInputSystem.h"

#include "../../util/utils.h"

//bool CInputSystem::IsKeyDown(int cKey)
//{
//	if (!this) {
//		return false;
//	}
//
//	using isKeyDown_t = bool(__fastcall*)(void*, int);
//	static isKeyDown_t isKeyDown = (isKeyDown_t)((*(uintptr_t**)this)[19]);
//	if (!isKeyDown) {
//		return false;
//	}
//
//	return isKeyDown(this, cKey);
//}
//
//int CInputSystem::VirtualKeyToButtonCode(int cVirtualKey)
//{
//	if (!this) {
//		return 0;
//	}
//
//	using virtualKeyToButtonCode_t = int(__fastcall*)(void*, int);
//	static virtualKeyToButtonCode_t virtualKeyToButtonCode = (virtualKeyToButtonCode_t)g_utils.GetPatternAddress("inputsystem.dll", "48 63 C2 48 8D 0D ? ? ? ? 8B 04 81 C3");
//	if (!virtualKeyToButtonCode) {
//		return 0;
//	}
//
//	return virtualKeyToButtonCode(this, cVirtualKey);
//}
