# Install script for directory: /cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Iex

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/dist")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p-build/Iex/libIex.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Iex/IexBaseExc.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Iex/IexMathExc.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Iex/IexThrowErrnoExc.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Iex/IexErrnoExc.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Iex/IexMacros.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Iex/Iex.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Iex/IexNamespace.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Iex/IexExport.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Iex/IexForward.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

