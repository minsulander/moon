@echo off
cd ..\src\moon\bindings
..\..\..\moon-dependencies-win32\bin\tolua++ -H tolua_moon.h -o tolua_moon.cpp moon.tolua
cd ..\..\..\src\moodyn\bindings
..\..\..\moon-dependencies-win32\bin\tolua++ -H tolua_moodyn.h -o tolua_moodyn.cpp moodyn.tolua
cd ..\..\..\src\maudio\bindings
..\..\..\moon-dependencies-win32\bin\tolua++ -H tolua_maudio.h -o tolua_maudio.cpp maudio.tolua
pause
