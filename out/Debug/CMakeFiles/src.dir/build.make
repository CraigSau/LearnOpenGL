# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/craigsau/Documents/Programming/LearnOpenGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/craigsau/Documents/Programming/LearnOpenGL/out/Debug

# Include any dependencies generated for this target.
include CMakeFiles/src.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/src.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/src.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/src.dir/flags.make

CMakeFiles/src.dir/src/shader.c.o: CMakeFiles/src.dir/flags.make
CMakeFiles/src.dir/src/shader.c.o: /Users/craigsau/Documents/Programming/LearnOpenGL/src/shader.c
CMakeFiles/src.dir/src/shader.c.o: CMakeFiles/src.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/craigsau/Documents/Programming/LearnOpenGL/out/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/src.dir/src/shader.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/src.dir/src/shader.c.o -MF CMakeFiles/src.dir/src/shader.c.o.d -o CMakeFiles/src.dir/src/shader.c.o -c /Users/craigsau/Documents/Programming/LearnOpenGL/src/shader.c

CMakeFiles/src.dir/src/shader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/src.dir/src/shader.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/craigsau/Documents/Programming/LearnOpenGL/src/shader.c > CMakeFiles/src.dir/src/shader.c.i

CMakeFiles/src.dir/src/shader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/src.dir/src/shader.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/craigsau/Documents/Programming/LearnOpenGL/src/shader.c -o CMakeFiles/src.dir/src/shader.c.s

# Object files for target src
src_OBJECTS = \
"CMakeFiles/src.dir/src/shader.c.o"

# External object files for target src
src_EXTERNAL_OBJECTS =

libsrc.a: CMakeFiles/src.dir/src/shader.c.o
libsrc.a: CMakeFiles/src.dir/build.make
libsrc.a: CMakeFiles/src.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/craigsau/Documents/Programming/LearnOpenGL/out/Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libsrc.a"
	$(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/src.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/src.dir/build: libsrc.a
.PHONY : CMakeFiles/src.dir/build

CMakeFiles/src.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/src.dir/cmake_clean.cmake
.PHONY : CMakeFiles/src.dir/clean

CMakeFiles/src.dir/depend:
	cd /Users/craigsau/Documents/Programming/LearnOpenGL/out/Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/craigsau/Documents/Programming/LearnOpenGL /Users/craigsau/Documents/Programming/LearnOpenGL /Users/craigsau/Documents/Programming/LearnOpenGL/out/Debug /Users/craigsau/Documents/Programming/LearnOpenGL/out/Debug /Users/craigsau/Documents/Programming/LearnOpenGL/out/Debug/CMakeFiles/src.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/src.dir/depend

