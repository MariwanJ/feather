project(feather_plugin)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

set(GLUT_INCLUDE_DIR  "e:/TEMP/venders/freeglut/include")
set(GLUT_glut_LIBRARY_DIR  "e:/TEMP/venders/freeglut/lib/x64")

set(DLFCN_WIN32_INCLUDE_DIR  "e:/TEMP/venders/dlfcn-win32/include")
set(DLFCN_WIN32_LIBRARY_DIR  "e:/TEMP/venders/dlfcn-win32/lib")
set(DLFCN_WIN32_ROOT_DIR  "e:/TEMP/venders/dlfcn-win32")
set(BOOST_INCLUDE_DIR  "c:/Boost")
set (SPECIAL_BOOST_LIBRARY_DIR "C:/Boost/lib64-msvc-14.2")

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
    ${DLFCN_WIN32_INCLUDE_DIR}
    ${BOOST_INCLUDE_DIR}
    ${SPECIAL_BOOST_LIBRARY_DIR})

LINK_DIRECTORIES(${feather_core_BINARY_DIR}
${GLUT_glut_LIBRARY_DIR}
${DLFCN_WIN32_LIBRARY_DIR}
${SPECIAL_BOOST_LIBRARY_DIR}

)

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
    DESTINATION e:/Feather/include)

INSTALL(TARGETS feather_plugin
    LIBRARY DESTINATION e:/Feather/lib)
