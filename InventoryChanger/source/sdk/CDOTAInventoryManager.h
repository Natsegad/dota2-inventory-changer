#pragma once
#include <Windows.h>

class CDOTAInventoryManager
{
public:
	void* GetPlayerInventory() {
		return (void*)((uintptr_t)this + 0x118);
	}

	void* GetSlotsForHero(int classId);
	void* GetItemInLoadoutSlot(int classId, int slot);
	void* GetSlotInfoByIndex(int slot);
	bool  IsEffectSlot(int classId,int slot);
};

