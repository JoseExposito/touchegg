cmake_minimum_required(VERSION 3.0.0)

project(touchegg VERSION 2.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# In debug mode check code style issues
if(CMAKE_BUILD_TYPE MATCHES Debug)
  include(./cmake/check-code-style.cmake)
endif()

# include(CTest)
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

set(
    SOURCE_FILES
    src/main.cpp
    src/config/config.h
    src/config/config.cpp
)

add_executable(touchegg ${SOURCE_FILES})
target_link_libraries(touchegg stdc++fs)
