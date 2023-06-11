# MPI-LCI-practice

"lci_random.cpp" and "mpi_random_pingpong1.cpp" are files for random send tests.
Path to LCI and MPI library should be modified in "CMakeLists.txt" (include_directories() and link_directories()).
Include paths to LCI and MPI header files shoud be modified in files "lci_random.cpp" and "mpi_random_pingpong1.cpp".

Bug in file "lci_random.cpp": the variable "LCI_short_t src" is not sent properly to other processes.
