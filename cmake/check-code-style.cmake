# If clang-tidy and/or clang-format are present run them and stop the compilation on error

find_program(CLANG_TIDY_EXEC NAMES "clang-tidy")
if(NOT CLANG_TIDY_EXEC)
  message(STATUS "Check for clang-tidy: Not found")
else()
  message(STATUS "Check for clang-tidy: Found")
  set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
endif()

find_program(CLANG_FORMAT_EXEC NAMES "clang-format")
if(NOT CLANG_FORMAT_EXEC)
  message(STATUS "Check for clang-format: Not found")
else()
  message(STATUS "Check for clang-format: Found")
  execute_process(
    COMMAND ./cmake/check-code-style.sh
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    RESULT_VARIABLE status
    ERROR_VARIABLE output
  )
  if(NOT status EQUAL 0)
    message(FATAL_ERROR "Code Style issues found")
  endif()
endif()