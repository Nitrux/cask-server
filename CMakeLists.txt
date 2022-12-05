cmake_minimum_required(VERSION 3.16)

project(CaskServerGroup)

set(CASKSERVER_VERSION 0.6.0)

add_subdirectory(api) #adds mauiman libs
add_subdirectory(server) #adds and installs the dbus service and is a server
