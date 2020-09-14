cmake_minimum_required(VERSION 3.0.0)

project(touchegg VERSION 2.0.0)

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
)


# include(CTest)
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
