#include "hooks.h"

#include "../source/protobuf/dotaproto.pb.h"

#include "../source/sdk/CProtobufManager.h"
#include "../source/DGlobalValues.h"

__int64 __fastcall hkGCRetrieveMessage(__int64 ecx, uint32_t* punMsgType, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize)
{
	__int64 result =
		ohkGCRetrieveMessage(ecx, punMsgType, pubDest, cubDest, pcubMsgSize);

	uint32_t MessageType = *punMsgType & 0x7FFFFFFF;

	if (MessageType == 24) {
		CMsgSOCacheSubscribed msg;
		std::string data;
		if (!msg.ParsePartialFromArray((void*)((uintptr_t)pubDest + 8),
			*pcubMsgSize - 8)) {
		}

		bool is = false;
		auto size = msg.objects_size();
		for (auto i = 0; i < size; i++) {
			auto obj = msg.objects(i);
			
			if (obj.type_id() == 1) {
				
				CProtobufManager::AddItems(obj);
				std::string data;
				data = obj.SerializeAsString();
				msg.add_objects()->ParseFromString(data);
				static auto thisPtr =
					Dota::GetCGCClient();
				if (!thisPtr) {
					fmt::log("GetCGCClient return nullptr ! \n");
					break;
				}

				fmt::log("WritePacket \n");

				CProtobufManager::WritePacket(msg.SerializeAsString(), thisPtr, 0, pubDest,
					cubDest, pcubMsgSize);
				global::m_u64OwnerSOID = msg.owner_soid().id();
				break;

			}
		}
	}

	return result;
}

__int64 __fastcall hkGCSendMessage(__int64 ecx, uint32_t unMsgType, void* pubData, uint32_t cubData)
{
	uint32_t messageType = unMsgType & 0x7FFFFFFF;
	switch (messageType) {
	case 2569: {
		CMsgClientToGCEquipItems ms;

		if (!ms.ParsePartialFromArray((void*)((uintptr_t)pubData + 8), cubData - 8)) {}
		static auto itemSchema = Dota::GetEconItemSystem();
		for (auto& a : ms.equips()) {

			CProtobufManager::EquipItemInHeroSlot(a.new_class(), a.new_slot(), a.item_id(), 0);
			
			auto isParticle = Dota::GetCDotaInventoryManager()->IsEffectSlot(a.new_class(),a.new_slot());
			auto itemSlot = itemSchema->GetItemDefinitionMutable(a.item_id())->GetLoadoutSlot();
			auto itemDef = a.item_id();

			if (isParticle) {
				global::g_mapSetReplaceItems[a.new_class()].insert(std::make_pair(itemDef, itemDef));
				break;
			}

			auto setItemsIT = global::g_mapSetItems.find(a.new_class());
			if (setItemsIT != global::g_mapSetItems.end()) {

				auto slotDefIT = setItemsIT->second.find(itemSlot);
				if (slotDefIT != setItemsIT->second.end()) {

					if (Engine::IsInGame()) {
						global::g_isHeroPick = false;
					}

					CProtobufManager::UnEquipItemInHeroSlot(a.new_class(), a.new_slot(), slotDefIT->second, 0);
					slotDefIT->second = itemDef;
					break;

				}
			}

			global::g_mapSetItems[a.new_class()].insert(std::make_pair(itemSlot, itemDef));
			global::g_mapItemSlot[a.item_id()] = a.new_slot();

			if (Engine::IsInGame()) {

				global::g_isHeroPick = false;

			}
		}
		break;
	}
	case 2577: {
		CMsgClientToGCSetItemStyle msg;
		if (!msg.ParsePartialFromArray((void*)((uintptr_t)pubData + 8), cubData - 8) && (!msg.has_item_id() || !msg.has_style_index())) {
			break;
		}

		global::g_mapItemStyles[msg.item_id()] = msg.style_index();

		auto it = global::g_mapSetItems.find(Dota::GetEconItemSystem()->GetItemDefinitionMutable(msg.item_id())->GetHeroID());
		if (it != global::g_mapSetItems.end()) {

			auto slotIt = it->second.find(Dota::GetEconItemSystem()->GetItemDefinitionMutable(msg.item_id())->GetLoadoutSlot());
			if (slotIt != it->second.end()) {

				if (Engine::IsInGame()) {
					global::g_isHeroPick = false;
				}
				CProtobufManager::EquipItemInHeroSlot(it->first, global::g_mapItemSlot[msg.item_id()], msg.item_id(), msg.style_index());

			}

		}
		break;
	}
	}
	return ohkGCSendMessage(
		ecx,
		unMsgType,
		pubData,
		cubData
	);
}