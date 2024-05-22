#pragma once
#include <Windows.h>
#include <string>
class CSkeletonInstance
{
public:
	void* get_ptr() { return this; }

	uintptr_t   get_model_state();
	std::string get_model_name();

	uintptr_t   get_c_model();

	void* CleanUpModel();

	std::string_view GetActivityName(const short& sequence);
	std::string_view GetSequenceName(const short& sequence);

	void SetSkeletonMaterialGroup(int group);
	void SkeletonSetModel(void* ptr);
	void SetModel(void* ptr);
};

