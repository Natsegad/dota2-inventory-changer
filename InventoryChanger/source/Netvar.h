#pragma once
#include <unordered_map>
#include <fstream>

#define NETVAR(type, table, netvar)                             \
  type& netvar() {                                              \
    static DWORD64 dwOffset = Netvars::netvars[table][#netvar]; \
    return *reinterpret_cast<type*>((DWORD64)this + dwOffset);  \
  }

namespace Netvars {
    void Initialize();
    unsigned long GetOffset(std::string class_name, std::string offset_name);
    void dump(std::string class_name);

    inline std::unordered_map<std::string,
        std::unordered_map<std::string, uint32_t>>
        netvars;
    inline std::unordered_map<std::string,
        std::unordered_map<std::string, uint32_t>>
        schema_netvars;
}  // namespace Netvars

#define NETVAR(_a, _b) Netvars::GetOffset(_a, _b)
#define CBENETVAR(_a) NETVAR("C_BaseEntity", _a)


