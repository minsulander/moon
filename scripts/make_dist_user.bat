@echo off
set prevdir=%CD%
    
cd ..
rd /s /q moon-win32-user
md moon-win32-user
md moon-win32-user\bin\moonPlugins
md moon-win32-user\data
xcopy /s /y moon-dependencies-win32\bin moon-win32-user\bin
xcopy /s /y moon-dependencies-win32\data moon-win32-user\data
copy /y build-win32\bin\Release\*.exe moon-win32-user\bin
copy /y build-win32\bin\Release\*.dll moon-win32-user\bin
copy /y build-win32\bin\moonPlugins\Release\*.dll moon-win32-user\bin\moonPlugins
xcopy /s /y data moon-win32-user\data

del /q moon-win32-user\bin\*d.dll
del /q moon-win32-user\bin\osgPlugins-2.8.0\*d.dll
del /q moon-win32-user\bin\*d.exe
del /q moon-win32-user\bin\cmake*.exe moon-win32-user\bin\cpack.exe moon-win32-user\bin\ctest.exe
del /q moon-win32-user\bin\*.dlla

del /q moon-win32-user\bin\moontest*.exe

del /q moon-win32-user.zip
moon-win32-user\bin\zip -r moon-win32-user.zip moon-win32-user
cd %prevdir%
