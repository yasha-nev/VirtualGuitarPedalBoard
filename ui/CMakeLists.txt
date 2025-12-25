cmake_minimum_required(VERSION 4.1.1)

project(vgpUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(vgpUI
    main.cpp
)

qt_add_qml_module(vgpUI
    URI vgpUI
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/UIBasePedal.qml
        qml/UIDistortionPedal.qml
        qml/UIDelayPedal.qml
        qml/CircleSwitch.qml
        qml/js/componentCreation.js

    SOURCES
        src/App.cpp
        src/UIBasePedal.cpp
        src/UIDistortionPedal.cpp
        src/UIDelayPedal.cpp
        include/App.hpp
        include/UIBasePedal.hpp
        include/UIDistortionPedal.hpp
        include/UIDelayPedal.hpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(vgpUI PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appvgp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(vgpUI
    PRIVATE
        Qt6::Quick
        vgp

)

include(GNUInstallDirs)
install(TARGETS vgpUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
