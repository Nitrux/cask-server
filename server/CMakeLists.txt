# Copyright 2018-2020 Camilo Higuita <milo.h@aol.com>
# Copyright 2018-2020 Nitrux Latinoamericana S.C.
#
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.16)

project(CaskServer VERSION ${CASKSERVER_VERSION})

find_package(Qt6 ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE COMPONENTS Core DBus)

add_subdirectory(src)

configure_file(org.cask.Server.service.in
    ${CMAKE_CURRENT_BINARY_DIR}/org.cask.Server.service)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/org.cask.Server.service
    DESTINATION ${KDE_INSTALL_DBUSSERVICEDIR})

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
