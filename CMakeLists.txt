project(Feather)

MESSAGE("CMAKE_HOST_SYSTEM_NAME ${CMAKE_HOST_SYSTEM_NAME}")

cmake_minimum_required(VERSION 3.25.1)

set(GLUT_INCLUDE_DIR  "e:\\TEMP\\vender\\freeglut\\include")
set(GLUT_glut_LIBRARY_DEBUG  "e:\\TEMP\\vender\\freeglut\\lib")
set(GLUT_glut_LIBRARY_RELEASE  "e:\\TEMP\\vender\\freeglut\\lib")
set(Boost_DIR "e:\\Boost\\boost")

set(dlfcn-win32_INCLUDE_DIR  "e:\\TEMP\\vender\\dlfcn-win32\\include")
set(dlfcn-win32_LIBRARY_DEBUG  "e:\\TEMP\\vender\\dlfcn-win32\\lib")
set(dlfcn-win32_ROOT_DIR  "e:\\TEMP\\vender\\dlfcn-win32")


find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLUT REQUIRED)
find_package(dlfcn-win32 REQUIRED)

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