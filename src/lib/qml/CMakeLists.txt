project(feather_qml)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

add_definitions( -DFEATHER_PLATFORM_WINDOWS=1 -DFEATHER_BUILD_DLL=1)

set(GLUT_ROOT_DIR  "e:\\TEMP\\venders\\freeglut")
set(GLUT_INCLUDE_DIR  "e:\\TEMP\\venders\\freeglut\\include")
set(GLUT_glut_LIBRARY_DIR  "e:\\TEMP\\venders\\freeglut\\lib\\x64")
set(Boost_DIR "e:\\Boost\\boost")
set (SPECIAL_BOOST_LIBRARY_DIR "C:/Boost/lib64-msvc-14.2")

set(DLFCN_WIN32_INCLUDE_DIR  "e:\\TEMP\\venders\\dlfcn-win32\\include")
set(DLFCN_WIN32_LIBRARY_DIR  "e:\\TEMP\\venders\\dlfcn-win32\\lib")
set(DLFCN_WIN32_ROOT_DIR  "e:\\TEMP\\venders\\dlfcn-win32")


find_package(OpenGL REQUIRED)
find_package(Boost REQUIRED)
#find_library(localGlut NAMES GLUT FreeGlUT 
#    PATH ${GLUT_ROOT_DIR} 
#    "lib\\Release\\x64"
#    "bin\\Release\\x64"
#    DOC
#    "GLUT library")
#    
#find_library(localDLFCN NAMES DLFCN
#    PATH ${dlfc-win32_ROOT_DIR} 
#    "lib"
#    "bin"
#    DOC
#    "DLFC-WIN32 library")
#
add_definitions( -DFEATHER_PLATFORM_WINDOWS=1 -DFEATHER_BUILD_DLL=1)

ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)

FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Qml REQUIRED)
FIND_PACKAGE(Qt5Quick REQUIRED)
FIND_PACKAGE(Boost COMPONENTS filesystem system REQUIRED)

#SET(QT_USE_QTOPENGL TRUE)

SET(feather_qml_SRCS
    qml_status.cpp
    viewport.cpp

    # qml
    commands.cpp
    curves.cpp
    field_model.cpp
    layer_model.cpp
    tree_model.cpp
    sg_editor.cpp
    qml.cpp
)

SET_SOURCE_FILES_PROPERTIES(${feather_qml_SRCS}
 PROPERTIES
 COMPILE_FLAGS ${CMAKE_CXX_FLAGS} )


INCLUDE_DIRECTORIES(${feather_core_SOURCE_DIR}
    ${feather_plugin_SOURCE_DIR}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Qml_INCLUDE_DIRS}
    ${Qt5Quick_INCLUDE_DIRS}
    ${Qt5Quick_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIR}     
    ${DLFCN_WIN32_INCLUDE_DIR}  
    ${BOOST_INCLUDE_DIR})

LINK_DIRECTORIES(${feather_core_BINARY_DIR}
    ${feather_plugin_BINARY_DIR}
    ${GLUT_glut_LIBRARY_DIR}
    ${DLFCN_WIN32_LIBRARY_DIR}
    ${SPECIAL_BOOST_LIBRARY_DIR}
    )

LINK_LIBRARIES(feather_core feather_plugin )

ADD_DEFINITIONS(${Qt5Widgets_DEFINITIONS}
    ${Qt5Qml_DEFINITIONS}
    ${Qt5Quick_DEFINITIONS}

)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Qml_EXECUTABLE_COMPILE_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Quick_EXECUTABLE_COMPILE_FLAGS}")

ADD_LIBRARY(feather_qml SHARED ${feather_qml_SRCS})

QT5_USE_MODULES(feather_qml Widgets Qml Quick)

SET(feather_qml_LIBS
 ${BOOST_LIBRARIES}
 ${OPENGL_LIBRARIES}
 ${QT5Widgets_LIBRARIES}
 ${QT5Qml_LIBRARIES}
 ${QT5Quick_LIBRARIES}
  )

TARGET_LINK_LIBRARIES(feather_qml ${feather_qml_LIBS} )


SET_TARGET_PROPERTIES(feather_qml
    PROPERTIES
    CMAKE_CXX_STANDARD 11
    CMAKE_CXX_STANDARD_REQUIRED ON
)

SET_TARGET_PROPERTIES(feather_qml
    PROPERTIES
    VERSION 0.01
    SOVERSION 1
)

INSTALL(TARGETS feather_qml
    LIBRARY DESTINATION E:/Feather/lib)

add_subdirectory(shaders)