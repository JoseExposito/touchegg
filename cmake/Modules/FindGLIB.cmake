find_package(PkgConfig)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLIB DEFAULT_MSG GLIB_FOUND)
