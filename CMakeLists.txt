cmake_minimum_required(VERSION 3.23)
project(lci_random CXX)

include_directories(/home/weixuan/library/lci/include /lib/x86_64-linux-gnu/openmpi/include)
link_directories(/home/weixuan/library/lci/lib lib/x86_64-linux-gnu/openmpi/lib)

find_package(LCI REQUIRED HINTS $ENV{LCI_ROOT} PATH_SUFFIXES lib/cmake lib64/cmake)

add_executable(lci_pingpong lci_random.cpp)
add_executable(lci_threads lci_multithreaded.cpp)
target_link_libraries(lci_pingpong PRIVATE LCI)
target_link_libraries(lci_threads PRIVATE LCI pthread)

add_executable(mpi_pingpong mpi_random_pingpong1.cpp)
add_executable(mpi_threads mpi_multithreaded.cpp)
target_link_libraries(mpi_pingpong PRIVATE mpi_cxx mpi)
target_link_libraries(mpi_threads PRIVATE mpi_cxx mpi pthread)
add_compile_options(-g)
