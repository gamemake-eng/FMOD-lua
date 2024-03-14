extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

}
#include <stdio.h>
#include "fmod_studio.h"
#include "fmod.h"
#include "fmod_errors.h"
#include "fmod_studio.h"
#include <string>
#include <unordered_map>



FMOD_RESULT result;
FMOD_STUDIO_SYSTEM* studiosystem = NULL;
FMOD_SYSTEM* coresystem = NULL;
std::unordered_map<const char*, FMOD_STUDIO_BANK*> banks;
std::unordered_map<const char*, FMOD_STUDIO_BANK*> bank_strings;
std::unordered_map<const char*, FMOD_STUDIO_EVENTINSTANCE*> instances;


static int l_load(lua_State* L)
{
	const char* mode = luaL_checkstring(L, 1);
	
	result = FMOD_Studio_System_Create(&studiosystem,FMOD_VERSION); // Create the Studio System object.
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }

    FMOD_Studio_System_GetCoreSystem(studiosystem, &coresystem);
    FMOD_System_SetSoftwareFormat(coresystem,0,FMOD_SPEAKERMODE_5POINT1,0);

    if (mode == "live")
	{
		result = FMOD_Studio_System_Initialize(studiosystem, 512, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_NORMAL, 0);

	}else
	{
		result = FMOD_Studio_System_Initialize(studiosystem, 512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);

	}
    // Initialize FMOD Studio, which will also initialize FMOD Core
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }

	return 1;

}

static int l_update(lua_State* L)
{
	FMOD_Studio_System_Update(studiosystem);
	return 1;
}

static int l_release(lua_State* L)
{
	FMOD_Studio_System_Release(studiosystem);
	return 1;
}

static int l_loadbank(lua_State* L)
{
	const char* file = luaL_checkstring(L, 1);

	const char* id = luaL_checkstring(L, 2);
	FMOD_STUDIO_BANK* bank;


	result = FMOD_Studio_System_LoadBankFile(studiosystem, file, 0, &bank);
	if(bank)
	{
		banks.emplace(id, bank);
	}else
	{
		printf("load failed");
	}
	
	return 1;
}
static int l_releasebank(lua_State* L)
{
	const char* id = luaL_checkstring(L, 1);
	FMOD_Studio_Bank_Unload(banks[id]);
	FMOD_Studio_Bank_Unload(bank_strings[id]);
	return 1;
}
static int l_oneshot(lua_State* L)
{
	FMOD_STUDIO_EVENTDESCRIPTION* ed = NULL;

	const char* id = luaL_checkstring(L, 1);


	result = FMOD_Studio_System_GetEvent(studiosystem, id, &ed);

	if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        
    }

	if (ed)
	{
		FMOD_STUDIO_EVENTINSTANCE* ei = NULL;
		FMOD_Studio_EventDescription_CreateInstance(ed, &ei);
		
		if (ei)
		{
			FMOD_Studio_EventInstance_Start(ei);
			FMOD_Studio_EventInstance_Release(ei);
		}else
		{
			printf("ei failed");
		}
	}else
	{
		printf("ed failed");
	}
	return 1;
}
static const struct luaL_Reg nativeFuncLib[] =
	{
		{"Load", l_load},
		{"Update", l_update},
		{"Release", l_release},
		{"LoadBank", l_loadbank},
		{"ReleaseBank", l_releasebank},
		{"OneShot", l_oneshot},
		{NULL, NULL}
	};
extern "C"
{
int luaopen_fmodstudiolua(lua_State* L)
{
	printf("Loading lib");

	luaL_newlib(L, nativeFuncLib);

	return 1;
}
}