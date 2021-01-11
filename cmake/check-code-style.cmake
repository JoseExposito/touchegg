# If clang-tidy, clang-format and/or cpplint are present run them and stop the compilation on error

find_program(CLANG_TIDY_EXEC NAMES "clang-tidy")
if(NOT CLANG_TIDY_EXEC)
  message(WARNING "Check for clang-tidy: Not found, clang-tidy will not be executed")
else()
  message(STATUS "Check for clang-tidy: Found")
  set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
endif()

find_program(CLANG_FORMAT_EXEC NAMES "clang-format")
if(NOT CLANG_FORMAT_EXEC)
  message(WARNING "Check for clang-format: Not found, clang-format will not be executed")
else()
  message(STATUS "Check for clang-format: Found")
  execute_process(
    COMMAND ./cmake/run-clang-format.sh
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    RESULT_VARIABLE status
  )
  if(NOT status EQUAL 0)
    message(FATAL_ERROR "Code Style issues found (clang-format)")
  endif()
endif()

find_program(PYTHON_EXEC NAMES "python2")
if(NOT PYTHON_EXEC)
  message(WARNING "Check for python2: Not found, cpplint.py will not be executed")
else()
  message(STATUS "Check for python2: Found")
  execute_process(
    COMMAND ./cmake/run-cpplint-py.sh
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    RESULT_VARIABLE status
  )
    if(NOT status EQUAL 0)
    message(FATAL_ERROR "Code Style issues found (cpplint.py)")
  endif()
endif()
