cd ..
cmake -B out -DCMAKE_TOOLCHAIN_FILE="cmake/toolchains.cmake" -G "Ninja"
cd out
ninja
