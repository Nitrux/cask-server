
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})

set(server_HDRS
    server.h
    modules/powerserver.h
    modules/screenshotserver.h)

set(server_SRCS
    main.cpp
    server.cpp
    modules/powerserver.cpp
    modules/screenshotserver.cpp
    modules/chromeserver.cpp)

qt_add_dbus_adaptor(DBUS_SOURCES modules/org.cask.Power.xml modules/powerserver.h PowerServer)
qt_add_dbus_adaptor(DBUS_SOURCES modules/org.cask.Screenshot.xml modules/screenshotserver.h ScreenshotServer)
qt_add_dbus_adaptor(DBUS_SOURCES modules/org.cask.Chrome.xml modules/chromeserver.h ChromeServer)

set_source_files_properties(${DBUS_SOURCES} PROPERTIES SKIP_AUTOGEN ON)

add_executable(${PROJECT_NAME}

    ${server_SRCS}
    ${server_HDRS}

    ${DBUS_SOURCES})

#target_include_directories(${PROJECT_NAME} INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/CaskServer>")

target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR};>")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    CaskServerLib
    Qt6::Core
    Qt6::DBus
    )

install(TARGETS ${PROJECT_NAME} ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
