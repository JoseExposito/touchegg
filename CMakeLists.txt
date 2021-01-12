cmake_minimum_required(VERSION 3.0.0)

project(touchegg)
set(MAJOR_VERSION "2")
set(MINOR_VERSION "0")
set(PATCH_VERSION "5")
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
find_package(XInput REQUIRED)

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
  ${XINPUT_INCLUDE_DIRS}
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
  ${XINPUT_LIBRARIES}
)

if(NOT DEFINED AUTO_COLORS OR AUTO_COLORS)
  find_package(Gtk3 REQUIRED)
  target_include_directories(touchegg PUBLIC ${GTK3_INCLUDE_DIRS})
  target_link_libraries(touchegg ${GTK3_LIBRARIES})
  add_definitions(-DAUTO_COLORS=ON)
else()
  message(WARNING "AUTO_COLORS OFF: GTK will NOT be used to and auto colors will NOT be available")
endif()


# Installation
# https://cmake.org/cmake/help/v3.4/module/GNUInstallDirs.html
# https://cmake.org/cmake/help/v3.12/module/CPack.html
# https://cmake.org/cmake/help/v3.7/module/CPackRPM.html
include(GNUInstallDirs)
set(CMAKE_INSTALL_PREFIX "/usr")
install(FILES ${PROJECT_SOURCE_DIR}/installation/touchegg.conf DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/touchegg) # /usr/share/touchegg/touchegg.conf
install(FILES ${PROJECT_SOURCE_DIR}/installation/touchegg.service DESTINATION /lib/systemd/system)
install(FILES ${PROJECT_SOURCE_DIR}/installation/touchegg.user.service DESTINATION usr/lib/systemd/user/)
install(PROGRAMS ${CMAKE_BINARY_DIR}/touchegg DESTINATION ${CMAKE_INSTALL_BINDIR}) # /usr/bin/touchegg

set(CPACK_PACKAGE_NAME touchegg)
set(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/JoseExposito/touchegg")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Multi-touch gesture recognizer")
set(CPACK_PACKAGE_DESCRIPTION "Multi-touch gesture recognizer.
 Touchégg is an app that runs in the background and transform the gestures you make in your touchpad into visible actions in your desktop.
 For example, you can swipe up with 3 fingers to maximize a window or swipe left with 4 finger to switch to the next desktop.")

# RPM package
# Run: $ cpack -G RPM
set(CPACK_RPM_PACKAGE_URL "${CPACK_PACKAGE_HOMEPAGE_URL}")
set(CPACK_RPM_PACKAGE_DESCRIPTION "${CPACK_PACKAGE_DESCRIPTION}")
set(CPACK_RPM_PACKAGE_LICENSE GPLv3+)
set(CPACK_RPM_PACKAGE_AUTOREQ 1)
set(CPACK_RPM_FILE_NAME RPM-DEFAULT)
set(CPACK_RPM_POST_INSTALL_SCRIPT_FILE "${CMAKE_SOURCE_DIR}/installation/rpm/postinst")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "${CMAKE_INSTALL_PREFIX}")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "${CMAKE_INSTALL_BINDIR}")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "${CMAKE_INSTALL_DATAROOTDIR}")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/lib")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/lib/systemd")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/lib/systemd/system")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/usr")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/usr/lib")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/usr/lib/systemd")
list(APPEND CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/usr/lib/systemd/user")

include(CPack)
