#include "CProtobufManager.h"

#include "../DGlobalValues.h"

#include "../../util/utils.h"

#define CAST(cast, address, add) reinterpret_cast<cast>((uintptr_t)address + (uintptr_t)add)

void CProtobufManager::SendHello()
{
	CMsgClientHello msg;

	msg.set_client_session_need(1);
	auto packet = msg.SerializeAsString();

	void* ptr = malloc(packet.size() + 8);
	((uint32_t*)ptr)[0] = 4006 | ((DWORD)1 << 31);
	((uint32_t*)ptr)[1] = 0;

	memcpy((void*)((uintptr_t)ptr + 8), (void*)packet.data(), packet.size());
	Dota::GetGameCoordinator()->GCSendMessage(4006 | ((DWORD)1 << 31), ptr, packet.size() + 8) == k_EGCResultOK;
	free(ptr);
}

void CProtobufManager::WritePacket(std::string packet, void* thisPtr, void* oldEBP, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize)
{
	if ((uint32_t)packet.size() <= cubDest - 8)
	{
		memcpy((void*)((uintptr_t)pubDest + 8), (void*)packet.data(), packet.size());
		*pcubMsgSize = packet.size() + 8;
	}
	else if (Dota::GetIMemAlloc())
	{
		DWORD Offset_1 = 0x20;
		DWORD Offset_1_1 = -0x30;
		DWORD Offset_2 = 0x20 + 0x8;

		auto memPtr = *CAST(void**, thisPtr, Offset_1);
		auto memPtrSize = *CAST(uint32_t*, thisPtr, Offset_2);
		auto newSize = (memPtrSize - cubDest) + packet.size() + 8;
		auto memory = Dota::GetIMemAlloc()->Realloc(memPtr, newSize + 8);

		*(void**)((DWORD64)thisPtr + Offset_1) = memory;
		*(uint32_t*)((DWORD64)thisPtr + Offset_2) = newSize;

		memcpy(CAST(void*, memory, 24), (void*)packet.data(), packet.size());
	}
}

void CProtobufManager::AddItems(CMsgSOCacheSubscribed::SubscribedType& subtype)
{
    DWORD id = user::GetUserId();
    CSOEconItem Skin;
    for (register int i = 0; i < 34463; i++) {
        if (!inventory::IsDefaultItem(i)) {
            Skin.set_id(i);
            Skin.set_account_id(id);
            Skin.set_def_index(i);
            Skin.set_inventory(i);
            Skin.set_origin(0);
            Skin.set_quantity(1);
            Skin.set_level(0);
            Skin.set_quality(5);
            Skin.set_quantity(2);
            Skin.set_style(0);
            Skin.set_flags(0);
            Skin.set_original_id(0);

            Skin.clear_equipped_state();

            Skin.clear_attribute();
            //auto EquipIT = g_vecEquippedItems.find(i);
            //if (EquipIT != g_vecEquippedItems.end()) {
            //    auto styleIT = g_mapDefIndexStyle.find(i);
            //    if (styleIT != g_mapDefIndexStyle.end()) {
            //        Skin.set_style(styleIT->second);
            //    }
            //    auto itemInfoPair = EquipIT->second;

            //    CSOEconItemEquipped* Equip = Skin.add_equipped_state();

            //    Equip->set_new_class(itemInfoPair.first);
            //    Equip->set_new_slot(itemInfoPair.second);
            //}
            subtype.add_object_data(std::move(Skin.SerializeAsString()));
        }
    }
}

void CProtobufManager::UnEquipItemInHeroSlot(const int& new_class, const int& new_slot, const short& def_index, const int& style)
{
    using fnupdatecache = void* (__fastcall*)(void*, CMsgSOMultipleObjects*);
    CMsgSOMultipleObjects* msgobj = new CMsgSOMultipleObjects();

    static auto UpdCache = (fnupdatecache)g_utils.GetPatternAddress("client.dll", "40 53 41 54 41 56 48 81 ec ? ? ? ? 48 8b 42");

    CSOEconItem Skin;

    Skin.set_id(def_index);
    Skin.set_account_id(user::GetUserId());
    Skin.set_def_index(def_index);
    Skin.set_inventory(def_index);
    Skin.set_origin(24);
    Skin.set_quantity(2);
    Skin.set_style(style);
    Skin.set_flags(0);
    Skin.set_original_id(0);

    auto objmod = msgobj->mutable_objects_modified()->Add();

    objmod->set_object_data(Skin.SerializeAsString());
    objmod->set_type_id(1);

    auto owner = msgobj->mutable_owner_soid();
    owner->set_type(1);
    owner->set_id(global::m_u64OwnerSOID);

#ifdef _DEBUG
    auto ptr = *(uintptr_t*)((uintptr_t)objmod + 0x18);
    *(uintptr_t*)(ptr) = *(uintptr_t*)(ptr + 0x8);

    *(uintptr_t*)(ptr + 0x10) = *(uintptr_t*)(ptr + 0x18);
    *(uintptr_t*)(ptr + 0x18) = *(uintptr_t*)(ptr + 0x20);
#endif // NDEBUG

    //logger::log("%p %p %p %p\n",gcclientptr, ptr, owner, Equip);
    UpdCache(Dota::GetCGCClient(), msgobj);
}

void CProtobufManager::EquipItemInHeroSlot(const int& new_class, const int& new_slot, const short& def_index, const int& style)
{
    using fnupdatecache = void* (__fastcall*)(void*, CMsgSOMultipleObjects*);
    CMsgSOMultipleObjects* msgobj = new CMsgSOMultipleObjects();

    static auto UpdCache = (fnupdatecache)g_utils.GetPatternAddress("client.dll", "40 53 41 54 41 56 48 81 ec ? ? ? ? 48 8b 42");

    CSOEconItem Skin;

    Skin.set_id(def_index);
    Skin.set_account_id(user::GetUserId());
    Skin.set_def_index(def_index);
    Skin.set_inventory(def_index);
    Skin.set_origin(24);
    Skin.set_quantity(2);
    Skin.set_style(style);
    Skin.set_flags(0);
    Skin.set_original_id(0);

    auto Equip = Skin.add_equipped_state();

    Equip->set_new_class(new_class);
    Equip->set_new_slot(new_slot);

    msgobj->set_service_id(1);

    auto objmod = msgobj->mutable_objects_modified()->Add();

    objmod->set_object_data(Skin.SerializeAsString());
    objmod->set_type_id(1);

    auto owner = msgobj->mutable_owner_soid();
    owner->set_type(1);
    owner->set_id(global::m_u64OwnerSOID);

#ifdef _DEBUG
    auto ptr = *(uintptr_t*)((uintptr_t)objmod + 0x18);
    *(uintptr_t*)(ptr + 8) = *(uintptr_t*)(ptr + 0x10);

    *(uintptr_t*)(ptr + 0x18) = *(uintptr_t*)(ptr + 0x20);
    *(uintptr_t*)(ptr + 0x20) = *(uintptr_t*)(ptr + 0x28);
#endif // NDEBUG

    //logger::log("%p %p %p %p\n",gcclientptr, ptr, owner, Equip);
    UpdCache(Dota::GetCGCClient(), msgobj);
}
