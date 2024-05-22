#include "CGameSceneNode.h"

#include "../Netvar.h"
#include "../DGlobalValues.h"

void* CGameSceneNode::operator new(size_t size)
{
    return Dota::GetIMemAlloc()->Alloc(size);
}

void CGameSceneNode::operator delete(void* mem)
{
    Dota::GetIMemAlloc()->Free(mem);
}

CSkeletonInstance* CGameSceneNode::get_skeleton_instance()
{
    return (CSkeletonInstance*)(m_CGameSceneNodePtr);
}

uintptr_t CGameSceneNode::get_vec_abs_origin() {
    if (!this->m_CGameSceneNodePtr) return 0;

    return reinterpret_cast<uintptr_t>(m_CGameSceneNodePtr) + Netvars::GetOffset("CGameSceneNode", "m_vecAbsOrigin");
}

uintptr_t CGameSceneNode::get_ang_abs_rotation() {
    if (!this->m_CGameSceneNodePtr) return 0;

    return reinterpret_cast<uintptr_t>(m_CGameSceneNodePtr) + Netvars::GetOffset("CGameSceneNode", "m_angAbsRotation");
}
