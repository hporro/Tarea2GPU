# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hporro/Documents/github/Tarea2GPU

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hporro/Documents/github/Tarea2GPU/build

# Include any dependencies generated for this target.
include libs/glfw-3.3/tests/CMakeFiles/title.dir/depend.make

# Include the progress variables for this target.
include libs/glfw-3.3/tests/CMakeFiles/title.dir/progress.make

# Include the compile flags for this target's objects.
include libs/glfw-3.3/tests/CMakeFiles/title.dir/flags.make

libs/glfw-3.3/tests/CMakeFiles/title.dir/title.c.o: libs/glfw-3.3/tests/CMakeFiles/title.dir/flags.make
libs/glfw-3.3/tests/CMakeFiles/title.dir/title.c.o: ../libs/glfw-3.3/tests/title.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hporro/Documents/github/Tarea2GPU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object libs/glfw-3.3/tests/CMakeFiles/title.dir/title.c.o"
	cd /home/hporro/Documents/github/Tarea2GPU/build/libs/glfw-3.3/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/title.dir/title.c.o -c /home/hporro/Documents/github/Tarea2GPU/libs/glfw-3.3/tests/title.c

libs/glfw-3.3/tests/CMakeFiles/title.dir/title.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/title.dir/title.c.i"
	cd /home/hporro/Documents/github/Tarea2GPU/build/libs/glfw-3.3/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hporro/Documents/github/Tarea2GPU/libs/glfw-3.3/tests/title.c > CMakeFiles/title.dir/title.c.i

libs/glfw-3.3/tests/CMakeFiles/title.dir/title.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/title.dir/title.c.s"
	cd /home/hporro/Documents/github/Tarea2GPU/build/libs/glfw-3.3/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hporro/Documents/github/Tarea2GPU/libs/glfw-3.3/tests/title.c -o CMakeFiles/title.dir/title.c.s

libs/glfw-3.3/tests/CMakeFiles/title.dir/__/deps/glad_gl.c.o: libs/glfw-3.3/tests/CMakeFiles/title.dir/flags.make
libs/glfw-3.3/tests/CMakeFiles/title.dir/__/deps/glad_gl.c.o: ../libs/glfw-3.3/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hporro/Documents/github/Tarea2GPU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object libs/glfw-3.3/tests/CMakeFiles/title.dir/__/deps/glad_gl.c.o"
	cd /home/hporro/Documents/github/Tarea2GPU/build/libs/glfw-3.3/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/title.dir/__/deps/glad_gl.c.o -c /home/hporro/Documents/github/Tarea2GPU/libs/glfw-3.3/deps/glad_gl.c

libs/glfw-3.3/tests/CMakeFiles/title.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/title.dir/__/deps/glad_gl.c.i"
	cd /home/hporro/Documents/github/Tarea2GPU/build/libs/glfw-3.3/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hporro/Documents/github/Tarea2GPU/libs/glfw-3.3/deps/glad_gl.c > CMakeFiles/title.dir/__/deps/glad_gl.c.i

libs/glfw-3.3/tests/CMakeFiles/title.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/title.dir/__/deps/glad_gl.c.s"
	cd /home/hporro/Documents/github/Tarea2GPU/build/libs/glfw-3.3/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hporro/Documents/github/Tarea2GPU/libs/glfw-3.3/deps/glad_gl.c -o CMakeFiles/title.dir/__/deps/glad_gl.c.s

# Object files for target title
title_OBJECTS = \
"CMakeFiles/title.dir/title.c.o" \
"CMakeFiles/title.dir/__/deps/glad_gl.c.o"

# External object files for target title
title_EXTERNAL_OBJECTS =

libs/glfw-3.3/tests/title: libs/glfw-3.3/tests/CMakeFiles/title.dir/title.c.o
libs/glfw-3.3/tests/title: libs/glfw-3.3/tests/CMakeFiles/title.dir/__/deps/glad_gl.c.o
libs/glfw-3.3/tests/title: libs/glfw-3.3/tests/CMakeFiles/title.dir/build.make
libs/glfw-3.3/tests/title: libs/glfw-3.3/src/libglfw3.a
libs/glfw-3.3/tests/title: /usr/lib/libm.so
libs/glfw-3.3/tests/title: /usr/lib/librt.so
libs/glfw-3.3/tests/title: /usr/lib/libm.so
libs/glfw-3.3/tests/title: /usr/lib/libX11.so
libs/glfw-3.3/tests/title: libs/glfw-3.3/tests/CMakeFiles/title.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hporro/Documents/github/Tarea2GPU/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable title"
	cd /home/hporro/Documents/github/Tarea2GPU/build/libs/glfw-3.3/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/title.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
libs/glfw-3.3/tests/CMakeFiles/title.dir/build: libs/glfw-3.3/tests/title

.PHONY : libs/glfw-3.3/tests/CMakeFiles/title.dir/build

libs/glfw-3.3/tests/CMakeFiles/title.dir/clean:
	cd /home/hporro/Documents/github/Tarea2GPU/build/libs/glfw-3.3/tests && $(CMAKE_COMMAND) -P CMakeFiles/title.dir/cmake_clean.cmake
.PHONY : libs/glfw-3.3/tests/CMakeFiles/title.dir/clean

libs/glfw-3.3/tests/CMakeFiles/title.dir/depend:
	cd /home/hporro/Documents/github/Tarea2GPU/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hporro/Documents/github/Tarea2GPU /home/hporro/Documents/github/Tarea2GPU/libs/glfw-3.3/tests /home/hporro/Documents/github/Tarea2GPU/build /home/hporro/Documents/github/Tarea2GPU/build/libs/glfw-3.3/tests /home/hporro/Documents/github/Tarea2GPU/build/libs/glfw-3.3/tests/CMakeFiles/title.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libs/glfw-3.3/tests/CMakeFiles/title.dir/depend

