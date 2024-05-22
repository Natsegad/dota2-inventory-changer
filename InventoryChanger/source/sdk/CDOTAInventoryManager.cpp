#include "CDOTAInventoryManager.h"
#include "../../util/utils.h"

void* CDOTAInventoryManager::GetSlotsForHero(int classId)
{
	if (!this) {
		return nullptr;
	}

	using getSlots_t = void* (__fastcall*)(void*, int);
	static getSlots_t getSlots = (getSlots_t)g_utils.GetPatternAddress("client.dll", "40 53 48 83 EC 20 48 8D 99 ? ? ? ? 48 8B CB E8 ? ? ? ? 83 F8 FF 75 08 33 C0 48 83 C4 20 5B C3 ");
	if (!getSlots) {
		return nullptr;
	}

	return getSlots(this, classId);
}

void* CDOTAInventoryManager::GetItemInLoadoutSlot(int classId, int slot)
{
	if (!this) {
		return nullptr;
	}

	using getItemInLoadoutSlot_t = void* (__fastcall*)(void*, int, int, int);
	static getItemInLoadoutSlot_t getItemInLoadoutSlot = (getItemInLoadoutSlot_t)g_utils.GetPatternAddress("client.dll", "89 54 24 10 55 56 57 48 83 EC 50 49 63 E8 41 0F B6 F1 48 8B F9 83 FD 1F 0F 87 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? ");
	if (!getItemInLoadoutSlot) {
		return nullptr;
	}

	return getItemInLoadoutSlot(GetPlayerInventory(),classId,slot,0);
}

bool CDOTAInventoryManager::IsEffectSlot(int classId, int iSlot)
{
	void* slotsInfo = GetSlotsForHero(classId);
	if (!slotsInfo) {
		return false;
	}

	auto slot = ((uintptr_t)slotsInfo + 0x38 * iSlot);
	if (*(uintptr_t*)slot) {

		auto loadOutSlot = *(const char**)slot;
		if (!strstr(loadOutSlot, "#")) {
			return true;
		}

	}


	return false;
}
