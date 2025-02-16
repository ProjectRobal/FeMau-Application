cmake_minimum_required(VERSION 3.16)

project(FeMauApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Widgets SerialPort Charts)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appFeMauApp
    main.cpp
)

qt_add_qml_module(appFeMauApp
    URI FeMauApp
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES serialinterface.h serialinterface.cpp
        SOURCES console.h console.cpp
        SOURCES pid.h
        SOURCES chart.h chart.cpp
        SOURCES common.h common.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appFeMauApp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appFeMauApp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appFeMauApp
    PRIVATE Qt6::Quick Qt6::Widgets Qt6::SerialPort Qt6::Charts
)

include(GNUInstallDirs)
install(TARGETS appFeMauApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
