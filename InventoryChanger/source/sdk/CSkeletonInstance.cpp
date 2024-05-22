#include "CSkeletonInstance.h"

#include "../DGlobalValues.h"
#include "../Netvar.h"

#include "../../util/utils.h"

uintptr_t CSkeletonInstance::get_model_state() {
	if (!get_ptr()) { fmt::log("get_ptr() is null !\n"); return 0; }

	static DWORD m_modelState = Netvars::GetOffset("CSkeletonInstance", "m_modelState");

	return ((uintptr_t)get_ptr() + m_modelState);
}

std::string CSkeletonInstance::get_model_name()
{
	if (!get_ptr()) {
		return "";
	}

	auto modelState = this->get_model_state();
	if (!modelState) {
		return "";
	}

	if (!g_utils.IsReadWriteMem((void*)modelState)) return "null";
	if (!*(uintptr_t*)(modelState + 0xA8)) return "null";

	auto modelName = *(const char**)(modelState + 0xA8);
	if (!modelName) {
		return "";
	}

	if (!g_utils.IsReadWriteMem((void*)modelName)) return "null";

	return modelName;
}

uintptr_t CSkeletonInstance::get_c_model()
{
	if (!get_ptr()) {
		fmt::log("[get_c_model] get_ptr() is null !\n");
		return 0;
	}

	auto modelState = this->get_model_state();
	if (!modelState) {
		fmt::log("[get_c_model] modelState is null !\n");
		return 0;
	}

	if (!g_utils.IsReadWriteMem((void*)modelState)) return 0;

	//CheatAssertR( !*( int* )(modelState + 0xA8), 0, "[%s] modelName + 0xA8 is null !\n", __func__ );
	if (!*(uintptr_t*)(modelState + 0xA0)) return 0;

	auto modelPtr = (modelState + 0xA0);
	if (!modelPtr) {
		fmt::log("[get_c_model] modelPtr is null !\n");
		return 0;
	}

	return modelPtr;
}

void* CSkeletonInstance::CleanUpModel()
{
	if (!get_ptr()) {
		return nullptr;
	}
	using initCModelState_t = void* (__fastcall*)(void*);
	using cleanUpModel_t = void* (__fastcall*)(void*, void*, void*);

	static initCModelState_t initCModelState = (initCModelState_t)g_utils.GetPatternAddress("client.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 7C 24 ? 41 56 48 83 EC 20 48 8D 05 ? ? ? ? 48 8B F9 48 89 01 48 83 C1 10 E8 ? ? ? ? 48 8D 4F 40 E8 ? ? ? ? 33 ED 48 8D 9F ? ? ? ? ");
	static cleanUpModel_t cleanUpModel = (cleanUpModel_t)g_utils.GetPatternAddress("client.dll", "48 89 5c 24 ? 48 89 6c 24 ? 48 89 74 24 ? 57 48 83 ec ? 48 8b f2 48 8b d9 49 8d 50");
	if (!initCModelState || !cleanUpModel || !this->get_c_model()) {
		return nullptr;
	}

	auto result = Dota::GetIMemAlloc()->Alloc(600);
	initCModelState(result);
	return cleanUpModel((void*)get_model_state(), this, result);
}


std::string_view CSkeletonInstance::GetActivityName(const short& sequence)
{
	if (!get_ptr()) {
		return "";
	}

	using getActivityName_t = const char* (__fastcall*)(void*, short);
	static getActivityName_t getActivityName = (getActivityName_t)g_utils.GetPatternAddress("client.dll", "48 89 5c 24 ? 57 48 83 ec ? 8b da 48 8b f9 48 85 c9 74 ? e8 ? ? ? ? 48 8b cf");
	if (!getActivityName) {
		fmt::log("#GetActivityName Pattern not found ! \n");
		return "";
	}

	return getActivityName(Dota::GetLocalHero()->GetModelImp(), sequence);
}

std::string_view CSkeletonInstance::GetSequenceName(const short& sequence) {
	if (!this) {
		return "";
	}

	using getSequenceName_t = const char* (__fastcall*)(void*, short);
	static getSequenceName_t getSequenceName = (getSequenceName_t)g_utils.GetPatternAddress("client.dll", "48 89 5c 24 ? 57 48 83 ec ? 8b da 48 8b f9 48 85 c9 74 ? e8 ? ? ? ? 84 c0 74 ? 8b d3 48 8b cf e8 ? ? ? ? 48 8b c8 48 8b 10 48 8b 5c 24 ? 48 83 c4 ? 5f 48 ff 62");
	if (!getSequenceName) {
		return "";
	}

	return getSequenceName(Dota::GetLocalHero()->GetModelImp(), sequence);
}

void CSkeletonInstance::SetModel(void* ptr)
{
	if (!get_ptr() || !ptr) {
		return;
	}

	using hideWearable_t = void(__fastcall*)(uintptr_t, void*);
	static hideWearable_t hideWearable = (hideWearable_t)g_utils.GetPatternAddress("client.dll", "48 89 5c 24 ? 56 48 83 ec ? 4c 8b 12");
	if (!hideWearable) {
		return;
	}
	auto modelPtr = get_model_state();
	hideWearable(modelPtr, ptr);
}

void CSkeletonInstance::SetSkeletonMaterialGroup(int group)
{
	if (!get_ptr()) {
		return;
	}

	using setSkeletonMaterialGroup_t = void(__fastcall*)(void*, int);
	static setSkeletonMaterialGroup_t setSkeletonMaterialGroup = (setSkeletonMaterialGroup_t)g_utils.GetPatternAddress("client.dll", "39 91 ? ? ? ? 74 ? 89 91 ? ? ? ? 48 8b 81");
	if (!setSkeletonMaterialGroup) {
		return;
	}

	setSkeletonMaterialGroup(get_ptr(), group);
}

void CSkeletonInstance::SkeletonSetModel(void* ptr) {
	if (!get_ptr()) {
		return;
	}

	using setModel_t = void(__fastcall*)(void*, void*);
	static setModel_t setModel = (setModel_t)g_utils.GetPatternAddress("client.dll", "48 89 54 24 ? 55 53 56 57 41 54 41 56 41 57 48 8d ac 24 ? ? ? ? 48 81 ec ? ? ? ? 4c 8b e2");
	if (!setModel) {
		return;
	}

	setModel(get_ptr(), ptr);
}