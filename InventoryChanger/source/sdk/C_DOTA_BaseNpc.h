#pragma once
#include <memory>
#include <vector>
#include <string_view>

#include "C_BaseEntity.h"
#include "CSkeletonInstance.h"
#include "CGameSceneNode.h"
#include "C_BodyComponentBaseAnimatingOverlay.h"

#include "../../defs/defs.h"

#include <future>

class ModelSequences {
public:
	void* pSequences;
	int count;

	DWORD GetCurrentSequence() {
		auto sequenceData = *(uintptr_t*)(this + 0x18);
		if (sequenceData) {
			return *(DWORD*)(sequenceData);
		}
	}
	void SetCurrentSequence(int hSequence) {
		auto sequenceData = *(uintptr_t*)(this + 0x18);
		if (sequenceData) {
			*(DWORD*)(sequenceData) = hSequence;
		}
	}
};

class C_DOTA_BaseNpc :
	public C_BaseEntity
{
public:
	uintptr_t*& get_m_pEntity() { return *(uintptr_t**)((uintptr_t)get_ptr() + 0x10); }

	void* GetHeroModelPtr();
	void* GenerateWearableByDefIndex(short defIndex);
	void* GetModelImp();
	ModelSequences* GetModelData(void* modelImp);

	std::unique_ptr<CGameSceneNode> GetSceneNode();

	C_BodyComponentBaseAnimatingOverlay* GetBodyComponent();

	std::string_view GetHeroModel();
	std::string_view GetDefaultModel();
	std::string_view GetNpcName();

	std::vector<short> GetDefaultItems();

	DWORD GetOwnerChandle();

	void EquipItem(void* itemPtr);
	void OnWearableSpawn(void* spawnedItem);
	void UpdateClientSideWearables();
	void ApplyWearableModifiers();
	void ApplyAssetModifiers();
	void SetForceDisableParticles(const bool& value);
	void SetRenderEnable(const bool& value);
	void SetModel(const char* model);
	void RemoveWearables();
	void RemoveWearable(void* item);
	void GetWearables(std::vector<void*>& list);
	void EquipItems();

	int GetLevel();

	bool IsMoving();
	bool IsIllusion();

	static void SetEntityModel(void* entity);
	static void LoadItems(void* entity);

	// только на локального героя
	static void LoadItems(bool i = false);
	static void SetHeroModel();
	static void ModelReset();
	static void HideWearable();
	static void IllusionSetter();

	static void CourierWearablesSpawn(C_DOTA_BaseNpc* myCourier);
	static void WardWearablesSpawn(C_DOTA_BaseNpc* myCourier);
};

