cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#project name
project(yk)

option(HEADLESS_MODE "Enable headless mode" OFF)

#--------third - party ---------#

if(NOT HEADLESS_MODE)
    #root directory path
    add_subdirectory(vendor/glfw)

    #include directory path
    include_directories(vendor/glad/include)
    include_directories(vendor/stb/include)
endif()

#------------------------------#


#--------target--------#

include_directories(src)
include_directories(src/math)


set(source_code_basic   "sandbox/main.c" "src/yk_file_reader.c" 
                        "src/math/yk_math_common.c" "src/math/yk_math_transform.c" "src/math/yk_math.c" 
                        "src/math/yk_matrix.c" "src/math/yk_vector.c" 
                        )

if(HEADLESS_MODE)
    set(source_code_extra "src/yk_app_h.c")
else()
    set(source_code_extra "src/yk_window.c" "src/yk_renderer.c" "src/yk_app.c" "vendor/glad/src/glad.c"
                        "vendor/stb/src/stb_image.c")
endif()


add_executable(${PROJECT_NAME} ${source_code_basic}  ${source_code_extra})

if(NOT HEADLESS_MODE)
    target_link_libraries(${PROJECT_NAME} glfw)
endif()

#----------------------#

#------Copy files------#

#To copy files like DLLs and assets. Here, I copy the compile_commands.json from the build dir, to the source dir
if(NOT UNIX)
    add_custom_target(
        copy-compile-commands ALL
        ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_LIST_DIR}
        )
endif()

if(NOT HEADLESS_MODE)
    add_custom_target(
        copy-resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/res
            ${CMAKE_BINARY_DIR}/res

    )
endif()
#----------------------#
