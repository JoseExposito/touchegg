find_package(PkgConfig)
pkg_check_modules(XTEST REQUIRED xtst)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(XTEST DEFAULT_MSG XTEST_FOUND)
