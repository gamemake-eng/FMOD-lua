extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

}
#include <stdio.h>
#include "fmod.h"
#include "fmod_errors.h"
#include "fmod_studio.h"
#include <vector>

FMOD_RESULT result;
FMOD_SYSTEM* system = NULL;
FMOD_SOUND* Sound;
FMOD_CHANNEL* Channel;

static int l_load(lua_State* L)
{
	result = FMOD_System_Create(&system,FMOD_VERSION); // Create the Studio System object.
    if (result != FMOD_OK)
    {
    	printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        return -1;
    }

    // Initialize FMOD Core
    result = FMOD_System_Init(system, 512, FMOD_INIT_NORMAL, FMOD_INIT_NORMAL);
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        return -1;
    }

	return 1;

}
static int l_play(lua_State* L)
{
	const char* file = luaL_checkstring (L, 1);

	result = FMOD_System_CreateSound(system, file, FMOD_DEFAULT, 0, &Sound);
	if (result != FMOD_OK)
    {
    	printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        return -1;
    }
	result = FMOD_System_PlaySound(system, Sound, 0, false, &Channel);
	if (result != FMOD_OK)
    {
    	printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        return -1;
    }

    printf("FMOD ACTIVATED!");

	

	return 1;
}

static int l_stop(lua_State* L)
{
	if(Channel)
	{
		FMOD_Channel_Stop(Channel);
	}

	

	return 1;
}

static int l_release(lua_State* L)
{
	FMOD_System_Release(system);

	return 1;
}



static const struct luaL_Reg nativeFuncLib[] =
	{
		{"Load", l_load},
		{"Release", l_release},
		{"Play", l_play},
		{"Stop", l_stop},
		{NULL, NULL}
	};
extern "C"
{
int luaopen_fmodlua(lua_State* L)
{
	printf("Loading lib");

	luaL_newlib(L, nativeFuncLib);

	return 1;
}
}