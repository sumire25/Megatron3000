# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /home/sumire/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/sumire/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sumire/CLionProjects/Megatron3000

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sumire/CLionProjects/Megatron3000/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/megatron.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/megatron.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/megatron.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/megatron.dir/flags.make

CMakeFiles/megatron.dir/main.cpp.o: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/main.cpp.o: /home/sumire/CLionProjects/Megatron3000/main.cpp
CMakeFiles/megatron.dir/main.cpp.o: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sumire/CLionProjects/Megatron3000/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/megatron.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/main.cpp.o -MF CMakeFiles/megatron.dir/main.cpp.o.d -o CMakeFiles/megatron.dir/main.cpp.o -c /home/sumire/CLionProjects/Megatron3000/main.cpp

CMakeFiles/megatron.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumire/CLionProjects/Megatron3000/main.cpp > CMakeFiles/megatron.dir/main.cpp.i

CMakeFiles/megatron.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumire/CLionProjects/Megatron3000/main.cpp -o CMakeFiles/megatron.dir/main.cpp.s

CMakeFiles/megatron.dir/Megatron.cpp.o: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Megatron.cpp.o: /home/sumire/CLionProjects/Megatron3000/Megatron.cpp
CMakeFiles/megatron.dir/Megatron.cpp.o: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sumire/CLionProjects/Megatron3000/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/megatron.dir/Megatron.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Megatron.cpp.o -MF CMakeFiles/megatron.dir/Megatron.cpp.o.d -o CMakeFiles/megatron.dir/Megatron.cpp.o -c /home/sumire/CLionProjects/Megatron3000/Megatron.cpp

CMakeFiles/megatron.dir/Megatron.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Megatron.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumire/CLionProjects/Megatron3000/Megatron.cpp > CMakeFiles/megatron.dir/Megatron.cpp.i

CMakeFiles/megatron.dir/Megatron.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Megatron.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumire/CLionProjects/Megatron3000/Megatron.cpp -o CMakeFiles/megatron.dir/Megatron.cpp.s

CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.o: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.o: /home/sumire/CLionProjects/Megatron3000/Query_Processor/Parser.cpp
CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.o: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sumire/CLionProjects/Megatron3000/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.o -MF CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.o.d -o CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.o -c /home/sumire/CLionProjects/Megatron3000/Query_Processor/Parser.cpp

CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumire/CLionProjects/Megatron3000/Query_Processor/Parser.cpp > CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.i

CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumire/CLionProjects/Megatron3000/Query_Processor/Parser.cpp -o CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.s

CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.o: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.o: /home/sumire/CLionProjects/Megatron3000/Storage_Manager/DiskManager.cpp
CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.o: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sumire/CLionProjects/Megatron3000/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.o -MF CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.o.d -o CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.o -c /home/sumire/CLionProjects/Megatron3000/Storage_Manager/DiskManager.cpp

CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumire/CLionProjects/Megatron3000/Storage_Manager/DiskManager.cpp > CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.i

CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumire/CLionProjects/Megatron3000/Storage_Manager/DiskManager.cpp -o CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.s

CMakeFiles/megatron.dir/Util/myFunc.cpp.o: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Util/myFunc.cpp.o: /home/sumire/CLionProjects/Megatron3000/Util/myFunc.cpp
CMakeFiles/megatron.dir/Util/myFunc.cpp.o: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sumire/CLionProjects/Megatron3000/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/megatron.dir/Util/myFunc.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Util/myFunc.cpp.o -MF CMakeFiles/megatron.dir/Util/myFunc.cpp.o.d -o CMakeFiles/megatron.dir/Util/myFunc.cpp.o -c /home/sumire/CLionProjects/Megatron3000/Util/myFunc.cpp

CMakeFiles/megatron.dir/Util/myFunc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Util/myFunc.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumire/CLionProjects/Megatron3000/Util/myFunc.cpp > CMakeFiles/megatron.dir/Util/myFunc.cpp.i

CMakeFiles/megatron.dir/Util/myFunc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Util/myFunc.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumire/CLionProjects/Megatron3000/Util/myFunc.cpp -o CMakeFiles/megatron.dir/Util/myFunc.cpp.s

CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.o: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.o: /home/sumire/CLionProjects/Megatron3000/Storage_Manager/FileManager.cpp
CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.o: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sumire/CLionProjects/Megatron3000/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.o -MF CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.o.d -o CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.o -c /home/sumire/CLionProjects/Megatron3000/Storage_Manager/FileManager.cpp

CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumire/CLionProjects/Megatron3000/Storage_Manager/FileManager.cpp > CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.i

CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumire/CLionProjects/Megatron3000/Storage_Manager/FileManager.cpp -o CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.s

CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.o: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.o: /home/sumire/CLionProjects/Megatron3000/Storage_Manager/Schema.cpp
CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.o: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sumire/CLionProjects/Megatron3000/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.o -MF CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.o.d -o CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.o -c /home/sumire/CLionProjects/Megatron3000/Storage_Manager/Schema.cpp

CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sumire/CLionProjects/Megatron3000/Storage_Manager/Schema.cpp > CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.i

CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sumire/CLionProjects/Megatron3000/Storage_Manager/Schema.cpp -o CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.s

# Object files for target megatron
megatron_OBJECTS = \
"CMakeFiles/megatron.dir/main.cpp.o" \
"CMakeFiles/megatron.dir/Megatron.cpp.o" \
"CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.o" \
"CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.o" \
"CMakeFiles/megatron.dir/Util/myFunc.cpp.o" \
"CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.o" \
"CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.o"

# External object files for target megatron
megatron_EXTERNAL_OBJECTS =

megatron: CMakeFiles/megatron.dir/main.cpp.o
megatron: CMakeFiles/megatron.dir/Megatron.cpp.o
megatron: CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.o
megatron: CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.o
megatron: CMakeFiles/megatron.dir/Util/myFunc.cpp.o
megatron: CMakeFiles/megatron.dir/Storage_Manager/FileManager.cpp.o
megatron: CMakeFiles/megatron.dir/Storage_Manager/Schema.cpp.o
megatron: CMakeFiles/megatron.dir/build.make
megatron: CMakeFiles/megatron.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/sumire/CLionProjects/Megatron3000/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable megatron"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/megatron.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/megatron.dir/build: megatron
.PHONY : CMakeFiles/megatron.dir/build

CMakeFiles/megatron.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/megatron.dir/cmake_clean.cmake
.PHONY : CMakeFiles/megatron.dir/clean

CMakeFiles/megatron.dir/depend:
	cd /home/sumire/CLionProjects/Megatron3000/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sumire/CLionProjects/Megatron3000 /home/sumire/CLionProjects/Megatron3000 /home/sumire/CLionProjects/Megatron3000/cmake-build-debug /home/sumire/CLionProjects/Megatron3000/cmake-build-debug /home/sumire/CLionProjects/Megatron3000/cmake-build-debug/CMakeFiles/megatron.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/megatron.dir/depend

