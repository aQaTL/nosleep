cmake_minimum_required(VERSION 3.9)

project(nosleep)

set(CMAKE_CXX_STANDARD 17)

set(source_dir "${PROJECT_SOURCE_DIR}/src/")
set(lib_dir "${PROJECT_SOURCE_DIR}/lib/")

file(GLOB_RECURSE source_files "${source_dir}/*.cpp")

add_executable(${PROJECT_NAME} ${source_files})
target_include_directories(${PROJECT_NAME} PRIVATE "${source_dir}")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	#Always use Release build type with msvc
	set(CMAKE_BUILD_TYPE Release)
else ()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Os -fno-exceptions -ffunction-sections -fdata-sections")
	set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

	if (WIN32)
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -Wl,-emainCRTStartup,-subsystem,windows")
		target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++)
	endif ()
	if (CMAKE_BUILD_TYPE EQUAL "RELEASE")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--gc-sections")
	endif ()
endif ()

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
