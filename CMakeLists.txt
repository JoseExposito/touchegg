cmake_minimum_required(VERSION 3.0.0)

project(touchegg)
SET(MAJOR_VERSION "2")
SET(MINOR_VERSION "0")
SET(PATCH_VERSION "0")
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
# TODO(jose) Copy the service file to /lib/systemd/system
# TODO(jose) Generate a proper DEB package
install(FILES ${PROJECT_SOURCE_DIR}/installation/touchegg.conf DESTINATION share/touchegg)
install(PROGRAMS ${CMAKE_BINARY_DIR}/touchegg DESTINATION bin)

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
SET(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Multi-touch gesture recognizer.
Touchégg is an app that runs in the background and transform the gestures you make in your touchpad into visible actions in your desktop.
For example, you can swipe up with 3 fingers to maximize a window or swipe left with 4 finger to switch to the next desktop.")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/JoseExposito/touchegg")
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")

# DEB package
# Run: $ cpack -G DEB
set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "José Expósito <jose.exposito89@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libudev-dev, libinput-dev, libpugixml-dev, libcairo2-dev, libx11-dev, libxtst-dev, libxrandr-dev")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
# set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/installation/debian/control")

include(CPack)
