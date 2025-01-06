#!/bin/bash

cd build
cp -r ../Examples/ .
cp -r ../../SimCenterBackendApplications/applications/ .
sudo chmod 'a+rwx' ./applications/*
sudo chmod 'a+rwx' ./applications/**/*
sudo chmod 'a+rwx' ./applications/**/**/*
