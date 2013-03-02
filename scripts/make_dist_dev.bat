@echo off
set prevdir=%CD%

cd ..
rd /s /q moon-win32-dev
md moon-win32-dev
md moon-win32-dev\bin\moonPlugins
md moon-win32-dev\data
xcopy /s /y moon-dependencies-win32 moon-win32-dev
copy /y build-win32\bin\Debug\*.exe moon-win32-dev\bin
copy /y build-win32\bin\Release\*.exe moon-win32-dev\bin
copy /y build-win32\bin\Debug\*.dll moon-win32-dev\bin
copy /y build-win32\bin\Release\*.dll moon-win32-dev\bin
copy /y build-win32\bin\moonPlugins\Debug\*.dll moon-win32-dev\bin\moonPlugins
copy /y build-win32\bin\moonPlugins\Release\*.dll moon-win32-dev\bin\moonPlugins
copy /y build-win32\lib\Debug\*.lib moon-win32-dev\lib
copy /y build-win32\lib\Release\*.lib moon-win32-dev\lib
xcopy /s /y data moon-win32-dev\data
rem TODO: header files! and documentation

del /q moon-win32-dev.zip
moon-win32-dev\bin\zip -r moon-win32-dev.zip moon-win32-dev
cd %prevdir%
