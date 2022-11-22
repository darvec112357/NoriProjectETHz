# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/apple/Desktop/ETHz/Year 1 Semester 1/Computer Graphics/nori/build/ext_build/src/nanogui_p-build/ext_build/src/glfw_p"
  "/Users/apple/Desktop/ETHz/Year 1 Semester 1/Computer Graphics/nori/build/ext_build/src/nanogui_p-build/ext_build/src/glfw_p-build"
  "/Users/apple/Desktop/ETHz/Year 1 Semester 1/Computer Graphics/nori/build/ext_build/src/nanogui_p-build/ext_build"
  "/Users/apple/Desktop/ETHz/Year 1 Semester 1/Computer Graphics/nori/build/ext_build/src/nanogui_p-build/ext_build/tmp"
  "/Users/apple/Desktop/ETHz/Year 1 Semester 1/Computer Graphics/nori/build/ext_build/src/nanogui_p-build/ext_build/src/glfw_p-stamp"
  "/Users/apple/Desktop/ETHz/Year 1 Semester 1/Computer Graphics/nori/build/ext_build/src/nanogui_p-build/ext_build/src"
  "/Users/apple/Desktop/ETHz/Year 1 Semester 1/Computer Graphics/nori/build/ext_build/src/nanogui_p-build/ext_build/src/glfw_p-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/apple/Desktop/ETHz/Year 1 Semester 1/Computer Graphics/nori/build/ext_build/src/nanogui_p-build/ext_build/src/glfw_p-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/apple/Desktop/ETHz/Year 1 Semester 1/Computer Graphics/nori/build/ext_build/src/nanogui_p-build/ext_build/src/glfw_p-stamp${cfgdir}") # cfgdir has leading slash
endif()
