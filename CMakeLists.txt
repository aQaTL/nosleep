cmake_minimum_required(VERSION 3.9)

project(nosleep)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(source_dir "${PROJECT_SOURCE_DIR}/src/")
set(lib_dir "${PROJECT_SOURCE_DIR}/lib/")

file(GLOB_RECURSE source_files "${source_dir}/*.cpp")

add_executable(${PROJECT_NAME} ${source_files} src/WindowUtils.hpp src/SleepPrevention.cpp src/SleepPrevention.hpp lib/nuklear/nuklear_gdi.h)
target_include_directories(${PROJECT_NAME} PRIVATE "${source_dir}")

# nuklear
set(nuklear_dir "${lib_dir}/nuklear")
target_include_directories(${PROJECT_NAME} PRIVATE "${nuklear_dir}")

# GLFW
set(glfw_dir "${lib_dir}/glfw")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${glfw_dir}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${glfw_dir}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# GLAD
set(glad_dir "${lib_dir}/glad")
add_library("glad" "${glad_dir}/src/glad.c")
target_include_directories("glad" PRIVATE "${glad_dir}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${glad_dir}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")
