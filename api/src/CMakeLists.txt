
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}

    ${CMAKE_CURRENT_SOURCE_DIR}/modules
    ${CMAKE_CURRENT_BINARY_DIR}/modules)

set(caskserver_HDRS
    caskpower.h
    caskscreenshot.h
    caskchrome.h
    serverutils.h
    screenshotinhibit.h
    settingsstore.h)

set(caskserver_SRCS
    caskpower.cpp
    caskscreenshot.cpp
    caskchrome.cpp
    serverutils.cpp
    screenshotinhibit.cpp
    settingsstore.cpp)

add_library(${PROJECT_NAME}
    SHARED
    ${caskserver_SRCS}
    ${caskserver_HDRS})

generate_export_header(${PROJECT_NAME} BASE_NAME CaskServer)

target_include_directories(${PROJECT_NAME}
    INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/CaskServer>")

target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_BINARY_DIR};>")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Core
    Qt6::DBus)

install(FILES
    ${caskserver_HDRS}
    ${CMAKE_CURRENT_BINARY_DIR}/caskserver_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR}/CaskServer
    COMPONENT Devel)

install(TARGETS ${PROJECT_NAME} EXPORT CaskServerTargets ${INSTALL_TARGETS_DEFAULT_ARGS})
