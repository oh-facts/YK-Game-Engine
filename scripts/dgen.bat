cd ..
cmake -B out/debug -DCMAKE_TOOLCHAIN_FILE="cmake/toolchains.cmake" -DHEADLESS_MODE=off -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
cd out/debug
ninja
