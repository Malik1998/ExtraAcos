# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /home/user/IDE/clion-2018.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/user/IDE/clion-2018.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/SafeStackTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SafeStackTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SafeStackTest.dir/flags.make

CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o: CMakeFiles/SafeStackTest.dir/flags.make
CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o: ../Tests/SafeStackTester/SafeStackTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o -c "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/Tests/SafeStackTester/SafeStackTest.cpp"

CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/Tests/SafeStackTester/SafeStackTest.cpp" > CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.i

CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/Tests/SafeStackTester/SafeStackTest.cpp" -o CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.s

CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o.requires:

.PHONY : CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o.requires

CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o.provides: CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/SafeStackTest.dir/build.make CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o.provides.build
.PHONY : CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o.provides

CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o.provides.build: CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o


CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o: CMakeFiles/SafeStackTest.dir/flags.make
CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o: ../SafeStack/SafeStack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o -c "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/SafeStack/SafeStack.cpp"

CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/SafeStack/SafeStack.cpp" > CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.i

CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/SafeStack/SafeStack.cpp" -o CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.s

CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o.requires:

.PHONY : CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o.requires

CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o.provides: CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o.requires
	$(MAKE) -f CMakeFiles/SafeStackTest.dir/build.make CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o.provides.build
.PHONY : CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o.provides

CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o.provides.build: CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o


# Object files for target SafeStackTest
SafeStackTest_OBJECTS = \
"CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o" \
"CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o"

# External object files for target SafeStackTest
SafeStackTest_EXTERNAL_OBJECTS =

SafeStackTest: CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o
SafeStackTest: CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o
SafeStackTest: CMakeFiles/SafeStackTest.dir/build.make
SafeStackTest: CMakeFiles/SafeStackTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable SafeStackTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SafeStackTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SafeStackTest.dir/build: SafeStackTest

.PHONY : CMakeFiles/SafeStackTest.dir/build

CMakeFiles/SafeStackTest.dir/requires: CMakeFiles/SafeStackTest.dir/Tests/SafeStackTester/SafeStackTest.cpp.o.requires
CMakeFiles/SafeStackTest.dir/requires: CMakeFiles/SafeStackTest.dir/SafeStack/SafeStack.cpp.o.requires

.PHONY : CMakeFiles/SafeStackTest.dir/requires

CMakeFiles/SafeStackTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SafeStackTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SafeStackTest.dir/clean

CMakeFiles/SafeStackTest.dir/depend:
	cd "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle" "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle" "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/cmake-build-debug" "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/cmake-build-debug" "/home/user/Desktop/Studying/MIPT/term_5/extra acos/hw/ExtraAcos/Task3/SafeStackCStyle/cmake-build-debug/CMakeFiles/SafeStackTest.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/SafeStackTest.dir/depend

