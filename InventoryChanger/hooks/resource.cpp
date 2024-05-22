#include "hooks.h"

#include "../source/DGlobalValues.h"

#include <intrin.h>

void hkDeallocateResource(void* pCResourceSystem, void* resource)
{
	oDeallocateResource(pCResourceSystem, resource);
}

class ResourceDataR
{
public:
	DWORD length; //0x0000
	char asdasd[4];
	char* begin;
	std::string GetName(){
		char name[256];
		memset(name, 0, 256);
		memcpy(name,  &begin, length);
		return name ? name : "";
	}
};

void* hkGetResourcePtr(void* rcx, int count, void* r8)
{
	if (Dota::GetLocalHero()->get_ptr() && !global::g_isLoadParticle) {
		int resCount = 0;
		const char* resources[200] = {

		};

		for (auto& a : global::g_mapReplaceParticles) {
			resources[resCount] = a.second.data();
			resCount++;
		}

		for (auto& a : global::g_mapHeroAssetModifiers) {

			for (auto& a : a.second) {
				resources[resCount] = a;
				resCount++;
			}
		}

		oGetResourcePtr(rcx, resCount, resources);
		global::g_isLoadParticle = true;
	}
	
	return oGetResourcePtr(rcx, count, r8);
}