#include "hooks.h"

void* hkCreateParticle(void* thisptr, __int64* particleMgr, void* unk, void* query, bool bUnk, float fUnk, int particleIndex)
{
	if (particleMgr && *particleMgr) {
		auto modelName = **(const char***)(*particleMgr + 8);
		auto replaceIT = global::g_mapReplaceParticles.find(modelName);
		if (replaceIT != global::g_mapReplaceParticles.end()) {

			*particleMgr = (__int64)inventory::GetParticlePtr(replaceIT->second.data());
			goto END;
		}

		auto assetModifierIT = global::g_mapModelParticles.find(modelName);
		if (assetModifierIT != global::g_mapModelParticles.end()) {
			*particleMgr = (__int64)inventory::GetParticlePtr(assetModifierIT->second.data());
		}
	}
	END:
	return oCreateParticle(thisptr, particleMgr, unk, query, bUnk, fUnk, particleIndex);
}