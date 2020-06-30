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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT

# Include any dependencies generated for this target.
include src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/depend.make

# Include the progress variables for this target.
include src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/progress.make

# Include the compile flags for this target's objects.
include src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/flags.make

src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/Guard.o: src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/flags.make
src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/Guard.o: src/Model/StateMachine/Guard/Guard.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/Guard.o"
	cd /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/src/Model/StateMachine/Guard && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Guard.dir/Guard.o -c /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/src/Model/StateMachine/Guard/Guard.cpp

src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/Guard.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Guard.dir/Guard.i"
	cd /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/src/Model/StateMachine/Guard && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/src/Model/StateMachine/Guard/Guard.cpp > CMakeFiles/Guard.dir/Guard.i

src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/Guard.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Guard.dir/Guard.s"
	cd /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/src/Model/StateMachine/Guard && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/src/Model/StateMachine/Guard/Guard.cpp -o CMakeFiles/Guard.dir/Guard.s

# Object files for target Guard
Guard_OBJECTS = \
"CMakeFiles/Guard.dir/Guard.o"

# External object files for target Guard
Guard_EXTERNAL_OBJECTS =

src/Model/StateMachine/Guard/libGuard.a: src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/Guard.o
src/Model/StateMachine/Guard/libGuard.a: src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/build.make
src/Model/StateMachine/Guard/libGuard.a: src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libGuard.a"
	cd /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/src/Model/StateMachine/Guard && $(CMAKE_COMMAND) -P CMakeFiles/Guard.dir/cmake_clean_target.cmake
	cd /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/src/Model/StateMachine/Guard && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Guard.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/build: src/Model/StateMachine/Guard/libGuard.a

.PHONY : src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/build

src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/clean:
	cd /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/src/Model/StateMachine/Guard && $(CMAKE_COMMAND) -P CMakeFiles/Guard.dir/cmake_clean.cmake
.PHONY : src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/clean

src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/depend:
	cd /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/src/Model/StateMachine/Guard /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/src/Model/StateMachine/Guard /home/clexma/Desktop/Disk_D/gitRepos/ISADT-common/ISADT/src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Model/StateMachine/Guard/CMakeFiles/Guard.dir/depend

