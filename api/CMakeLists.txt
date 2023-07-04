# Copyright 2018-2020 Camilo Higuita <milo.h@aol.com>
# Copyright 2018-2020 Nitrux Latinoamericana S.C.
#
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.16)

project(CaskServerLib VERSION ${CASKSERVER_VERSION})

##CMAKE PARTS
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/CaskServer")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/CaskServerConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/CaskServerConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
    PATH_VARS CMAKE_INSTALL_PREFIX)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX CaskServer
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/caskserver_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/CaskServerConfigVersion.cmake"
    SOVERSION ${PROJECT_VERSION_MAJOR})

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/CaskServerConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/CaskServerConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel)

install(EXPORT CaskServerTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE CaskServerTargets.cmake
    NAMESPACE CaskServer::)

find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS Core DBus)

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
