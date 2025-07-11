cmake_minimum_required(VERSION 3.10)

project(
  YAKL
  LANGUAGES C CXX Fortran
  HOMEPAGE_URL https://github.com/mrnorman/YAKL/
  VERSION 0.1
  DESCRIPTION
    "A Simple C++ Framework for Performance Portability and Fortran Code Porting"
)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Release
      CACHE STRING "Choose the type of build." FORCE)
endif()

find_package(Kokkos REQUIRED)

set(YAKL_F90_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/YAKL_gator_mod.F90)
set(YAKL_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/YAKL_fortran_interfaces.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/src/YAKL_gator_mod.F90)

# Ensure the Fortran file uses the desired flags
set_source_files_properties(${YAKL_F90_SOURCE} PROPERTIES COMPILE_FLAGS
                                                          "${YAKL_F90_FLAGS}")

# Add the header-only YAKL C++ library target as well as the YAKL Fortran
# interface library target
add_library(yakl INTERFACE)
target_link_libraries(yakl INTERFACE Kokkos::kokkos)
target_include_directories(
  yakl
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external>
            $<INSTALL_INTERFACE:include/YAKL>)

add_library(yakl_fortran STATIC ${YAKL_SOURCE})
set_target_properties(yakl_fortran PROPERTIES Fortran_MODULE_DIRECTORY
                                              ${CMAKE_CURRENT_BINARY_DIR}/mod)
target_link_libraries(yakl_fortran PUBLIC Kokkos::kokkos)
target_include_directories(
  yakl_fortran
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external>
         $<INSTALL_INTERFACE:include/YAKL>)

# Special treatment for MPI
if(YAKL_HAVE_MPI)
  find_package(
    MPI
    COMPONENTS C
    REQUIRED)
  if(MPI_FOUND)
    target_link_libraries(yakl INTERFACE MPI::MPI_C)
    target_link_libraries(${YAKL_FORTRAN_INTERFACE_TARGET} MPI::MPI_C)
  endif()
endif()

install(
  TARGETS yakl yakl_fortran
  EXPORT YAKLTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include/YAKL)

install(
  DIRECTORY src/ external/ ${CMAKE_CURRENT_BINARY_DIR}/mod/
  DESTINATION include/YAKL
  FILES_MATCHING
  PATTERN "*.h"
  PATTERN "*.hpp"
  PATTERN "*.mod")

install(
  EXPORT YAKLTargets
  FILE YAKLTargets.cmake
  NAMESPACE YAKL::
  DESTINATION lib/cmake/YAKL)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/YAKLConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/YAKLConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/YAKLConfig.cmake"
  INSTALL_DESTINATION lib/cmake/YAKL)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/YAKLConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/YAKLConfigVersion.cmake
        DESTINATION lib/cmake/YAKL)
