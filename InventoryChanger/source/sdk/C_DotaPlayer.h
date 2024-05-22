#pragma once
#include <Windows.h>

class C_DotaPlayer
{
public:
	FORCEINLINE C_DotaPlayer(void* playerPointer) :m_playerPtr(playerPointer) {}
	FORCEINLINE void* GetPtr() { return this->m_playerPtr; }

	void* operator new(size_t size);
	void  operator delete(void* memory);

	char* GetPlayerSelectedHero();
	int GetPlayerID();

private:
	void* m_playerPtr = nullptr;
};

