# Install script for directory: /cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p-build/Imath/libImath.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathBoxAlgo.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathBox.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathColorAlgo.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathColor.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathEuler.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathExc.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathExport.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathForward.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathFrame.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathFrustum.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathFrustumTest.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathFun.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathGL.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathGLU.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathHalfLimits.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathInt64.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathInterval.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathLimits.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathLineAlgo.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathLine.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathMath.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathMatrixAlgo.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathMatrix.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathNamespace.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathPlane.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathPlatform.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathQuat.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathRandom.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathRoots.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathShear.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathSphere.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathVecAlgo.h"
    "/cluster/home/jiusun/NoriProjectETHz/build/ext_build/src/IlmBase_p/Imath/ImathVec.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

