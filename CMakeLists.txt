cmake_minimum_required(VERSION 3.28.3)
cmake_policy(SET CMP0124 NEW) # https://cmake.org/cmake/help/latest/policy/CMP0124.html#policy:CMP0124
include(FetchContent)

project(game VERSION 0.0.1 LANGUAGES CXX)
add_executable(${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Change this to change build type: https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#build-configurations
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_BUILD_TYPE "Release")
set(GAME_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(GAME_INCLUDE_PATHS "")
set(GAME_LIBRARIES "")
set(GAME_DEFINITIONS "")

list(APPEND GAME_INCLUDE_PATHS "${GAME_ROOT}/include")


macro(game_add_dependency name lib_name repo_url tag_hash)
FetchContent_Declare(
    ${name}
    GIT_REPOSITORY ${repo_url}
    GIT_TAG ${tag_hash})

FetchContent_MakeAvailable(${name})
FetchContent_GetProperties(${name} SOURCE_DIR "${name}_SOURCE_DIR" BINARY_DIR "${name}_BINARY_DIR" POPULATED "${name}_POPULATED")

list(APPEND GAME_INCLUDE_PATHS "${${name}_SOURCE_DIR}/include")
list(APPEND GAME_LIBRARIES ${lib_name})
endmacro()

macro(game_add_sources)
    file(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
    target_sources(${PROJECT_NAME} PRIVATE ${files})
endmacro()


# Use: https://api.github.com/repos/"user"/"repo"/tags
# To get the tag hash
# Try disabling the test, install targets for faster build times
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_UNINSTALL OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
game_add_dependency(SDL3 SDL3::SDL3 https://github.com/libsdl-org/SDL.git badbf8da4ee72b3ef599c721ffc9899e8d7c8d90)


target_link_libraries(${PROJECT_NAME} PRIVATE ${GAME_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${GAME_INCLUDE_PATHS})
target_compile_options(${PROJECT_NAME} PRIVATE "-Wall" "-Wextra" "-Wpedantic" "-O3")
target_compile_definitions(${PROJECT_NAME} PRIVATE ${GAME_DEFINITIONS})

message(STATUS "\nInclude paths:")
foreach(path ${GAME_INCLUDE_PATHS})
    message(STATUS "${path}")
endforeach()

message(STATUS "\nLibraries:")
foreach(lib ${GAME_LIBRARIES})
    message(STATUS "${lib}")
endforeach()

# TODO: Please refactor this
target_sources(${PROJECT_NAME} PRIVATE "${GAME_ROOT}/main.cpp")
add_subdirectory("${GAME_ROOT}/src")