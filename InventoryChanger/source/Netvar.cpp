#include "Netvar.h"

#include "../util/utils.h"

#include "DGlobalValues.h"

using std::endl;
using std::ofstream;
static std::string push = "asdfg";

class ParsingEnum {
public:
public:
    char pad_0000[8];   // 0x0000
    char* N0000003A;    // 0x0008
    char pad_0010[16];  // 0x0010
    void* interfaces;   // 0x0020
    char pad_0028[24];  // 0x0028
    int32_t length;     // 0x0040
    char pad_0044[2];   // 0x0044
};                    // Size: 0x0148 //Enum

class EnumInfo {
public:
    char* name;         // 0x0000
    int32_t arg;        // 0x0008
    char pad_000C[56];  // 0x000C
};                    // Size: 0x0044

class MainClass {
public:
    class N0000002D* N00000001;  // 0x0000
    char pad_0008[16];           // 0x0008
    class ParsingEnum* GetPars;  // 0x0018
    char pad_0020[288];          // 0x0020
};                             // Size: 0x0140 //Enum

class Parsing {
public:
    char pad_0000[24];    // 0x0000
    int32_t memnum;       // 0x0018
    int16_t length;       // 0x001C
    char pad_001E[10];    // 0x001E
    void* server;         // 0x0028
    char pad_0030[1000];  // 0x0030
};                      // class

class CBaseEnt {
public:
    char pad_0000[32];        // 0x0000
    class Parsing* Pasrsing;  // 0x0018
    char pad_0020[4];         // 0x0020
};                          // class

class variable {
public:
    char pad_0000[8];  // 0x0000
    char* mtype;       // 0x0008
    char pad_0010[3];  // 0x0010
};                   // Size: 0x0030//

class interfaces {
public:
    // char* name; //0x0000
    // class variable* type; //0x008
    // int32_t offset; //0x0018

    char* name;            // 0x0000
    class variable* type;  // 0x0008
    int32_t offset;        // 0x0010
    char pad_0014[44];     // 0x0014

};  // class

std::vector<std::pair<std::string, std::string>> classExceptions = {
    std::make_pair("client.dll", "C_BodyComponentBaseAnimating"),
    std::make_pair("client.dll", "CGameSceneNode"),
    std::make_pair("client.dll", "C_BaseEntity"),
    std::make_pair("client.dll", "CDOTAItemDefinition"),
    std::make_pair("client.dll", "CRenderComponent"),
    std::make_pair("client.dll", "C_BaseModelEntity"),
    std::make_pair("client.dll", "CSkeletonInstance"),
    std::make_pair("client.dll", "C_DOTA_BaseNPC"),
    std::make_pair("client.dll", "C_BaseModelEntity"),
    std::make_pair("client.dll", "C_DOTAGamerules"),
    std::make_pair("client.dll", "C_EconEntity"),
    std::make_pair("client.dll", "C_EconItemView"),
    std::make_pair("client.dll", "CAttributeContainer"),
    std::make_pair("client.dll", "C_BaseCombatCharacter"),
    std::make_pair("client.dll", "C_DOTAPlayerController"),
    std::make_pair("client.dll", "C_DOTAGameManager"),
    std::make_pair("client.dll", "CAnimationLayer"),
    std::make_pair("client.dll","C_DOTAWearableItem"),
    std::make_pair("client.dll", "C_BaseAnimatingController") };//CAnimationLayer

void Netvars::Initialize() {
    // ofstream file("netvars.txt");

    for (auto& a : classExceptions) {
        auto schema = Dota::GetSchemaSystem();
        if (!schema) {
            return;
        }

        auto parsing = (CBaseEnt*)(schema
            ->FindTypeScopeForModule(a.first.c_str())
            ->FindDeclaredClass(a.second.c_str()));

        //ClientFrameStage_t
        if (parsing) {
            for (uintptr_t i = 0; i < parsing->Pasrsing->length; i++) {
                auto name =
                    (interfaces*)((uintptr_t)parsing->Pasrsing->server + i * 0x20);

                schema_netvars[a.second.c_str()][name->name] = name->offset;
            }
        }
    }

     printf("");
}

unsigned long Netvars::GetOffset(std::string class_name,
    std::string offset_name) {
    auto offsetNameIt = netvars.find(class_name);

    if (offsetNameIt != netvars.end()) {
        auto offsetValIt = offsetNameIt->second.find(offset_name);

        if (offsetValIt != offsetNameIt->second.end()) {
            return offsetValIt->second;
        }
        else {
        }
    }
    else {
    }

    auto schemaOffsetNameIt = schema_netvars.find(class_name);

    if (schemaOffsetNameIt != schema_netvars.end()) {
        auto offsetValIt = schemaOffsetNameIt->second.find(offset_name);

        if (offsetValIt != schemaOffsetNameIt->second.end()) {
            return offsetValIt->second;
        }
        else {
        }
    }
    else {
    }

    fmt::log("Offset or Class not found, class_name = %s offset_name = %s\n",
        class_name.c_str(), offset_name.c_str());

    return 3;
}

void Netvars::dump(std::string class_name) {
    auto class_offsetsIT = schema_netvars.find(class_name);
    if (class_offsetsIT != schema_netvars.end()) {
        for (auto& a : class_offsetsIT->second) {
            fmt::log(
                "[DUMP] member_name static DWORD %s = "
                "Netvars::GetOffset(\"%s\",\"%s\")    offset %i\n",
                a.first.c_str(), class_name.c_str(), a.first.c_str(), a.second);
        }
    }
}
