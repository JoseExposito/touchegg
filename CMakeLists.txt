cmake_minimum_required(VERSION 3.0.0)

project(touchegg)
set(MAJOR_VERSION "2")
set(MINOR_VERSION "0")
set(PATCH_VERSION "14")
add_definitions(-D_VERSION="v${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules")

# In debug mode check code style issues
if(CMAKE_BUILD_TYPE MATCHES Debug)
  include(./cmake/check-code-style.cmake)
endif()

find_package(Threads REQUIRED) # Required to use std threads
find_package(LIBUDEV REQUIRED)
find_package(LIBINPUT REQUIRED)
find_package(PUGIXML REQUIRED)
find_package(CAIRO REQUIRED)
find_package(X11 REQUIRED)
find_package(XTEST REQUIRED)
find_package(XRANDR REQUIRED)
find_package(XINPUT REQUIRED)
find_package(GLIB REQUIRED)
find_package(GIO REQUIRED)

# libinput 1.18 filters unaccelerated deltas for gestures and we need to adjust our thresholds:
# https://gitlab.freedesktop.org/libinput/libinput/-/commit/60d5172e15728cc25db889a7a6bcf37a06a15a3a
if(LIBINPUT_VERSION VERSION_GREATER_EQUAL "1.18")
  message(STATUS "Found libinput >= 1.18: LIBINPUT_FILTER_DELTAS=ON")
  add_definitions(-DLIBINPUT_FILTER_DELTAS=ON)
endif()

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
  ${GLIB_INCLUDE_DIRS}
  ${GIO_INCLUDE_DIRS}
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
  ${GLIB_LIBRARIES}
  ${GIO_LIBRARIES}
)

if(NOT DEFINED AUTO_COLORS OR AUTO_COLORS)
  find_package(GTK3 REQUIRED)
  target_include_directories(touchegg PUBLIC ${GTK3_INCLUDE_DIRS})
  target_link_libraries(touchegg ${GTK3_LIBRARIES})
  add_definitions(-DAUTO_COLORS=ON)
else()
  message(WARNING "AUTO_COLORS OFF: GTK will NOT be used to and auto colors will NOT be available")
endif()


# Installation
# https://cmake.org/cmake/help/v3.4/module/GNUInstallDirs.html
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_INSTALL_PREFIX "/usr")
endif()

include(GNUInstallDirs)

set(SYSTEM_CONFIG_FILE_PATH "${CMAKE_INSTALL_FULL_DATAROOTDIR}/touchegg/touchegg.conf")
target_compile_definitions(touchegg PUBLIC SYSTEM_CONFIG_FILE_PATH=\"${SYSTEM_CONFIG_FILE_PATH}\")

install(FILES ${PROJECT_SOURCE_DIR}/installation/touchegg.conf DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/touchegg) # /usr/share/touchegg/touchegg.conf
install(FILES ${PROJECT_SOURCE_DIR}/installation/touchegg.desktop DESTINATION ${CMAKE_INSTALL_FULL_SYSCONFDIR}/xdg/autostart)
install(PROGRAMS ${PROJECT_BINARY_DIR}/touchegg DESTINATION ${CMAKE_INSTALL_BINDIR}) # /usr/bin/touchegg

if(NOT DEFINED USE_SYSTEMD OR USE_SYSTEMD)
  # configure systemd service unit to use the right path, e.g. @CMAKE_INSTALL_BINDIR@/touchegg
  configure_file(${PROJECT_SOURCE_DIR}/installation/touchegg.service.in ${PROJECT_SOURCE_DIR}/installation/touchegg.service @ONLY)
  pkg_get_variable(SYSTEMD_SERVICE_DIR systemd systemdsystemunitdir)

  install(FILES ${PROJECT_SOURCE_DIR}/installation/touchegg.service DESTINATION ${SYSTEMD_SERVICE_DIR})
else()
  message(WARNING "USE_SYSTEMD OFF: Systemd related file will NOT be installed")
endif()
