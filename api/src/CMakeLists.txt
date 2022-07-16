
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}

    ${CMAKE_CURRENT_SOURCE_DIR}/modules
    ${CMAKE_CURRENT_BINARY_DIR}/modules
    )

set(caskserver_HDRS
    code/settingsstore.h
    code/modules/backgroundmanager.h
    code/modules/thememanager.h
    code/modules/screenmanager.h
    code/mauimanutils.h
    )

set(caskserver_SRCS
    code/settingsstore.cpp
    code/modules/backgroundmanager.cpp
    code/modules/thememanager.cpp
    code/modules/screenmanager.cpp
    code/mauimanutils.cpp
    )

add_library(${PROJECT_NAME}
    SHARED
    ${caskserver_SRCS}
    ${caskserver_HDRS}
    )

#add_library(MauiMan::MauiMan ALIAS MauiMan)

generate_export_header(${PROJECT_NAME} BASE_NAME CaskServer)

target_include_directories(${PROJECT_NAME}
    INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/CaskServer>")

target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR};>")


target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Core
    Qt5::DBus
    )

install(FILES
    ${caskserver_HDRS}
    ${CMAKE_CURRENT_BINARY_DIR}/caskserver_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/CaskServer
    COMPONENT Devel)

install(TARGETS ${PROJECT_NAME} EXPORT CaskServerTargets ${INSTALL_TARGETS_DEFAULT_ARGS})
