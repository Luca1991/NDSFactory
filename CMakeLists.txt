cmake_minimum_required(VERSION 3.25)

project(NDSFactory)

# Require Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Include sanitizers
include(${CMAKE_SOURCE_DIR}/cmake/sanitizers.cmake)

# Determine the Git commit hash if in a git repository
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
else()
  set(GIT_COMMIT_HASH "")
endif()

# Configure the revision header file
configure_file(
  ${CMAKE_SOURCE_DIR}/ui/dialogs/about/revision.h.in
  ${CMAKE_SOURCE_DIR}/ui/dialogs/about/revision.h
)

# Collect source and header files
## Dialogs
file(GLOB_RECURSE DIALOGS_HEADERS ui/dialogs/*.h)
file(GLOB_RECURSE DIALOGS_SOURCES ui/dialogs/*.cpp)
file(GLOB_RECURSE DIALOGS_UIS ui/dialogs/*.ui)

## Tabs
file(GLOB_RECURSE TABS_HEADERS ui/tabs/*.h)
file(GLOB_RECURSE TABS_SOURCES ui/tabs/*.cpp)

## Models
file(GLOB_RECURSE MODELS_HEADERS ui/models/*.h)
file(GLOB_RECURSE MODELS_SOURCES ui/models/*.cpp)

## Utils
file(GLOB_RECURSE UTILS_HEADERS ui/utils/*.h)

## NDSFactory
file(GLOB_RECURSE NDSFACTORY_SOURCES ndsfactory/*.cpp)
file(GLOB_RECURSE NDSFACTORY_HEADERS ndsfactory/*.h)

set(SOURCES
    main.cpp
    ui/mainwindow.cpp
    ${NDSFACTORY_SOURCES}
    ${DIALOGS_SOURCES}
    ${MODELS_SOURCES}
    ${TABS_SOURCES}
)

SET(HEADERS
    ui/mainwindow.h
    ${NDSFACTORY_HEADERS}
    ${TABS_HEADERS}
    ${MODELS_HEADERS}
    ${DIALOGS_HEADERS}
    ${UTILS_HEADERS}
)

set(FORMS
    ui/mainwindow.ui
    ${DIALOGS_UIS}
)

# Platform-specific executable creation
if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE ndsfactory.icns)
    set(MACOSX_BUNDLE_GUI_IDENTIFIER dev.lucadamico.ndsfactory)
    set(MACOS_ICNS "res/ndsfactory.icns")
    set_source_files_properties(${MACOS_ICNS} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${SOURCES} ${HEADERS} ${FORMS} ${MACOS_ICNS})
elseif(WIN32)
    set(WIN32_RESOURCES "res/resources.rc")
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${FORMS} ${WIN32_RESOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS})
endif()

# Set C++ standard for the target
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

# Enable Qt's automatic features for the target
set_target_properties(${PROJECT_NAME} PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
)

# Add compile options for different compilers
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /WX /W4 /EHsc)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif()

# Link the necessary Qt6 libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
