cmake_minimum_required(VERSION 3.23)
project(lci_random CXX)

include_directories(/home/weixuan/library/lci/include /lib/x86_64-linux-gnu/openmpi/include)
link_directories(/home/weixuan/library/lci/lib lib/x86_64-linux-gnu/openmpi/lib)

find_package(LCI REQUIRED HINTS $ENV{LCI_ROOT} PATH_SUFFIXES lib/cmake lib64/cmake)

add_executable(lci_pingpong lci_random.cpp)
target_link_libraries(lci_pingpong PRIVATE LCI)
add_compile_options(-g)


add_executable(mpi_pingpong mpi_random_pingpong1.cpp)
target_link_libraries(mpi_pingpong PRIVATE mpi_cxx mpi)
