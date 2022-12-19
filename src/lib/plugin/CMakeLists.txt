project(feather_plugin)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

set(BOOST_INCLUDE_DIR  "c:/Boost")

set(GLUT_INCLUDE_DIR  "e:\\TEMP\\venders\\freeglut\\include")
set(GLUT_glut_LIBRARY_DEBUG  "e:\\TEMP\\venders\\freeglut\\lib")
set(GLUT_glut_LIBRARY_RELEASE  "e:\\TEMP\\venders\\freeglut\\lib")
set(Boost_DIR "e:\\Boost\\boost")

set(dlfcn-win32_INCLUDE_DIR  "e:\\TEMP\\venders\\dlfcn-win32\\include")
set(dlfcn-win32_LIBRARY_DEBUG  "e:\\TEMP\\venders\\dlfcn-win32\\lib")
set(dlfcn-win32_ROOT_DIR  "e:\\TEMP\\venders\\dlfcn-win32")
set (BOOST_INCLUDE_DIR ""c:/Boost")
set (BOOST_INCLUDE_DIR ""c:/Boost")
FIND_PACKAGE(Boost COMPONENTS filesystem system REQUIRED)


SET(feather_plugin_SRCS
    core_access.cpp
    plugin.cpp
)
add_definitions( -DFEATHER_PLATFORM_WINDOWS=1 -DFEATHER_BUILD_DLL=1)

SET_SOURCE_FILES_PROPERTIES(${feather_plugin_SRCS}
 PROPERTIES
 COMPILE_FLAGS ${CMAKE_CXX_FLAGS} )

INCLUDE_DIRECTORIES(
    ${feather_core_SOURCE_DIR}
    ${GLUT_INCLUDE_DIR}
    ${dlfcn-win32_INCLUDE_DIR}
    ${BOOST_INCLUDE_DIR}
)

LINK_DIRECTORIES(${feather_core_BINARY_DIR})

LINK_LIBRARIES(${feather_core})

ADD_LIBRARY(feather_plugin SHARED ${feather_plugin_SRCS})

SET_TARGET_PROPERTIES(feather_plugin
    PROPERTIES
    CMAKE_CXX_STANDARD 14
    CMAKE_CXX_STANDARD_REQUIRED ON
)

SET_TARGET_PROPERTIES(feather_plugin
    PROPERTIES
    VERSION 0.01
    SOVERSION 1
)

SET(feather_plugin_HDRS
    plugin.hpp
)

INSTALL(FILES ${feather_plugin_HDRS}
    DESTINATION /usr/include/feather)

INSTALL(TARGETS feather_plugin
    LIBRARY DESTINATION /usr/lib64/feather)
