# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /root/github/MusicPlayer/server/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/github/MusicPlayer/server/src/bld

# Include any dependencies generated for this target.
include network/boot/CMakeFiles/Network.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include network/boot/CMakeFiles/Network.dir/compiler_depend.make

# Include the progress variables for this target.
include network/boot/CMakeFiles/Network.dir/progress.make

# Include the compile flags for this target's objects.
include network/boot/CMakeFiles/Network.dir/flags.make

network/boot/CMakeFiles/Network.dir/network.cxx.o: network/boot/CMakeFiles/Network.dir/flags.make
network/boot/CMakeFiles/Network.dir/network.cxx.o: ../network/boot/network.cxx
network/boot/CMakeFiles/Network.dir/network.cxx.o: network/boot/CMakeFiles/Network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/github/MusicPlayer/server/src/bld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object network/boot/CMakeFiles/Network.dir/network.cxx.o"
	cd /root/github/MusicPlayer/server/src/bld/network/boot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT network/boot/CMakeFiles/Network.dir/network.cxx.o -MF CMakeFiles/Network.dir/network.cxx.o.d -o CMakeFiles/Network.dir/network.cxx.o -c /root/github/MusicPlayer/server/src/network/boot/network.cxx

network/boot/CMakeFiles/Network.dir/network.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Network.dir/network.cxx.i"
	cd /root/github/MusicPlayer/server/src/bld/network/boot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/github/MusicPlayer/server/src/network/boot/network.cxx > CMakeFiles/Network.dir/network.cxx.i

network/boot/CMakeFiles/Network.dir/network.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Network.dir/network.cxx.s"
	cd /root/github/MusicPlayer/server/src/bld/network/boot && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/github/MusicPlayer/server/src/network/boot/network.cxx -o CMakeFiles/Network.dir/network.cxx.s

# Object files for target Network
Network_OBJECTS = \
"CMakeFiles/Network.dir/network.cxx.o"

# External object files for target Network
Network_EXTERNAL_OBJECTS =

network/boot/libNetwork.a: network/boot/CMakeFiles/Network.dir/network.cxx.o
network/boot/libNetwork.a: network/boot/CMakeFiles/Network.dir/build.make
network/boot/libNetwork.a: network/boot/CMakeFiles/Network.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/github/MusicPlayer/server/src/bld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libNetwork.a"
	cd /root/github/MusicPlayer/server/src/bld/network/boot && $(CMAKE_COMMAND) -P CMakeFiles/Network.dir/cmake_clean_target.cmake
	cd /root/github/MusicPlayer/server/src/bld/network/boot && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Network.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
network/boot/CMakeFiles/Network.dir/build: network/boot/libNetwork.a
.PHONY : network/boot/CMakeFiles/Network.dir/build

network/boot/CMakeFiles/Network.dir/clean:
	cd /root/github/MusicPlayer/server/src/bld/network/boot && $(CMAKE_COMMAND) -P CMakeFiles/Network.dir/cmake_clean.cmake
.PHONY : network/boot/CMakeFiles/Network.dir/clean

network/boot/CMakeFiles/Network.dir/depend:
	cd /root/github/MusicPlayer/server/src/bld && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/github/MusicPlayer/server/src /root/github/MusicPlayer/server/src/network/boot /root/github/MusicPlayer/server/src/bld /root/github/MusicPlayer/server/src/bld/network/boot /root/github/MusicPlayer/server/src/bld/network/boot/CMakeFiles/Network.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : network/boot/CMakeFiles/Network.dir/depend

