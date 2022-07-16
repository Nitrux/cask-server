
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    )

set(mauimanserver_HDRS
    server.h
    modules/background.h
    src/modules/theme.h
    src/modules/screen.h
    )

set(mauimanserver_SRCS
    main.cpp
    server.cpp
    modules/background.cpp
    modules/theme.cpp
    modules/screen.cpp
    )

qt5_add_dbus_adaptor(DBUS_SOURCES modules/org.cask.Power.xml modules/powerserver.h Power)
qt5_add_dbus_adaptor(DBUS_SOURCES modules/org.cask.Screenshot.xml modules/screenshotserver.h Screenshot)
qt5_add_dbus_adaptor(DBUS_SOURCES modules/org.cask.Shell.xml modules/shellserver.h Shell)

set_source_files_properties(${DBUS_SOURCES} PROPERTIES SKIP_AUTOGEN ON)

add_executable(${PROJECT_NAME}

    ${mauimanserver_SRCS}
    ${mauimanserver_HDRS}

    ${DBUS_SOURCES}
)

target_include_directories(${PROJECT_NAME}
    INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/MauiManServer>")

target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR};>")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    MauiMan
    Qt5::Core
    Qt5::DBus
    )

install(TARGETS ${PROJECT_NAME} ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
