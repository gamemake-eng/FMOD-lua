#	FMOD lua

NOTE: fmod is not a free libary, get it [here](https://www.fmod.com/)


The only fmod lua binding I could find was abandoned so I made one myself because I am big brain

##	How to use

Build the dll using make (windows only but I guess you can change it for linux)

After it creates fmodlua.dll copy the file into any lua project (LOVE, [GXE](https://github.com/gamemake-eng/GXE), OTHER)

now you can include it in your projects!

```lua
-- NOTE: Make sure to include fmod.dll IN THE DIRECTORY OF THE EXE (where love, GXE, lua, etc is installed)
local fmod = require("fmodlua")
```

You are free to contribute!