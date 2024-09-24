#!/bin/bash 

#
# create build dir if does not exist, cd to build, conan install and then qmake
# 

mkdir -p build
cd build
rm -fr Hydro_UQ.app

#
# Use c++17 standard so we have if constexpr, etc.
# TODO: Make sure there aren't old 'make' and conan files laying around
#

CXXFLAGS="—std=c++17:$CXXFLAGS"

# conan install
conan install .. --build missing
status=$?
if [[ $status != 0 ]]
then
    echo "Hydro-UQ: conan install failed";
    exit $status;
fi

# qmake
qmake ../Hydro-UQ.pro
status=$?
if [[ $status != 0 ]]
then
    echo "Hydro-UQ: qmake failed";
    exit $status;
fi

# make
make -j5
status=$?;
if [[ $status != 0 ]]
then
    echo "Hydro-UQ: make failed";
    exit $status;
fi

if [[ "$OSTYPE" == "darwin"* ]]
then
    cp -r ../Examples ./Hydro_UQ.app/contents/MacOS
    rm -fr ./Hydro_UQ.app/contents/MacOS/Examples/.archive
    rm -fr ./Hydro_UQ.app/contents/MacOS/Examples/.aurore
    rm -fr ./Hydro_UQ.app/contents/MacOS/Examples/.conf
    rm -fr ./Hydro_UQ.app/contents/MacOS/Examples/Makefile
    rm -fr ./Hydro_UQ.app/contents/MacOS/Examples/README.md        
else
    #
    echo "No Examples Copied"
fi
