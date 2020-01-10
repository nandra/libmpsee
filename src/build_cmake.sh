#!/bin/sh

# create build dir
mkdir -p .build

# format sources
clang-format -i *.c *.h

pushd .build

# run cmake
cmake ..

# build project
make -j `nproc`

popd

