#include "hooks.h"

#include "../source/sdk/CGameManager.h"
#include "../source/DGlobalValues.h"

void __fastcall hkAddInternal(__int64 rcx, const char* rdx) {

	//auto assetModifiers = global::g_mapHeroAssetModifiers.find(rdx);
	//if (assetModifiers != global::g_mapHeroAssetModifiers.end()) {
	//    for (auto& a : assetModifiers->second) {
	//        oAddInternal(rcx, a);
	//    }
	//}

	//auto replaceIT = global::g_mapReplaceParticles.find(rdx);
	//if (replaceIT != global::g_mapReplaceParticles.end()) {
	//    oAddInternal(rcx, replaceIT->second.data());
	//}
	//if (Dota::GetLocalHero()->get_ptr()) {
	//	if (!global::g_isLoadParticle) {
	//		for (auto& a : global::g_mapReplaceParticles) {
	//			oAddInternal(rcx, a.second.data());
	//		}

	//		for (auto& a : global::g_mapHeroAssetModifiers) {

	//			for (auto& a : a.second) {
	//				oAddInternal(rcx, a);
	//			}
	//		}
	//		global::g_isLoadParticle = true;
	//	}
	//}
	/*  if (Dota::GetLocalHero()->get_ptr()) {
		  if (!global::g_mapReplaceParticles.empty()) {
			  for (auto& a : global::g_mapReplaceParticles) {
				  oAddInternal(rcx, a.second.data());
			  }
			  global::g_mapReplaceParticles.clear();
		  }

		  if (!global::g_mapHeroAssetModifiers.empty()) {
			  for (auto& a : global::g_mapHeroAssetModifiers) {

				  for (auto& a : a.second) {
					  oAddInternal(rcx, a);
				  }
			  }
			  global::g_mapHeroAssetModifiers.clear();
		  }

	  }*/

	  //if (!global::g_mapHeroAssetModifiers.empty()) {
	  //    for (auto& heroAssetModifiers : global::g_mapHeroAssetModifiers) {
	  //        for (auto& a : heroAssetModifiers.second) {
	  //            oAddInternal(rcx, a);
	  //        }
	  //    }

	  //    global::g_mapHeroAssetModifiers.clear();
	  //}

	oAddInternal(rcx, rdx);
}