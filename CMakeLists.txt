##############################################################################
# Cmake
##############################################################################

cmake_minimum_required(VERSION 3.5)
project(kobuki_ftdi)

##############################################################################
# Find Packages
##############################################################################

find_package(ament_cmake_ros REQUIRED)
find_package(ecl_build REQUIRED)
find_package(ecl_command_line REQUIRED)

# pkg-config packages
find_package(PkgConfig)
pkg_search_module(libusb REQUIRED libusb)
pkg_search_module(libftdi REQUIRED libftdi)

##############################################################################
# Platform Configuration
##############################################################################

ament_package_xml()
ecl_enable_cxx14_compiler()
ecl_enable_cxx_warnings()

##############################################################################
# Sources
##############################################################################

add_subdirectory(src)

##############################################################################
# Install data files
##############################################################################

install(DIRECTORY eeproms
        DESTINATION share/${PROJECT_NAME}
)

install(FILES 60-kobuki.rules
        DESTINATION share/${PROJECT_NAME}
)

##############################################################################
# Exports
##############################################################################

ament_package()
