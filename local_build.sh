#!/bin/bash

rm -rf build
mkdir -p build
cd build
cp -r ../Examples/ .
cp -r ../../SimCenterBackendApplications_JohnMerge/SimCenterBackendApplications/applications/ .
sudo conan install .. --build missing
sudo /opt/qt515/bin/qmake ../Hydro-UQ.pro
sudo make -j8
