#pragma once
#include <Windows.h>

#include "CSkeletonInstance.h"

class CGameSceneNode {
public:
	__inline CGameSceneNode(uintptr_t ptr) :m_CGameSceneNodePtr(reinterpret_cast<void*>(ptr)) {

	}

	void* get_ptr() { return this->m_CGameSceneNodePtr; }

	void* operator new(size_t size);
	void operator delete(void* mem);

	CSkeletonInstance* get_skeleton_instance();
	//Vector* get_vec_abs_origin_v();
	//QAngle* get_ang_abs_rotation_v();
	//QAngle* get_ang_rotation();

	uintptr_t get_vec_abs_origin();
	uintptr_t get_ang_abs_rotation();

private:
	void* m_CGameSceneNodePtr;
};

