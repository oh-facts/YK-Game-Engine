cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#project name
project(yk)

#--------third - party ---------#


add_subdirectory(vendor/glfw)

#include directory path
include_directories(vendor/glad/include)
include_directories(vendor/stb/include)


#------------------------------#


#--------target--------#

include_directories(include)
include_directories(include/yk/data_structures)

set(yk_src_math    "src/math/yk_math_common.c" "src/math/yk_math_transform.c" "src/math/yk_math.c" 
                    "src/math/yk_matrix.c"
)

set(yk_src_rendering    "vendor/glad/src/glad.c" "vendor/stb/src/stb_image.c" "src/rendering/yk_shader.c"
                        "src/rendering/yk_camera2d.c" "src/rendering/yk_renderer2d.c" "src/rendering/yk_texture.c" 
                        "src/rendering/yk_color.c" "src/yk_window.c"
)

set(yk_src_core     "src/yk_file_reader.c" "src/math/yk_vector.c" "src/data_structures/yk_yektor.c" "src/ecs/yk_ecs.c"
                    "src/physics/yk_physics.c" "src/yk_input.c"
)


add_library(${PROJECT_NAME} ${yk_src_math}  ${yk_src_rendering} ${yk_src_core})

target_include_directories(${PROJECT_NAME} PUBLIC
    "vendor/glad/include"
    "vendor/stb/include"
)


target_link_libraries(${PROJECT_NAME} glfw)

if(UNIX)
    target_link_libraries(${PROJECT_NAME} m)
endif()

#----------------------#

#------Copy files------#

#To copy files like DLLs and assets. Here, I copy the compile_commands.json from the build dir, to the source dir

add_custom_target(
    yk_copy-compile-commands ALL
    ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_LIST_DIR}
)


add_custom_target(
     yk_copy-resources ALL
     COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/yk-res
        ${CMAKE_BINARY_DIR}/yk-res
)


    
add_custom_target(
    yk_copy-resources-example ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/yk-res
        ${CMAKE_CURRENT_BINARY_DIR}/yk-res
)


#----------------------#



#temp
#add_executable(yk-test sandbox/main.c)
add_executable(yk-test sandbox/main2.c)

target_link_libraries(yk-test yk)