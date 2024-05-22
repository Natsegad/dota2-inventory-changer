#pragma once
#include <Windows.h>

#include "../../util/utils.h"

class GameManager {
public:
	GameManager();
	~GameManager();

	__int64 GetHeroIdByName(const char* name);
	const char* GetHeroNameById(int hero_id);

private:
	uintptr_t pointer = 0;
};

__forceinline __int64 GameManager::GetHeroIdByName(const char* name) {
	using fn = __int64(__fastcall*)(uintptr_t, const char*);

	static auto GetId = (fn)g_utils.GetPatternAddress("client.dll", "48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B DA 48 8B F9 48 85 D2 0F 84 ? ? ? ? 80 3A 00 0F 84 ? ? ? ? ");

	return GetId(pointer, name);
}

inline const char* GameManager::GetHeroNameById(int hero_id) {
	using fn = const char* (__fastcall*)(uintptr_t, int);

	static auto GetId = (fn)g_utils.GetPatternAddress("client.dll", "48 89 6C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 8B F2 48 8B E9 E8 ? ? ? ? 80 B8 ? ? ? ? ? 75 18 80 B8 ? ? ? ? ? 75 0F  ");

	return GetId(pointer, hero_id);
}

__forceinline GameManager::GameManager() {
	if (pointer == 0) {
		pointer = g_utils.GetAbsOrigin((uintptr_t)g_utils.GetAbsOrigin((uintptr_t)g_utils.GetPatternAddress("client.dll", "E8 ? ? ? ? 80 B8 ? ? ? ? ? 75 17 80 B8 ? ? ? ? ? 75 0E 80 B8 ? ? ? ? ? B9 ? ? ? ? "),1,5), 3, 7) + 0x260;
	}
}

__forceinline GameManager::~GameManager() {

}

