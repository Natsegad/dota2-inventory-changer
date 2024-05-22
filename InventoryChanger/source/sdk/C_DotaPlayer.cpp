#include "C_DotaPlayer.h"

#include "../DGlobalValues.h"
#include "../Netvar.h"

void* C_DotaPlayer::operator new(size_t size)
{

	return Dota::GetIMemAlloc()->Alloc(size);
}

void C_DotaPlayer::operator delete(void* memory)
{
	Dota::GetIMemAlloc()->Free(memory);
}

char* C_DotaPlayer::GetPlayerSelectedHero()
{
	if (!this->m_playerPtr) return (char*)"";

	using fn = char* (__fastcall*)(void*, int);
	static auto playerResourcePtr = (void*)g_utils.GetAbsOrigin((uintptr_t)g_utils.GetPatternAddress("client.dll", "48 8b 0d ? ? ? ? 48 85 c9 74 ? 8b 54 24 ? e8 ? ? ? ? 48 8b f8"), 3, 7);
	if (!playerResourcePtr) {
		return (char*)"";
	}
	auto playerResource = *(uintptr_t*)playerResourcePtr;
	if (!playerResource) {
		return (char*)"";
	}

	static auto _fn = (fn)(g_utils.GetPatternAddress("client.dll", "48 83 ec ? 85 d2 0f 88 ? ? ? ? 3b 91 ? ? ? ? 0f 8d ? ? ? ? 48 8b 81 ? ? ? ? 4c 63 c2 49 69 d0 ? ? ? ? 80 7c 02 ? ? 0f 84"));
	if (!_fn) {
		return (char*)"";
	}

	return _fn((void*)playerResource, GetPlayerID());
}

int C_DotaPlayer::GetPlayerID()
{
	if (!m_playerPtr) {
		return -2;
	}

	static DWORD playerIDOffset = Netvars::GetOffset("C_DOTAPlayerController", "m_nPlayerID");
	return *(int*)((uintptr_t)m_playerPtr + playerIDOffset);
}
