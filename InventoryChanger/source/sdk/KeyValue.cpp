#include "KeyValue.h"

#include "../../util/utils.h"

void* KeyValues::GetFirstSubKey(void* key_value) {
    using _fn = void* (__fastcall*)(void*);
    static auto o_fn = (_fn)GetProcAddress(GetModuleHandleA("tier0.dll"), "?GetFirstSubKey@KeyValues@@QEBAPEAV1@XZ");

    return (o_fn) ? o_fn(key_value) : 0x0;
}

void* KeyValues::GetNextKey(void* key_value) {
    using _fn = void* (__fastcall*)(void*);
    static auto o_fn = (_fn)GetProcAddress(GetModuleHandleA("tier0.dll"), "?GetNextKey@KeyValues@@QEBAPEAV1@XZ");

    return (o_fn) ? o_fn(key_value) : 0x0;
}

void* KeyValues::GetFirstTrueSubKey(void* key_value) {
    using _fn = void* (__fastcall*)(void*);
    static auto o_fn = (_fn)GetProcAddress(GetModuleHandleA("tier0.dll"), "?GetFirstTrueSubKey@KeyValues@@QEBAPEAV1@XZ");

    return (o_fn) ? o_fn(key_value) : 0x0;
}

void* KeyValues::GetNextTrueSubKey(void* key_value) {
    using _fn = void* (__fastcall*)(void*);
    static auto o_fn = (_fn)GetProcAddress(GetModuleHandleA("tier0.dll"), "?GetNextTrueSubKey@KeyValues@@QEBAPEAV1@XZ");

    return (o_fn) ? o_fn(key_value) : 0x0;
}

void* KeyValues::GetNextValue(void* key_value) {
    using _fn = void* (__fastcall*)(void*);
    static auto o_fn = (_fn)GetProcAddress(GetModuleHandleA("tier0.dll"), "?GetNextValue@KeyValues@@QEBAPEAV1@XZ");

    return (o_fn) ? o_fn(key_value) : 0x0;
}

void* KeyValues::GetFirstValue(void* key_value) {
    using _fn = void* (__fastcall*)(void*);
    static auto o_fn = (_fn)GetProcAddress(GetModuleHandleA("tier0.dll"), "?GetFirstValue@KeyValues@@QEBAPEAV1@XZ");

    return (o_fn) ? o_fn(key_value) : 0x0;
}

void* KeyValues::FindKey(void* key_value, const char* key_name, bool unk) //пиздец, походу в кей нейм какой-то -> MemAlloc key_name = (_QWORD *)(*(__int64 (__fastcall **)(_QWORD, signed __int64))(*g_pMemAlloc + 8i64))(g_pMemAlloc, 56i64);
{
    using _fn = void* (__fastcall*)(void*, const char*, bool);
    static auto o_fn = (_fn)GetProcAddress(GetModuleHandleA("tier0.dll"), "?FindKey@KeyValues@@QEAAPEAV1@PEBD_N@Z");

    return (o_fn) ? o_fn(key_value, key_name, unk) : 0x0; //return key_value для использования например в GetFirstSubKey снизу
}

void* KeyValues::LoadTemporaryFromFile(const char* name, const char* MOD) {
    using _fn = void* (__fastcall*)(bool, uintptr_t, const char*, const char*, bool (*)(char const*, void*), void*, char const*);
    static auto ptr = *(uintptr_t*)(g_utils.GetAbsOrigin((uintptr_t)g_utils.GetPatternAddress("client.dll", "48 8B 0D ? ? ? ? 4C 8D 4C 24 ? 4C 89 64 24 ? 4C 8D 05 ? ? ? ? 44 89 64 24 ? 49 8B D6 "), 3, 7));

    auto tier_dll = GetModuleHandleA("tier0.dll");
    static auto o_fn = (_fn)GetProcAddress(tier_dll, "?LoadTemporaryFromFile@KeyValues@@SAPEAVCTemporaryKeyValues@@_NPEAVIFileSystem@@PEBD2P6A_N2PEAX@Z32@Z");

    if (ptr) {
        return o_fn(1, ptr, name, MOD, 0, 0, 0);
    }
}

bool KeyValues::IsEmpty(void* kv, const char* key) {
    using _fn = const int(__fastcall*)(void*, char const*);

    static auto o_fn = (_fn)GetProcAddress(GetModuleHandleA("tier0.dll"), "?IsEmpty@KeyValues@@QEAA_NPEBD@Z");

    return o_fn(kv, key);
}

const int KeyValues::GetInt(void* key_value, const char* key, int defaultValue) {
    using _fn = const int(__fastcall*)(void*, char const*, int);

    static auto o_fn = (_fn)GetProcAddress(GetModuleHandleA("tier0.dll"), "?GetInt@KeyValues@@QEBAHPEBDH@Z");

    return (o_fn) ? o_fn(key_value, key, defaultValue) : 0;
}

const char* KeyValues::GetString(void* key_value, const char* key) {
    using _fn = const char* (__fastcall*)(void*, char const*,void*, char*, unsigned __int64);
    static char* byte;
    static auto o_fn = (_fn)GetProcAddress(GetModuleHandleA("tier0.dll"), "?GetString@KeyValues@@QEAAPEBDPEBD0PEAD_K@Z");

    return (o_fn) ? o_fn(key_value, key, byte, 0, 0) : "";
}

const char* KeyValues::GetName(void* key_value) {
    using _fn = const char* (__fastcall*)(void*);
    static auto o_fn = (_fn)GetProcAddress(GetModuleHandleA("tier0.dll"), "?GetName@KeyValues@@QEBAPEBDXZ");

    return (o_fn) ? o_fn(key_value) : "";
}