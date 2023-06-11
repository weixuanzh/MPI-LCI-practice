# MPI-LCI-practice

"lci_random.cpp" and "mpi_random_pingpong1.cpp" are files for random send tests.
path to LCI and MPI library should be modified in "CMakeLists.txt" (include_directories() and link_directories()) to compile.

Bug in file "lci_random.cpp": the variable "LCI_short_t src" is not sent properly to other processes.
