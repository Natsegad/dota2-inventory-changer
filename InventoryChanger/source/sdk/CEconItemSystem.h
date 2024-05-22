#pragma once
#include <Windows.h>

class CDOTAItemDefinition {
public:
	FORCEINLINE CDOTAItemDefinition(void* dotaItemDefPtr) :m_dotaItemDefinitionPtr(dotaItemDefPtr) {}

	int GetLoadoutSlot();
	int GetHeroID();

	uintptr_t get_asset_modifier_container();
private:
	void* m_dotaItemDefinitionPtr = nullptr;
};

class CEconItemSystem {
public:
	FORCEINLINE CEconItemSystem(void* dotaItemDefPtr) :m_econItemSystemPtr(dotaItemDefPtr) {}

	CDOTAItemDefinition* GetItemDefinitionMutable(__int16 a2);
	__int64 get_attribute_definition(int a1);

private:
	void* m_econItemSystemPtr = nullptr;
};