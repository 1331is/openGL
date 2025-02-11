cmake_minimum_required(VERSION 3.5)

project(bomberMan VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGL)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
set(PROJECT_SOURCES
        main.cpp
        glview.cpp
        glview.h
        glview.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(bomberMan
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        player.h player.cpp
        map.h map.cpp

    )
else()
    if(ANDROID)
        add_library(bomberMan SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(bomberMan
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Связать с OpenGL и Widgets
target_link_libraries(bomberMan PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL)
target_link_libraries(bomberMan PRIVATE Qt6::OpenGLWidgets)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.bomberMan)
endif()
set_target_properties(bomberMan PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS bomberMan
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(bomberMan)
endif()
