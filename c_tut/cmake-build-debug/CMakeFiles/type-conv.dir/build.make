# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sammuel.rice139/Desktop/comp232/c_tut

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sammuel.rice139/Desktop/comp232/c_tut/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/type-conv.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/type-conv.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/type-conv.dir/flags.make

CMakeFiles/type-conv.dir/src/type-conv.c.o: CMakeFiles/type-conv.dir/flags.make
CMakeFiles/type-conv.dir/src/type-conv.c.o: ../src/type-conv.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sammuel.rice139/Desktop/comp232/c_tut/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/type-conv.dir/src/type-conv.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/type-conv.dir/src/type-conv.c.o   -c /Users/sammuel.rice139/Desktop/comp232/c_tut/src/type-conv.c

CMakeFiles/type-conv.dir/src/type-conv.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/type-conv.dir/src/type-conv.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/sammuel.rice139/Desktop/comp232/c_tut/src/type-conv.c > CMakeFiles/type-conv.dir/src/type-conv.c.i

CMakeFiles/type-conv.dir/src/type-conv.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/type-conv.dir/src/type-conv.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/sammuel.rice139/Desktop/comp232/c_tut/src/type-conv.c -o CMakeFiles/type-conv.dir/src/type-conv.c.s

# Object files for target type-conv
type__conv_OBJECTS = \
"CMakeFiles/type-conv.dir/src/type-conv.c.o"

# External object files for target type-conv
type__conv_EXTERNAL_OBJECTS =

type-conv: CMakeFiles/type-conv.dir/src/type-conv.c.o
type-conv: CMakeFiles/type-conv.dir/build.make
type-conv: CMakeFiles/type-conv.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/sammuel.rice139/Desktop/comp232/c_tut/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable type-conv"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/type-conv.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/type-conv.dir/build: type-conv

.PHONY : CMakeFiles/type-conv.dir/build

CMakeFiles/type-conv.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/type-conv.dir/cmake_clean.cmake
.PHONY : CMakeFiles/type-conv.dir/clean

CMakeFiles/type-conv.dir/depend:
	cd /Users/sammuel.rice139/Desktop/comp232/c_tut/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sammuel.rice139/Desktop/comp232/c_tut /Users/sammuel.rice139/Desktop/comp232/c_tut /Users/sammuel.rice139/Desktop/comp232/c_tut/cmake-build-debug /Users/sammuel.rice139/Desktop/comp232/c_tut/cmake-build-debug /Users/sammuel.rice139/Desktop/comp232/c_tut/cmake-build-debug/CMakeFiles/type-conv.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/type-conv.dir/depend

