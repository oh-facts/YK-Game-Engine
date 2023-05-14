cmake_minimum_required(VERSION 3.21)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#project name
project(spacelemon)

#--------third - party ---------#

#root directory path
add_subdirectory(vendor/glfw)

#include directory path
include_directories(vendor/glfw/include)

#------------------------------#


#--------target--------#

include_directories(include)

add_executable(${PROJECT_NAME} "src/main.cpp")

target_link_libraries(${PROJECT_NAME} glfw)

#----------------------#

#------Copy files------#

#To copy files like DLLs and assets. Here, I copy the compile_commands.json from the build dir, to the source dir
add_custom_target(
    copy-compile-commands ALL
    ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_LIST_DIR}
    )

#----------------------#