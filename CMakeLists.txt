cmake_minimum_required(VERSION 3.18)

project(NDSFactory)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
    main.cpp
    mainwindow.cpp
    ndsfactory.cpp
    aboutdialog.cpp
    unpackertabfunctions.cpp
    unpackertabsignals.cpp
    packertabsignals.cpp
    packertabfunctions.cpp
    fatpatchingtabsignals.cpp
    fatpatchingtabfunctions.cpp
)

SET(HEADERS
    mainwindow.h
    ndsheader.h
    ndsfactory.h
    aboutdialog.h
    fatstruct.h
    crctable.h
)

set(FORMS
    mainwindow.ui
    aboutdialog.ui
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES} ${HEADERS} ${FORMS})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${FORMS})
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS})
endif()

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
