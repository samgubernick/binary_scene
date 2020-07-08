
# CMakeList.txt : CMake project for binary_scene, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

if(${CMAKE_EXE_LINKER_FLAGS} STREQUAL /machine:x64)
	set(ARCH_X64 TRUE)
elseif(${CMAKE_EXE_LINKER_FLAGS} STREQUAL /machine:X86)
	set(ARCH_X86 TRUE)
endif()

project ("binary_scene")

# Add source to this project's executable.
add_executable (binary_scene "binary_scene.cpp"  "texture.hpp" "scene.hpp" "scenes.hpp")

set(LIB_DIR "${CMAKE_SOURCE_DIR}/libs")

set(BOOST_ROOT ${LIB_DIR}/boost/1_73_0)
set(BOOST_INCLUDEDIR ${LIB_DIR}/boost/1_73_0/boost)

message(STATUS "Lib path: ${LIB_DIR}")

if(DEFINED ARCH_X64)
    if(WIN32)
        message(STATUS "Setting Boost variables for Windows")
	    set(BOOST_LIBRARYDIR ${LIB_DIR}/boost/1_73_0/stage/x64/lib)
	    set(Boost_DIR ${LIB_DIR}/boost/1_73_0/stage/x64/lib/cmake/Boost-1.73.0)
	    set(LOCAL_BOOST_LIB "${LIB_DIR}/boost/1_73_0/stage/x64/lib/cmake/Boost-1.73.0")
    endif() # WIN32
elseif(DEFINED ARCH_X86)
    if(WIN32)
        message(STATUS "Setting Boost variables for Windows")

        set(BOOST_LIBRARYDIR ${LIB_DIR}/boost/1_73_0/stage/x86/lib)
        set(Boost_DIR ${LIB_DIR}/boost/1_73_0/stage/x86/lib/cmake/Boost-1.73.0)
        set(LOCAL_BOOST_LIB "${LIB_DIR}/boost/1_73_0/stage/x86/lib/cmake/Boost-1.73.0")
    else()
        message(STATUS "***Error: No environment selected***")
    endif() # WIN32
endif() # ARCH

set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS OFF)
if(DEFINED BUILD_DEBUG)
	message(STATUS "Debug environment is selected")
	set(Boost_USE_DEBUG_RUNTIME ON)
	set(Boost_USE_DEBUG_LIBS ON)
	#set(Boost_DEBUG ON)
	set(Boost_USE_RELEASE_LIBS OFF)
elseif(DEFINED BUILD_RELEASE)
	message(STATUS "Release environment is selected")
	set(Boost_USE_DEBUG_RUNTIME OFF)
	set(Boost_USE_DEBUG_LIBS OFF)
	set(Boost_DEBUG OFF)
	set(Boost_USE_RELEASE_LIBS ON)
else()
	message(STATUS "***Error: No environment selected***")
endif() # debug

if(DEFINED ARCH_X64)
	set(Boost_ARCHITECTURE -x64)
elseif(DEFINED ARCH_X86)
	set(Boost_ARCHITECTURE -x86)
endif() # ARCH


#message(FATAL_ERROR "Local Boost lib path: ${LOCAL_BOOST_LIB}")
find_package(
	Boost REQUIRED COMPONENTS serialization thread
	PATHS ${LOCAL_BOOST_LIB}
)
message(STATUS "Boost: ${Boost_LIBRARIES}, version: ${Boost_VERSION}, include: ${Boost_INCLUDE_DIRS}")

target_compile_features(binary_scene PUBLIC cxx_std_20)

target_compile_definitions(binary_scene
	PRIVATE X_WINDOWS
	PRIVATE BOOST_ALL_DYN_LINK
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
	message(STATUS "***Error: No architecture specified***")
endif() # ARCH

target_link_libraries(binary_scene PUBLIC ${Boost_LIBRARIES})
