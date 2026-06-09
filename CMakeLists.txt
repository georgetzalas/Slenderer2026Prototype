cmake_minimum_required(VERSION 3.20)
project(Slenderer2026Prototype LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    src/main.cpp
    src/*/*.cpp
    src/*/*.c
)

add_library(stb_image STATIC vendors/stb/stb_image.c)
target_include_directories(stb_image PUBLIC vendors/stb)

add_library(glad STATIC vendors/glad/src/glad.c)
target_include_directories(glad PUBLIC vendors/glad/include)

add_subdirectory(vendors/glfw)

set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)   
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory(vendors/assimp)

set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory(vendors/glm)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/vendors/stb
    ${CMAKE_SOURCE_DIR}/vendors/glad/include
    ${CMAKE_SOURCE_DIR}/vendors/glfw/include
    ${CMAKE_SOURCE_DIR}/vendors/assimp/include
    ${CMAKE_SOURCE_DIR}/vendors/glm/glm
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    glad
    stb_image
    assimp
    glm
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(OPENGL_LIBRARY OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${OPENGL_LIBRARY}
    )
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        OpenGL::GL
        dl
        pthread
        X11
    )
endif()