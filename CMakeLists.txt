project(Feather)

MESSAGE("CMAKE_HOST_SYSTEM_NAME ${CMAKE_HOST_SYSTEM_NAME}")

cmake_minimum_required(VERSION 3.25.1)

set(GLUT_ROOT_DIR  "e:\\TEMP\\venders\\freeglut\\include")
set(GLUT_INCLUDE_DIR  "e:\\TEMP\\venders\\freeglut\\include")
set(GLUT_glut_LIBRARY_DEBUG  "e:\\TEMP\\venders\\freeglut\\lib\\x64")
set(GLUT_glut_LIBRARY_RELEASE  "e:\\TEMP\\venders\\freeglut\\lib\\x64")
set(Boost_DIR "e:\\Boost\\boost")

set(DLFCN_WIN32_INCLUDE_DIR  "e:\\TEMP\\venders\\dlfcn-win32\\include")
set(DLFCN_WIN32_LIBRARY_DIR  "e:\\TEMP\\venders\\dlfcn-win32\\lib")
set(DLFCN_WIN32_ROOT_DIR  "e:\\TEMP\\venders\\dlfcn-win32")


find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED)
# find_library(localGlut GLUT NAMES GLUT FreeGlUT 
    # PATH ${GLUT_ROOT_DIR} 
    # "lib\\Release\\x64"
    # "bin\\Release\\x64"
    # DOC
    # "GLUT library")
    
# find_library(localGlut GLUT NAMES GLUT FreeGlUT 
    # PATH ${dlfc-win32_ROOT_DIR} 
    # "lib"
    # "bin"
    # DOC
    # "DLFC-WIN32 library")

set(QT_USE_OPENGL TRUE)

ADD_DEFINITIONS("-D GL_GLEXT_PROTOTYPES")

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# DEBUG VERSION
set(CMAKE_BUILD_TYPE=Debug)
set(CMAKE_CXX_FLAGS "-ggdb -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")
set(CMAKE_CXX_LINK_FLAGS "-ldl")

add_subdirectory(src)
add_subdirectory(assets)