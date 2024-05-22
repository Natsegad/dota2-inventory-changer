#include "CEconItemSystem.h"

#include "../../util/utils.h"

int CDOTAItemDefinition::GetLoadoutSlot() {
    return (this->m_dotaItemDefinitionPtr) ? *(unsigned int*)(reinterpret_cast<uintptr_t>(m_dotaItemDefinitionPtr) + 0x188) : NULL;
}

int CDOTAItemDefinition::GetHeroID() {
    return (this->m_dotaItemDefinitionPtr) ? *(unsigned int*)(reinterpret_cast<uintptr_t>(m_dotaItemDefinitionPtr) + 0x18c) : NULL;
}

uintptr_t CDOTAItemDefinition::get_asset_modifier_container() {
    return *(uintptr_t*)((uintptr_t)m_dotaItemDefinitionPtr + 0xb8);
}

CDOTAItemDefinition* CEconItemSystem::GetItemDefinitionMutable(__int16 a2) {
    using fn = void* (__fastcall*)(void*, __int16);

    static auto _fn = reinterpret_cast<fn>(g_utils.GetPatternAddress("client.dll", "40 53 48 83 EC 20 48 8B D9 89 54 24 38 48 83 C1 20 48 8D 54 24 ? E8 ? ? ? ? 85 C0 78 21 3B 43 68 7D 1C 48 98 "));

    return (_fn) ? new CDOTAItemDefinition(_fn(this->m_econItemSystemPtr, a2)) : new CDOTAItemDefinition(0);
}

__int64 CEconItemSystem::get_attribute_definition(int a1) {
  /*  __int64 v11, v12, v13, v14, v15, v10 = a1, v9 = (uintptr_t)m_econItemSystemPtr;

    v11 = *((DWORD*)v9 + 106);;
    if (v11 != -1) {
        v12 = *(__int64*)(v9 + 51 * 8);
        do {
            v13 = 15i64 * v11;
            if (v10 >= SLODWORD(*(DWORD*)(v12 + (v13 * 8 + 2)))) {
                if (v10 <= SLODWORD(*(DWORD*)(v12 + (v13 * 8 + 2))))
                    break;
                v11 = *(__int64*)(v12 + v13 * 8);
            }
            else {
                v11 = *(int*)(v12 + v13 * 8);
            }
        } while (v11 != -1);
    }
    if (v11 < 0
        || v11 >= *((_DWORD*)v9 + 104)
        || v11 > *((_DWORD*)v9 + 109)
        || (v14 = 15i64 * v11, v15 = v9, LODWORD(*(__int64*)(v15 + v14 * 8)) == v11)) {
        return 0i64;
    }
    else {
        return(signed __int64)&v15 + (v14 * 8) + 3;
    }*/

    return 0;
}