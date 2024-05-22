// dllmain.cpp : Определяет точку входа для приложения DLL.
#include <Windows.h>
#include <cstdio>

#include "source/sdk/CProtobufManager.h"
#include "source/DGlobalValues.h"
#include "source/Netvar.h"

#include "hooks/hooks.h"

void EntryPoint() {


    Netvars::Initialize();
    InitializeHooks();
    for (int i = 0;
        i < 2;
        i++) {
        fmt::log(xorstr_("Sending hello \n"));
        CProtobufManager::SendHello();
        Sleep(4000);
    }
    while (!GetAsyncKeyState(VK_ESCAPE)) {
        Sleep(50);
   
    }
    CProtobufManager::SendHello();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        AllocConsole();
        AttachConsole(GetCurrentProcessId());

        FILE* fp;
        freopen_s(&fp, "CONOUT$", "w", stdout);
        freopen_s(&fp, "CONOUT$", "w", stdin);

        HANDLE mainCheatThreadHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)EntryPoint, 0, 0, 0);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

