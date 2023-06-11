# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/snap/cmake/1299/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/snap/cmake/1299/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/weixuan/mpiTest/CMakeFiles /home/weixuan/mpiTest//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/weixuan/mpiTest/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named lci_pingpong

# Build rule for target.
lci_pingpong: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 lci_pingpong
.PHONY : lci_pingpong

# fast build rule for target.
lci_pingpong/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/lci_pingpong.dir/build.make CMakeFiles/lci_pingpong.dir/build
.PHONY : lci_pingpong/fast

#=============================================================================
# Target rules for targets named mpi_pingpong

# Build rule for target.
mpi_pingpong: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 mpi_pingpong
.PHONY : mpi_pingpong

# fast build rule for target.
mpi_pingpong/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/mpi_pingpong.dir/build.make CMakeFiles/mpi_pingpong.dir/build
.PHONY : mpi_pingpong/fast

lci_random.o: lci_random.cpp.o
.PHONY : lci_random.o

# target to build an object file
lci_random.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/lci_pingpong.dir/build.make CMakeFiles/lci_pingpong.dir/lci_random.cpp.o
.PHONY : lci_random.cpp.o

lci_random.i: lci_random.cpp.i
.PHONY : lci_random.i

# target to preprocess a source file
lci_random.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/lci_pingpong.dir/build.make CMakeFiles/lci_pingpong.dir/lci_random.cpp.i
.PHONY : lci_random.cpp.i

lci_random.s: lci_random.cpp.s
.PHONY : lci_random.s

# target to generate assembly for a file
lci_random.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/lci_pingpong.dir/build.make CMakeFiles/lci_pingpong.dir/lci_random.cpp.s
.PHONY : lci_random.cpp.s

mpi_random_pingpong1.o: mpi_random_pingpong1.cpp.o
.PHONY : mpi_random_pingpong1.o

# target to build an object file
mpi_random_pingpong1.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/mpi_pingpong.dir/build.make CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.o
.PHONY : mpi_random_pingpong1.cpp.o

mpi_random_pingpong1.i: mpi_random_pingpong1.cpp.i
.PHONY : mpi_random_pingpong1.i

# target to preprocess a source file
mpi_random_pingpong1.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/mpi_pingpong.dir/build.make CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.i
.PHONY : mpi_random_pingpong1.cpp.i

mpi_random_pingpong1.s: mpi_random_pingpong1.cpp.s
.PHONY : mpi_random_pingpong1.s

# target to generate assembly for a file
mpi_random_pingpong1.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/mpi_pingpong.dir/build.make CMakeFiles/mpi_pingpong.dir/mpi_random_pingpong1.cpp.s
.PHONY : mpi_random_pingpong1.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... lci_pingpong"
	@echo "... mpi_pingpong"
	@echo "... lci_random.o"
	@echo "... lci_random.i"
	@echo "... lci_random.s"
	@echo "... mpi_random_pingpong1.o"
	@echo "... mpi_random_pingpong1.i"
	@echo "... mpi_random_pingpong1.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
