# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/zlib_p"
  "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/zlib_p-build"
  "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build"
  "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/tmp"
  "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/zlib_p-stamp"
  "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src"
  "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/zlib_p-stamp"
)

set(configSubDirs Debug;Release;MinSizeRel;RelWithDebInfo)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/zlib_p-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/Rongxing/Desktop/ETH/CG/nori/build/ext_build/src/zlib_p-stamp${cfgdir}") # cfgdir has leading slash
endif()
