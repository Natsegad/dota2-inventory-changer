#pragma once
#include <Windows.h>

#include "SchemaType.h"

template <typename T> static T GetVirtual(void* object, int index) {
	return (*(T**)object)[index];
}
//template
//<typename T>
//static T GetVirtual(void* object, int index) {
//	return (*(T**)object)[index];
//}

using namespace std;
//template <typename T = void, int i = 0, typename... Args>
//T CallVirtual(void* classptr, Args... name) {
//
//	using fn = T * (__fastcall*)(void*, Args...);
//	auto func = GetVirtual<fn>(classptr, i);
//	return func(classptr, std::forward<Args>(name)...);
//}

struct TypeScope {
public:

	//schema::CSchemaClassInfo* FindDeclaredClass(const char* name) {

	//	auto find = GetVirtual<void*>(this, 22);

	//	using  GetTypeScope = uintptr_t * (__fastcall*)(void* ecx, const char* name);

	//	auto GetsCOPE = reinterpret_cast<GetTypeScope>(find);
	//	return (schema::CSchemaClassInfo*)GetsCOPE(this, name);


	//}

	//__int64 __fastcall sub_7FFA77EDFFE0( BYTE* a2 ) {
	//	BYTE* v2; // rbx
	//	__int64 v3; // rdi
	//	signed __int64 v4; // rax
	//	int v5; // eax
	//	__int64 result; // rax
	//	__int64 v7; // rcx
	//	int v8; // [rsp+30h] [rbp+8h]
	//	__int64 a1 = ( __int64 )this;
	//	using fn = __int64( __fastcall* )(__int64, __int64, __int64);
	//	using sub_fn = __int64( __fastcall* )(__int64, __int64);

	//	auto MurmurHash2 = ( fn )GetProcAddress( GetModuleHandleA( "tier0.dll" ), "MurmurHash2" );
	//	auto sub_7FFA77EE2220 = ( sub_fn )Util::PatternScan( "schemasystem.dll", "40 55 57 48 83 EC 48 48 89 5C 24 ? 48 8D 79 28 48 89 74 24 ? 48 8B F1 4C 89 64 24 ? 4C 8B E2 " );
	//	v2 = a2;
	//	v3 = a1;
	//	if ( a2 && *a2 ) {
	//		v4 = -1i64;
	//		do
	//			++v4;
	//		while ( a2[v4] );
	//		v5 = MurmurHash2( ( __int64 )a2, ( unsigned int )v4, 0xBAADFEEDi64 );
	//	} else {
	//		v5 = 0;
	//	}
	//	v8 = v5;
	//	result = sub_7FFA77EE2220( v3 + 1176, ( __int64 )&v8 );
	//	if ( !result ) {
	//		v7 = *( _QWORD* )(v3 + 264);
	//		if ( v7 )
	//			result = (*(__int64( __fastcall** )(__int64, BYTE*))(*( _QWORD* )v7 + 176i64))(v7, v2);
	//		else
	//			result = 0i64;
	//	}
	//	return result;
	//}

	void* FindDeclaredEnum(const char* name) {
		auto find = GetVirtual<void*>(this, 4);

		using  GetTypeScope = uintptr_t * (__fastcall*)(void* ecx, const char* name);

		auto GetsCOPE = reinterpret_cast<GetTypeScope>(find);
		return GetsCOPE(this, name);

	}

	schema::CSchemaClassInfo* FindDeclaredClass(const char* name) {

		auto find = GetVirtual<void*>(this, 22);

		using  GetTypeScope = uintptr_t * (__fastcall*)(void* ecx, const char* name);

		auto GetsCOPE = reinterpret_cast<GetTypeScope>(find);
		return (schema::CSchemaClassInfo*)GetsCOPE(this, name);


	}

	void* FindType_DeclaredEnum(const char* name) {

		auto find = GetVirtual<void*>(this, 23);

		using  GetTypeScope = uintptr_t * (__fastcall*)(void* ecx, const char* name);

		auto GetsCOPE = reinterpret_cast<GetTypeScope>(find);
		return GetsCOPE(this, name);
	}
};
struct CShemaSystem {
public:
	TypeScope* GlobalTypeCope() {
		auto find = GetVirtual<void*>(this, 11);

		using  GetTypeScope = uintptr_t * (__fastcall*)(void* ecx);

		auto GetsCOPE = reinterpret_cast<GetTypeScope>(find);
		return (TypeScope*)GetsCOPE(this);

	}

	TypeScope* FindTypeScopeForModule(const char* name) {
		auto find = GetVirtual<void*>(this, 13);

		using  GetTypeScope = uintptr_t * (__fastcall*)(void* ecx, const char* name);

		auto GetsCOPE = reinterpret_cast<GetTypeScope>(find);
		auto ret = (TypeScope*)GetsCOPE(this, name);
		return ret;

	}
};