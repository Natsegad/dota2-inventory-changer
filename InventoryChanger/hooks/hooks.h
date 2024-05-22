#pragma once
#include <iostream>

#include "../util/MinHook/MinHook.h"
#include "../util/utils.h"

#include "../source/DGlobalValues.h"

#include "../source/dota_enums.h"

#define Hook(function, detour, original)                                       \
  if (MH_CreateHook((LPVOID)(function), detour, (LPVOID *)(&original)) !=      \
      MH_OK) {                                                                 \
    fmt::log("Hooks not install dw name = %s\n", #function);                                                                        \
  }\


bool hkIsStyleUnlocked(void*, void*);
inline decltype(&hkIsStyleUnlocked) oIsStyleUnlocked;

__int64 hkModelChange(__int64 a1, __int64 a2, __int64* a3);
inline decltype(&hkModelChange) oModelChange;

void hkSetParticleVisible(void*, int, int);
inline decltype(&hkSetParticleVisible) oSetParticleVisible;

__int64 hkStartSoundEvent(__int64 a1, __int64 a2, __int64 a3);
inline decltype(&hkStartSoundEvent) oStartSoundEvent;

void* hkFrameStage(void* rcx, ClientFrameStage_t state);
inline decltype(&hkFrameStage) oFrameStage;

int hkCreateEntity(void* rcx, void* entity, int id);
inline decltype(&hkCreateEntity) oCreateEntity;

int hkRemoveEntity(void* rcx, void* entity, int id);
inline decltype(&hkRemoveEntity) oRemoveEntity;

__int64 hkSetAbilityIcon(__int64 rcx, __int64 econ);
inline decltype(&hkSetAbilityIcon) oSetAbilityIcon;

bool hkGetParticleAttachment(__int64 a1, __int64 a2, __int64 a3);
inline decltype(&hkGetParticleAttachment) oGetParticleAttachment;

__int64 hkCreateAbilityIcon(void* rcx, void* rdx);
inline decltype(&hkCreateAbilityIcon) oCreateAbilityIcon;

void __fastcall hkAddInternal(__int64 rcx, const char* rdx);
inline decltype(&hkAddInternal) oAddInternal;

__int64 __fastcall hkGCRetrieveMessage(__int64 ecx, uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize);
inline decltype(&hkGCRetrieveMessage) ohkGCRetrieveMessage;

__int64 __fastcall hkGCSendMessage(__int64 ecx, uint32_t unMsgType, void* pubData, uint32_t cubData);
inline decltype(&hkGCSendMessage) ohkGCSendMessage;

void hkPreSetSequence(void* a1, DWORD* pHSequence, int a3, int a4);
inline decltype(&hkPreSetSequence) oPreSetSequence;

void hkDeallocateResource(void* pCResourceSystem, void* resource);
inline decltype(&hkDeallocateResource) oDeallocateResource;

void hkCycleReset(void*, void*, void*);
inline decltype(&hkCycleReset) oCycleReset;

void* hkGetResourceId(void*, const char*);
inline decltype(&hkGetResourceId) oGetResourceId;

void* hkSetSummonModel(void* rcx, __int64*, __int64*);
inline decltype(&hkSetSummonModel) oSetSummonModel;

void* hkGetResourcePtr(void* rcx, int count, void* r8);
inline decltype(&hkGetResourcePtr) oGetResourcePtr;

void* hkCreateParticle(void* thisptr, __int64* particleMgr, void* unk, void* query, bool bUnk, float fUnk, int particleIndex);
inline decltype(&hkCreateParticle) oCreateParticle;

void* hkPrecacheEntity(void*, void*);
inline decltype(&hkPrecacheEntity) oPrecacheEntity;

static void InitializeHooks() {
	MH_Initialize();

	// dance hook 48 89 5c 24 ? 48 89 6c 24 ? 48 89 7c 24 ? 41 56 48 83 ec ? 48 8b f9 48 8b da
	//Start End Game 48 83 ec ? 44 0f b6 ea   // rdx == 0 start game rdx == 1 end game

	uintptr_t dwPrecacheEntity = (uintptr_t)g_utils.GetPatternAddress("client.dll","40 56 48 83 EC 40 48 89 5C 24 ? 48 8B F2 48 89 7C 24 ? 48 8B F9 4C 89 74 24 ? 4C 89 7C 24 ? E8 ? ? ? ? ");
	Hook(dwPrecacheEntity, hkPrecacheEntity, oPrecacheEntity);

	//uintptr_t dwCreateManifest = (uintptr_t)g_utils.GetPatternAddress("resourcesystem.dll", "48 89 5c 24 ? 48 89 74 24 ? 55 57 41 55");
	//Hook(dwCreateManifest, hkGetResourcePtr, oGetResourcePtr);

	uintptr_t dwCreateParticle = (uintptr_t)g_utils.GetPatternAddress("particles.dll", "48 8B C4 48 89 58 10 4C 89 48 20 4C 89 40 18 55 56 57 41 54 41 55 41 56 41 57 48 8D 68 98 48 81 EC ? ? ? ? 45 33 F6 0F 29 70 B8 ");
	Hook(dwCreateParticle, hkCreateParticle, oCreateParticle);

	uintptr_t dwSetSummonModel = (uintptr_t)g_utils.GetPatternAddress("client.dll", "49 8b 00 48 3b 81 ? ? ? ? 75 ? 48 8b 81");
	Hook(dwSetSummonModel, hkSetSummonModel, oSetSummonModel);

	//uintptr_t dwDeallocateResource = (uintptr_t)g_utils.GetPatternAddress("resourcesystem.dll", "48 8b c4 48 89 58 ? 48 89 70");
	//Hook(dwDeallocateResource, hkDeallocateResource, oDeallocateResource);

	uintptr_t dwCycleReset = g_utils.GetAbsOrigin((uintptr_t)g_utils.GetPatternAddress("client.dll", "48 8D 05 ? ? ? ? 48 89 45 58 C6 44 24 ? ? 48 89 54 24 ? C7 44 24 ? ? ? ? ? C7 44 24 ? ? ? ? ? 48 89 4D 88 C6 45 A0 01 48 89 55 90 C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? "), 3, 7);
	Hook(dwCycleReset, hkCycleReset, oCycleReset);

	DWORD64 dwSetSeq = g_utils.GetAbsOrigin(
		(uintptr_t)g_utils.GetPatternAddress(
			"client.dll", "E8 ? ? ? ? 8B 5C 24 70 48 8B 4E 28 4C 8B 7C 24 ? EB 05 BB ? ? ? ?"),
		1, 5);
	Hook(dwSetSeq, hkPreSetSequence, oPreSetSequence);

	uintptr_t dwCreateEntity = (uintptr_t)g_utils.GetPatternAddress("client.dll", "48 89 5c 24 ? 56 48 83 ec ? 48 8b d9 41 8b c0");
	Hook(dwCreateEntity, hkCreateEntity, oCreateEntity);

	uintptr_t dwGetParticleAttachment = (uintptr_t)g_utils.GetPatternAddress("client.dll", "48 89 5C 24 ? 57 48 83 EC 20 41 0F B6 D8 48 8B FA 48 85 D2 74 42 48 8B CA E8 ? ? ? ? 48 85 C0 ");
	Hook(dwGetParticleAttachment, hkGetParticleAttachment, oGetParticleAttachment);

	uintptr_t dwCreateAbilityIcon = (uintptr_t)g_utils.GetPatternAddress("client.dll", "48 89 6c 24 ? 48 89 74 24 ? 57 48 83 ec ? 48 8b e9 48 8b f2 b9 ? ? ? ? e8 ? ? ? ? 48 8b f8 48 85 c0 0f 84 ? ? ? ? 48 85 f6 74 ? 4c 8b 06 48 8b ce 41 ff 50 ? eb ? 33 c0 4c 8b c5 48 8b d0 48 8b cf e8 ? ? ? ? 48 8d 05 ? ? ? ? c7 87 ? ? ? ? ? ? ? ? 48 89 07 48 8d 8f ? ? ? ? 48 8d 15 ? ? ? ? 48 c7 87 ? ? ? ? ? ? ? ? 48 c7 87 ? ? ? ? ? ? ? ? 48 c7 01");
	Hook(dwCreateAbilityIcon, hkCreateAbilityIcon, oCreateAbilityIcon);

	uintptr_t dwModelChange = (uintptr_t)g_utils.GetPatternAddress("client.dll", "49 8b 00 48 89 81 ? ? ? ? c6 81");
	Hook(dwModelChange, hkModelChange, oModelChange);

	uintptr_t dwStartSoundEvent = (uintptr_t)g_utils.GetPatternAddress(xorstr_("client.dll"), xorstr_("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 60 8B 42 10 0F 57 C0 C1 E8 04 48 8B DA F2 0F 11 44 24 ? "));
	Hook(dwStartSoundEvent, hkStartSoundEvent, oStartSoundEvent);

	uintptr_t dwFrameStage = (uintptr_t)g_utils.GetPatternAddress(xorstr_("client.dll"), xorstr_("48 89 5C 24 ? 56 48 83 EC 30 8B 05 ? ? ? ? 8D 5A FF 3B C2 48 8B F1 48 8B 0D ? ? ? ? 0F 45 C2 89 05 ? ? ? ? 48 8B 01 FF 90 ? ? ? ? 88 05 ? ? ? ? "));
	Hook(dwFrameStage, hkFrameStage, oFrameStage);

	uintptr_t dwSetParticleVisible = (uintptr_t)g_utils.GetPatternAddress("client.dll", "48 8b c4 55 57 41 55 48 8b ec 48 83 ec ? 44 0f b6 d2");
	Hook(dwSetParticleVisible, hkSetParticleVisible, oSetParticleVisible);

	uintptr_t dwAddInternal = (uintptr_t)g_utils.GetPatternAddress("engine2.dll", "48 83 ec ? 45 33 c9 48 c7 44 24 ? ? ? ? ? 45 33 c0 e8");
	Hook(dwAddInternal, hkAddInternal, oAddInternal);

	uintptr_t dwIsStyleUnlocked = (uintptr_t)g_utils.GetPatternAddress(xorstr_("client.dll"), xorstr_("48 89 5c 24 ? 56 48 83 ec ? 0f b6 da"));
	Hook(dwIsStyleUnlocked, hkIsStyleUnlocked, oIsStyleUnlocked);

	DWORD64 dwGCSendMessage = reinterpret_cast<DWORD64>(g_utils.GetPatternAddress(
		xorstr_("steamclient64.dll"), xorstr_("48 83 ec ? 48 8b 49 ? 44 89 4c 24 ? 4d 8b c8")));
	Hook(dwGCSendMessage, hkGCSendMessage, ohkGCSendMessage);

	DWORD64 dwGCRetrieveMessage = reinterpret_cast<DWORD64>(
		g_utils.GetPatternAddress(xorstr_("steamclient64.dll"),
			xorstr_("48 83 ec ? 48 8b 49 ? 48 8b 01 4c 8b 50 ? 48 8b 44 24 ? 48 89 44 24 ? 44 89 4c 24")));
	Hook(dwGCRetrieveMessage, hkGCRetrieveMessage, ohkGCRetrieveMessage);

	MH_EnableHook(MH_ALL_HOOKS);
}

static void Release() {
	while (MH_DisableHook(MH_ALL_HOOKS));
}