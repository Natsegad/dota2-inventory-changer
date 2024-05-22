#pragma once
#include <Windows.h>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include <functional>

#include "sdk/Steam.h"
#include "sdk/C_DOTA_BaseNpc.h"
#include "sdk/KeyValue.h"
#include "sdk//C_DotaPlayer.h"
#include "sdk/CSoundOpGameSystem.h"
#include "sdk/CDOTAInventoryManager.h"
#include "sdk/CEconItemSystem.h"
#include "sdk//CGameEntitySystem.h"
#include "sdk/CInputSystem.h"
#include "sdk/CGameManager.h"

#include "TypeScope.h"

#pragma pack(1)
typedef struct ItemData {
	int   slot;
	short defIndex;
}ITEMDATA;

typedef struct AssetModifierData {
	const char* modifier;
	int style;
};

#pragma pack(pop)

class KeyValueManager {
public:
	KeyValueManager() {
		KeyValues* m_kv = new KeyValues();
		m_loadTemporaryFile = m_kv->LoadTemporaryFromFile("scripts/items/items_game.txt", "MOD");
		m_loadUnitsKv = m_kv->LoadTemporaryFromFile("scripts/npc/npc_units.txt", "GAME");
		m_loadHeroesKv = m_kv->LoadTemporaryFromFile("scripts/npc/npc_heroes.txt", "GAME");
		delete m_kv;
	}

	void* GetItemsData() { return m_loadTemporaryFile; }
	void* GetHeroesData() { return m_loadHeroesKv; }
	void* GetUnitsData() { return m_loadUnitsKv; }
private:
	void* m_loadTemporaryFile;
	void* m_loadHeroesKv;
	void* m_loadUnitsKv;
};


class Dota {
public:
	static ISteamGameCoordinator* GetGameCoordinator();
	static ISteamClient* GetSteamClient();
	static IMemAlloc* GetIMemAlloc();
	static CInputSystem* GetCInputSystem();
	static C_DOTA_BaseNpc* GetLocalHero();
	static CShemaSystem* GetSchemaSystem();
	static CEconItemSystem* GetEconItemSystem();
	static GameManager* GetGameManager();
	static std::unique_ptr< C_DotaPlayer> GetPlayer();
	static CDOTAInventoryManager* GetCDotaInventoryManager();
	static CSoundOpGameSystem* GetSoundOpSystem();
	static std::vector<void*> GetMyAbility();

	static void IterateEntityes(std::function<void(void*)> callBack);

	static void SetAbilityIcon(void* ability, const char* icon);

	static CGameEntitySystem* GetCGameEntitySystem() {
		static auto pCGameEntitySysytem = *(uintptr_t*)g_utils.GetAbsOrigin((uintptr_t)g_utils.GetPatternAddress("client.dll", "48 8B 0D ? ? ? ? E8 ? ? ? ? 48 85 C0 74 2F 33 C9 45 33 C9 88 4C 24 40 4C 8B C0 48 89 4C 24 ? 33 D2 C7 44 24 ? ? ? ? ? "), 3, 7);
		return (CGameEntitySystem*)pCGameEntitySysytem;
	}
	static void* GetCGCClient();
	static void* GetEntityByChandle(const DWORD& chanle);
	static void* GetEntityByIndex(const DWORD& index);
	static void* GetResourcePtr();
	static void* GetParticleMgr();
private:
};

class Engine {
public:
	static bool IsInGame();
};

class KeyValueResource {
public:
	std::string_view m_svKey;
	std::string_view m_svValue;

	void* m_pOldKey;
	void* m_pOldValue;

	void* m_pNewKey;
	void* m_pNewValue;
};

namespace global {
	extern uint64_t m_u64OwnerSOID;
	extern KeyValueManager g_kv;

	// Для фиксов
	extern std::map<std::string_view, std::vector<const char*>> g_mapHeroAssetModifiers;

	extern std::vector<void*> g_vecAbilityIcons;
	extern std::vector<void*> g_vecMyWearables;
	extern std::vector<std::string_view> g_vecBaseAttacks;
	extern std::set<void*> g_vecMyReplicates;
	extern std::map<short, short> g_mapItemStyles;
	extern std::map<short, short> g_mapItemSlot;
	extern std::map<short, short> g_mapAnimating;
	extern std::map<std::string_view, std::string_view> g_mapReplaceParticles;
	extern std::map<std::string_view, std::string_view> g_mapModelParticles;

	extern std::map<short, std::map<short, short>> g_mapSetItems;
	extern std::map<short, std::map<short, short>> g_mapSetReplaceItems;
	extern std::map<short, short> g_mapItemsHero;
	extern std::set<short> g_setReplaceItemsHero;
	extern std::map<std::string, std::map<std::string, AssetModifierData>> g_mapModifierTypeAsset;

	extern short g_personDefIndex;
	extern short g_arcanaDefIndex;
	extern short g_shSomeDefIndex;
	extern short g_shCourierDefIndex;
	extern short g_shWardDefIndex;
	extern short g_shReplaceParticlesItemDefIndex;

	extern bool g_isHideParticle;
	extern bool g_isModelChange;
	extern bool g_isInGame;
	extern bool g_isIllusionSpawn;
	extern bool g_isHeroPick;
	extern bool g_isLoadParticle;
}