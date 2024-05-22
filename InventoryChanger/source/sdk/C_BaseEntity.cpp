#include "C_BaseEntity.h"

#include "../DGlobalValues.h"

void* C_BaseEntity::operator new(size_t size)
{
    return Dota::GetIMemAlloc()->Alloc(size);
}

void C_BaseEntity::operator delete(void* mem)
{
    Dota::GetIMemAlloc()->Free(mem);
}
