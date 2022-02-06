
# CMakeList.txt : CMake project for binary_scene, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

if(${ARCH} STREQUAL "x64")
	message(STATUS "Using x64")
	set(ARCH_X64 TRUE)
elseif(${ARCH} STREQUAL "x86")
	message(STATUS "Using x86")
	set(ARCH_X86 TRUE)
else()
	message(STATUS "Unknown linker flags: ${CMAKE_EXE_LINKER_FLAGS}")
endif() # ARCH

project ("binary_scene")

# Add source to this project's executable.
add_executable (binary_scene "binary_scene.cpp"  "program.cpp" "assign_unique_index.hpp" "assign_unique_index.cpp" "is_match.hpp" "is_match.cpp")

if (DEFINED ARCH_X64)
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "binary_data_x64")
else()
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "binary_data_x86")
endif() # ARCH_X64

set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")

message(STATUS "Lib path: ${LIB_DIR}")

if(DEFINED ARCH_X64)
	set(SOIL2_PATH "${LIB_DIR}/soil2/SOIL2-master/make/windows/x64/debug/")
elseif(DEFINED ARCH_X86)
	set(SOIL2_PATH "${LIB_DIR}/soil2/SOIL2-master/make/windows/x86/debug/")
else()
	message(FATAL_ERROR "***Error: No environment selected***")
endif() # ARCH

target_compile_features(binary_scene PUBLIC cxx_std_20)

target_compile_definitions(binary_scene
	PRIVATE X_WINDOWS
	)

if(DEFINED ARCH_X64)
	target_compile_definitions(binary_scene
		PRIVATE ARCH_X64
		)
elseif(DEFINED ARCH_X86)
	target_compile_definitions(binary_scene
		PRIVATE ARCH_X86
		)
else()
	message(FATAL_ERROR "***Error: No architecture specified***")
endif() # ARCH

include_directories("${LIB_DIR}/")

find_library(
	soil2
	NAMES soil2-debug soil2
	PATHS ${SOIL2_PATH}
	NO_DEFAULT_PATH
	NO_CMAKE_ENVIRONMENT_PATH
	NO_SYSTEM_ENVIRONMENT_PATH
)
message(STATUS "SOIL2 status: ${soil2}")
