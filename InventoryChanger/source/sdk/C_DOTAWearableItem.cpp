#include "C_DOTAWearableItem.h"

#include "../../defs/defs.h"

#include "../Netvar.h"

#include "../DGlobalValues.h"
#include "../../util/utils.h"

std::unique_ptr<CRenderComponent> C_DOTAWearableItem::GetRenderComponent() {
	if (!get_ptr()) {
		return std::make_unique<CRenderComponent>(nullptr);
}

	static auto offsetRenderComponent = Netvars::GetOffset("C_BaseModelEntity", "m_CRenderComponent");

	return std::make_unique<CRenderComponent>((void*)(*(uintptr_t*)(reinterpret_cast<uintptr_t>(get_ptr()) + offsetRenderComponent)));
}

uintptr_t C_DOTAWearableItem::GetAttributeManager()
{
	if (!this) return 0;

	static auto mAttributeOffset = Netvars::GetOffset("C_EconEntity", "m_AttributeManager");
	return (uintptr_t)this + mAttributeOffset;
}

short C_DOTAWearableItem::GetItemDefIndex()
{
	if (!this) return 0;

	static auto mAttributeOffset = Netvars::GetOffset("C_EconEntity", "m_AttributeManager");
	static auto mItem = Netvars::GetOffset("CAttributeContainer", "m_Item");

	auto ecomitemview = (uintptr_t)this + mAttributeOffset + mItem;
	//static MEMORY_BASIC_INFORMATION mbi;

	//if (!VirtualQuery((LPVOID)ecomitemview, &mbi, sizeof(mbi))) return 0;
	//if (mbi.AllocationProtect != PAGE_READWRITE) return 0;
	
	return *(short*)(ecomitemview + Netvars::GetOffset("C_EconItemView", "m_iItemDefinitionIndex"));
}
