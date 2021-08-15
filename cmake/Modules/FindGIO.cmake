find_package(PkgConfig)
pkg_check_modules(GIO REQUIRED gio-2.0)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GIO DEFAULT_MSG GIO_FOUND)
