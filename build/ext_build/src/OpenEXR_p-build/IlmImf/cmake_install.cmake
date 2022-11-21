# Install script for directory: C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf

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
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/lib/IlmImf.lib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p-build/IlmImf/Debug/IlmImf.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/lib/IlmImf.lib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p-build/IlmImf/Release/IlmImf.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/lib/IlmImf.lib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p-build/IlmImf/MinSizeRel/IlmImf.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/lib/IlmImf.lib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
      message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    file(INSTALL DESTINATION "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p-build/IlmImf/RelWithDebInfo/IlmImf.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfForward.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfExport.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfBoxAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfCRgbaFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfChannelList.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfChannelListAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfCompressionAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfDoubleAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfFloatAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfFrameBuffer.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfHeader.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfIO.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfInputFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfIntAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfLineOrderAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfMatrixAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfOpaqueAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfOutputFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfRgbaFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfStringAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfVecAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfHuf.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfWav.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfLut.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfArray.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfCompression.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfLineOrder.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfName.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfPixelType.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfVersion.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfXdr.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfConvert.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfPreviewImage.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfPreviewImageAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfChromaticities.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfChromaticitiesAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfKeyCode.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfKeyCodeAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfTimeCode.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfTimeCodeAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfRational.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfRationalAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfFramesPerSecond.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfStandardAttributes.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfEnvmap.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfEnvmapAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfInt64.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfRgba.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfTileDescription.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfTileDescriptionAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfTiledInputFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfTiledOutputFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfTiledRgbaFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfRgbaYca.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfTestFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfThreading.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfB44Compressor.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfStringVectorAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfMultiView.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfAcesFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfMultiPartOutputFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfGenericOutputFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfMultiPartInputFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfGenericInputFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfPartType.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfPartHelper.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfOutputPart.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfTiledOutputPart.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfInputPart.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfTiledInputPart.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfDeepScanLineOutputFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfDeepScanLineOutputPart.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfDeepScanLineInputFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfDeepScanLineInputPart.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfDeepTiledInputFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfDeepTiledInputPart.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfDeepTiledOutputFile.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfDeepTiledOutputPart.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfDeepFrameBuffer.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfDeepCompositing.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfCompositeDeepScanLine.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfNamespace.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfMisc.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfDeepImageState.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfDeepImageStateAttribute.h;C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR/ImfFloatVectorAttribute.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/dist/include/OpenEXR" TYPE FILE FILES
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfForward.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfExport.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfBoxAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfCRgbaFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfChannelList.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfChannelListAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfCompressionAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDoubleAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfFloatAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfFrameBuffer.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfHeader.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfIO.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfInputFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfIntAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfLineOrderAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfMatrixAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfOpaqueAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfOutputFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfRgbaFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfStringAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfVecAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfHuf.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfWav.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfLut.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfArray.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfCompression.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfLineOrder.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfName.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfPixelType.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfVersion.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfXdr.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfConvert.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfPreviewImage.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfPreviewImageAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfChromaticities.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfChromaticitiesAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfKeyCode.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfKeyCodeAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTimeCode.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTimeCodeAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfRational.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfRationalAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfFramesPerSecond.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfStandardAttributes.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfEnvmap.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfEnvmapAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfInt64.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfRgba.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTileDescription.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTileDescriptionAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTiledInputFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTiledOutputFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTiledRgbaFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfRgbaYca.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTestFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfThreading.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfB44Compressor.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfStringVectorAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfMultiView.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfAcesFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfMultiPartOutputFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfGenericOutputFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfMultiPartInputFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfGenericInputFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfPartType.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfPartHelper.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfOutputPart.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTiledOutputPart.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfInputPart.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfTiledInputPart.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepScanLineOutputFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepScanLineOutputPart.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepScanLineInputFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepScanLineInputPart.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepTiledInputFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepTiledInputPart.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepTiledOutputFile.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepTiledOutputPart.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepFrameBuffer.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepCompositing.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfCompositeDeepScanLine.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfNamespace.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfMisc.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepImageState.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfDeepImageStateAttribute.h"
    "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/OpenEXR_p/IlmImf/ImfFloatVectorAttribute.h"
    )
endif()

