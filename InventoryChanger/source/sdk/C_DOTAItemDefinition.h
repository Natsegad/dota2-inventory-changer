#pragma once
#include <Windows.h>

class C_DOTAItemDefinition {
public:
	FORCEINLINE C_DOTAItemDefinition(void* dotaItemDefPtr) :m_dotaItemDefinitionPtr(dotaItemDefPtr) {}

	int get_loadout_slot();
	int get_hero_id();

	uintptr_t get_asset_modifier_container();
private:
	void* m_dotaItemDefinitionPtr = nullptr;
};

