find_package(PkgConfig)
pkg_check_modules(PUGIXML REQUIRED pugixml)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PugiXML DEFAULT_MSG PUGIXML_FOUND)
