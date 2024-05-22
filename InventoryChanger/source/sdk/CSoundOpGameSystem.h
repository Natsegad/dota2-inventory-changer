#pragma once
#include <Windows.h>
#include "../../util/utils.h"

class CSoundOpGameSystem {
public:
	std::string_view GetSoundName(const DWORD& id) {
		if (!this) {
			return "";
		}

		using getSoundName_t = const char* (__fastcall*)(void*, DWORD);
		static getSoundName_t getSoundName = (getSoundName_t)g_utils.GetPatternAddress("soundsystem.dll","48 8b 41 ? 48 83 c1 ? 48 ff 60 ? cc cc cc cc 48 8b 41 ? 48 83 c1 ? 48 ff 60 ? cc cc cc cc 48 8b 05");
		if (!getSoundName) {
			return "";
		}
		auto sName = getSoundName(this, id);
	
		return (sName) ? sName : "nety";
	}

	DWORD GetSoundId(const char* name) {
		//48 8b 41 ? 48 83 c1 ? 48 ff 20
		if (!this) {
			return 0;
		}

		using getSoundName_t = DWORD (__fastcall*)(void*, const char*);
		static getSoundName_t getSoundName = (getSoundName_t)g_utils.GetPatternAddress("soundsystem.dll", "48 8b 41 ? 48 83 c1 ? 48 ff 20");
		if (!getSoundName) {
			return 0;
		}

		return getSoundName(this, name);
	}
};