cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#project name
project(yk)

set(MODE "normal" CACHE STRING "Set the mode: normal, headless, or docker")

if(MODE STREQUAL "normal")
    message("Normal mode enabled")
elseif(MODE STREQUAL "headless")
    message("Headless mode enabled")
elseif(MODE STREQUAL "docker")
    message("Docker mode enabled")
else()
    message(FATAL_ERROR "Invalid mode specified: ${MODE}")
endif()

#--------third - party ---------#

if(MODE STREQUAL "normal")
    #root directory path
    add_subdirectory(vendor/glfw)

    #include directory path
    include_directories(vendor/glad/include)
    include_directories(vendor/stb/include)
endif()

#------------------------------#


#--------target--------#

include_directories(include)

set(source_code_basic   "src/yk_file_reader.c" 
                        "src/math/yk_math_common.c" "src/math/yk_math_transform.c" "src/math/yk_math.c" 
                        "src/math/yk_matrix.c" "src/math/yk_vector.c" 
                        )

if(MODE STREQUAL "headless")
    set(source_code_extra "sandbox/main_h.c" "src/yk_app_h.c")
elseif(MODE STREQUAL "docker")
    set(source_code_extra "sandbox/main_docker.c")
elseif(MODE STREQUAL "normal" )
    set(source_code_extra "src/yk_window.c" "src/yk_renderer.c" "src/yk_app.c" "vendor/glad/src/glad.c"
                          "vendor/stb/src/stb_image.c")
endif()

add_library(${PROJECT_NAME} SHARED ${source_code_basic}  ${source_code_extra})
target_include_directories(${PROJECT_NAME} PUBLIC
    "vendor/glad/include"
)


#target_compile_definitions(yk PRIVATE YK_EXPORTS)

if(MODE STREQUAL "normal")
    target_link_libraries(${PROJECT_NAME} glfw)
endif()

if(UNIX)
    target_link_libraries(${PROJECT_NAME} m)
endif()

#----------------------#

#------Copy files------#

#To copy files like DLLs and assets. Here, I copy the compile_commands.json from the build dir, to the source dir
if(MODE STREQUAL "normal")
    add_custom_target(
        copy-compile-commands ALL
        ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_LIST_DIR}
        )
endif()

if(MODE STREQUAL "normal")
    add_custom_target(
        copy-resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/res
            ${CMAKE_BINARY_DIR}/res

    )
endif()
#----------------------#



#temp
add_executable(yk-test sandbox/main.c)
target_link_libraries(yk-test yk)