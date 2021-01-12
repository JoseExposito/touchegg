find_package(PkgConfig)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GTK3 DEFAULT_MSG GTK3_FOUND)
