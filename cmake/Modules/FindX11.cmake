find_package(PkgConfig)
pkg_check_modules(X11 REQUIRED x11)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(X11 DEFAULT_MSG X11_FOUND)
