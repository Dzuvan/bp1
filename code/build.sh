#!/bin/bash

mkdir -p ../build
pushd ../build

c++ -g -o bioskop ../code/main.cpp

popd

../build/./bioskop
