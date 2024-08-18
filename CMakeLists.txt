cmake_minimum_required(VERSION 3.5)

project(Cinema-Sansaar VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Change the build directory name
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/Cinema-Sansaar)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Network)

# Database is located in the 'Database' subfolder
set(DATABASE_PATH "Database/Data.db")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${DATABASE_PATH}
    ${CMAKE_CURRENT_BINARY_DIR}/${DATABASE_PATH}
    COPYONLY
)

add_definitions(-DDATABASE_PATH="${DATABASE_PATH}")

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp	mainwindow.h	mainwindow.ui
        database.h database.cpp #file for function for database interaction
        verification.h verification.cpp verification.ui #verification dialog box
        change_pass.h change_pass.cpp change_pass.ui #change password
        dashboard.h dashboard.cpp dashboard.ui #movie selection for user
        sinister.h sinister.cpp sinister.ui
        mirzapur.h mirzapur.cpp mirzapur.ui
        sanju.h sanju.cpp sanju.ui
        mahajatra.h mahajatra.cpp mahajatra.ui
        kabir.h kabir.cpp kabir.ui
        thor.h thor.cpp thor.ui
        harry.h harry.cpp harry.ui
        Posters.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Cinema-Sansaar
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Cinema-Sansaar SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Cinema-Sansaar
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Cinema-Sansaar PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Network)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Cinema-Sansaar)
endif()
set_target_properties(Cinema-Sansaar PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Cinema-Sansaar
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Cinema-Sansaar)
endif()
