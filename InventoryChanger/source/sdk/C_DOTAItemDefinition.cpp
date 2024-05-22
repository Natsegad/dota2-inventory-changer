#include "C_DOTAItemDefinition.h"

int C_DOTAItemDefinition::get_loadout_slot() {
	return (this->m_dotaItemDefinitionPtr) ? *(unsigned int*)(reinterpret_cast<uintptr_t>(m_dotaItemDefinitionPtr) + 0x1c8) : NULL;
}

int C_DOTAItemDefinition::get_hero_id() {
	return (this->m_dotaItemDefinitionPtr) ? *(unsigned int*)(reinterpret_cast<uintptr_t>(m_dotaItemDefinitionPtr) + 0x1BC) : NULL;
}

uintptr_t C_DOTAItemDefinition::get_asset_modifier_container() {
	return *(uintptr_t*)((uintptr_t)m_dotaItemDefinitionPtr + 0xb8);
}