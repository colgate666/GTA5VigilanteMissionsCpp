add_definitions(-D_USE_MATH_DEFINES)
cmake_minimum_required(VERSION 3.30)
project(VigilanteMissionsCpp)

if(NOT MSVC)
    message(FATAL_ERROR "This project requires MSVC compiler. Please use Visual Studio or set the compiler to MSVC.")
endif()

set(CMAKE_CXX_STANDARD 23)

file(GLOB MENU_BASE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/GTAVMenuBase/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/GTAVMenuBase/*.h"
)

# Create the library target first
add_library(VigilanteMissionsCpp SHARED
        dllmain.cpp
        Blip.hpp
        Blip.cpp
        framework.h
        Music.hpp
        Music.cpp
        Screen.hpp
        Screen.cpp
        Script.hpp
        Script.cpp
        UIScript.hpp
        UIScript.cpp
        RandomMission.h
        RandomMission.cpp
        Utils.h
        MissionPed.h
        MissionPed.cpp
        ${MENU_BASE_SOURCES}
)

set_target_properties(VigilanteMissionsCpp PROPERTIES
        SUFFIX ".asi"
)

# Enable precompiled headers
target_precompile_headers(VigilanteMissionsCpp PRIVATE
        pch.h
)

# Windows-specific settings
add_definitions(-DWIN32 -D_WINDOWS -D_USRDLL)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Add include directories (equivalent to "Additional Include Directories" in VS)
include_directories(
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/inc"
        "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann"
        "${CMAKE_CURRENT_SOURCE_DIR}/simpleini"
        "${CMAKE_CURRENT_SOURCE_DIR}/GTAVMenuBase"
)

# Link against specific .lib files
target_link_libraries(VigilanteMissionsCpp PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/ScriptHookV.lib
)