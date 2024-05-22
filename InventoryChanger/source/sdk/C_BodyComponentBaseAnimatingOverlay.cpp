#include "C_BodyComponentBaseAnimatingOverlay.h"

#include "../Netvar.h"

C_BaseAnimatingController* C_BodyComponentBaseAnimatingOverlay::GetAnimatingController()
{
	if (!this) {
		return nullptr;
	}

	static auto animControllOffset = Netvars::GetOffset("C_BodyComponentBaseAnimating", "m_animationController");

	return (C_BaseAnimatingController*)((uintptr_t)this + animControllOffset);
}
