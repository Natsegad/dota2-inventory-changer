#include <Windows.h>

#include "../../util/utils.h"


class CGameEntitySystem {
public:
	__forceinline void* GetEntityByClassName(void* p,const char* className) {
		if (!this) {
			return nullptr;
		}

		using getEntityByClassName_t = void* (__fastcall*)(void*, void*, const char*);
		static getEntityByClassName_t getEntityByClassName = (getEntityByClassName_t)g_utils.GetPatternAddress("client.dll", "48 83 EC 68 45 33 C9 C7 44 24 ? ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 48 83 C4 68 C3 ");
		if (!getEntityByClassName) {
			return nullptr;
		}

		return getEntityByClassName(this,p,className);
	}
};