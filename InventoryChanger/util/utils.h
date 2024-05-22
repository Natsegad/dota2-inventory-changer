#pragma once
#include <cstdint>
#include <Windows.h>
#include <string_view>
#include <map>
#include <functional>

#include "xor.h"

template <typename T>
class InterfaceA {
public:
    typedef void* (*CreateInterfaceFn)(const char*, int*);

    static T* Get(const std::string& dllName, const std::string& fullName) {
        static T* interfacePtr = nullptr;

        if (interfacePtr) {
            return interfacePtr;
        }

        HMODULE dll = nullptr;

        do {
            dll = GetModuleHandleA(dllName.c_str());
        } while (!dll);

        auto factory = (CreateInterfaceFn)GetProcAddress(dll, "CreateInterface");

        interfacePtr = (T*)(factory(fullName.c_str(), nullptr));
        return interfacePtr;
    }
};

class ResourceData {
public:
	void* m_pParticleData;
	void* m_pParticleName;
};

class ResourcePtr {
public:
	ResourceData* m_pResData;
};

namespace fmt {
	void log(const char* _f, ...);
};

namespace inventory {
	ResourceData* GetResourcePtr(const char* model);
	void* GetParticlePtr(const char* particle);
	void* GetResourcePtrHost(const char* resource);


	void* GetResourceId(const char* resourceName);
	void* GetParticleResourceId(const char* resourceName);

	bool IsHaveFixResource(std::string_view resource);
	bool IsHaveThisItem(void* ent,short defIndex);
	short IsDefaultItem(short defIndex);

	short GetActivitySequence(std::string_view activity,short currentS);

	void CreateResourceManifest();
	void LoadEquipsItems();
	void LoadAssetModifirs();
	void FixResources();
	void SpawnItems();
	void AnimatingUpdate();
	void Courier();
	void Wards();

	std::string_view GetEntityModel(const std::string_view& npc);
	std::string_view GetUnitModel(const std::string_view& unit);
	std::string_view GetCourModel(short defIndex,bool isFlying);
	std::string_view GetWardModel(short defIndex);

	void* GetItemDataByDefIndex(const short& def_index);
	void* GetItemDataByDefIndex(void* item,const short& def_index);
	void IterateItems(std::function<void(void*)> callBack);
	void IterateHeroesData(std::function<void(void*)> callBack);
	void GetHeroDefaultItems(std::map<short, short>& list, std::map<short, short>& personList,const std::string_view& hero);

	constexpr std::string_view GetModelByHeroID(const BYTE id) {
		switch (id) {
		case 1: {return "models/heroes/antimage/antimage.vmdl"; }
		case 2: {return "models/heroes/axe/axe.vmdl"; }
		case 3: {return "models/heroes/bane/bane.vmdl"; }
		case 4: {return "models/heroes/blood_seeker/blood_seeker.vmdl"; }
		case 5: {return "models/heroes/crystal_maiden/crystal_maiden.vmdl"; }
		case 6: {return "models/heroes/drow/drow_base.vmdl"; }
		case 7: {return "models/heroes/earthshaker/earthshaker.vmdl"; }
		case 8: {return "models/heroes/juggernaut/juggernaut.vmdl"; }
		case 9: {return "models/heroes/mirana/mirana.vmdl"; }
		case 11: {return "models/heroes/shadow_fiend/shadow_fiend.vmdl"; }
		case 10: {return "models/heroes/morphling/morphling.vmdl"; }
		case 12: {return "models/heroes/phantom_lancer/phantom_lancer.vmdl"; }
		case 13: {return "models/heroes/puck/puck.vmdl"; }
		case 14: {return "models/heroes/pudge/pudge.vmdl"; }
		case 15: {return "models/heroes/razor/razor.vmdl"; }
		case 16: {return "models/heroes/sand_king/sand_king.vmdl"; }
		case 17: {return "models/heroes/storm_spirit/storm_spirit.vmdl"; }
		case 18: {return "models/heroes/sven/sven.vmdl"; }
		case 19: {return "models/heroes/tiny/tiny_01/tiny_01.vmdl"; }
		case 20: {return "models/heroes/vengeful/vengeful.vmdl"; }
		case 21: {return "models/heroes/windrunner/windrunner.vmdl"; }
		case 22: {return "models/heroes/zeus/zeus.vmdl"; }
		case 23: {return "models/heroes/kunkka/kunkka.vmdl"; }
		case 25: {return "models/heroes/lina/lina.vmdl"; }
		case 31: {return "models/heroes/lich/lich.vmdl"; }
		case 26: {return "models/heroes/lion/lion.vmdl"; }
		case 27: {return "models/heroes/shadowshaman/shadowshaman.vmdl"; }
		case 28: {return "models/heroes/slardar/slardar.vmdl"; }
		case 29: {return "models/heroes/tidehunter/tidehunter.vmdl"; }
		case 30: {return "models/heroes/witchdoctor/witchdoctor.vmdl"; }
		case 32: {return "models/heroes/rikimaru/rikimaru.vmdl"; }
		case 33: {return "models/heroes/enigma/enigma.vmdl"; }
		case 34: {return "models/heroes/tinker/tinker.vmdl"; }
		case 35: {return "models/heroes/sniper/sniper.vmdl"; }
		case 36: {return "models/heroes/necrolyte/necrolyte.vmdl"; }
		case 37: {return "models/heroes/warlock/warlock.vmdl"; }
		case 38: {return "models/heroes/beastmaster/beastmaster.vmdl"; }
		case 39: {return "models/heroes/queenofpain/queenofpain.vmdl"; }
		case 40: {return "models/heroes/venomancer/venomancer.vmdl"; }
		case 41: {return "models/heroes/faceless_void/faceless_void.vmdl"; }
		case 42: {return "models/heroes/wraith_king/wraith_king.vmdl"; }
		case 43: {return "models/heroes/death_prophet/death_prophet.vmdl"; }
		case 44: {return "models/heroes/phantom_assassin/phantom_assassin.vmdl"; }
		case 45: {return "models/heroes/pugna/pugna.vmdl"; }
		case 46: {return "models/heroes/lanaya/lanaya.vmdl"; }
		case 47: {return "models/heroes/viper/viper.vmdl"; }
		case 48: {return "models/heroes/luna/luna.vmdl"; }
		case 49: {return "models/heroes/dragon_knight/dragon_knight.vmdl"; }
		case 50: {return "models/heroes/dazzle/dazzle.vmdl"; }
		case 51: {return "models/heroes/rattletrap/rattletrap.vmdl"; }
		case 52: {return "models/heroes/leshrac/leshrac.vmdl"; }
		case 53: {return "models/heroes/furion/furion.vmdl"; }
		case 54: {return "models/heroes/life_stealer/life_stealer.vmdl"; }
		case 55: {return "models/heroes/dark_seer/dark_seer.vmdl"; }
		case 56: {return "models/heroes/clinkz/clinkz.vmdl"; }
		case 57: {return "models/heroes/omniknight/omniknight.vmdl"; }
		case 58: {return "models/heroes/enchantress/enchantress.vmdl"; }
		case 59: {return "models/heroes/huskar/huskar.vmdl"; }
		case 60: {return "models/heroes/nightstalker/nightstalker.vmdl"; }
		case 61: {return "models/heroes/broodmother/broodmother.vmdl"; }
		case 62: {return "models/heroes/bounty_hunter/bounty_hunter.vmdl"; }
		case 63: {return "models/heroes/weaver/weaver.vmdl"; }
		case 64: {return "models/heroes/jakiro/jakiro.vmdl"; }
		case 65: {return "models/heroes/batrider/batrider.vmdl"; }
		case 66: {return "models/heroes/chen/chen.vmdl"; }
		case 67: {return "models/heroes/spectre/spectre.vmdl"; }
		case 69: {return "models/heroes/doom/doom.vmdl"; }
		case 68: {return "models/heroes/ancient_apparition/ancient_apparition.vmdl"; }
		case 70: {return "models/heroes/ursa/ursa.vmdl"; }
		case 71: {return "models/heroes/spirit_breaker/spirit_breaker.vmdl"; }
		case 72: {return "models/heroes/gyro/gyro.vmdl"; }
		case 73: {return "models/heroes/alchemist/alchemist.vmdl"; }
		case 74: {return "models/heroes/invoker/invoker.vmdl"; }
		case 75: {return "models/heroes/silencer/silencer.vmdl"; }
		case 76: {return "models/heroes/obsidian_destroyer/obsidian_destroyer.vmdl"; }
		case 77: {return "models/heroes/lycan/lycan.vmdl"; }
		case 78: {return "models/heroes/brewmaster/brewmaster.vmdl"; }
		case 79: {return "models/heroes/shadow_demon/shadow_demon.vmdl"; }
		case 80: {return "models/heroes/lone_druid/lone_druid.vmdl"; }
		case 81: {return "models/heroes/chaos_knight/chaos_knight.vmdl"; }
		case 82: {return "models/heroes/meepo/meepo.vmdl"; }
		case 83: {return "models/heroes/treant_protector/treant_protector.vmdl"; }
		case 84: {return "models/heroes/ogre_magi/ogre_magi.vmdl"; }
		case 85: {return "models/heroes/undying/undying.vmdl"; }
		case 86: {return "models/heroes/rubick/rubick.vmdl"; }
		case 87: {return "models/heroes/disruptor/disruptor.vmdl"; }
		case 88: {return "models/heroes/nerubian_assassin/nerubian_assassin.vmdl"; }
		case 89: {return "models/heroes/siren/siren.vmdl"; }
		case 90: {return "models/heroes/keeper_of_the_light/keeper_of_the_light.vmdl"; }
		case 91: {return "models/heroes/wisp/wisp.vmdl"; }
		case 92: {return "models/heroes/visage/visage.vmdl"; }
		case 93: {return "models/heroes/slark/slark.vmdl"; }
		case 94: {return "models/heroes/medusa/medusa.vmdl"; }
		case 95: {return "models/heroes/troll_warlord/troll_warlord.vmdl"; }
		case 96: {return "models/heroes/centaur/centaur.vmdl"; }
		case 97: {return "models/heroes/magnataur/magnataur.vmdl"; }
		case 98: {return "models/heroes/shredder/shredder.vmdl"; }
		case 99: {return "models/heroes/bristleback/bristleback.vmdl"; }
		case 100: {return "models/heroes/tuskarr/tuskarr.vmdl"; }
		case 101: {return "models/heroes/skywrath_mage/skywrath_mage.vmdl"; }
		case 102: {return "models/heroes/abaddon/abaddon.vmdl"; }
		case 103: {return "models/heroes/elder_titan/elder_titan.vmdl"; }
		case 104: {return "models/heroes/legion_commander/legion_commander.vmdl"; }
		case 106: {return "models/heroes/ember_spirit/ember_spirit.vmdl"; }
		case 107: {return "models/heroes/earth_spirit/earth_spirit.vmdl"; }
		case 109: {return "models/heroes/terrorblade/terrorblade.vmdl"; }
		case 110: {return "models/heroes/phoenix/phoenix_bird.vmdl"; }
		case 111: {return "models/heroes/oracle/oracle.vmdl"; }
		case 105: {return "models/heroes/techies/techies.vmdl"; }
		case 127: {return "models/props_gameplay/dummy/dummy.vmdl"; }
		case 112: {return "models/heroes/winterwyvern/winterwyvern.vmdl"; }
		case 113: {return "models/heroes/arc_warden/arc_warden.vmdl"; }
		case 108: {return "models/heroes/abyssal_underlord/abyssal_underlord_v2.vmdl"; }
		case 114: {return "models/heroes/monkey_king/monkey_king.vmdl"; }
		case 120: {return "models/heroes/pangolier/pangolier.vmdl"; }
		case 119: {return "models/heroes/dark_willow/dark_willow.vmdl"; }
		case 121: {return "models/heroes/grimstroke/grimstroke.vmdl"; }
		case 129: {return "models/heroes/mars/mars.vmdl"; }
		case 126: {return "models/heroes/void_spirit/void_spirit.vmdl"; }
		case 128: {return "models/heroes/snapfire/snapfire.vmdl"; }
		case 123: {return "models/heroes/hoodwink/hoodwink.vmdl"; }
		case 135: {return "models/heroes/dawnbreaker/dawnbreaker.vmdl"; }
		case 136: {return "models/heroes/marci/marci_base.vmdl"; }
		case 137: {return "models/heroes/primal_beast/primal_beast_base.vmdl"; }
		}

		return "";
	}
    constexpr short IsArcana(const short& defIndex) {
		switch (defIndex) {
		case 5957: {return 5957; }
		case 6914: {return 6914; }
		case 6996: {return 6996; }
		case 7247: {return 7247; }
		case 7385: {return 7385; }
		case 7756: {return 7756; }
		case 9059: {return 9059; }
		case 9662: {return 9662; }
		case 12451: {return 12451; }
		case 12692: {return 12692; }
		case 12930: {return 12930; }
		case 13456: {return 13456; }
		case 13670: {return 13670; }
		case 13806: {return 13806; }
		case 19090: {return 19090; }
		case 23095: {return 23095; }
		case 18033: {return 18033; }
		}
		return 0;
	}
	constexpr short isPersona(const short& defIndex) {
		switch (defIndex) {
		case 13042: {return 13042; }
		case 13783: {return 13783; }
		case 13786: {return 13786; }
		case 18113: {return 18113; }
		case 18178: {return 18178; }
		case 19205: {return 19205; }
		case 22723: {return 22723; }
		}

		return 0;
	}
    std::string_view GetArcanaModelByDefIndex(const short& defIndex);
	std::string_view GetPersonModelByDefIndex(const short& defIndex);

	void InitItemsForEquip();

	void Patch();
	void UnPatch();
};

namespace user {
	DWORD GetUserId();
};

class utils
{
public:
	bool IsReadWriteMem(void* address);
	uint8_t* GetPatternAddress(const char* dll,const char* pattern);
	uintptr_t GetAbsOrigin(uintptr_t pInstruction, int iOffset, int iSize);
	LPVOID HookMethod(_In_ LPVOID lpVirtualTable, _In_ PVOID pHookMethod,
		_In_opt_ uintptr_t dwOffset);
};

extern utils g_utils;