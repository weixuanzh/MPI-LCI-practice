cmake_minimum_required(VERSION 3.16.3)
project(lci_random CXX)

string(REPLACE ":" ";" LIBRARY_DIRS $ENV{LD_LIBRARY_PATH})

find_package(LCI REQUIRED HINTS $ENV{LCI_ROOT} PATH_SUFFIXES lib/cmake lib64/cmake)

find_library(MPI REQUIRED
             NAMES libmpi openmpi mpi
             PATHS ${LIBRARY_DIRS})
find_path(MPI_INCLUDE_DIR
          NAMES mpi.h
          HINTS ${LIBRARY_DIRS}
          PATH_SUFFIXES ../include)

find_library(PT REQUIRED
             NAMES pthread
             PATHS ${LIBRARY_DIRS})
find_path(PT_INCLUDE_DIR
          NAMES pthread.h
          HINTS ${LIBRARY_DIRS}
          PATH_SUFFIXES ../include)


add_executable(lci_pingpong lci_random.cpp)
target_link_libraries(lci_pingpong PRIVATE LCI)

add_executable(lci_threads lci_multithreaded.cpp)
target_link_libraries(lci_threads PRIVATE LCI pthread)

add_executable(mpi_pingpong mpi_random_pingpong1.cpp)
target_link_libraries(mpi_pingpong PRIVATE "${MPI}" "${PT}")
target_include_directories(mpi_pingpong PRIVATE "${MPI_INCLUDE_DIR}" "${PT_INCLUDE_DIR}")

add_executable(mpi_threads mpi_multithreaded.cpp)
target_link_libraries(mpi_threads PRIVATE "${MPI}" "${PT}")
target_include_directories(mpi_threads PRIVATE "${MPI_INCLUDE_DIR}" "${PT_INCLUDE_DIR}")

add_compile_options(-g)
