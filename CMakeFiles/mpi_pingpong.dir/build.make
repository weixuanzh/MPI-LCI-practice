# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/cmake/1299/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1299/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/weixuan/mpiTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/weixuan/mpiTest

# Include any dependencies generated for this target.
include CMakeFiles/mpi_pingpong.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mpi_pingpong.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mpi_pingpong.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mpi_pingpong.dir/flags.make

CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.o: CMakeFiles/mpi_pingpong.dir/flags.make
CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.o: mpi_random_pingpong1.cpp
CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.o: CMakeFiles/mpi_pingpong.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/weixuan/mpiTest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.o -MF CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.o.d -o CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.o -c /home/weixuan/mpiTest/mpi_random_pingpong1.cpp

CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/weixuan/mpiTest/mpi_random_pingpong1.cpp > CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.i

CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/weixuan/mpiTest/mpi_random_pingpong1.cpp -o CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.s

# Object files for target mpi_pingpong
mpi_pingpong_OBJECTS = \
"CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.o"

# External object files for target mpi_pingpong
mpi_pingpong_EXTERNAL_OBJECTS =

mpi_pingpong: CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.o
mpi_pingpong: CMakeFiles/mpi_pingpong.dir/build.make
mpi_pingpong: CMakeFiles/mpi_pingpong.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/weixuan/mpiTest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mpi_pingpong"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mpi_pingpong.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mpi_pingpong.dir/build: mpi_pingpong
.PHONY : CMakeFiles/mpi_pingpong.dir/build

CMakeFiles/mpi_pingpong.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mpi_pingpong.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mpi_pingpong.dir/clean

CMakeFiles/mpi_pingpong.dir/depend:
	cd /home/weixuan/mpiTest && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/weixuan/mpiTest /home/weixuan/mpiTest /home/weixuan/mpiTest /home/weixuan/mpiTest /home/weixuan/mpiTest/CMakeFiles/mpi_pingpong.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mpi_pingpong.dir/depend
