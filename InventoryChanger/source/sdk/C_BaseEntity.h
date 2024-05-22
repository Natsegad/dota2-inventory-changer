#pragma once
#include "C_BaseCombatCharacter.h"
class C_BaseEntity :
    public C_BaseCombatCharacter
{
public:
    DWORD Owner() {
        return *(DWORD*)((uintptr_t)(get_ptr()) + 0x43C);
    }

    void* operator new(size_t size);
    void operator delete(void* mem);
};

