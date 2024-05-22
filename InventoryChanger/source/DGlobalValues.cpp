#include "DGlobalValues.h"
#include "../util/utils.h"

uint64_t global::m_u64OwnerSOID = 0;
KeyValueManager global::g_kv;

std::map<short, std::map<short, short>> global::g_mapSetItems;
std::map<short, std::map<short, short>> global::g_mapSetReplaceItems;
std::map<short, short> global::g_mapItemsHero;
std::set<short> global::g_setReplaceItemsHero;
std::map<short, short> global::g_mapItemStyles;
std::map<short, short> global::g_mapItemSlot;
std::map<short, short> global::g_mapAnimating;

std::map<std::string_view, std::vector<const char*>> global::g_mapHeroAssetModifiers;
std::map<std::string_view, std::string_view> global::g_mapReplaceParticles;
std::map<std::string, std::map<std::string, AssetModifierData>> global::g_mapModifierTypeAsset;

std::map<std::string_view, std::string_view> global::g_mapModelParticles;
std::vector<std::string_view> global::g_vecBaseAttacks = {
	"particles/units/heroes/hero_windrunner/windrunner_base_attack.vpcf",
	"particles/units/heroes/hero_windrunner/windrunner_focusfire_attack.vpcf",
	"particles/units/heroes/hero_drow/drow_base_attack.vpcf",
	"particles/units/heroes/hero_keeper_of_the_light/keeper_of_the_light_base_attack.vpcf",
	"particles/units/heroes/hero_queenofpain/queen_base_attack.vpcf",
	"particles/units/heroes/hero_zuus/zuus_base_attack.vpcf",
	"particles/units/heroes/hero_luna/luna_base_attack.vpcf",
	"particles/units/heroes/hero_nevermore/nevermore_base_attack.vpcf",
	"particles/econ/items/shadow_fiend/sf_desolation/sf_base_attack_desolation.vpcf",
	"particles/units/heroes/hero_razor/razor_base_attack.vpcf",
	"particles/units/heroes/hero_mirana/mirana_base_attack.vpcf",
	"particles/econ/items/razor/razor_arcana/razor_arcana_base_attack_impact.vpcf",
	"particles/units/heroes/hero_invoker_kid/invoker_kid_base_attack_all.vpcf"
};

std::vector<void*> global::g_vecAbilityIcons;
std::vector<void*> global::g_vecMyWearables;
std::set<void*> global::g_vecMyReplicates;

bool  global::g_isHideParticle = false;
bool  global::g_isInGame = false;
bool  global::g_isHeroPick = false;
bool  global::g_isModelChange = false;
bool  global::g_isIllusionSpawn = false;
bool  global::g_isLoadParticle = false;

short global::g_arcanaDefIndex;
short global::g_personDefIndex;
short global::g_shSomeDefIndex;
short global::g_shCourierDefIndex;
short global::g_shWardDefIndex;
short global::g_shReplaceParticlesItemDefIndex;

CSoundOpGameSystem* Dota::GetSoundOpSystem() {
	static auto sound = *(uintptr_t*)g_utils.GetAbsOrigin((uintptr_t)g_utils.GetPatternAddress("client.dll",
		"48 8B 0D ? ? ? ? 41 8B D4 48 83 C1 08 48 8B 01 FF 50 10 48 8B F0 48 85 C0 0F 84 ? ? ? ? "), 3, 7);

	return (CSoundOpGameSystem*)(sound + 8);
}

std::vector<void*> Dota::GetMyAbility()
{
	std::vector<void*> ret;

	for (auto& a : global::g_vecAbilityIcons) {
		auto entity = GetEntityByChandle(*(DWORD*)((uintptr_t)a + 0xe0));
		if (entity) {
			auto abilityOwner = GetEntityByChandle(*(DWORD*)((uintptr_t)entity + 0x43c));
			if (abilityOwner && abilityOwner == GetLocalHero()->get_ptr()) {
				ret.push_back(a);
			}
		}
	}

	return ret;
}

void Dota::IterateEntityes(std::function<void(void*)> callBack)
{
	for (size_t i = 0; i < MAXSHORT; i++) {
		auto identity = Dota::GetEntityByIndex(i);
		if(identity)
			callBack(identity);
	}
}

void Dota::SetAbilityIcon(void* ability, const char* icon)
{
	using SetAbilityIcon_t = void(__fastcall*)(void*, const char*);
	static SetAbilityIcon_t oSetAbilityIcon = (SetAbilityIcon_t)(g_utils.GetPatternAddress("client.dll", "48 89 5c 24 ? 48 89 74 24 ? 48 89 7c 24 ? 55 41 56 41 57 48 8d ac 24 ? ? ? ? 48 81 ec ? ? ? ? 48 8b 05"));
	if (!oSetAbilityIcon) {
		return;
	}
	oSetAbilityIcon(ability, icon);
}

ISteamGameCoordinator* Dota::GetGameCoordinator()
{
	return (ISteamGameCoordinator*)GetSteamClient()->GetISteamGenericInterface(1, 1, "SteamGameCoordinator001");;
}

ISteamClient* Dota::GetSteamClient()
{
	return ((ISteamClient * (__cdecl*)(void))GetProcAddress(GetModuleHandleA("steam_api64.dll"), "SteamClient"))();;
}

IMemAlloc* Dota::GetIMemAlloc()
{
	return *(IMemAlloc**)GetProcAddress(GetModuleHandleW(L"tier0.dll"), "g_pMemAlloc");
}

CInputSystem* Dota::GetCInputSystem()
{
	static auto cInputSystem = g_utils.GetAbsOrigin((uintptr_t)g_utils.GetPatternAddress("inputsystem.dll","4C 8D 15 ? ? ? ? 43 8B 8C 2A ? ? ? ? 8B C1 89 8C 24 ? ? ? ? 43 3B 8C 2A ? ? ? ? 0F 85 ? ? ? ? 43 F7 84 2A ? ? ? ? ? ? ? ? "),3,7);
	if (!cInputSystem) {
		return nullptr;
	}

	return (CInputSystem*)(cInputSystem);
}

// Реализацию потом поменять обязательно
C_DOTA_BaseNpc* Dota::GetLocalHero()
{
	using fn = void* (__fastcall*)();
	static auto getLocalHeroByPlayerId = (fn)g_utils.GetPatternAddress(
		"client.dll",
		"48 89 5c 24 ? 57 48 83 ec ? 33 ff 8b cf e8 ? ? ? ? 48 8b d8 48 85 c0 74 ? 48 8b 10 48 8b c8 ff 92 ? ? ? ? 84 c0 74 ? 48 8b cb");

	if (getLocalHeroByPlayerId != NULL) {
		auto retHero = getLocalHeroByPlayerId();
		if (retHero != nullptr)
			return (C_DOTA_BaseNpc*)(retHero);
	}

	return nullptr;
}

CShemaSystem* Dota::GetSchemaSystem()
{
	return (CShemaSystem*)(g_utils.GetAbsOrigin((uintptr_t)g_utils.GetPatternAddress("schemasystem.dll", "48 8B 05 ? ? ? ? 48 8D 0D ? ? ? ? FF 90 ? ? ? ? 4C 8B 05 ? ? ? ? 48 8D 0D ? ? ? ? 48 8B 56 20 48 8B D8 41 FF 90 ? ? ? ? 48 8D 4F 10"), 3, 7));;
}

CEconItemSystem* Dota::GetEconItemSystem()
{
	using getItemSystem_t = uintptr_t(__fastcall*)();
	static getItemSystem_t getItemSystem = (getItemSystem_t)g_utils.GetAbsOrigin((uintptr_t)g_utils.GetPatternAddress("client.dll", "E8 ? ? ? ? 4C 8B 35 ? ? ? ? 48 8B E8 8B FB 39 98 ? ? ? ? 7E 48 48 8B F3 "), 1, 5);

	static auto m_CEconItemSystem = new CEconItemSystem((void*)(getItemSystem() + 8));
	return m_CEconItemSystem;
}

GameManager* Dota::GetGameManager()
{
	static auto gm = new GameManager();
	return gm;
}

std::unique_ptr< C_DotaPlayer> Dota::GetPlayer()
{
	using getLocalPlayer_t = void* (__fastcall*)(int);
	static getLocalPlayer_t getLocalPlayer = (getLocalPlayer_t)g_utils.GetPatternAddress("client.dll", "33 c0 83 f9 ? 0f 44 c8");

	return std::make_unique<C_DotaPlayer>(getLocalPlayer(0));
}

CDOTAInventoryManager* Dota::GetCDotaInventoryManager()
{
	//48 8B 1D ? ? ? ? FF 90 ? ? ? ? 8B D0 48 8D 0D ? ? ? ? FF 93 ? ? ? ? 8B D0 48 8D 0D ? ? ? ? E8 ? ? ? ? 
	static auto pCDotaInvManager = g_utils.GetAbsOrigin(
		(uintptr_t)g_utils.GetPatternAddress("client.dll", "48 8B 1D ? ? ? ? FF 90 ? ? ? ? 8B D0 48 8D 0D ? ? ? ? FF 93 ? ? ? ? 8B D0 48 8D 0D ? ? ? ? E8 ? ? ? ?"),
		3, 7);

	return (CDOTAInventoryManager*)pCDotaInvManager;
}

void* Dota::GetCGCClient()
{
	using getcgcclient_t = void* (__fastcall*)();
	static getcgcclient_t getCgcClient = (getcgcclient_t)g_utils.GetAbsOrigin((uintptr_t)g_utils.GetPatternAddress("client.dll",
		"E8 ? ? ? ? 48 8B CE 48 8B F8 48 8D 50 38 E8 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 BE ? ? ? ? 48 8B 7C 24 ? 48 89 06 48 8D 05 ? ? ? ? C7 86 ? ? ? ? ? ? ? ? 48 89 9E ? ? ? ? 48 89 46 48 EB 02 "), 1, 5);
	if (!getCgcClient) {
		return nullptr;
	}

	return getCgcClient();
}

void* Dota::GetEntityByChandle(const DWORD& chandle)
{
	return GetEntityByIndex(chandle & MAXSHORT);
}

void* Dota::GetEntityByIndex(const DWORD& index)
{
	__int64 v3, v2, result;
	auto static asd = (uintptr_t)GetCGameEntitySystem();
	if ((unsigned int)index <= 0x7FFE
		&& (unsigned int)(index >> 9) <= 0x3F
		&& (v2 = *(__int64*)(asd + 8i64 * (index >> 9) + 16)) != 0
		&& (v3 = 120i64 * (index & 0x1FF), v3 + v2)
		&& (*(__int64*)(v3 + v2 + 16) & 0x7FFF) == index)
	{
		result = *(__int64*)(v3 + v2);
	}
	else
	{
		result = 0i64;
	}
	return (void*)result;
}

void* Dota::GetResourcePtr()
{
	static auto pResource = g_utils.GetAbsOrigin(
		(uintptr_t)g_utils.GetPatternAddress("host.dll","48 8b 35 ? ? ? ? 74"),
		3, 7);
	if (!pResource) {
		return nullptr;
	}

	return (void*)(*(uintptr_t*)pResource);
}

void* Dota::GetParticleMgr()
{
	static auto pResource = g_utils.GetAbsOrigin(
		(uintptr_t)g_utils.GetPatternAddress("particles.dll", "48 8D 0D ? ? ? ? E8 ? ? ? ? 4C 8D 05 ? ? ? ? BA ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 4C 8D 05 ? ? ? ? BA ? ? ? ? 48 8D 0D ? ? ? ?"),
		3, 7);
	if (!pResource) {
		return nullptr;
	}

	return (void*)(pResource);
}

bool Engine::IsInGame()
{
	using isInGame_t = bool(__fastcall*)();

	static auto isInGame = (isInGame_t)g_utils.GetPatternAddress("engine2.dll", "48 8b 0d ? ? ? ? 48 85 c9 74 ? 48 8b 01 48 ff a0 ? ? ? ? 32 c0 c3 cc cc cc cc cc cc cc 48 8b 0d ? ? ? ? 48 85 c9 74 ? 48 8b 01 48 ff 60");

	return (isInGame) ? isInGame() : false;
}
