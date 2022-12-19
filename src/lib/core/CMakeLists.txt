project(feather_core)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)

set(BOOST_INCLUDE_DIR  "c:/Boost")


set(GLUT_INCLUDE_DIR  "e:\\TEMP\\venders\\freeglut\\include")
set(GLUT_glut_LIBRARY_DEBUG  "e:\\TEMP\\venders\\freeglut\\lib")
set(GLUT_glut_LIBRARY_RELEASE  "e:\\TEMP\\venders\\freeglut\\lib")
set(Boost_DIR "e:\\Boost\\boost")

set(dlfcn-win32_INCLUDE_DIR  "e:\\TEMP\\venders\\dlfcn-win32\\include")
set(dlfcn-win32_LIBRARY_DEBUG  "e:\\TEMP\\venders\\dlfcn-win32\\lib")
set(dlfcn-win32_ROOT_DIR  "e:\\TEMP\\venders\\dlfcn-win32")


FIND_PACKAGE(Boost COMPONENTS filesystem system REQUIRED)
FIND_PACKAGE(Qt5OpenGL REQUIRED)
FIND_PACKAGE(GLUT REQUIRED)
FIND_PACKAGE(dlfcn-win32 REQUIRED)

SET(QT_USE_QTOPENGL TRUE)

SET(feather_core_SRCS
    tools.cpp
    pluginmanager.cpp
)
add_definitions( -DFEATHER_PLATFORM_WINDOWS=1 -DFEATHER_BUILD_DLL=1)
SET_SOURCE_FILES_PROPERTIES(${feather_core_SRCS}
 PROPERTIES
 COMPILE_FLAGS ${CMAKE_CXX_FLAGS} )

INCLUDE_DIRECTORIES(${BOOST_INCLUDE_DIRS} 
        ${GLUT_INCLUDE_DIR}
        ${dlfcn-win32_INCLUDE_DIR}
            ${QtOpenGL_INCLUDE_DIRS}
            ${BOOST_INCLUDE_DIR})

SET(feather_core_LIBS
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY})

ADD_LIBRARY(feather_core SHARED ${feather_core_SRCS})

QT5_USE_MODULES(feather_core OpenGL)

TARGET_LINK_LIBRARIES(feather_core ${feather_core_LIBS}  ${CMAKE_DL_LIBS})


SET_TARGET_PROPERTIES(feather_core
    PROPERTIES
    CMAKE_CXX_STANDARD 11
    CMAKE_CXX_STANDARD_REQUIRED ON
)

SET_TARGET_PROPERTIES(feather_core
    PROPERTIES
    VERSION 0.01
    SOVERSION 1
)

SET(feather_core_HDRS
    deps.hpp
    types.hpp
    singleton.hpp
    scenegraph.hpp
    tools.hpp
    pluginmanager.hpp
    types.hpp
    state.hpp
    status.hpp
    parameter.hpp
    command.hpp
    curve.hpp
    field.hpp
    node.hpp
    data.hpp
    selection.hpp
    object.hpp
    camera.hpp
    light.hpp
    texture.hpp
    shader.hpp
    draw.hpp   
    gl.hpp
)

INSTALL(FILES ${feather_core_HDRS}
    DESTINATION E:/Feather/Include)

INSTALL(TARGETS feather_core
    LIBRARY DESTINATION E:/Feather/lib)
