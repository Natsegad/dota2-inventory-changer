#include "CRenderComponent.h"

#include "../Netvar.h"
#include "../../util/utils.h"

bool CRenderComponent::GetRenderEnable() {
	if (!m_pRenderCompPtr) return false;
	static auto offsetRenderEnable = Netvars::GetOffset("CRenderComponent", "m_bEnableRendering");
	return *(bool*)((uintptr_t)m_pRenderCompPtr + offsetRenderEnable);
}

void CRenderComponent::SetRenderEnable(const bool& value)
{
	if (!m_pRenderCompPtr) {
		return;
	}

	using setRenderEnable_t = void(__fastcall*)(void*, bool);
	static auto setRenderEnable = (setRenderEnable_t)g_utils.GetPatternAddress("client.dll", "40 53 48 83 EC 20 0F B6 41 60 48 8B D9 3A C2 0F 84 ? ? ? ?");
	if (!setRenderEnable) {
		fmt::log("#setRenderEnable not found ! \n");
		return;
	}

	setRenderEnable(m_pRenderCompPtr, value);
}