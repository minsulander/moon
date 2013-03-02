@echo off
set build_prefix=%1
set deps_prefix=%2
shift
shift
if %build_prefix%.==. set build_prefix=%CD%/../build-win32
if %deps_prefix%.==. set deps_prefix=%CD%/../moon-dependencies-win32

set PATH=%build_prefix%/bin/Release;%build_prefix%/bin/Debug;%build_prefix%/bin;%deps_prefix%/bin;%PATH%
set OSG_FILE_PATH=%build_prefix%/data;%build_prefix%/../data;%deps_prefix%/data;$deps_prefix/data/OpenSceneGraph-Data-2.8.0;%OSG_FILE_PATH%
set OSG_LIBRARY_PATH=%build_prefix%/lib/moonPlugins/Release;%build_prefix%/lib/moonPlugins/Debug;%deps_prefix%/lib/osgPlugins-2.8.0;%OSG_LIBRARY_PATH%
%1 %2 %3 %4 %5 %6 %7 %8 %9
