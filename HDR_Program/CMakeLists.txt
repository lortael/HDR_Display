project(HDR_display)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

#find_package(Qt4 REQUIRED)
#SET(QT_USE_QTXML TRUE)
#include(${QT_USE_FILE})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Xml REQUIRED)
FIND_PACKAGE(Qt5OpenGL REQUIRED)

find_package(OpenGL REQUIRED)
find_package(Eigen3 "3.0.3" REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories( ${QT_INCLUDE_DIR} )
include_directories( ${EIGEN3_INCLUDE_DIR} )
include_directories( ${PROJECT_SOURCE_DIR}/src )
#include_directories( ${PROJECT_SOURCE_DIR}/lib3ds )

add_definitions(-DHDR_DIR="${PROJECT_SOURCE_DIR}")
add_definitions(-DEIGEN_DONT_ALIGN_STATICALLY)

# the list of source files
set(HDR_SRCS src/cpp/main.cpp src/headers/DisplayManager.h src/cpp/DisplayManager.cpp 
	     src/headers/DisplayDevice.h src/cpp/DisplayDevice.cpp src/headers/HDRProcess.h 
	     src/cpp/HDRProcess.cpp src/headers/FrontPanel.h src/cpp/FrontPanel.cpp 
	     src/headers/BackPanel.h src/cpp/BackPanel.cpp src/headers/ImageManager.h 
	     src/cpp/ImageManager.cpp src/headers/Correction.h src/cpp/Correction.cpp 
	     src/headers/Window.h src/cpp/Window.cpp src/headers/GLRender.h src/cpp/GLRender.cpp 
	     src/headers/ImageIO.h src/cpp/ImageIO.cpp
              ${APPLE_WORKAROUND_SRCS})

#qt4_automoc(${sire_SRCS})

add_executable(HDR_displaying ${HDR_SRCS})

target_link_libraries(HDR_displaying
    Qt5::Widgets Qt5::Xml Qt5::OpenGL
#  ${QT_QTCORE_LIBRARY}    ${QT_QTGUI_LIBRARY}  ${QT_QTXML_LIBRARY}
#  ${QT_QTOPENGL_LIBRARY}
    ${OPENGL_LIBRARIES}
)

