# -*- cmake -*-

cmake_minimum_required(VERSION 2.8)

set(CMAKE_COLOR_MAKEFILE OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(TCF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tcf-c-core)
set(TCF_APPCLOUD_CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/appcloud-core/agent)
set(NOPOLL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/appcloud-core/nopoll)
set(TCF_LIB_NAME tcf-agent)

if (NOT EXEC_NAME)
 set(EXEC_NAME device)
endif()

if (NOT WIN32)
  if(NOT TCF_OPSYS)
    set(TCF_OPSYS "GNU/Linux")
  endif()
  if(NOT TCF_MACHINE)
    set(TCF_MACHINE "x86_64")
  endif()
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "SunOS")
  set(MULTI_THREADED_COMPILE_FLAGS "-pthreads")
  set(MULTI_THREADED_LINK_LIBS pthread rt)
elseif(APPLE)
  set(MULTI_THREADED_COMPILE_FLAGS "-pthread -D_REENTRANT")
  set(MULTI_THREADED_LINK_FLAGS "")
  set(MULTI_THREADED_LINK_LIBS pthread)
elseif(UNIX)
  set(MULTI_THREADED_COMPILE_FLAGS "-pthread -D_REENTRANT")
  set(MULTI_THREADED_LINK_FLAGS "")
  set(MULTI_THREADED_LINK_LIBS pthread rt)
  set(UUID_LIB_NAME uuid)
elseif(WIN32)
  set(SOCKET_LINK_LIBS ws2_32 iphlpapi)
endif()

include(${NOPOLL_DIR}/nopoll.cmake)
message(STATUS "operating system:" ${TCF_OPSYS})
message(STATUS "machine:" ${TCF_MACHINE})
include_directories(${TCF_APPCLOUD_CORE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/tcf/services/ ${CMAKE_CURRENT_SOURCE_DIR} ${NOPOLL_DIR}/src)

add_subdirectory(${NOPOLL_DIR} ${CMAKE_CURRENT_BINARY_DIR}/nopoll)

if (NOT DEFINED MAIN)
    set(MAIN tcf/main/main.c)
endif()

set (TCF_EXTRA_DIR ${TCF_APPCLOUD_CORE_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
include(${TCF_DIR}/cmake-tcf-lib.txt)

add_executable(${EXEC_NAME} ${SRC} ${MAIN})
if(WIN32)
    target_link_libraries(${TCF_LIB_NAME} version.lib psapi.lib)
endif()
target_link_libraries(${EXEC_NAME} ${TCF_LIB_NAME} ${NOPOLL_LIB_NAME})

