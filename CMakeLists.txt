cmake_minimum_required(VERSION 3.21)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#project name
project(yk)

#--------third - party ---------#

#root directory path
add_subdirectory(vendor/glfw)

#include directory path
include_directories(vendor/glad/include)
include_directories(vendor/stb/include)

#------------------------------#


#--------target--------#

include_directories(src)
include_directories(src/math)

add_executable(${PROJECT_NAME} "sandbox/main.c" "src/yk_app.c" "src/yk_file_reader.c" "src/yk_window.c" "src/yk_renderer.c" 
                               "src/math/yk_math_common.c"  "src/math/yk_math.c" "src/math/yk_matrix.c"
                                "src/math/yk_vector.c"  
                                "vendor/glad/src/glad.c" "vendor/stb/src/stb_image.c" )

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
    add_custom_target(
        copy-resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/res
            ${CMAKE_BINARY_DIR}/res

    )
#----------------------#
