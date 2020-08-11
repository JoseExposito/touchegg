cmake_minimum_required(VERSION 3.0.0)

project(touchegg VERSION 2.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# In debug mode check code style issues
if(CMAKE_BUILD_TYPE MATCHES Debug)
  include(./cmake/check-code-style.cmake)
endif()

find_package(LibXml2 REQUIRED)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${LIBXML2_INCLUDE_DIR}
)

set(
    SOURCE_FILES
    src/main.cpp
    src/config/config.h
    src/config/config.cpp
    src/config/parser.h
    src/config/parser.cpp
)

add_executable(touchegg ${SOURCE_FILES})
target_link_libraries(touchegg stdc++fs ${LIBXML2_LIBRARIES})


# include(CTest)
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
