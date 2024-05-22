#pragma once
#include "CRenderComponent.h"

#include <memory>

class C_DOTAWearableItem
{
public:
	std::unique_ptr<CRenderComponent> GetRenderComponent();

	uintptr_t GetAttributeManager();
	short GetItemDefIndex();

	void* get_ptr() { return this; }
};

