cmake_minimum_required(VERSION 3.0.0)

project(touchegg VERSION 2.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# In debug mode check code style issues
if(CMAKE_BUILD_TYPE MATCHES Debug)
  include(./cmake/check-code-style.cmake)
endif()


# PugiXML
add_library(
  pugixml
  OBJECT
  third-party/pugixml/pugixml.hpp
  third-party/pugixml/pugiconfig.hpp
  third-party/pugixml/pugixml.cpp
)
set_target_properties(pugixml PROPERTIES CXX_CLANG_TIDY "")

# Touchégg
include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_SOURCE_DIR}/third-party
)

set(
  SOURCE_FILES
  src/main.cpp
  src/config/config.h
  src/config/config.cpp
  src/config/xml-config-loader.h
  src/config/xml-config-loader.cpp
  src/utils/filesystem.h
  src/utils/split.h
  src/utils/split.cpp
)

add_executable(touchegg ${SOURCE_FILES} $<TARGET_OBJECTS:pugixml>)
target_link_libraries(touchegg stdc++fs)


# include(CTest)
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
