#!/bin/bash
cd /app
mkdir -p build
cd build
cmake .. -DMODE=docker
make all

./yk