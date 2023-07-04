cmake_minimum_required(VERSION 3.16)

project(CaskServerGroup)

set(CASKSERVER_VERSION 0.6.6)

set(REQUIRED_QT_VERSION 6.4)
set(REQUIRED_KF_VERSION 5.240.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(ECM ${REQUIRED_KF_VERSION} NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

include(GenerateExportHeader)
include(GNUInstallDirs)
include(FeatureSummary)
include(ECMSetupVersion)
include(ECMGenerateQmlTypes)
include(CMakePackageConfigHelpers)
include(KDEPackageAppTemplates)
include(KDECompilerSettings)
include(KDEInstallDirs)
include(KDECMakeSettings)

add_subdirectory(api) #adds mauiman libs
add_subdirectory(server) #adds and installs the dbus service and is a server
