cmake_minimum_required(VERSION 3.0.0)

project(touchegg)
set(MAJOR_VERSION "2")
set(MINOR_VERSION "0")
set(PATCH_VERSION "0")
add_definitions(-D_VERSION="v${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

# In debug mode check code style issues
if(CMAKE_BUILD_TYPE MATCHES Debug)
  include(./cmake/check-code-style.cmake)
endif()

find_package(Threads REQUIRED) # Required to use std threads
find_package(Libudev REQUIRED)
find_package(Libinput REQUIRED)
find_package(PugiXML REQUIRED)
find_package(Cairo REQUIRED)
find_package(X11 REQUIRED)
find_package(XTest REQUIRED)
find_package(Xrandr REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE SOURCE_FILES RELATIVE ${PROJECT_SOURCE_DIR} src/*.h src/*.cpp)

add_executable(touchegg ${SOURCE_FILES})
target_include_directories(touchegg PUBLIC
  ${LIBUDEV_INCLUDE_DIRS}
  ${LIBINPUT_INCLUDE_DIRS}
  ${PUGIXML_INCLUDE_DIRS}
  ${CAIRO_INCLUDE_DIRS}
  ${X11_INCLUDE_DIRS}
  ${XTEST_INCLUDE_DIRS}
  ${XRANDR_INCLUDE_DIRS}
)
target_link_libraries(touchegg
  stdc++fs # std::filesystem
  Threads::Threads # std::thread
  ${LIBUDEV_LIBRARIES}
  ${LIBINPUT_LIBRARIES}
  ${PUGIXML_LIBRARIES}
  ${CAIRO_LIBRARIES}
  ${X11_LIBRARIES}
  ${XTEST_LIBRARIES}
  ${XRANDR_LIBRARIES}
)


# Installation
# https://cmake.org/cmake/help/v3.12/module/CPack.html
# https://cmake.org/cmake/help/v3.6/module/CPackDeb.html
# https://cmake.org/cmake/help/v3.7/module/CPackRPM.html
set(CPACK_PACKAGE_NAME touchegg)
set(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/JoseExposito/touchegg")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Multi-touch gesture recognizer")
set(CPACK_PACKAGE_DESCRIPTION "Multi-touch gesture recognizer.
 Touchégg is an app that runs in the background and transform the gestures you make in your touchpad into visible actions in your desktop.
 For example, you can swipe up with 3 fingers to maximize a window or swipe left with 4 finger to switch to the next desktop.")
set(CMAKE_INSTALL_PREFIX "/")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})

install(FILES ${PROJECT_SOURCE_DIR}/installation/touchegg.conf DESTINATION usr/share/touchegg)
install(FILES ${PROJECT_SOURCE_DIR}/installation/touchegg.service DESTINATION lib/systemd/system)
install(PROGRAMS ${CMAKE_BINARY_DIR}/touchegg DESTINATION usr/bin)

# DEB package
# Run: $ cpack -G DEB
set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "José Expósito <jose.exposito89@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "${CPACK_PACKAGE_HOMEPAGE_URL}")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "${CPACK_PACKAGE_DESCRIPTION}")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/installation/debian/postinst")

# RPM package
# Run: $ cpack -G RPM
set(CPACK_RPM_PACKAGE_URL "${CPACK_PACKAGE_HOMEPAGE_URL}")
set(CPACK_RPM_PACKAGE_DESCRIPTION "${CPACK_PACKAGE_DESCRIPTION}")
set(CPACK_RPM_PACKAGE_LICENSE GPLv3+)
set(CPACK_RPM_PACKAGE_AUTOREQ 1)
set(CPACK_RPM_FILE_NAME RPM-DEFAULT)
set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE "${CMAKE_SOURCE_DIR}/installation/rpm/postinst")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/lib")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/lib/systemd")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/lib/systemd/system")

include(CPack)
