#pragma once
#include <Windows.h>

class KeyValues {
public:
    void* GetFirstSubKey(void* key_value);
    void* GetNextKey(void* key_value);
    void* GetFirstTrueSubKey(void* key_value);
    void* GetNextTrueSubKey(void* key_value);
    void* GetNextValue(void* key_value);
    void* GetFirstValue(void* key_value);
    void* FindKey(void* mem_alloc, const char* key_name, bool unk);
    void* LoadTemporaryFromFile(const char* name, const char* MOD);
    bool IsEmpty(void* kv, const char* key);
    const int GetInt(void* key_value, const char* key, int defaultValue = 0);

    const char* GetString(void* key_value, const char* key);
    const char* GetName(void* key_value);

    template<typename T>
    T GetValue(void* key_value) {
        if (!key_value)  return (T)"";

        MEMORY_BASIC_INFORMATION MBI;
        if (VirtualQuery(key_value, &MBI, sizeof(MBI))) {
            if (MBI.AllocationProtect == 4)
                return *reinterpret_cast<T*>(key_value);
            else
                return (T)"";
        }
        return (T)"";
    }
private:

};

