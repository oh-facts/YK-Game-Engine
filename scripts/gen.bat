cd ..
cmake -B out/release -DCMAKE_TOOLCHAIN_FILE="cmake/toolchains.cmake" -DHEADLESS_MODE=off -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cd out/release
ninja
