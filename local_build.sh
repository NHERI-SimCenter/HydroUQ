#!/bin/bash

# source ~/HydroUQ_venv/venv3.9.16/bin/activate
rm -rf build
mkdir -p build
cd build
cp -r ../Examples/ .
#cp -r ../../SimCenterBackendApplications_JohnMerge/SimCenterBackendApplications/applications/ .
cp -r ../../SimCenterBackendApplications/applications/ .
mkdir -p ./applications/ClaymoreUW
export CLUW_SRC_PATH=/home/justinbonus/SimCenter/claymore
cp $CLUW_SRC_PATH/Projects/OSU_LWF/osu_lwf ./applications/ClaymoreUW/
cp applications/ClaymoreUW/osu_lwf applications/ClaymoreUW/osu_lwf.exe
sudo chmod 'a+rwx' ./applications/ClaymoreUW/*

sudo chmod 'a+rwx' ./applications/*
sudo chmod 'a+rwx' ./applications/**/*
sudo chmod 'a+rwx' ./applications/**/**/*
sudo conan install .. --build missing
sudo /opt/qt515/bin/qmake ../Hydro-UQ.pro
sudo make -j8
