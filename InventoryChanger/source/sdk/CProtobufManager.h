#pragma once
#include "../protobuf/dotaproto.pb.h"

#include <Windows.h>

class CProtobufManager
{
public:
	static void SendHello();
	static void WritePacket(std::string packet, void* thisPtr, void* oldEBP, void* pubDest, uint32_t cubDest, uint32_t* pcubMsgSize);
	static void AddItems(CMsgSOCacheSubscribed::SubscribedType& subtype);
	static void EquipItemInHeroSlot(const int& new_class, const int& new_slot, const short& def_index, const int& style);
	static void UnEquipItemInHeroSlot(const int& new_class, const int& new_slot, const short& def_index, const int& style);
};

