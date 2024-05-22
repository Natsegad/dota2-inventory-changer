#pragma once
#include <Windows.h>
#include <utility>

#include "../../util/utils.h"

#include "../DGlobalValues.h"

class Item {
public:
	uintptr_t get_def_index(void) {
		return m_def_index;
	}
	uintptr_t get_item_id() {
		return m_itemId;
	}
	int get_entityQuality() {
		return m_entityQuality;
	}
	int get_entityLevel() {
		return m_entityLevel;
	}
	int get_account_id() {
		return m_accountId;
	}
	int get_invPos() {
		return m_invPos;
	}
	bool get_initialized() {
		return m_initialized;
	}
	signed char get_ovverideStyle() {
		return m_ovverideStyle;
	}
	bool is_store_item() {
		return m_isStoreItem;
	}
	bool is_trade_item() {
		return m_isTradeItem;
	}

	void set_vtable(void* vtable) {
		m_vtable = vtable;
	}
	void set_def_index(const uintptr_t& defindex) {
		m_def_index = defindex;
	}
	void set_item_id(const uintptr_t& itemid) {
		m_itemId = itemid;
	}
	void set_entityQuality(const int& entityquality) {
		m_entityQuality = entityquality;
	}
	void set_entityLevel(const int& entitylevel) {
		m_entityLevel = entitylevel;
	}
	void set_account_id(const int& accountid) {
		m_accountId = accountid;
	}
	void set_invPos(const int& invpos) {
		m_invPos = invpos;
	}
	void set_initialized(const bool& initialized) {
		m_initialized = initialized;
	}
	void set_attach_particles_has(const bool& atach_particles_has) {
		m_hasComputedAttachedParticles = atach_particles_has;
	}
	void set_ovverideStyle(const signed char& ovveidestyle) {
		m_ovverideStyle = ovveidestyle;
	}
	void set_store_item(const bool& isstoreitem) {
		m_isStoreItem = isstoreitem;
	}
	void set_trade_item(const bool& istardeitem) {
		m_isTradeItem = istardeitem;
	}
	void set_client_glag(const int& flag) {
		m_ClientFlags = flag;
	}
	//uintptr_t get_def_index()
	//{
	//	return m_def_index;
	//}
	//void set_class(long long a)
	//{
	//	m_class = a;
	//}
	//void set_def_index(uintptr_t a)
	//{
	//	this->m_def_index = a;
	//}
	//void set(void* a)
	//{
	//	this->m_vtable = a;
	//}
private:
	void* m_vtable; //0x0000
	short m_def_index; //0x0008
	short N00000056; //0x000A
	int m_entityQuality; //0x000C
	int m_entityLevel; //0x0010
	int N00000004; //0x0014
	uintptr_t m_itemId; //0x0018
	int m_accountId; //0x0020
	int m_invPos; //0x0024
	char pad_0028[8]; //0x0028
	bool m_initialized; //0x0030
	signed char m_ovverideStyle; //0x0031
	bool m_isStoreItem; //0x0032
	bool m_isTradeItem; //0x0033
	bool m_hasComputedAttachedParticles; //0x0034
	bool m_hasAttachedParticles; //0x0035
	char pad_0036[2]; //0x0036
	int m_entityQuantity; //0x0038
	int m_ClientFlags; //0x003C

	/*void* m_vtable;
	uintptr_t m_def_index;
	char m_bool;
	char pad_0010[31];
	long long m_class;*/
};

class CAttributeContainer {
private:
	void* m_ptr;
public:
	CAttributeContainer(void* ptr) :m_ptr(ptr) {

	}

	Item* get_item() {
		if (!this->m_ptr) return nullptr;

		return (Item*)(reinterpret_cast<uintptr_t>(m_ptr) + 0x68);
	}

	static CAttributeContainer* create_atrribute_container() {
		using fn = void* (__fastcall*)(void* alloc);

		static auto create_wearable_item = reinterpret_cast<fn>(g_utils.GetPatternAddress("client.dll", "48 89 5C 24 ? 57 48 83 EC 20 33 C0 48 8B F9 48 89 41 10 48 89 41 18 89 41 08 48 89 41 28 48 89 41 30 89 41 20 89 41 38 "));
		if (!create_wearable_item) return nullptr;

		auto alloc = Dota::GetIMemAlloc()->Alloc(3408i64);

		return new CAttributeContainer(create_wearable_item(alloc));
	}
};