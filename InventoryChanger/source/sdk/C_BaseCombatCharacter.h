#pragma once
#include <Windows.h>
#include <set>
#include <vcruntime.h>

class C_BaseCombatCharacter
{
public:
	C_BaseCombatCharacter() {}

	_NODISCARD FORCEINLINE void* get_ptr() { return this; }

	void remove_all_wearables();
	void remove_item(void* item);
	void remove_wearables();
	void c_remove_wearables();

};

