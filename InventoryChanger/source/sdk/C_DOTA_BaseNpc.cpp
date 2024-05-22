#include "C_DOTA_BaseNpc.h"

#include "../DGlobalValues.h"
#include "../Netvar.h"

#include "../../util/utils.h"

#include "C_DOTAWearableItem.h"
#include "CAttributeContainer.h"

void* C_DOTA_BaseNpc::GetHeroModelPtr()
{
	if (!get_ptr()) {
		return nullptr;
	}

	return (void*)((uintptr_t)get_ptr() + 0x14b8);
}

std::unique_ptr<CGameSceneNode> C_DOTA_BaseNpc::GetSceneNode()
{
	if (!get_ptr()) {
		return std::make_unique<CGameSceneNode>(0);
	}
	static auto gameScnedeNodeOffset = Netvars::GetOffset("C_BaseEntity", "m_pGameSceneNode");
	auto entPtr = reinterpret_cast<uintptr_t>(this->get_ptr());

	return std::make_unique<CGameSceneNode>(*reinterpret_cast<uintptr_t*>(entPtr + gameScnedeNodeOffset));
}

C_BodyComponentBaseAnimatingOverlay* C_DOTA_BaseNpc::GetBodyComponent()
{
	if (!this->get_ptr()) {
		//g_pDebugManager->SetErrorOrWarning(ErrorWarning_t::WARN_LOW, "C_BodyComponentBaseAnimatingOverlay* C_BaseEntity::get_body_component() entityptr is null !");
		return nullptr;
	}

	static DWORD bodyComponent = Netvars::GetOffset("C_BaseEntity", "m_CBodyComponent");
	auto pBodyComponent = *(uintptr_t*)((uintptr_t)get_ptr() + bodyComponent);
	if (!pBodyComponent) {
		return nullptr;
	}

	return (C_BodyComponentBaseAnimatingOverlay*)pBodyComponent;
}

std::string_view C_DOTA_BaseNpc::GetHeroModel()
{
	if (!get_ptr()) {
		return "..";
	}

	if (global::g_arcanaDefIndex) {
		return inventory::GetArcanaModelByDefIndex(global::g_arcanaDefIndex);
	}
	else if (global::g_personDefIndex) {
		return inventory::GetPersonModelByDefIndex(global::g_personDefIndex);
	}
	else {
		return inventory::GetEntityModel(GetNpcName());
	}

	return "...";
}

std::string_view C_DOTA_BaseNpc::GetDefaultModel()
{
	return inventory::GetEntityModel(GetNpcName());
}

std::string_view C_DOTA_BaseNpc::GetNpcName()
{
	if (!get_ptr()) {
		return "_not_hero_name_";
	}

	uintptr_t* pEntity = get_m_pEntity();
	if (pEntity) {
		const char** szRet = reinterpret_cast<const char**>((DWORD64)pEntity + 0x20);
		return (szRet && *szRet) ? *szRet : "_not_hero_name_";
	}

	return "_not_hero_name_";
}

std::vector<short> C_DOTA_BaseNpc::GetDefaultItems()
{
	return std::vector<short>();
}

DWORD C_DOTA_BaseNpc::GetOwnerChandle()
{
	if (!get_ptr()) { fmt::log("get_ptr() is return null ! \n"); return 0; }

	static DWORD cHandleOffset = Netvars::GetOffset("C_BaseEntity", "m_hOwnerEntity");
	if (cHandleOffset == 3)
		return 0;

	return *(DWORD*)((uintptr_t)get_ptr() + cHandleOffset);
}

void C_DOTA_BaseNpc::EquipItem(void* itemPtr)
{
	if (!get_ptr()) {
		return;
	}

	using equipItemFunctionTemplate = void(__fastcall*)(void*, void*);
	static equipItemFunctionTemplate equipItem = (equipItemFunctionTemplate)g_utils.GetPatternAddress("client.dll", "48 85 D2 0F 84 ?? ?? ?? ?? 57 41 56 48 83 EC ?? 4C 8B F2");
	if (!equipItem) {
		return;
	}

	equipItem(get_ptr(), itemPtr);
}

//ё мае пиздец!
void* C_DOTA_BaseNpc::GenerateWearableByDefIndex(short defIndex)
{
	CHECK_PTR_R_P;

	using generateWearableByDefIndexTemplate = void* (__fastcall*)(void* a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, unsigned int a7);
	static generateWearableByDefIndexTemplate generateWearableByDefIndex = (generateWearableByDefIndexTemplate)g_utils.GetPatternAddress("client.dll", "40 55 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 4D 8B F9 4D 8B F0 48 8B FA 48 85 D2 0F 84 ? ? ? ? 48 8B CA E8 ? ? ? ? 48 85 C0 0F 84 ? ? ? ? ");
	if (!generateWearableByDefIndex) {
		fmt::log("#GenerateWearableByDefIndex pattern not found \n");
		return nullptr;
	}

	auto econitem = CAttributeContainer::create_atrribute_container()->get_item();
	if (!econitem)
		return nullptr;

	econitem->set_ovverideStyle(255);
	auto itemStyleIT = global::g_mapItemStyles.find(defIndex);
	if (itemStyleIT != global::g_mapItemStyles.end()) {
		econitem->set_ovverideStyle(itemStyleIT->second);
	}

	econitem->set_entityQuality(1);
	econitem->set_client_glag(0);
	econitem->set_def_index(defIndex);
	econitem->set_attach_particles_has(true);
	econitem->set_initialized(true);

	auto m_vecAbsOrigin = GetSceneNode()->get_vec_abs_origin();//Vector
	auto m_vecAbsRotation = GetSceneNode()->get_ang_abs_rotation();//QAngle

	return generateWearableByDefIndex(get_ptr(), (__int64)econitem, m_vecAbsOrigin, m_vecAbsRotation, 0, 0, 0);
}

void* C_DOTA_BaseNpc::GetModelImp()
{
	if (!get_ptr()) {
		return nullptr;
	}

	using getModelImp_t = void* (__fastcall*)(void*);
	static getModelImp_t getModelImp = (getModelImp_t)g_utils.GetPatternAddress("client.dll", "48 83 ec ? 48 8b 41 ? 4c 8b 00 4d 85 c0 74 ? 48 8b 40 ? 48 63 15 ? ? ? ? 48 8b 48 ? 0f b7 04 51 b9 ? ? ? ? 66 3b c1 74 ? 4a 8b 0c 00 eb");
	if (!getModelImp) {
		return nullptr;
	}

	return getModelImp(get_ptr());
}

ModelSequences* C_DOTA_BaseNpc::GetModelData(void* modelImp)
{
	if (!get_ptr() || !modelImp) {
		return nullptr;
	}

	using fn = ModelSequences * (__fastcall*)(void*);

	static auto o_fn = (fn)g_utils.GetPatternAddress("client.dll", "40 57 48 83 EC 30 48 8B 81 ?? ?? ?? ?? 48 8B F9 48 85 C0 75 6B 8D 48 38");
	if (!o_fn) {
		return nullptr;
	}

	return (o_fn) ? o_fn(modelImp) : 0;
}

void C_DOTA_BaseNpc::OnWearableSpawn(void* spawnedItem)
{
	CHECK_PTR

		if (spawnedItem)                      // begin inline
		{
			using eqpItem_t = void(__fastcall*)(void*, void*);
			static auto eqpItem = (eqpItem_t)g_utils.GetAbsOrigin((uintptr_t)
				g_utils.GetPatternAddress("client.dll", "48 85 D2 74 4E 57 48 83 EC 20 48 8B 02 48 8B F9 48 8B CA 48 89 5C 24 ? FF 90 ? ? ? ? ") + 0x44, 1, 5);
			eqpItem(get_ptr(), spawnedItem);
		}
}

void C_DOTA_BaseNpc::UpdateClientSideWearables()
{
	CHECK_PTR

		using updClientSideWearables_t = void(__fastcall*)(void*);
	static auto updClientSideWearables = (updClientSideWearables_t)g_utils.GetPatternAddress("client.dll", "48 89 4C 24 ? 55 41 54 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 01 4C 8B E1 80 A1 ? ? ? ? ? FF 90 ? ? ? ? 49 8B 04 24 49 8B CC FF 90 ? ? ? ?");
	if (!updClientSideWearables) {
		fmt::log("#updClientSideWearables not found ! \n");
		return;
	}

	updClientSideWearables(get_ptr());
}

void C_DOTA_BaseNpc::ApplyWearableModifiers()
{
	CHECK_PTR;
	//4c 8b dc 55 41 57 49 8d 6b ? 48 81 ec ? ? ? ? 48 8b 05     41 55 48 83 ec ? 4c 8b e9 e8 ? ? ? ? 84 c0 
	using applyWearableModifiers_t = void(__fastcall*)(void*);
	static auto applyWearableModifiers = (applyWearableModifiers_t)g_utils.GetPatternAddress("client.dll", "40 55 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 41 10 4C 8B F9 48 8D 4D 67 8B 50 38 E8 ? ? ? ? 8B 45 67 41 39 87 ? ? ? ? 0F 84 ? ? ? ? 49 8B 47 10 ");
	if (!applyWearableModifiers) {
		fmt::log("#applyWearableModifiers not found ! \n");
		return;
	}

	applyWearableModifiers(get_ptr());
}

void C_DOTA_BaseNpc::ApplyAssetModifiers()
{
	if (!get_ptr()) {
		return;
	}

	using apllyAssetModifier_t = void(__fastcall*)(void*);
	static apllyAssetModifier_t apllyAssetModifier = (apllyAssetModifier_t)g_utils.GetPatternAddress("client.dll", "41 55 48 83 EC 70 4C 8B E9 E8 ? ? ? ? 84 C0");
	if (!apllyAssetModifier) {
		fmt::log("#ApplyAssetModifiers error get pattern !\n");
		return;
	}

	apllyAssetModifier(get_ptr());
}

void C_DOTA_BaseNpc::SetForceDisableParticles(const bool& value)
{
	if (!get_ptr()) {
		return;
	}

	using setForceDisableParticles_t = void(__fastcall*)(void*, bool);
	static setForceDisableParticles_t setForceDisableParticles = (setForceDisableParticles_t)g_utils.GetPatternAddress("client.dll", "48 89 6c 24 ? 48 89 74 24 ? 57 48 83 ec ? 48 63 b9 ? ? ? ? 8b ea");
	if (!setForceDisableParticles) {
		return;
	}

	setForceDisableParticles(get_ptr(), value);
}

void C_DOTA_BaseNpc::SetRenderEnable(const bool& value)
{
	CHECK_PTR;

	using setRenderEnable_t = void(__fastcall*)(void*, bool);
	static auto setRenderEnable = (setRenderEnable_t)g_utils.GetPatternAddress("client.dll", "40 53 48 83 EC 20 0F B6 41 60 48 8B D9 3A C2 0F 84 ? ? ? ?");
	if (!setRenderEnable) {
		return;
	}

	setRenderEnable(get_ptr(), value);
}

void C_DOTA_BaseNpc::SetModel(const char* model)
{
	if (!get_ptr()) {
		return;
	}

	using setModel_t = void(__fastcall*)(void*, const char*);
	static setModel_t setModel = (setModel_t)g_utils.GetPatternAddress("client.dll", "48 89 5c 24 ? 48 89 7c 24 ? 55 48 8b ec 48 83 ec ? 48 8b f9 4c 8b c2");
	if (!setModel) {
		return;
	}

	setModel(get_ptr(), model);
}

void C_DOTA_BaseNpc::RemoveWearables()
{
	if (!get_ptr()) {
		return;
	}

	using removeWearables_t = void(__fastcall*)(void*);
	static removeWearables_t removeWearable = (removeWearables_t)((uintptr_t)g_utils.GetPatternAddress("client.dll", "75 54 48 8B 38 48 85 FF 74 4C 48 8B CF E8 ? ? ? ? 48 8B 07 48 8B D3 48 8B CF FF 90 ? ? ? ? E8 ? ? ? ? ") - 0x98);
	if (!removeWearable) {
		return;
	}

	removeWearable(get_ptr());
}

void C_DOTA_BaseNpc::RemoveWearable(void* item)
{
	if (!get_ptr()) {
		return;
	}

	using removeWearable_t = void(__fastcall*)(void*, void*);
	static removeWearable_t removeWearable = (removeWearable_t)g_utils.GetPatternAddress("client.dll", "48 89 5c 24 ? 57 48 83 ec ? 48 8b f9 e8 ? ? ? ? 48 8b cf e8 ? ? ? ? 84 c0");
	if (!removeWearable) {
		fmt::log("#RemoveWearable pattern not found ! \n");
		return;
	}

	removeWearable(item, get_ptr());
}

void C_DOTA_BaseNpc::GetWearables(std::vector<void*>& list)
{
	if (!get_ptr()) {
		return;
	}

	static auto offsetWearableSize = Netvars::GetOffset("C_BaseCombatCharacter", "m_hMyWearables");
	if (offsetWearableSize == 3) {
		return;
	}
	auto myWearablessize = *(int*)((uintptr_t)get_ptr() + offsetWearableSize);
	auto myWearables = *(uintptr_t*)((uintptr_t)get_ptr() + offsetWearableSize + 0x8);

	if (myWearablessize == 0) {
		return;
	}

	list.reserve(myWearablessize);

	for (int i = 0; i < myWearablessize; i++) {
		auto wearableCHandle = *(DWORD*)(myWearables + i * 0x4);
		auto entity = Dota::GetEntityByChandle(wearableCHandle);
		if (entity) {
			list.push_back(entity);
		}
	}
}

bool C_DOTA_BaseNpc::IsMoving()
{
	if (!get_ptr()) {
		return false;
	}
	static DWORD isMovingOffset = Netvars::GetOffset("C_DOTA_BaseNPC", "m_bIsMoving");

	return *(bool*)((uintptr_t)get_ptr() + isMovingOffset);
}

bool C_DOTA_BaseNpc::IsIllusion() {
	if (!get_ptr()) {
		return false;
	}
	using isIllusion_t = bool(__fastcall*)(void*);
	static isIllusion_t isIllusion = (isIllusion_t)(*(uintptr_t*)(*(uintptr_t*)(this) + 2840));
	if (!isIllusion) {
		return false;
	}

	return isIllusion(this);
}

void C_DOTA_BaseNpc::SetEntityModel(void* entity)
{
	if (!entity) {
		return;
	}
	auto npc = (C_DOTA_BaseNpc*)(entity);

	auto heroName = npc->GetNpcName();
	auto heroModel = inventory::GetEntityModel(heroName);
	if (heroModel.empty()) {
		return;
	}

	if (global::g_arcanaDefIndex) {
		npc->SetModel(inventory::GetArcanaModelByDefIndex(global::g_arcanaDefIndex).data());
	}
	else if (global::g_personDefIndex) {
		npc->SetModel(inventory::GetPersonModelByDefIndex(global::g_personDefIndex).data());
	}
	else {
		npc->SetModel(heroModel.data());
	}
}

void C_DOTA_BaseNpc::LoadItems(void* entity)
{
	if (!entity) {
		return;
	}
	auto npc = (C_DOTA_BaseNpc*)(entity);

	std::vector<void*> list;
	npc->GetWearables(list);

	inventory::Patch();

	for (auto& a : list) {
		auto i = (C_DOTAWearableItem*)(a);
		i->GetRenderComponent()->SetRenderEnable(false);
	
	}
	npc->RemoveWearables();

	for (auto& def : global::g_mapItemsHero) {
		auto item = npc->GenerateWearableByDefIndex(def.second);
		if (item) {
			auto wearable = (C_DOTAWearableItem*)(item);
			wearable->GetRenderComponent()->SetRenderEnable(true);
			npc->OnWearableSpawn(item);
			global::g_shSomeDefIndex = def.second;
		}
	}

	npc->ApplyWearableModifiers();
	npc->UpdateClientSideWearables();
	inventory::UnPatch();
}

void C_DOTA_BaseNpc::EquipItems()
{
	global::g_vecMyWearables.clear();
	for (auto& def : global::g_mapItemsHero) {
		auto item = this->GenerateWearableByDefIndex(def.second);
		if (item) {
			global::g_vecMyWearables.push_back(item);
			auto wearable = (C_DOTAWearableItem*)(item);
			wearable->GetRenderComponent()->SetRenderEnable(true);
			this->OnWearableSpawn(item);
		}
	}
}

int C_DOTA_BaseNpc::GetLevel()
{
	if (!get_ptr()) {
		return 0;
	}

	static DWORD levelOffset = Netvars::GetOffset("C_DOTA_BaseNPC", "m_iCurrentLevel");
	return *(int*)((uintptr_t)get_ptr() + levelOffset);
}

void C_DOTA_BaseNpc::LoadItems(bool i)
{
	auto localHero = Dota::GetLocalHero();
	if (!localHero->get_ptr()) {
		return;
	}

	inventory::Patch();

	Dota::GetLocalHero()->RemoveWearables();

	localHero->EquipItems();

	localHero->ApplyWearableModifiers();
	localHero->UpdateClientSideWearables();
	inventory::UnPatch();
}

void C_DOTA_BaseNpc::SetHeroModel()
{
	auto localHero = Dota::GetLocalHero();
	if (!localHero->get_ptr()) {
		return;
	}

	auto heroName = localHero->GetNpcName();
	auto heroModel = inventory::GetEntityModel(heroName);
	if (heroModel.empty()) {
		return;
	}

	if (global::g_arcanaDefIndex) {
		localHero->SetModel(inventory::GetArcanaModelByDefIndex(global::g_arcanaDefIndex).data());
	}
	else if (global::g_personDefIndex) {
		localHero->SetModel(inventory::GetPersonModelByDefIndex(global::g_personDefIndex).data());
	}
	else {
		localHero->SetModel(heroModel.data());
	}
}

void C_DOTA_BaseNpc::IllusionSetter() {
	auto myHero = Dota::GetLocalHero();
	auto myHeroCopy = (C_DOTA_BaseNpc*)(Dota::GetCGameEntitySystem()->GetEntityByClassName(0, myHero->GetNpcName().data()));

	while (myHeroCopy) {

		if (myHero->get_ptr() != myHeroCopy->get_ptr()) {
			if (myHeroCopy->IsIllusion() || myHero->GetNpcName() == "npc_dota_hero_monkey_king") {

				bool found = false;

				vector<void*> wearables;
				myHeroCopy->GetWearables(wearables);
				for (auto& a : wearables) {

					auto wearable = (C_DOTAWearableItem*)(a);
					if (global::g_personDefIndex) {
						if (wearable->GetItemDefIndex() == global::g_personDefIndex) {
							found = true;
							break;
						}
					}
					else if (wearable->GetItemDefIndex() == global::g_shSomeDefIndex) {
						found = true;
						break;
					}

				}

				if (!found) {

					C_DOTA_BaseNpc::SetEntityModel(myHeroCopy);
					C_DOTA_BaseNpc::LoadItems(myHeroCopy);

				}
			}
		}
		myHeroCopy = (C_DOTA_BaseNpc*)(Dota::GetCGameEntitySystem()->GetEntityByClassName(myHeroCopy, myHero->GetNpcName().data()));

	}
}

void C_DOTA_BaseNpc::CourierWearablesSpawn(C_DOTA_BaseNpc* myCourier)
{
	using courierParticleSet_t = void(__fastcall*)(void*);
	if (!myCourier) {
		return;
	}

	inventory::Patch();

	auto courier = global::g_mapSetItems.find(1000);
	if (courier != global::g_mapSetItems.end()) {
		global::g_shCourierDefIndex = courier->second.at(67);

		myCourier->SetModel(inventory::GetCourModel(courier->second.at(67), false).data());

		auto item = (C_DOTAWearableItem*)(myCourier->GenerateWearableByDefIndex(courier->second.at(67)));
		if (item) {
			*(BYTE*)(item + 2793) = 1;

			*(BYTE*)(item + 2794) = 1;

			myCourier->OnWearableSpawn(item);
		}
	}
	myCourier->ApplyWearableModifiers();
	inventory::UnPatch();
}

void C_DOTA_BaseNpc::WardWearablesSpawn(C_DOTA_BaseNpc* ward)
{
	using courierParticleSet_t = void(__fastcall*)(void*);
	if (!ward) {
		return;
	}

	inventory::Patch();
	ward->RemoveWearables();
	auto courier = global::g_mapSetItems.find(1000);
	if (courier != global::g_mapSetItems.end()) {
		global::g_shWardDefIndex = courier->second.at(71);

		ward->SetModel(inventory::GetWardModel(courier->second.at(71)).data());

		auto item = (C_DOTAWearableItem*)(ward->GenerateWearableByDefIndex(courier->second.at(71)));
		if (item) {

			*(BYTE*)(item + 2793) = 1;

			*(BYTE*)(item + 2794) = 1;

			ward->OnWearableSpawn(item);
		}
	}
	ward->ApplyWearableModifiers();
	inventory::UnPatch();
}

void C_DOTA_BaseNpc::ModelReset()
{
	for (auto& a : global::g_vecMyWearables) {
		auto item = (C_DOTAWearableItem*)(a);
		item->GetRenderComponent()->SetRenderEnable(false);
	}
	SetHeroModel();
	C_DOTA_BaseNpc::LoadItems();
	//switch (global::g_personDefIndex) {
	//case 18178: {
	//	C_DOTA_BaseNpc::LoadItems(true);
	//	break;
	//}
	//case 22723: {
	//	C_DOTA_BaseNpc::LoadItems(true);
	//	break;
	//}
	//case 18113: {
	//	C_DOTA_BaseNpc::LoadItems(true);
	//	break;
	//}
	//}
}

void C_DOTA_BaseNpc::HideWearable()
{
	for (auto& a : global::g_vecMyWearables) {
		auto item = (C_DOTAWearableItem*)(a);
		item->GetRenderComponent()->SetRenderEnable(false);
	}
}
