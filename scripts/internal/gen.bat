cmake -B out/release -DCMAKE_TOOLCHAIN_FILE="cmake/toolchains.cmake" -DMODE=normal -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cd out/release
ninja