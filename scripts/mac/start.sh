#!/bin/sh
PREFIX=`dirname $0`/../Resources
export OSG_FILE_PATH="$PREFIX/data:$PREFIX/data/OpenSceneGraph-Data-2.8.0:$OSG_FILE_PATH"
export OSG_LIBRARY_PATH="$PREFIX/lib/moonPlugins:$PREFIX/lib/osgPlugins-2.8.2:$OSG_LIBRARY_PATH"

if [ -z "$*" ]; then
	scenario=default
fi

mkdir -p $HOME/Documents/moon
$PREFIX/moonshell -d 5 -allplugins $scenario >$HOME/Documents/moon/moon.log 2>&1
