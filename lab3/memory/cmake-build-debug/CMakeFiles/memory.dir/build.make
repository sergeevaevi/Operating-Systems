# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /snap/clion/111/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/111/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/llen/CLionProjects/memory

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/llen/CLionProjects/memory/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/memory.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/memory.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/memory.dir/flags.make

CMakeFiles/memory.dir/main.c.o: CMakeFiles/memory.dir/flags.make
CMakeFiles/memory.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/llen/CLionProjects/memory/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/memory.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/memory.dir/main.c.o   -c /home/llen/CLionProjects/memory/main.c

CMakeFiles/memory.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/memory.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/llen/CLionProjects/memory/main.c > CMakeFiles/memory.dir/main.c.i

CMakeFiles/memory.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/memory.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/llen/CLionProjects/memory/main.c -o CMakeFiles/memory.dir/main.c.s

# Object files for target memory
memory_OBJECTS = \
"CMakeFiles/memory.dir/main.c.o"

# External object files for target memory
memory_EXTERNAL_OBJECTS =

memory: CMakeFiles/memory.dir/main.c.o
memory: CMakeFiles/memory.dir/build.make
memory: CMakeFiles/memory.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/llen/CLionProjects/memory/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable memory"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/memory.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/memory.dir/build: memory

.PHONY : CMakeFiles/memory.dir/build

CMakeFiles/memory.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/memory.dir/cmake_clean.cmake
.PHONY : CMakeFiles/memory.dir/clean

CMakeFiles/memory.dir/depend:
	cd /home/llen/CLionProjects/memory/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/llen/CLionProjects/memory /home/llen/CLionProjects/memory /home/llen/CLionProjects/memory/cmake-build-debug /home/llen/CLionProjects/memory/cmake-build-debug /home/llen/CLionProjects/memory/cmake-build-debug/CMakeFiles/memory.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/memory.dir/depend

