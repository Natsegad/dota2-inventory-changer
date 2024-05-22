#include "hooks.h"

#include "../source/DGlobalValues.h"

#include "../source/sdk/C_DOTAWearableItem.h"
#include <string>

std::vector<short> items = { 5957,26449,26448,26445,26446 };

std::vector<std::string> ReadFileData() {
	std::vector<std::string> ret;
	std::ifstream fs("items.txt");
	if (fs.is_open()) {
		std::string word;
		while (fs >> word)
		{
			ret.push_back(word);
		}
	}
	else {
		fmt::log("File items not open ! \n");
	}
	fs.close();
	return ret;
}

bool hkIsStyleUnlocked(void*, void*)
{
	return true;
}

__int64 hkModelChange(__int64 skeletonInstace, __int64 entity, __int64* model)
{

	*(__int64*)(skeletonInstace + 184) = *model;
	*(BYTE*)(skeletonInstace + 176) = 1;

	auto localHero = Dota::GetLocalHero();
	if (localHero->GetSceneNode()->get_skeleton_instance()->get_model_state() == skeletonInstace) {

		uintptr_t ptr = *(uintptr_t*)(model);
		char* changeToModel = **(char***)(ptr + 0x8);
		auto modelChangeIT = global::g_mapModifierTypeAsset.find("hero_model_change");
		if (modelChangeIT != global::g_mapModifierTypeAsset.end()) {

			auto assetIT = modelChangeIT->second.find(changeToModel);
			if (assetIT != modelChangeIT->second.end()) {

				auto elderd = inventory::GetResourcePtr(assetIT->second.modifier);
				model = (__int64*)&elderd;
				*(__int64*)(skeletonInstace + 184) = *model;

			}

		}

		if (localHero->GetDefaultModel() != changeToModel)
		{

			global::g_isHideParticle = true;
			C_DOTA_BaseNpc::HideWearable();

		}
		else if (localHero->GetDefaultModel() == changeToModel && !global::g_isModelChange) {

			global::g_isModelChange = true;
			global::g_isHideParticle = false;

		}
	}
	return *model;
}

void hkSetParticleVisible(void* ths, int visible, int unk)
{
	if (global::g_isHideParticle) {
		for (auto& obj : global::g_vecMyWearables) {
			if (obj == ths) {
				oSetParticleVisible(ths, 0, unk);
				return;
			}
		}
	}
	oSetParticleVisible(ths, visible, unk);
}

void* hkSetSummonModel(void* rcx, __int64* rdx, __int64* resorcePtr)
{
	auto modelName = **(const char***)(*resorcePtr + 8);
	auto assetModifierIT = global::g_mapModelParticles.find(modelName);
	if (assetModifierIT != global::g_mapModelParticles.end()) {
		*resorcePtr = (__int64)inventory::GetResourcePtr(assetModifierIT->second.data());
	}

	return oSetSummonModel(rcx, rdx, resorcePtr);
}

__int64 hkStartSoundEvent(__int64 a1, __int64 a2, __int64 a3)
{
	auto soundName = Dota::GetSoundOpSystem()->GetSoundName(*(DWORD*)(a2 + 0x24));
	auto soundAssetModifiers = global::g_mapModifierTypeAsset["sound"];
	auto soundIT = soundAssetModifiers.find(soundName.data());
	if (soundIT != soundAssetModifiers.end()) {
		*(DWORD*)(a2 + 0x24) = Dota::GetSoundOpSystem()->GetSoundId(soundIT->second.modifier);
	}
	return oStartSoundEvent(a1, a2, a3);
}

void hkPreSetSequence(void* a1, DWORD* pHSequence, int a3, int a4)
{
	oPreSetSequence(a1, pHSequence, a3, a4);
	if (Dota::GetLocalHero()->GetModelData(Dota::GetLocalHero()->GetModelImp()) == a1) {
		auto activity = Dota::GetLocalHero()->GetSceneNode()->get_skeleton_instance()->GetActivityName(*pHSequence).data();
		//fmt::log("asdasdasdas %p %i %s\n",a1,*pHSequence, Dota::GetLocalHero()->GetSceneNode()->get_skeleton_instance()->GetSequenceName(*pHSequence).data());
		/*fmt::log("%s - %i - %i\n", activity, inventory::GetActivitySequence(activity, *pHSequence),*pHSequence);*/
		auto new_sequence = inventory::GetActivitySequence(activity, *pHSequence);
		*pHSequence = new_sequence;
	}

}

void* hkGetResourceId(void* rcx, const char* resource)
{
	if (Dota::GetLocalHero()->get_ptr()) {
		if (!strcmp(resource, "models/heroes/invoker/forge_spirit.vmdl")) {
			resource = "models/items/invoker/forge_spirit/dark_sorcerer_forge_spirit/dark_sorcerer_forge_spirit.vmdl";
			fmt::log("%s \n", resource);
		}
	}
	return oGetResourceId(rcx, resource);
}

void hkCycleReset(void* rcx, void* rdx, void* r8)
{
	if (global::g_personDefIndex || global::g_arcanaDefIndex) {
		if (rcx == Dota::GetLocalHero()->GetBodyComponent()->GetAnimatingController()) {
			return;
		}
	}

	oCycleReset(rcx, rdx, r8);
}

void* hkPrecacheEntity(void* entity, void* ckv)
{
	auto ent = (C_DOTA_BaseNpc*)(entity);

	if (ent->GetNpcName() == Dota::GetPlayer()->GetPlayerSelectedHero()) {
		inventory::CreateResourceManifest();
	}
	return oPrecacheEntity(entity,ckv);
}

bool isMov = false;
void* hkFrameStage(void* rcx, ClientFrameStage_t state)
{
	/*fmt::log("hkFrameStage %i \n", state);*/
	switch (state) {
	case 9: {
		/*if (GetAsyncKeyState(VK_SPACE)) {
			auto modelSeqData = Dota::GetLocalHero()->GetModelData(Dota::GetLocalHero()->GetModelImp());
			if (modelSeqData) {
				for (int i = 0; i < modelSeqData->count; i++) {
					auto sequence = (DWORD*)((uintptr_t)modelSeqData->pSequences + i * 0x8);
					auto sequenceActivity = Dota::GetLocalHero()->GetSceneNode()->get_skeleton_instance()->GetActivityName(*sequence);
					fmt::log("%i - %s \n", sequence, sequenceActivity.data());
				}
			}
		}*/
		if (strstr(Dota::GetPlayer()->GetPlayerSelectedHero(), "npc_") && !global::g_isHeroPick) {
			global::g_isHeroPick = true;
			inventory::LoadAssetModifirs();
		}
	
		switch (Engine::IsInGame()) {
		case true: {
			if (!global::g_isInGame) {
				global::g_isInGame = true;
			}
			break;
		}
		case false: {
			if (global::g_isInGame) {
				isMov = false;

				global::g_arcanaDefIndex = 0;
				global::g_personDefIndex = 0;
				global::g_shCourierDefIndex = 0;

				global::g_isInGame = false;
				global::g_isHeroPick = false;
				global::g_isLoadParticle = false;

				global::g_mapHeroAssetModifiers.clear();
				global::g_mapItemsHero.clear();
				global::g_mapModifierTypeAsset.clear();
				global::g_vecMyWearables.clear();
				global::g_mapAnimating.clear();
				global::g_setReplaceItemsHero.clear();
				global::g_mapReplaceParticles.clear();
			}
			break;
		}
		}
		break;
	}
	case 6: {

		inventory::Courier();
		inventory::Wards();

		if (global::g_isModelChange) {
			C_DOTA_BaseNpc::ModelReset();

			global::g_isModelChange = false;
		}

		C_DOTA_BaseNpc::IllusionSetter();
		if (!isMov && Dota::GetLocalHero()->get_ptr() && Dota::GetLocalHero()->IsMoving()) {
			isMov = true;

			inventory::InitItemsForEquip();
			inventory::SpawnItems();
			global::g_isLoadParticle = true;
			global::g_mapHeroAssetModifiers.clear();
		}

		break;
	}
	}
	return oFrameStage(rcx, state);
}

int hkCreateEntity(void* rcx, void* entity, int id)
{
	auto npc = (C_DOTA_BaseNpc*)entity;
	/*fmt::log("%s \n", npc->GetNpcName().data());*/
	return oCreateEntity(rcx, entity, id);
}

int hkRemoveEntity(void* rcx, void* entity, int id)
{
	return oRemoveEntity(rcx, entity, id);
}

__int64 hkSetAbilityIcon(__int64 rcx, __int64 econ)
{
	if (!strcmp((const char*)econ, "queenofpain_sonic_wave")) {
		econ = (__int64)"queen_of_pain/arcana/queenofpain_sonic_wave_alt1";
	}
	return oSetAbilityIcon(rcx, econ);
}

bool hkGetParticleAttachment(__int64 a1, __int64 a2, __int64 v3)
{
	if (global::g_personDefIndex == 13042) {
		if (a2 == (__int64)Dota::GetLocalHero()->get_ptr()) {
			switch (v3)
			{
			case 1:
				v3 = 5;
				break;
			case 2:
				v3 = 4;
				break;
			case 7:
				v3 = 2;
				break;
			case 8:
				v3 = 1;
				break;
			case 9:
				v3 = 3;
				break;
			}
		}
	}
	return oGetParticleAttachment(a1, a2, v3);
}

__int64 hkCreateAbilityIcon(void* rcx, void* rdx)
{
	auto ret = oCreateAbilityIcon(rcx, rdx);
	global::g_vecAbilityIcons.push_back((void*)ret);
	return ret;
}

//static auto kv = new KeyValues();
//inventory::IterateItems([](void* data) {
//	auto modelPlayer = kv->GetString(data, "model_player");
//	if (modelPlayer && strstr(modelPlayer, "arcana")) {
//		for (auto kk = kv->GetFirstTrueSubKey(kv->FindKey(data, "visuals", false)); kk; kk = kv->GetNextTrueSubKey(kk)) {
//			auto type = kv->GetString(kk, "type");
//			if (type && !strcmp(type, "entity_model")) {
//				if (kv->GetInt(kv->FindKey(data, "used_by_heroes", false), kv->GetString(kk, "asset"))) {
//					printf("case %s:{return %s;} \n", kv->GetName(data), kv->GetName(data));
//				}
//			}
//		}
//	}
//	});