# Copyright 2018-2020 Camilo Higuita <milo.h@aol.com>
# Copyright 2018-2020 Nitrux Latinoamericana S.C.
#
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.16)

set(KF5_VERSION "5.70.0")
set(REQUIRED_QT_VERSION 5.15.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(AUTOMOC_MOC_OPTIONS -Muri=org.cask.server)

project(CaskServerLib VERSION ${CASKSERVER_VERSION})

find_package(ECM ${KF5_VERSION} NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(GNUInstallDirs)
include(FeatureSummary)
include(ECMPoQmTools)
include(ECMSetupVersion)
include(ECMGenerateQmlTypes)
include(CMakePackageConfigHelpers)
include(KDEPackageAppTemplates)
include(KDECompilerSettings)
include(KDEInstallDirs)
include(KDECMakeSettings)

##CMAKE PARTS
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/CaskServer")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/CaskServerConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/CaskServerConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    PATH_VARS KF5_INCLUDE_INSTALL_DIR CMAKE_INSTALL_PREFIX
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/CaskServerConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/CaskServerConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT CaskServerTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE CaskServerTargets.cmake
    NAMESPACE CaskServer::)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX CaskServer
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/caskserver_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/CaskServerConfigVersion.cmake"
    SOVERSION ${PROJECT_VERSION_MAJOR}
    )

find_package(Qt5 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS Core DBus)

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
