#include "utils.h"

#include <iostream>
#include <vector>
#include <vcruntime_string.h>
#include <cstdarg>
#include <string.h>
#include <array>

#include "../source/DGlobalValues.h"

#include "../hooks/hooks.h"

#include "../source/sdk/Steam.h"
#include "../source/sdk/C_DOTAWearableItem.h"

#include <string>
#include <algorithm>

utils g_utils;

BYTE m_aplAssetModPatchOne[10];
BYTE m_aplAssetModPatchTwo[10];
BYTE m_equipWearablePatchOne[10];
BYTE m_equipWearablePatchTwo[10];
BYTE m_removeWearablePatch[10];
BYTE m_remove_one_item[10];


uintptr_t o_assetModifier = reinterpret_cast<uintptr_t>(g_utils.GetPatternAddress("client.dll", "0F 84 ? ? ? ? 49 8D 8D ? ? ? ? 48 89 6C 24 ?"));
uintptr_t o_equipWearable = reinterpret_cast<uintptr_t>(g_utils.GetPatternAddress("client.dll", "48 85 D2 0F 84 ?? ?? ?? ?? 57 41 56 48 83 EC ?? 4C 8B F2"));
uintptr_t remove_wearable_patch_address = (uintptr_t)g_utils.GetPatternAddress("client.dll", "0F 84 ? ? ? ? 48 89 74 24 ? 33 F6 39 B3 ? ? ? ?");
uintptr_t remove_one_item = (uintptr_t)g_utils.GetPatternAddress("client.dll", "74 52 8B 97 ? ? ? ? 83 FA FD 77 47 8B C2 25 ? ? ? ?");


constexpr BYTE removeItemOriginal[2] = { 0x74, 0x52 };
constexpr BYTE equipItemOriginalFirstLabel[6] = { 0x0F, 0x84, 0x60, 0x01, 0x00, 0x00 };
constexpr BYTE equipItemOriginalTwoLabel[6] = { 0x0F, 0x84, 0x50, 0x01, 0x00, 0x00 };
constexpr BYTE applyAssetModifierOirign[6] = { 0x0F, 0x84, 0x7a, 0x07, 0x00, 0x00 };
constexpr BYTE removeAllWearableOrigin[6] = { 0x0F, 0x84, 0x45, 0x01, 0x00, 0x00 };
constexpr BYTE equipWearableOne[6] = { 0x0F, 0x84, 0x45, 0x01, 0x00, 0x00 };

void inventory::CreateResourceManifest()
{
	using initManifest_t = void* (__fastcall*)(void*, int a2, int a3, char a4, const char* a5);
	static initManifest_t initManifest = (initManifest_t)g_utils.GetPatternAddress("resourcesystem.dll", "48 89 5c 24 ? 48 89 6c 24 ? 48 89 7c 24 ? 4c 89 74 24 ? 41 57");
	if (!initManifest) {
		fmt::log("#CreateResourceManifest #1 pattern error \n");
		return;
	}

	using createManifest_t = void* (__fastcall*)(void*, int, void*);
	static createManifest_t createManifest = (createManifest_t)g_utils.GetPatternAddress("resourcesystem.dll", "48 89 5c 24 ? 48 89 74 24 ? 55 57 41 55");
	if (!createManifest) {
		fmt::log("#CreateResourceManifest #2 pattern error \n");
		return;
	}

	using applyResource_t = void(__fastcall*)(void*);
	static applyResource_t applyResource = (applyResource_t)g_utils.GetAbsOrigin((uintptr_t)g_utils.GetPatternAddress("resourcesystem.dll", "E8 ? ? ? ? C6 87 ? ? ? ? ? EB 1C E8 ? ? ? ? EB 15 48 8D 8F ? ? ? ? C6 43 46 01 48 8D 54 24 ? E8 ? ? ? ? "), 1, 5);
	if (!applyResource) {
		fmt::log("#CreateResourceManifest #3 pattern error \n");
		return;
	}

	auto group = "SV:  [3: <none> | CDOTA_BaseNPC] spawn group prerequisites";
	auto manifestData = Dota::GetIMemAlloc()->Alloc(96);
	initManifest(manifestData, 0, 1, 1, group);

	int count = 0;
	const char* resources[200] = {

	};

	for (auto& a : global::g_mapReplaceParticles) {
		resources[count] = a.second.data();
		count++;
	}

	for (auto& a : global::g_mapHeroAssetModifiers) {

		for (auto& a : a.second) {
			resources[count] = a;
			count++;
		}
	}

	createManifest(manifestData, count, resources);
	applyResource(manifestData);
}

void inventory::LoadEquipsItems() {

}

void inventory::LoadAssetModifirs() {
	global::g_mapModelParticles.clear();
	global::g_mapHeroAssetModifiers.clear();
	global::g_mapModifierTypeAsset.clear();

	static KeyValues* kv = new KeyValues();

	auto playerSelectedHero = Dota::GetPlayer()->GetPlayerSelectedHero();
	auto unitName = inventory::GetEntityModel(playerSelectedHero);

	auto hndrd = global::g_mapSetItems.find(1000);
	if (hndrd != global::g_mapSetItems.end()) {
		auto wardModel = hndrd->second[71];
		if (wardModel) {
			global::g_mapHeroAssetModifiers[unitName].push_back(inventory::GetWardModel(wardModel).data());
		}
	}

	auto replaceItems = global::g_mapSetReplaceItems.find(Dota::GetGameManager()->GetHeroIdByName(playerSelectedHero));
	if (replaceItems != global::g_mapSetReplaceItems.end()) {
		for (auto& a : replaceItems->second) {
			global::g_setReplaceItemsHero.insert(a.second);
		}
	}

	auto slotDef = global::g_mapSetItems.find(Dota::GetGameManager()->GetHeroIdByName(playerSelectedHero));
	if (slotDef != global::g_mapSetItems.end()) {

		inventory::IterateItems([&slotDef, &playerSelectedHero, &unitName](void* data) {
			auto defIndex = std::atoi(kv->GetName(data));
			auto replaceItem = global::g_setReplaceItemsHero.find(defIndex);
			if (replaceItem != global::g_setReplaceItemsHero.end()) {

				auto visuals = kv->FindKey(data, "visuals", false);
				if (visuals) {

					for (auto kk = kv->GetFirstTrueSubKey(visuals); kk; kk = kv->GetNextTrueSubKey(kk)) {

						auto modifier = kv->GetString(kk, "modifier");
						if (modifier) {

							auto style = kv->GetInt(kk, "style");
							auto type = kv->GetString(kk, "type");
							auto asset = kv->GetString(kk, "asset");

							if (!strcmp(type, "particle")) {

								if (asset && modifier) {
									global::g_mapReplaceParticles[asset] = modifier;
								}

							}
						}
					}

				}

			}

			for (auto& a : slotDef->second) {

				if (defIndex == a.second) {
					auto visuals = kv->FindKey(data, "visuals", false);
					if (visuals) {
						for (auto kk = kv->GetFirstTrueSubKey(visuals); kk; kk = kv->GetNextTrueSubKey(kk)) {

							auto modifier = kv->GetString(kk, "modifier");
							if (modifier) {

								auto style = kv->GetInt(kk, "style");
								auto type = kv->GetString(kk, "type");
								auto asset = kv->GetString(kk, "asset");

								if (!strcmp(type, "activity")) {
									type = "sound";
								}

								BYTE lStyle = 0;
								AssetModifierData assModData = { 0,style };

								auto m_svKey = asset ? std::string_view(asset) : "";
								std::string_view m_svValue = "";

								auto styleIt = global::g_mapItemStyles.find(a.second);
								if (styleIt != global::g_mapItemStyles.end()) {
									lStyle = styleIt->second;
									if (styleIt->second == style) {

										assModData = { modifier,styleIt->second };
										m_svValue = modifier;
									}
								}

								if (m_svValue.empty()) {
									m_svValue = modifier;
								}
								if (!assModData.modifier) {
									assModData.modifier = modifier;
								}

								global::g_mapHeroAssetModifiers[unitName].push_back(modifier);
								if (asset && type && lStyle == style) {
									//
									// Если к примеру надо заменить базовую атаку у беби вокера
									//
									if (!strcmp(type, "entity_model")) {

										auto unitModel = inventory::GetUnitModel(asset);
										if (unitModel != "nullmodelname") {

											m_svKey = unitModel;
											asset = unitModel.data();
											if (!inventory::IsHaveFixResource(asset)) {
												global::g_mapModelParticles[m_svKey] = m_svValue;
											}

										}

									}
									for (auto& a : global::g_vecBaseAttacks) {

										if (a == asset) {
											global::g_mapModelParticles[m_svKey] = m_svValue;
										}

									}

									global::g_mapModifierTypeAsset[type].insert(std::make_pair(asset, assModData));

								}
							}
						}
					}
				}
			}
			});
	}
}

void inventory::FixResources()
{
	for (auto& a : global::g_mapItemsHero) {
		switch (a.second) {
		case 13806: {
			global::g_mapAnimating[43] = 46;
			global::g_mapAnimating[89] = 25;//attack
			global::g_mapAnimating[17] = 18;

			break;
		}
		case 9059: {
			global::g_mapAnimating[7] = 34; // run walk. have 6 if not fast run
			break;
		}
		case 6879: {
			global::g_mapAnimating[31] = 72; 
			global::g_mapAnimating[14] = 59;
			global::g_mapAnimating[22] = 63;
			break;
		}
		}
	}
}

void inventory::SpawnItems()
{

	C_DOTA_BaseNpc::SetHeroModel();
	C_DOTA_BaseNpc::LoadItems();

	inventory::FixResources();
	inventory::AnimatingUpdate();

}

void inventory::AnimatingUpdate()
{
	/*auto modelSeqData = Dota::GetLocalHero()->GetModelData(Dota::GetLocalHero()->GetModelImp());
	if (modelSeqData) {
		for (int i = 0; i < modelSeqData->count; i++) {
			auto sequence = (DWORD*)((uintptr_t)modelSeqData->pSequences + i * 0x8);
			auto animIT = global::g_mapAnimating.find(*sequence);
			if (animIT != global::g_mapAnimating.end()) {
				*sequence = animIT->second;
			}
		}
	}*/
}

void inventory::Courier()
{
	auto courier = (C_DOTA_BaseNpc*)(Dota::GetCGameEntitySystem()->GetEntityByClassName(0, "npc_dota_courier"));
	while (courier) {

		auto entityByChandle = Dota::GetEntityByChandle(courier->GetOwnerChandle());
		if (entityByChandle) {

			if (entityByChandle == Dota::GetPlayer()->GetPtr()) {

				if (Dota::GetLocalHero()->GetLevel() >= 4 && global::g_shCourierDefIndex) {
					auto flyCourModel = inventory::GetCourModel(global::g_shCourierDefIndex, true);
					if (courier->GetSceneNode()->get_skeleton_instance()->get_model_name() != flyCourModel)
						courier->SetModel(flyCourModel.data());
				}

				std::vector<void*> list;
				bool found = false;
				courier->GetWearables(list);
				for (auto& a : list) {

					auto item = (C_DOTAWearableItem*)a;
					if (global::g_shCourierDefIndex == item->GetItemDefIndex()) {
						found = true;
					}

				}

				if (!found) {
					C_DOTA_BaseNpc::CourierWearablesSpawn(courier);
					inventory::Patch();
					courier->ApplyWearableModifiers();
					inventory::UnPatch();
				}
			}

		}

		courier = (C_DOTA_BaseNpc*)(Dota::GetCGameEntitySystem()->GetEntityByClassName(courier, "npc_dota_courier"));

	}
}

LPVOID utils::HookMethod(_In_ LPVOID lpVirtualTable, _In_ PVOID pHookMethod,
	_In_opt_ uintptr_t dwOffset)
{
	uintptr_t dwVTable = *((uintptr_t*)lpVirtualTable);
	uintptr_t dwEntry = dwVTable + dwOffset;
	uintptr_t dwOrig = *((uintptr_t*)dwEntry);

	DWORD dwOldProtection;
	::VirtualProtect((LPVOID)dwEntry, sizeof(dwEntry),
		PAGE_EXECUTE_READWRITE, &dwOldProtection);

	*((uintptr_t*)dwEntry) = (uintptr_t)pHookMethod;

	::VirtualProtect((LPVOID)dwEntry, sizeof(dwEntry),
		dwOldProtection, &dwOldProtection);

	return (LPVOID)dwOrig;
}

void inventory::Wards()
{
	{
		auto ward = (C_DOTA_BaseNpc*)(Dota::GetCGameEntitySystem()->GetEntityByClassName(0, "npc_dota_ward_base"));
		while (ward) {

			auto entityByChandle = Dota::GetEntityByChandle(ward->GetOwnerChandle());
			if (entityByChandle) {

				if (entityByChandle == Dota::GetPlayer()->GetPtr()) {

					std::vector<void*> list;
					bool found = false;
					ward->GetWearables(list);
					for (auto& a : list) {

						auto item = (C_DOTAWearableItem*)a;
						if (global::g_shWardDefIndex == item->GetItemDefIndex()) {
							found = true;
						}

					}

					if (!found) {
						C_DOTA_BaseNpc::WardWearablesSpawn(ward);
						inventory::Patch();
						ward->ApplyWearableModifiers();
						inventory::UnPatch();
					}
				}

			}

			ward = (C_DOTA_BaseNpc*)(Dota::GetCGameEntitySystem()->GetEntityByClassName(ward, "npc_dota_ward_base"));
		}
	}

	{
		//npc_dota_ward_base_truesight

		auto trueSightWard = (C_DOTA_BaseNpc*)(Dota::GetCGameEntitySystem()->GetEntityByClassName(0, "npc_dota_ward_base_truesight"));
		while (trueSightWard) {

			auto entityByChandle = Dota::GetEntityByChandle(trueSightWard->GetOwnerChandle());
			if (entityByChandle) {

				if (entityByChandle == Dota::GetLocalHero()) {

					std::vector<void*> list;
					bool found = false;
					trueSightWard->GetWearables(list);
					for (auto& a : list) {

						auto item = (C_DOTAWearableItem*)a;
						if (global::g_shWardDefIndex == item->GetItemDefIndex()) {
							found = true;
						}

					}

					if (!found) {

						C_DOTA_BaseNpc::WardWearablesSpawn(trueSightWard);
						inventory::Patch();
						trueSightWard->ApplyWearableModifiers();
						inventory::UnPatch();

					}
				}

			}

			trueSightWard = (C_DOTA_BaseNpc*)(Dota::GetCGameEntitySystem()->GetEntityByClassName(trueSightWard, "npc_dota_ward_base"));
		}
	}
}

bool utils::IsReadWriteMem(void* address) {
	static MEMORY_BASIC_INFORMATION MBI;
	if (VirtualQuery(address, &MBI, sizeof(MBI)))
		if (MBI.AllocationProtect == 4) return true;

	return false;
}

uint8_t* utils::GetPatternAddress(const char* dll, const char* pattern)
{
	HANDLE module = GetModuleHandleA(dll);
	static auto pattern_to_byte = [](const char* pattern) {
		auto bytes = std::vector<int>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current) {
			if (*current == '?') {
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else {
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	auto dosHeader = (PIMAGE_DOS_HEADER)module;
	auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

	auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto patternBytes = pattern_to_byte(pattern);
	auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

	auto s = patternBytes.size();
	auto d = patternBytes.data();

	for (auto i = 0ul; i < sizeOfImage - s; ++i) {
		bool found = true;
		for (auto j = 0ul; j < s; ++j) {
			if (scanBytes[i + j] != d[j] && d[j] != -1) {
				found = false;
				break;
			}
		}
		if (found) {
			return &scanBytes[i];
		}
	}
	return nullptr;
}

uintptr_t utils::GetAbsOrigin(uintptr_t pInstruction, int iOffset, int iSize)
{
	if (!pInstruction) {
		fmt::log("Pattern is null ! \n");
		return 0;
	}

	DWORD offset = *(DWORD*)(pInstruction + iOffset);
	DWORD_PTR ptr = pInstruction + offset + iSize;

	if (offset > 0xF0000000) {
		ptr -= 0x100000000;
	}

	return ptr;
}

void fmt::log(const char* _f, ...)
{
	char msg[256];
	memset(msg, 0, 256);

	va_list v_arg;
	va_start(v_arg, _f);

	vsprintf_s(msg, _f, v_arg);
#ifndef NDEBUG
	std::cout << "[ DBG ] " << msg;
#else
	std::cout << "[ - ] " << msg;
	/*logFile.open(logPath, std::ios::out | std::ios::app | std::ios::binary);
	if (logFile.is_open()) {
		logFile << "[.] " << msg;
	}
	logFile.close();*/
#endif
	va_end(v_arg);
}

ResourceData* inventory::GetResourcePtr(const char* model)
{
	if (!model) {
		return nullptr;
	}

	using getResourcePtr_t = void* (__fastcall*)(void*, void*, char);
	static getResourcePtr_t getResourcePtr = (getResourcePtr_t)g_utils.GetPatternAddress("resourcesystem.dll", "48 89 5c 24 ? 48 89 74 24 ? 57 48 81 ec ? ? ? ? f7 02");
	if (!getResourcePtr) {
		return nullptr;
	}

	auto modelData = GetResourceId(model);
	if (!modelData) {
		return nullptr;
	}

	return (ResourceData*)getResourcePtr(Dota::GetResourcePtr(), modelData, 0);;
}

void* inventory::GetParticleResourceId(const char* resourceName)
{
	using getResourceId_t = void* (__fastcall*)(__int64*, const char*);
	static getResourceId_t getResourceId = (getResourceId_t)g_utils.GetPatternAddress("particles.dll", "48 89 5C 24 ? 57 48 83 EC 30 8B 41 04 48 8D 79 08 48 8B D9 A9 ? ? ? ? 76 0F 0F BA E0 1E 48 8B C7 72 03 ");
	if (!getResourceId) {
		return 0;
	}

	__int64* resource = (__int64*)Dota::GetIMemAlloc()->Alloc(200);
	*(__int64*)resource = 13835058914275622912;
	auto ret = getResourceId(resource, resourceName);

	return resource;
}

void* inventory::GetParticlePtr(const char* particle)
{
	if (!particle) {
		return nullptr;
	}

	using getResourcePtr_t = void* (__fastcall*)(void*, void*, char);
	static getResourcePtr_t getResourcePtr = (getResourcePtr_t)g_utils.GetPatternAddress("resourcesystem.dll", "48 89 5c 24 ? 48 89 74 24 ? 57 48 81 ec ? ? ? ? f7 02");
	if (!getResourcePtr) {
		return nullptr;
	}

	auto modelData = GetParticleResourceId(particle);
	if (!modelData) {
		return nullptr;
	}

	return (ResourceData*)getResourcePtr(Dota::GetResourcePtr(), modelData, 0);;
}

#pragma optimize("", off)
void* inventory::GetResourcePtrHost(const char* resource)
{
	constexpr BYTE oldBytes[] = { 0x74,0x3d };
	using getResPtr_t = void* (__fastcall*)(uintptr_t, void*, const char*);
	static getResPtr_t getResPtr = (getResPtr_t)g_utils.GetPatternAddress("host.dll", "48 8b c4 48 89 58 ? 57");
	if (!getResPtr) {
		return nullptr;
	}

	static auto modelInfoPtr = *(uintptr_t*)g_utils.GetAbsOrigin((uintptr_t)g_utils.GetPatternAddress("client.dll", "48 8b 0d ? ? ? ? 48 8d 55 ? 48 8b 01 ff 50 ? 48 8b 47"), 3, 7);
	if (!modelInfoPtr) {
		return nullptr;
	}

	auto retPre = Dota::GetIMemAlloc()->Alloc(8);

	auto ret = getResPtr(modelInfoPtr, retPre, resource);


	return ret;
}

void* inventory::GetResourceId(const char* resourceName)
{
	using getResourceId_t = void* (__fastcall*)(void*, const char*);
	static getResourceId_t getResourceId = (getResourceId_t)g_utils.GetPatternAddress("resourcesystem.dll", "48 89 5C 24 ? 57 48 83 EC 30 8B 41 04 48 8D 79 08 48 8B D9 A9 ? ? ? ? 76 0F 0F BA E0 1E 48 8B C7 72 03 ");
	if (!getResourceId) {
		return 0;
	}

	__int64* resource = (__int64*)Dota::GetIMemAlloc()->Alloc(200);
	*(__int64*)resource = 13835058914275622912;
	auto ret = getResourceId(resource, resourceName);

	return resource;
}
#pragma optimize("", on)
bool inventory::IsHaveFixResource(std::string_view resource)
{
	bool found = false;
	for (auto& kvRes : global::g_mapModelParticles) {
		if (kvRes.first == resource) {
			found = true;
			break;
		}
	}
	return found;
}

bool inventory::IsHaveThisItem(void* ent, short defIndex)
{
	auto entity = (C_DOTA_BaseNpc*)ent;
	std::vector<void*> list;
	bool found = false;
	entity->GetWearables(list);
	for (auto& a : list) {

		auto item = (C_DOTAWearableItem*)a;
		if (defIndex == item->GetItemDefIndex()) {
			found = true;
		}

	}

	return found;
}

short inventory::IsDefaultItem(short defIndex)
{
	switch (defIndex) {
	case 1: {return 1; }
	case 2: {return 2; }
	case 3: {return 3; }
	case 4: {return 4; }
	case 5: {return 5; }
	case 6: {return 6; }
	case 7: {return 7; }
	case 8: {return 8; }
	case 9: {return 9; }
	case 10: {return 10; }
	case 11: {return 11; }
	case 12: {return 12; }
	case 13: {return 13; }
	case 14: {return 14; }
	case 15: {return 15; }
	case 16: {return 16; }
	case 17: {return 17; }
	case 18: {return 18; }
	case 19: {return 19; }
	case 20: {return 20; }
	case 21: {return 21; }
	case 22: {return 22; }
	case 23: {return 23; }
	case 24: {return 24; }
	case 25: {return 25; }
	case 26: {return 26; }
	case 27: {return 27; }
	case 28: {return 28; }
	case 29: {return 29; }
	case 30: {return 30; }
	case 31: {return 31; }
	case 32: {return 32; }
	case 33: {return 33; }
	case 34: {return 34; }
	case 35: {return 35; }
	case 36: {return 36; }
	case 37: {return 37; }
	case 38: {return 38; }
	case 39: {return 39; }
	case 40: {return 40; }
	case 41: {return 41; }
	case 42: {return 42; }
	case 43: {return 43; }
	case 44: {return 44; }
	case 45: {return 45; }
	case 46: {return 46; }
	case 47: {return 47; }
	case 48: {return 48; }
	case 49: {return 49; }
	case 50: {return 50; }
	case 51: {return 51; }
	case 52: {return 52; }
	case 53: {return 53; }
	case 54: {return 54; }
	case 55: {return 55; }
	case 56: {return 56; }
	case 57: {return 57; }
	case 58: {return 58; }
	case 59: {return 59; }
	case 60: {return 60; }
	case 61: {return 61; }
	case 62: {return 62; }
	case 63: {return 63; }
	case 64: {return 64; }
	case 65: {return 65; }
	case 66: {return 66; }
	case 67: {return 67; }
	case 68: {return 68; }
	case 69: {return 69; }
	case 70: {return 70; }
	case 71: {return 71; }
	case 72: {return 72; }
	case 73: {return 73; }
	case 74: {return 74; }
	case 75: {return 75; }
	case 76: {return 76; }
	case 77: {return 77; }
	case 78: {return 78; }
	case 79: {return 79; }
	case 80: {return 80; }
	case 81: {return 81; }
	case 82: {return 82; }
	case 83: {return 83; }
	case 84: {return 84; }
	case 85: {return 85; }
	case 86: {return 86; }
	case 87: {return 87; }
	case 88: {return 88; }
	case 89: {return 89; }
	case 90: {return 90; }
	case 91: {return 91; }
	case 92: {return 92; }
	case 93: {return 93; }
	case 94: {return 94; }
	case 95: {return 95; }
	case 96: {return 96; }
	case 97: {return 97; }
	case 98: {return 98; }
	case 99: {return 99; }
	case 100: {return 100; }
	case 101: {return 101; }
	case 102: {return 102; }
	case 103: {return 103; }
	case 104: {return 104; }
	case 105: {return 105; }
	case 106: {return 106; }
	case 107: {return 107; }
	case 108: {return 108; }
	case 109: {return 109; }
	case 110: {return 110; }
	case 111: {return 111; }
	case 112: {return 112; }
	case 113: {return 113; }
	case 114: {return 114; }
	case 115: {return 115; }
	case 116: {return 116; }
	case 117: {return 117; }
	case 118: {return 118; }
	case 119: {return 119; }
	case 120: {return 120; }
	case 121: {return 121; }
	case 122: {return 122; }
	case 123: {return 123; }
	case 124: {return 124; }
	case 125: {return 125; }
	case 126: {return 126; }
	case 127: {return 127; }
	case 128: {return 128; }
	case 129: {return 129; }
	case 130: {return 130; }
	case 131: {return 131; }
	case 132: {return 132; }
	case 133: {return 133; }
	case 134: {return 134; }
	case 135: {return 135; }
	case 136: {return 136; }
	case 137: {return 137; }
	case 138: {return 138; }
	case 139: {return 139; }
	case 140: {return 140; }
	case 141: {return 141; }
	case 142: {return 142; }
	case 143: {return 143; }
	case 144: {return 144; }
	case 145: {return 145; }
	case 146: {return 146; }
	case 147: {return 147; }
	case 148: {return 148; }
	case 149: {return 149; }
	case 150: {return 150; }
	case 151: {return 151; }
	case 152: {return 152; }
	case 153: {return 153; }
	case 154: {return 154; }
	case 155: {return 155; }
	case 156: {return 156; }
	case 157: {return 157; }
	case 158: {return 158; }
	case 159: {return 159; }
	case 160: {return 160; }
	case 161: {return 161; }
	case 162: {return 162; }
	case 163: {return 163; }
	case 164: {return 164; }
	case 165: {return 165; }
	case 166: {return 166; }
	case 167: {return 167; }
	case 168: {return 168; }
	case 169: {return 169; }
	case 170: {return 170; }
	case 171: {return 171; }
	case 172: {return 172; }
	case 173: {return 173; }
	case 174: {return 174; }
	case 175: {return 175; }
	case 176: {return 176; }
	case 177: {return 177; }
	case 178: {return 178; }
	case 179: {return 179; }
	case 180: {return 180; }
	case 181: {return 181; }
	case 182: {return 182; }
	case 183: {return 183; }
	case 184: {return 184; }
	case 185: {return 185; }
	case 186: {return 186; }
	case 187: {return 187; }
	case 188: {return 188; }
	case 189: {return 189; }
	case 190: {return 190; }
	case 191: {return 191; }
	case 192: {return 192; }
	case 193: {return 193; }
	case 194: {return 194; }
	case 195: {return 195; }
	case 196: {return 196; }
	case 197: {return 197; }
	case 198: {return 198; }
	case 199: {return 199; }
	case 200: {return 200; }
	case 201: {return 201; }
	case 203: {return 203; }
	case 204: {return 204; }
	case 205: {return 205; }
	case 206: {return 206; }
	case 207: {return 207; }
	case 208: {return 208; }
	case 209: {return 209; }
	case 210: {return 210; }
	case 211: {return 211; }
	case 212: {return 212; }
	case 213: {return 213; }
	case 214: {return 214; }
	case 215: {return 215; }
	case 216: {return 216; }
	case 217: {return 217; }
	case 218: {return 218; }
	case 219: {return 219; }
	case 220: {return 220; }
	case 221: {return 221; }
	case 222: {return 222; }
	case 223: {return 223; }
	case 224: {return 224; }
	case 225: {return 225; }
	case 226: {return 226; }
	case 227: {return 227; }
	case 228: {return 228; }
	case 229: {return 229; }
	case 230: {return 230; }
	case 231: {return 231; }
	case 232: {return 232; }
	case 233: {return 233; }
	case 234: {return 234; }
	case 235: {return 235; }
	case 236: {return 236; }
	case 237: {return 237; }
	case 238: {return 238; }
	case 239: {return 239; }
	case 240: {return 240; }
	case 241: {return 241; }
	case 242: {return 242; }
	case 243: {return 243; }
	case 244: {return 244; }
	case 245: {return 245; }
	case 246: {return 246; }
	case 247: {return 247; }
	case 248: {return 248; }
	case 249: {return 249; }
	case 250: {return 250; }
	case 251: {return 251; }
	case 252: {return 252; }
	case 253: {return 253; }
	case 254: {return 254; }
	case 255: {return 255; }
	case 256: {return 256; }
	case 257: {return 257; }
	case 258: {return 258; }
	case 259: {return 259; }
	case 260: {return 260; }
	case 261: {return 261; }
	case 262: {return 262; }
	case 263: {return 263; }
	case 264: {return 264; }
	case 265: {return 265; }
	case 266: {return 266; }
	case 267: {return 267; }
	case 268: {return 268; }
	case 269: {return 269; }
	case 270: {return 270; }
	case 271: {return 271; }
	case 272: {return 272; }
	case 273: {return 273; }
	case 274: {return 274; }
	case 275: {return 275; }
	case 276: {return 276; }
	case 277: {return 277; }
	case 278: {return 278; }
	case 279: {return 279; }
	case 280: {return 280; }
	case 281: {return 281; }
	case 282: {return 282; }
	case 283: {return 283; }
	case 284: {return 284; }
	case 285: {return 285; }
	case 286: {return 286; }
	case 287: {return 287; }
	case 288: {return 288; }
	case 289: {return 289; }
	case 290: {return 290; }
	case 291: {return 291; }
	case 292: {return 292; }
	case 293: {return 293; }
	case 294: {return 294; }
	case 295: {return 295; }
	case 296: {return 296; }
	case 297: {return 297; }
	case 298: {return 298; }
	case 299: {return 299; }
	case 300: {return 300; }
	case 301: {return 301; }
	case 302: {return 302; }
	case 303: {return 303; }
	case 304: {return 304; }
	case 305: {return 305; }
	case 306: {return 306; }
	case 307: {return 307; }
	case 308: {return 308; }
	case 309: {return 309; }
	case 310: {return 310; }
	case 311: {return 311; }
	case 312: {return 312; }
	case 313: {return 313; }
	case 314: {return 314; }
	case 315: {return 315; }
	case 316: {return 316; }
	case 317: {return 317; }
	case 318: {return 318; }
	case 319: {return 319; }
	case 320: {return 320; }
	case 321: {return 321; }
	case 322: {return 322; }
	case 323: {return 323; }
	case 324: {return 324; }
	case 325: {return 325; }
	case 326: {return 326; }
	case 327: {return 327; }
	case 328: {return 328; }
	case 329: {return 329; }
	case 330: {return 330; }
	case 331: {return 331; }
	case 332: {return 332; }
	case 333: {return 333; }
	case 334: {return 334; }
	case 335: {return 335; }
	case 336: {return 336; }
	case 337: {return 337; }
	case 338: {return 338; }
	case 339: {return 339; }
	case 340: {return 340; }
	case 341: {return 341; }
	case 342: {return 342; }
	case 343: {return 343; }
	case 344: {return 344; }
	case 345: {return 345; }
	case 346: {return 346; }
	case 347: {return 347; }
	case 348: {return 348; }
	case 349: {return 349; }
	case 350: {return 350; }
	case 351: {return 351; }
	case 352: {return 352; }
	case 353: {return 353; }
	case 354: {return 354; }
	case 355: {return 355; }
	case 356: {return 356; }
	case 357: {return 357; }
	case 358: {return 358; }
	case 359: {return 359; }
	case 360: {return 360; }
	case 361: {return 361; }
	case 362: {return 362; }
	case 363: {return 363; }
	case 364: {return 364; }
	case 365: {return 365; }
	case 366: {return 366; }
	case 367: {return 367; }
	case 368: {return 368; }
	case 369: {return 369; }
	case 370: {return 370; }
	case 371: {return 371; }
	case 372: {return 372; }
	case 373: {return 373; }
	case 374: {return 374; }
	case 375: {return 375; }
	case 376: {return 376; }
	case 377: {return 377; }
	case 378: {return 378; }
	case 379: {return 379; }
	case 380: {return 380; }
	case 381: {return 381; }
	case 382: {return 382; }
	case 383: {return 383; }
	case 384: {return 384; }
	case 385: {return 385; }
	case 386: {return 386; }
	case 387: {return 387; }
	case 388: {return 388; }
	case 389: {return 389; }
	case 390: {return 390; }
	case 391: {return 391; }
	case 392: {return 392; }
	case 393: {return 393; }
	case 394: {return 394; }
	case 395: {return 395; }
	case 396: {return 396; }
	case 397: {return 397; }
	case 398: {return 398; }
	case 399: {return 399; }
	case 400: {return 400; }
	case 401: {return 401; }
	case 402: {return 402; }
	case 403: {return 403; }
	case 404: {return 404; }
	case 405: {return 405; }
	case 406: {return 406; }
	case 407: {return 407; }
	case 408: {return 408; }
	case 409: {return 409; }
	case 410: {return 410; }
	case 411: {return 411; }
	case 412: {return 412; }
	case 413: {return 413; }
	case 414: {return 414; }
	case 415: {return 415; }
	case 416: {return 416; }
	case 417: {return 417; }
	case 418: {return 418; }
	case 419: {return 419; }
	case 420: {return 420; }
	case 421: {return 421; }
	case 422: {return 422; }
	case 423: {return 423; }
	case 424: {return 424; }
	case 425: {return 425; }
	case 426: {return 426; }
	case 427: {return 427; }
	case 428: {return 428; }
	case 429: {return 429; }
	case 430: {return 430; }
	case 431: {return 431; }
	case 432: {return 432; }
	case 433: {return 433; }
	case 434: {return 434; }
	case 435: {return 435; }
	case 436: {return 436; }
	case 437: {return 437; }
	case 438: {return 438; }
	case 439: {return 439; }
	case 440: {return 440; }
	case 441: {return 441; }
	case 442: {return 442; }
	case 443: {return 443; }
	case 444: {return 444; }
	case 445: {return 445; }
	case 446: {return 446; }
	case 447: {return 447; }
	case 448: {return 448; }
	case 449: {return 449; }
	case 450: {return 450; }
	case 451: {return 451; }
	case 452: {return 452; }
	case 453: {return 453; }
	case 454: {return 454; }
	case 455: {return 455; }
	case 456: {return 456; }
	case 457: {return 457; }
	case 458: {return 458; }
	case 459: {return 459; }
	case 460: {return 460; }
	case 461: {return 461; }
	case 462: {return 462; }
	case 463: {return 463; }
	case 464: {return 464; }
	case 465: {return 465; }
	case 466: {return 466; }
	case 467: {return 467; }
	case 468: {return 468; }
	case 469: {return 469; }
	case 470: {return 470; }
	case 471: {return 471; }
	case 472: {return 472; }
	case 473: {return 473; }
	case 474: {return 474; }
	case 475: {return 475; }
	case 476: {return 476; }
	case 477: {return 477; }
	case 478: {return 478; }
	case 479: {return 479; }
	case 480: {return 480; }
	case 481: {return 481; }
	case 482: {return 482; }
	case 483: {return 483; }
	case 484: {return 484; }
	case 485: {return 485; }
	case 486: {return 486; }
	case 487: {return 487; }
	case 488: {return 488; }
	case 489: {return 489; }
	case 490: {return 490; }
	case 491: {return 491; }
	case 492: {return 492; }
	case 493: {return 493; }
	case 494: {return 494; }
	case 495: {return 495; }
	case 496: {return 496; }
	case 497: {return 497; }
	case 498: {return 498; }
	case 499: {return 499; }
	case 500: {return 500; }
	case 501: {return 501; }
	case 502: {return 502; }
	case 503: {return 503; }
	case 504: {return 504; }
	case 505: {return 505; }
	case 506: {return 506; }
	case 507: {return 507; }
	case 508: {return 508; }
	case 509: {return 509; }
	case 510: {return 510; }
	case 511: {return 511; }
	case 512: {return 512; }
	case 513: {return 513; }
	case 514: {return 514; }
	case 515: {return 515; }
	case 516: {return 516; }
	case 517: {return 517; }
	case 518: {return 518; }
	case 519: {return 519; }
	case 520: {return 520; }
	case 521: {return 521; }
	case 522: {return 522; }
	case 523: {return 523; }
	case 524: {return 524; }
	case 525: {return 525; }
	case 526: {return 526; }
	case 527: {return 527; }
	case 528: {return 528; }
	case 529: {return 529; }
	case 530: {return 530; }
	case 531: {return 531; }
	case 532: {return 532; }
	case 533: {return 533; }
	case 534: {return 534; }
	case 535: {return 535; }
	case 536: {return 536; }
	case 537: {return 537; }
	case 538: {return 538; }
	case 539: {return 539; }
	case 540: {return 540; }
	case 541: {return 541; }
	case 542: {return 542; }
	case 543: {return 543; }
	case 544: {return 544; }
	case 545: {return 545; }
	case 546: {return 546; }
	case 547: {return 547; }
	case 548: {return 548; }
	case 549: {return 549; }
	case 550: {return 550; }
	case 551: {return 551; }
	case 552: {return 552; }
	case 553: {return 553; }
	case 554: {return 554; }
	case 556: {return 556; }
	case 557: {return 557; }
	case 558: {return 558; }
	case 559: {return 559; }
	case 560: {return 560; }
	case 561: {return 561; }
	case 562: {return 562; }
	case 563: {return 563; }
	case 564: {return 564; }
	case 565: {return 565; }
	case 566: {return 566; }
	case 567: {return 567; }
	case 568: {return 568; }
	case 569: {return 569; }
	case 570: {return 570; }
	case 571: {return 571; }
	case 572: {return 572; }
	case 573: {return 573; }
	case 574: {return 574; }
	case 575: {return 575; }
	case 576: {return 576; }
	case 577: {return 577; }
	case 578: {return 578; }
	case 579: {return 579; }
	case 580: {return 580; }
	case 581: {return 581; }
	case 582: {return 582; }
	case 583: {return 583; }
	case 584: {return 584; }
	case 585: {return 585; }
	case 589: {return 589; }
	case 591: {return 591; }
	case 592: {return 592; }
	case 593: {return 593; }
	case 594: {return 594; }
	case 598: {return 598; }
	case 599: {return 599; }
	case 600: {return 600; }
	case 601: {return 601; }
	case 602: {return 602; }
	case 603: {return 603; }
	case 604: {return 604; }
	case 605: {return 605; }
	case 606: {return 606; }
	case 607: {return 607; }
	case 608: {return 608; }
	case 609: {return 609; }
	case 610: {return 610; }
	case 611: {return 611; }
	case 612: {return 612; }
	case 613: {return 613; }
	case 614: {return 614; }
	case 615: {return 615; }
	case 616: {return 616; }
	case 617: {return 617; }
	case 618: {return 618; }
	case 619: {return 619; }
	case 620: {return 620; }
	case 621: {return 621; }
	case 622: {return 622; }
	case 623: {return 623; }
	case 624: {return 624; }
	case 625: {return 625; }
	case 626: {return 626; }
	case 627: {return 627; }
	case 628: {return 628; }
	case 629: {return 629; }
	case 630: {return 630; }
	case 631: {return 631; }
	case 632: {return 632; }
	case 633: {return 633; }
	case 634: {return 634; }
	case 635: {return 635; }
	case 636: {return 636; }
	case 637: {return 637; }
	case 639: {return 639; }
	case 640: {return 640; }
	case 641: {return 641; }
	case 642: {return 642; }
	case 643: {return 643; }
	case 644: {return 644; }
	case 645: {return 645; }
	case 646: {return 646; }
	case 648: {return 648; }
	case 649: {return 649; }
	case 650: {return 650; }
	case 651: {return 651; }
	case 652: {return 652; }
	case 653: {return 653; }
	case 654: {return 654; }
	case 656: {return 656; }
	case 657: {return 657; }
	case 658: {return 658; }
	case 659: {return 659; }
	case 662: {return 662; }
	case 664: {return 664; }
	case 666: {return 666; }
	case 667: {return 667; }
	case 668: {return 668; }
	case 669: {return 669; }
	case 670: {return 670; }
	case 671: {return 671; }
	case 672: {return 672; }
	case 673: {return 673; }
	case 674: {return 674; }
	case 679: {return 679; }
	case 680: {return 680; }
	case 681: {return 681; }
	case 682: {return 682; }
	case 683: {return 683; }
	case 684: {return 684; }
	case 685: {return 685; }
	case 686: {return 686; }
	case 687: {return 687; }
	case 688: {return 688; }
	case 689: {return 689; }
	case 690: {return 690; }
	case 691: {return 691; }
	case 692: {return 692; }
	case 693: {return 693; }
	case 694: {return 694; }
	case 695: {return 695; }
	case 696: {return 696; }
	case 697: {return 697; }
	case 698: {return 698; }
	case 707: {return 707; }
	case 708: {return 708; }
	case 709: {return 709; }
	case 712: {return 712; }
	case 713: {return 713; }
	case 714: {return 714; }
	case 715: {return 715; }
	case 716: {return 716; }
	case 717: {return 717; }
	case 719: {return 719; }
	case 720: {return 720; }
	case 721: {return 721; }
	case 722: {return 722; }
	case 724: {return 724; }
	case 726: {return 726; }
	case 728: {return 728; }
	case 731: {return 731; }
	case 732: {return 732; }
	case 733: {return 733; }
	case 734: {return 734; }
	case 735: {return 735; }
	case 736: {return 736; }
	case 737: {return 737; }
	case 738: {return 738; }
	case 739: {return 739; }
	case 740: {return 740; }
	case 741: {return 741; }
	case 742: {return 742; }
	case 743: {return 743; }
	case 744: {return 744; }
	case 745: {return 745; }
	case 746: {return 746; }
	case 748: {return 748; }
	case 749: {return 749; }
	case 750: {return 750; }
	case 751: {return 751; }
	case 752: {return 752; }
	case 755: {return 755; }
	case 756: {return 756; }
	case 757: {return 757; }
	case 758: {return 758; }
	case 759: {return 759; }
	case 762: {return 762; }
	case 763: {return 763; }
	case 764: {return 764; }
	case 765: {return 765; }
	case 766: {return 766; }
	case 768: {return 768; }
	case 769: {return 769; }
	case 770: {return 770; }
	case 771: {return 771; }
	case 772: {return 772; }
	case 773: {return 773; }
	case 774: {return 774; }
	case 775: {return 775; }
	case 776: {return 776; }
	case 777: {return 777; }
	case 778: {return 778; }
	case 779: {return 779; }
	case 780: {return 780; }
	case 781: {return 781; }
	case 783: {return 783; }
	case 784: {return 784; }
	case 785: {return 785; }
	case 786: {return 786; }
	case 787: {return 787; }
	case 788: {return 788; }
	case 789: {return 789; }
	case 790: {return 790; }
	case 791: {return 791; }
	case 792: {return 792; }
	case 793: {return 793; }
	case 794: {return 794; }
	case 795: {return 795; }
	case 796: {return 796; }
	case 797: {return 797; }
	case 798: {return 798; }
	case 799: {return 799; }
	case 800: {return 800; }
	case 803: {return 803; }
	case 804: {return 804; }
	case 805: {return 805; }
	case 806: {return 806; }
	case 807: {return 807; }
	case 808: {return 808; }
	case 7555: {return 7555; }
	case 7556: {return 7556; }
	case 8362: {return 8362; }
	case 8363: {return 8363; }
	case 8364: {return 8364; }
	case 8365: {return 8365; }
	case 8366: {return 8366; }
	case 8367: {return 8367; }
	case 8368: {return 8368; }
	case 8369: {return 8369; }
	case 8370: {return 8370; }
	case 8371: {return 8371; }
	case 8625: {return 8625; }
	case 8626: {return 8626; }
	case 8627: {return 8627; }
	case 8628: {return 8628; }
	case 8629: {return 8629; }
	case 8630: {return 8630; }
	case 8631: {return 8631; }
	case 8632: {return 8632; }
	case 8633: {return 8633; }
	case 8634: {return 8634; }
	case 8635: {return 8635; }
	case 8636: {return 8636; }
	case 8637: {return 8637; }
	case 8638: {return 8638; }
	case 8639: {return 8639; }
	case 8640: {return 8640; }
	case 8643: {return 8643; }
	case 8644: {return 8644; }
	case 8645: {return 8645; }
	case 8646: {return 8646; }
	case 8647: {return 8647; }
	case 8648: {return 8648; }
	case 8649: {return 8649; }
	case 8650: {return 8650; }
	case 8651: {return 8651; }
	case 8652: {return 8652; }
	case 8653: {return 8653; }
	case 8654: {return 8654; }
	case 8655: {return 8655; }
	case 8656: {return 8656; }
	case 8657: {return 8657; }
	case 8658: {return 8658; }
	case 8659: {return 8659; }
	case 8660: {return 8660; }
	case 8661: {return 8661; }
	case 8662: {return 8662; }
	case 13043: {return 13043; }
	case 13044: {return 13044; }
	case 13045: {return 13045; }
	case 13046: {return 13046; }
	case 13047: {return 13047; }
	case 13049: {return 13049; }
	case 13078: {return 13078; }
	case 13784: {return 13784; }
	}
	return 0;
}

short inventory::GetActivitySequence(std::string_view activity, short currentSequence)
{
	auto modelSeqData = Dota::GetLocalHero()->GetModelData(Dota::GetLocalHero()->GetModelImp());
	if (modelSeqData) {
		for (int i = 0; i < modelSeqData->count; i++) {
			auto sequence = (DWORD*)((uintptr_t)modelSeqData->pSequences + i * 0x8);
			auto sequenceActivity = Dota::GetLocalHero()->GetSceneNode()->get_skeleton_instance()->GetActivityName(*sequence);
			if (currentSequence) {
				if (sequenceActivity == activity && *sequence != currentSequence) {
					return *sequence;
				}
			}
			else {
				if (sequenceActivity == activity) {
					return *sequence;
				}
			}
		}
	}

	return 0;
}

DWORD user::GetUserId()
{
	static int hSteamUser = ((int(__cdecl*)(void))GetProcAddress(GetModuleHandleA("steam_api64.dll"), "SteamAPI_GetHSteamUser"))();
	static int hSteamPipe = ((int(__cdecl*)(void))GetProcAddress(GetModuleHandleA("steam_api64.dll"), "SteamAPI_GetHSteamPipe"))();
	static auto SteamClient = ((ISteamClient * (__cdecl*)(void))GetProcAddress(GetModuleHandleA("steam_api64.dll"), "SteamClient"))();
	static auto g_vSteamUser = (ISteamUser*)SteamClient->GetISteamUser(hSteamUser, hSteamPipe, "SteamUser019");
	static auto id = g_vSteamUser->GetSteamID().GetAccountID();

	return id;
}

DWORD oldP;

std::string_view inventory::GetUnitModel(const std::string_view& unit)
{
	static auto kv = new KeyValues();
	for (auto i = kv->GetFirstTrueSubKey(*(void**)(global::g_kv.GetUnitsData())); i;
		i = kv->GetNextTrueSubKey(i)) {

		if (strstr(kv->GetName(i), unit.data())) {
			return kv->GetString(i, "Model");
		}
	}

	return "nullmodelname";
}

std::string_view inventory::GetWardModel(short defIndex)
{
	auto style = global::g_mapItemStyles[defIndex];

	static auto kv = new KeyValues();
	void* items = kv->FindKey(*(void**)(global::g_kv.GetItemsData()), "items", false);
	void* itemData = kv->FindKey(items, std::to_string(defIndex).c_str(), false);
	if (itemData) {

		auto visuals = kv->FindKey(itemData, "visuals", false);
		if (visuals) {
			for (auto kk = kv->GetFirstTrueSubKey(visuals); kk; kk = kv->GetNextTrueSubKey(kk)) {

				auto itemStyle = kv->GetInt(kk, "style");
				if (itemStyle == style) {

					auto itemModifier = kv->GetString(kk, "modifier");
					auto itemType = kv->GetString(kk, "type");

					if (itemModifier) {
						if (!strcmp(itemType, "entity_model")) {
							return itemModifier;
						}
					}
				}
			}
		}

	}
	return "";
}

std::string_view inventory::GetCourModel(short defIndex, bool isFlying)
{
	auto style = global::g_mapItemStyles[defIndex];

	static auto kv = new KeyValues();
	void* items = kv->FindKey(*(void**)(global::g_kv.GetItemsData()), "items", false);
	void* itemData = kv->FindKey(items, std::to_string(defIndex).c_str(), false);
	if (itemData) {

		auto visuals = kv->FindKey(itemData, "visuals", false);
		if (visuals) {
			for (auto kk = kv->GetFirstTrueSubKey(visuals); kk; kk = kv->GetNextTrueSubKey(kk)) {

				auto itemStyle = kv->GetInt(kk, "style");
				if (itemStyle == style) {

					auto itemModifier = kv->GetString(kk, "modifier");
					auto itemType = kv->GetString(kk, "type");

					if (itemModifier) {
						if (isFlying) {
							if (!strcmp(itemType, "courier_flying")) {
								return itemModifier;
							}
						}
						else {
							if (!strcmp(itemType, "courier")) {
								return itemModifier;
							}
						}
					}
				}
			}
		}

	}
	return "";
}

std::string_view inventory::GetEntityModel(const std::string_view& npc)
{
	static auto kv = new KeyValues();
	for (auto i = kv->GetFirstTrueSubKey(*(void**)(global::g_kv.GetHeroesData())); i;
		i = kv->GetNextTrueSubKey(i)) {

		if (strstr(kv->GetName(i), npc.data())) {
			return kv->GetString(i, "Model");
		}
	}

	return "nullmodelname";
}
static auto kv = new KeyValues();
void* inventory::GetItemDataByDefIndex(const short& def_index)
{
	void* items = kv->FindKey(*(void**)(global::g_kv.GetItemsData()), "items", false);
	if (items) {
		return kv->FindKey(items, std::to_string(def_index).c_str(), false);
	}

	return nullptr;
}

void* inventory::GetItemDataByDefIndex(void* item, const short& def_index)
{
	return kv->FindKey(item, std::to_string(def_index).c_str(), false);
}

void inventory::IterateItems(std::function<void(void*)> callBack)
{
	void* items = kv->FindKey(*(void**)(global::g_kv.GetItemsData()), "items", false);
	for (auto kk = kv->GetFirstTrueSubKey(items); kk; kk = kv->GetNextTrueSubKey(kk)) {
		callBack(kk);
	}
}

void inventory::IterateHeroesData(std::function<void(void*)> callBack)
{
	for (auto i = kv->GetFirstTrueSubKey(*(void**)(global::g_kv.GetHeroesData())); i;
		i = kv->GetNextTrueSubKey(i)) {

		callBack(i);
	}
}

void inventory::GetHeroDefaultItems(std::map<short, short>& list, std::map<short, short>& personList, const std::string_view& hero)
{
	inventory::IterateItems([&list, &hero, &personList](void* data) {
		auto usdbhero = kv->FindKey(data, "used_by_heroes", false);
		if (usdbhero && kv->GetInt(usdbhero, hero.data()))
			if (!strcmp(kv->GetString(data, "prefab"), "default_item")) {
				auto slot
					= Dota::GetEconItemSystem()->GetItemDefinitionMutable(std::stoi(kv->GetName(data)))->GetLoadoutSlot();
				auto defIndex
					= std::stoi(kv->GetName(data));

				auto itemSlotKv = kv->GetString(data, "item_slot");
				if (itemSlotKv) {
					if (strstr(itemSlotKv, "persona_1") || !strcmp(itemSlotKv, "shapeshift")) {
						personList[slot] = defIndex;
						return;
					}
				}

				list[slot] = defIndex;
			}
		});
}

std::string_view inventory::GetArcanaModelByDefIndex(const short& defIndex)
{
	switch (defIndex) {
	case 5957: {return "models/heroes/terrorblade/terrorblade_arcana.vmdl"; }
	case 6914: {return "models/heroes/zeus/zeus_arcana.vmdl"; }
	case 6996: {return "models/heroes/shadow_fiend/shadow_fiend_arcana.vmdl"; }
	case 7247: {return "models/heroes/phantom_assassin/pa_arcana.vmdl"; }
	case 7385: {return "models/heroes/crystal_maiden/crystal_maiden_arcana.vmdl"; }
	case 7756: {return "models/items/pudge/arcana/pudge_arcana_base.vmdl"; }
	case 9059: {return "models/heroes/juggernaut/juggernaut_arcana.vmdl"; }
	case 9662: {return "models/items/spectre/spectre_arcana/spectre_arcana_base.vmdl"; }
	case 12451: {return "models/items/rubick/rubick_arcana/rubick_arcana_base.vmdl"; }
	case 12692: {return "models/items/earthshaker/earthshaker_arcana/earthshaker_arcana.vmdl"; }
	case 12930: {return "models/items/queenofpain/queenofpain_arcana/queenofpain_arcana.vmdl"; }
	case 13456: {return "models/items/wraith_king/arcana/wraith_king_arcana.vmdl"; }
	case 13670: {return "models/items/ogre_magi/ogre_arcana/ogre_magi_arcana.vmdl"; }
	case 13806: {return "models/items/windrunner/windrunner_arcana/wr_arcana_base.vmdl"; }
	case 19090: {return "models/items/drow/drow_arcana/drow_arcana.vmdl"; }
	case 23095: {return "models/items/razor/razor_arcana/razor_arcana.vmdl"; }
	case 18033: {return "models/items/faceless_void/faceless_void_arcana/faceless_void_arcana_base.vmdl"; }
	}
	return "";
}
std::string_view inventory::GetPersonModelByDefIndex(const short& defIndex)
{
	switch (defIndex) {
	case 13042: {return "models/heroes/invoker_kid/invoker_kid.vmdl"; }
	case 13783: {return "models/heroes/antimage_female/antimage_female.vmdl"; }
	case 13786: {return "models/heroes/pudge_cute/pudge_cute.vmdl"; }
	case 18113: {return "models/heroes/dragon_knight_persona/dk_persona_base.vmdl"; }
	case 18178: {return "models/heroes/mirana_persona/mirana_persona_base.vmdl"; }
	case 19205: {return "models/heroes/crystal_maiden_persona/crystal_maiden_persona.vmdl"; }
	case 22723: {return "models/heroes/phantom_assassin_persona/phantom_assassin_persona.vmdl"; }
	}

	return "not_person_model";
}

void inventory::InitItemsForEquip()
{
	auto itemSchema = Dota::GetEconItemSystem();
	auto pushPersonDefs = [&](const short& slotItem, const short& defIndex, std::map<short, short> personItems) {
		auto slot = personItems.find(slotItem);
		if (slot != personItems.end()) {
			global::g_mapItemsHero[slot->first] = defIndex;
		}
	};

	auto localHero = Dota::GetLocalHero();
	auto heroName = localHero->GetNpcName();

	std::map<short, short> list;
	std::map<short, short> personList;
	inventory::GetHeroDefaultItems(list, personList, heroName);

	auto slotDef = global::g_mapSetItems.find(Dota::GetGameManager()->GetHeroIdByName(heroName.data()));
	if (slotDef != global::g_mapSetItems.end()) {
		// Тут мы пушим айтемы которые мы поставили в меню героя
		for (auto& a : slotDef->second) {
			if (!global::g_arcanaDefIndex) {
				global::g_arcanaDefIndex = inventory::IsArcana(a.second);
			}
			if (!global::g_personDefIndex) {
				global::g_personDefIndex = inventory::isPersona(a.second);
			}
			if (global::g_personDefIndex) {
				global::g_mapItemsHero = personList;
				global::g_mapItemsHero[a.first] = a.second;
				for (auto& a : slotDef->second) {
					pushPersonDefs(a.first, a.second, personList);
				}
				return;
			}
			global::g_shSomeDefIndex = a.second;
			global::g_mapItemsHero[a.first] = a.second;
		}

		// Тут мы пушим айтемы дефолтные которые мы не ставили в меню героя
		for (auto& obj : list) {
			auto defitemIT = slotDef->second.find(obj.first);
			if (defitemIT == slotDef->second.end()) {
				global::g_mapItemsHero[obj.first] = obj.second;
			}
		}
	}

}

void inventory::Patch()
{
	if (!remove_one_item || !remove_wearable_patch_address || !m_aplAssetModPatchOne) return;

	MEMORY_BASIC_INFORMATION meminf;

	VirtualQuery((LPVOID)remove_one_item, &meminf, sizeof(meminf));
	VirtualProtect((LPVOID)meminf.BaseAddress, meminf.RegionSize, PAGE_EXECUTE_READWRITE, &oldP);

	memcpy(m_remove_one_item, (void*)remove_one_item, 2);
	memset((void*)remove_one_item, 0x90, 2);


	VirtualQuery((LPVOID)remove_wearable_patch_address, &meminf, sizeof(meminf));
	VirtualProtect((LPVOID)meminf.BaseAddress, meminf.RegionSize, PAGE_EXECUTE_READWRITE, &oldP);
	//74 7F 8B 97 ? ? ? ? 83 FA FD 77 74 8B C2 25 ? ? ? ? 8B C8 48 C1 E9 09 44 8B C0 
	memcpy(m_removeWearablePatch, (void*)remove_wearable_patch_address, 6);
	memset((void*)remove_wearable_patch_address, 0x90, 6);


	VirtualQuery((LPVOID)o_assetModifier, &meminf, sizeof(meminf));
	VirtualProtect((LPVOID)meminf.BaseAddress, meminf.RegionSize, PAGE_EXECUTE_READWRITE, &oldP);

	memset((void*)o_assetModifier, 0x90, 6);

	VirtualQuery((LPVOID)(o_equipWearable), &meminf, sizeof(meminf));
	VirtualProtect((LPVOID)meminf.BaseAddress, meminf.RegionSize, PAGE_EXECUTE_READWRITE, &oldP);

	memcpy(m_equipWearablePatchOne, (void*)((uintptr_t)o_equipWearable + 0x2d), 6);
	memcpy(m_equipWearablePatchTwo, (void*)((uintptr_t)o_equipWearable + 0x1d), 6);

	memset((void*)((uintptr_t)o_equipWearable + 0x2d), 0x90, 6);
	memset((void*)((uintptr_t)o_equipWearable + 0x1d), 0x90, 6);

}

void inventory::UnPatch()
{
	if (!remove_one_item || !remove_wearable_patch_address || !m_aplAssetModPatchOne) return;

	MEMORY_BASIC_INFORMATION meminf;
	VirtualQuery((LPVOID)remove_one_item, &meminf, sizeof(meminf));

	memcpy((void*)remove_one_item, m_remove_one_item, 2);

	VirtualProtect((LPVOID)meminf.BaseAddress, meminf.RegionSize, oldP, &meminf.Protect);

	VirtualQuery((LPVOID)remove_wearable_patch_address, &meminf, sizeof(meminf));

	memcpy((void*)remove_wearable_patch_address, m_removeWearablePatch, 6);

	VirtualProtect((LPVOID)meminf.BaseAddress, meminf.RegionSize, oldP, &meminf.Protect);

	VirtualQuery((LPVOID)(o_equipWearable), &meminf, sizeof(meminf));

	memcpy((void*)((uintptr_t)o_equipWearable + 0x2d), m_equipWearablePatchOne, 6);
	memcpy((void*)((uintptr_t)o_equipWearable + 0x1d), m_equipWearablePatchTwo, 6);

	VirtualProtect((LPVOID)meminf.BaseAddress, meminf.RegionSize, oldP, &meminf.Protect);

	VirtualQuery((LPVOID)o_assetModifier, &meminf, sizeof(meminf));

	memcpy((void*)o_assetModifier, applyAssetModifierOirign, 6);

	VirtualProtect((LPVOID)meminf.BaseAddress, meminf.RegionSize, oldP, &meminf.Protect);
}
