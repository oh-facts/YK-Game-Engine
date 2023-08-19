#!/bin/bash


# Build and run your application
cd /app
mkdir -p build
cd build
cmake .. -DHEADLESS_MODE=on
make all

chmod -R a+r /app/res

./yk
