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
include CMakeFiles/ptr-func.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ptr-func.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ptr-func.dir/flags.make

CMakeFiles/ptr-func.dir/src/ptr-func.c.o: CMakeFiles/ptr-func.dir/flags.make
CMakeFiles/ptr-func.dir/src/ptr-func.c.o: ../src/ptr-func.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sammuel.rice139/Desktop/comp232/c_tut/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ptr-func.dir/src/ptr-func.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ptr-func.dir/src/ptr-func.c.o   -c /Users/sammuel.rice139/Desktop/comp232/c_tut/src/ptr-func.c

CMakeFiles/ptr-func.dir/src/ptr-func.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ptr-func.dir/src/ptr-func.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/sammuel.rice139/Desktop/comp232/c_tut/src/ptr-func.c > CMakeFiles/ptr-func.dir/src/ptr-func.c.i

CMakeFiles/ptr-func.dir/src/ptr-func.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ptr-func.dir/src/ptr-func.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/sammuel.rice139/Desktop/comp232/c_tut/src/ptr-func.c -o CMakeFiles/ptr-func.dir/src/ptr-func.c.s

# Object files for target ptr-func
ptr__func_OBJECTS = \
"CMakeFiles/ptr-func.dir/src/ptr-func.c.o"

# External object files for target ptr-func
ptr__func_EXTERNAL_OBJECTS =

ptr-func: CMakeFiles/ptr-func.dir/src/ptr-func.c.o
ptr-func: CMakeFiles/ptr-func.dir/build.make
ptr-func: CMakeFiles/ptr-func.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/sammuel.rice139/Desktop/comp232/c_tut/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ptr-func"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ptr-func.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ptr-func.dir/build: ptr-func

.PHONY : CMakeFiles/ptr-func.dir/build

CMakeFiles/ptr-func.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ptr-func.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ptr-func.dir/clean

CMakeFiles/ptr-func.dir/depend:
	cd /Users/sammuel.rice139/Desktop/comp232/c_tut/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sammuel.rice139/Desktop/comp232/c_tut /Users/sammuel.rice139/Desktop/comp232/c_tut /Users/sammuel.rice139/Desktop/comp232/c_tut/cmake-build-debug /Users/sammuel.rice139/Desktop/comp232/c_tut/cmake-build-debug /Users/sammuel.rice139/Desktop/comp232/c_tut/cmake-build-debug/CMakeFiles/ptr-func.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ptr-func.dir/depend
