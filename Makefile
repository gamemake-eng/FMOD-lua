FMOD = -I"C:\\Program Files\\FMOD SoundSystem\\FMOD Studio API Windows\\api\\core\\inc" -L"C:\\Program Files\\FMOD SoundSystem\\FMOD Studio API Windows\\api\\core\\lib\\x86\\"
FMODSTUDIO = -I"C:\\Program Files\\FMOD SoundSystem\\FMOD Studio API Windows\\api\\studio\\inc" -L"C:\\Program Files\\FMOD SoundSystem\\FMOD Studio API Windows\\api\\studio\\lib\\x86\\"
fmodlua.dll: fmodlua.cpp
	g++ $^ $(FMOD) $(FMODSTUDIO) -fpic -llua -lfmod -shared -o $@