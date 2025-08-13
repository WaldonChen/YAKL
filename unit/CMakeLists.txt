cmake_minimum_required(VERSION 3.5)
project(yakl_unit)
enable_testing()

enable_language(Fortran)
enable_language(CXX)
enable_language(C)

set(CMAKE_CXX_STANDARD 17)

find_package(YAKL REQUIRED)

# Unit test directories
add_subdirectory(CArray)
add_subdirectory(FArray)
add_subdirectory(Random)
add_subdirectory(Reductions)
add_subdirectory(Atomics)
add_subdirectory(Lambda)
add_subdirectory(Fortran_Link)
add_subdirectory(Fortran_Gator)
add_subdirectory(OpenMP_Regions)
add_subdirectory(Intrinsics)
add_subdirectory(ParForC)
add_subdirectory(ParForFortran)
add_subdirectory(performance)
if (YAKL_TEST_NETCDF)
  add_subdirectory(NetCDF)
endif()

