# Install script for directory: C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p-build/Imath/Debug/Imath.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p-build/Imath/Release/Imath.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p-build/Imath/MinSizeRel/Imath.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p-build/Imath/RelWithDebInfo/Imath.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OpenEXR" TYPE FILE FILES
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathBoxAlgo.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathBox.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathColorAlgo.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathColor.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathEuler.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathExc.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathExport.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathForward.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathFrame.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathFrustum.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathFrustumTest.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathFun.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathGL.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathGLU.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathHalfLimits.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathInt64.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathInterval.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathLimits.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathLineAlgo.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathLine.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathMath.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathMatrixAlgo.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathMatrix.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathNamespace.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathPlane.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathPlatform.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathQuat.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathRandom.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathRoots.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathShear.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathSphere.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathVecAlgo.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/IlmBase_p/Imath/ImathVec.h"
    )
endif()

