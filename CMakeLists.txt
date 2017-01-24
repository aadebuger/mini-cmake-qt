# Reference: http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html
# export CMAKE_PREFIX_PATH=/Users/aadebuger/Qt5.7.1/5.7/clang_64/lib/cmake
project( Qt5Project )
cmake_minimum_required(VERSION 3.0)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Include Qt basic functions
include(QtCommon)

# Basic information about project

project(example VERSION 1.0)

# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()

# Set additional project information
set(COMPANY "Example")
set(COPYRIGHT "Copyright (c) 2014 Vincent Lee. All rights reserved.")
set(IDENTIFIER "com.example.Example")

set(SOURCE_FILES
    src/main.cc
    src/mainwindow.cc
)

add_project_meta(META_FILES_TO_INCLUDE)

set(RESOURCE_FILES example.qrc)

find_package(Qt5Widgets REQUIRED)

include("cmake/Modules/FindGlog.cmake")  
#find_package(lib_glog REQUIRED)  
include_directories(${GLOG_INCLUDE_DIRS})

ADD_SUBDIRECTORY(ext/curlcpp)
INCLUDE_DIRECTORIES(${CURLCPP_SOURCE_DIR}/include)

# source_group("UI Files" FILES ${UI_FILES})

add_executable(${PROJECT_NAME} ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
    ${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
)
target_link_libraries(${PROJECT_NAME} curlcpp)
qt5_use_modules(${PROJECT_NAME} Widgets)
