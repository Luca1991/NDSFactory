cmake_minimum_required(VERSION 3.18)

project(NDSFactory)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
else(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(GIT_COMMIT_HASH "")
endif(EXISTS "${CMAKE_SOURCE_DIR}/.git")

configure_file(
  ${CMAKE_SOURCE_DIR}/ui/dialogs/about/revision.h.in
  ${CMAKE_SOURCE_DIR}/ui/dialogs/about/revision.h
)

# Dialogs
file(GLOB_RECURSE DIALOGS_HEADERS ui/dialogs/*.h)
file(GLOB_RECURSE DIALOGS_SOURCES ui/dialogs/*.cpp)
file(GLOB_RECURSE DIALOGS_UIS ui/dialogs/*.ui)

# Tabs
file(GLOB_RECURSE TABS_SOURCES ui/tabs/*.cpp)

# NDSFactory
file(GLOB_RECURSE NDSFACTORY_SOURCES ndsfactory/*.cpp)
file(GLOB_RECURSE NDSFACTORY_HEADERS ndsfactory/*.h)

set(SOURCES
    main.cpp
    ui/mainwindow.cpp
    ${NDSFACTORY_SOURCES}
    ${DIALOGS_SOURCES}
    ${TABS_SOURCES}
)

SET(HEADERS
    ui/mainwindow.h
    ${NDSFACTORY_HEADERS}
    ${DIALOGS_HEADERS}
)

set(FORMS
    ui/mainwindow.ui
    ${DIALOGS_UIS}
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES} ${HEADERS} ${FORMS})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${FORMS})
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS})
endif()

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
