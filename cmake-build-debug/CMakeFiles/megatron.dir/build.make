# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\msumi\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\msumi\AppData\Local\Programs\CLion\bin\cmake\win\x64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\BD2\Megatron

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\BD2\Megatron\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/megatron.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/megatron.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/megatron.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/megatron.dir/flags.make

CMakeFiles/megatron.dir/main.cpp.obj: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/main.cpp.obj: D:/BD2/Megatron/main.cpp
CMakeFiles/megatron.dir/main.cpp.obj: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\BD2\Megatron\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/megatron.dir/main.cpp.obj"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/main.cpp.obj -MF CMakeFiles\megatron.dir\main.cpp.obj.d -o CMakeFiles\megatron.dir\main.cpp.obj -c D:\BD2\Megatron\main.cpp

CMakeFiles/megatron.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/main.cpp.i"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\BD2\Megatron\main.cpp > CMakeFiles\megatron.dir\main.cpp.i

CMakeFiles/megatron.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/main.cpp.s"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\BD2\Megatron\main.cpp -o CMakeFiles\megatron.dir\main.cpp.s

CMakeFiles/megatron.dir/Megatron.cpp.obj: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Megatron.cpp.obj: D:/BD2/Megatron/Megatron.cpp
CMakeFiles/megatron.dir/Megatron.cpp.obj: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\BD2\Megatron\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/megatron.dir/Megatron.cpp.obj"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Megatron.cpp.obj -MF CMakeFiles\megatron.dir\Megatron.cpp.obj.d -o CMakeFiles\megatron.dir\Megatron.cpp.obj -c D:\BD2\Megatron\Megatron.cpp

CMakeFiles/megatron.dir/Megatron.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Megatron.cpp.i"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\BD2\Megatron\Megatron.cpp > CMakeFiles\megatron.dir\Megatron.cpp.i

CMakeFiles/megatron.dir/Megatron.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Megatron.cpp.s"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\BD2\Megatron\Megatron.cpp -o CMakeFiles\megatron.dir\Megatron.cpp.s

CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.obj: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.obj: D:/BD2/Megatron/Query_Processor/Parser.cpp
CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.obj: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\BD2\Megatron\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.obj"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.obj -MF CMakeFiles\megatron.dir\Query_Processor\Parser.cpp.obj.d -o CMakeFiles\megatron.dir\Query_Processor\Parser.cpp.obj -c D:\BD2\Megatron\Query_Processor\Parser.cpp

CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.i"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\BD2\Megatron\Query_Processor\Parser.cpp > CMakeFiles\megatron.dir\Query_Processor\Parser.cpp.i

CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.s"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\BD2\Megatron\Query_Processor\Parser.cpp -o CMakeFiles\megatron.dir\Query_Processor\Parser.cpp.s

CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.obj: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.obj: D:/BD2/Megatron/Storage_Manager/DiskManager.cpp
CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.obj: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\BD2\Megatron\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.obj"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.obj -MF CMakeFiles\megatron.dir\Storage_Manager\DiskManager.cpp.obj.d -o CMakeFiles\megatron.dir\Storage_Manager\DiskManager.cpp.obj -c D:\BD2\Megatron\Storage_Manager\DiskManager.cpp

CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.i"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\BD2\Megatron\Storage_Manager\DiskManager.cpp > CMakeFiles\megatron.dir\Storage_Manager\DiskManager.cpp.i

CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.s"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\BD2\Megatron\Storage_Manager\DiskManager.cpp -o CMakeFiles\megatron.dir\Storage_Manager\DiskManager.cpp.s

CMakeFiles/megatron.dir/Util/myFunc.cpp.obj: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Util/myFunc.cpp.obj: D:/BD2/Megatron/Util/myFunc.cpp
CMakeFiles/megatron.dir/Util/myFunc.cpp.obj: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\BD2\Megatron\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/megatron.dir/Util/myFunc.cpp.obj"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Util/myFunc.cpp.obj -MF CMakeFiles\megatron.dir\Util\myFunc.cpp.obj.d -o CMakeFiles\megatron.dir\Util\myFunc.cpp.obj -c D:\BD2\Megatron\Util\myFunc.cpp

CMakeFiles/megatron.dir/Util/myFunc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Util/myFunc.cpp.i"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\BD2\Megatron\Util\myFunc.cpp > CMakeFiles\megatron.dir\Util\myFunc.cpp.i

CMakeFiles/megatron.dir/Util/myFunc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Util/myFunc.cpp.s"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\BD2\Megatron\Util\myFunc.cpp -o CMakeFiles\megatron.dir\Util\myFunc.cpp.s

CMakeFiles/megatron.dir/Query_Processor/ExecutionEngine.cpp.obj: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Query_Processor/ExecutionEngine.cpp.obj: D:/BD2/Megatron/Query_Processor/ExecutionEngine.cpp
CMakeFiles/megatron.dir/Query_Processor/ExecutionEngine.cpp.obj: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\BD2\Megatron\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/megatron.dir/Query_Processor/ExecutionEngine.cpp.obj"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Query_Processor/ExecutionEngine.cpp.obj -MF CMakeFiles\megatron.dir\Query_Processor\ExecutionEngine.cpp.obj.d -o CMakeFiles\megatron.dir\Query_Processor\ExecutionEngine.cpp.obj -c D:\BD2\Megatron\Query_Processor\ExecutionEngine.cpp

CMakeFiles/megatron.dir/Query_Processor/ExecutionEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Query_Processor/ExecutionEngine.cpp.i"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\BD2\Megatron\Query_Processor\ExecutionEngine.cpp > CMakeFiles\megatron.dir\Query_Processor\ExecutionEngine.cpp.i

CMakeFiles/megatron.dir/Query_Processor/ExecutionEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Query_Processor/ExecutionEngine.cpp.s"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\BD2\Megatron\Query_Processor\ExecutionEngine.cpp -o CMakeFiles\megatron.dir\Query_Processor\ExecutionEngine.cpp.s

CMakeFiles/megatron.dir/Query_Processor/Schema.cpp.obj: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Query_Processor/Schema.cpp.obj: D:/BD2/Megatron/Query_Processor/Schema.cpp
CMakeFiles/megatron.dir/Query_Processor/Schema.cpp.obj: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\BD2\Megatron\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/megatron.dir/Query_Processor/Schema.cpp.obj"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Query_Processor/Schema.cpp.obj -MF CMakeFiles\megatron.dir\Query_Processor\Schema.cpp.obj.d -o CMakeFiles\megatron.dir\Query_Processor\Schema.cpp.obj -c D:\BD2\Megatron\Query_Processor\Schema.cpp

CMakeFiles/megatron.dir/Query_Processor/Schema.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Query_Processor/Schema.cpp.i"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\BD2\Megatron\Query_Processor\Schema.cpp > CMakeFiles\megatron.dir\Query_Processor\Schema.cpp.i

CMakeFiles/megatron.dir/Query_Processor/Schema.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Query_Processor/Schema.cpp.s"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\BD2\Megatron\Query_Processor\Schema.cpp -o CMakeFiles\megatron.dir\Query_Processor\Schema.cpp.s

CMakeFiles/megatron.dir/Query_Processor/Page.cpp.obj: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Query_Processor/Page.cpp.obj: D:/BD2/Megatron/Query_Processor/Page.cpp
CMakeFiles/megatron.dir/Query_Processor/Page.cpp.obj: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\BD2\Megatron\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/megatron.dir/Query_Processor/Page.cpp.obj"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Query_Processor/Page.cpp.obj -MF CMakeFiles\megatron.dir\Query_Processor\Page.cpp.obj.d -o CMakeFiles\megatron.dir\Query_Processor\Page.cpp.obj -c D:\BD2\Megatron\Query_Processor\Page.cpp

CMakeFiles/megatron.dir/Query_Processor/Page.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Query_Processor/Page.cpp.i"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\BD2\Megatron\Query_Processor\Page.cpp > CMakeFiles\megatron.dir\Query_Processor\Page.cpp.i

CMakeFiles/megatron.dir/Query_Processor/Page.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Query_Processor/Page.cpp.s"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\BD2\Megatron\Query_Processor\Page.cpp -o CMakeFiles\megatron.dir\Query_Processor\Page.cpp.s

CMakeFiles/megatron.dir/Query_Processor/Record.cpp.obj: CMakeFiles/megatron.dir/flags.make
CMakeFiles/megatron.dir/Query_Processor/Record.cpp.obj: D:/BD2/Megatron/Query_Processor/Record.cpp
CMakeFiles/megatron.dir/Query_Processor/Record.cpp.obj: CMakeFiles/megatron.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\BD2\Megatron\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/megatron.dir/Query_Processor/Record.cpp.obj"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/megatron.dir/Query_Processor/Record.cpp.obj -MF CMakeFiles\megatron.dir\Query_Processor\Record.cpp.obj.d -o CMakeFiles\megatron.dir\Query_Processor\Record.cpp.obj -c D:\BD2\Megatron\Query_Processor\Record.cpp

CMakeFiles/megatron.dir/Query_Processor/Record.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/megatron.dir/Query_Processor/Record.cpp.i"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\BD2\Megatron\Query_Processor\Record.cpp > CMakeFiles\megatron.dir\Query_Processor\Record.cpp.i

CMakeFiles/megatron.dir/Query_Processor/Record.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/megatron.dir/Query_Processor/Record.cpp.s"
	C:\Users\msumi\AppData\Local\Programs\CLion\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\BD2\Megatron\Query_Processor\Record.cpp -o CMakeFiles\megatron.dir\Query_Processor\Record.cpp.s

# Object files for target megatron
megatron_OBJECTS = \
"CMakeFiles/megatron.dir/main.cpp.obj" \
"CMakeFiles/megatron.dir/Megatron.cpp.obj" \
"CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.obj" \
"CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.obj" \
"CMakeFiles/megatron.dir/Util/myFunc.cpp.obj" \
"CMakeFiles/megatron.dir/Query_Processor/ExecutionEngine.cpp.obj" \
"CMakeFiles/megatron.dir/Query_Processor/Schema.cpp.obj" \
"CMakeFiles/megatron.dir/Query_Processor/Page.cpp.obj" \
"CMakeFiles/megatron.dir/Query_Processor/Record.cpp.obj"

# External object files for target megatron
megatron_EXTERNAL_OBJECTS =

megatron.exe: CMakeFiles/megatron.dir/main.cpp.obj
megatron.exe: CMakeFiles/megatron.dir/Megatron.cpp.obj
megatron.exe: CMakeFiles/megatron.dir/Query_Processor/Parser.cpp.obj
megatron.exe: CMakeFiles/megatron.dir/Storage_Manager/DiskManager.cpp.obj
megatron.exe: CMakeFiles/megatron.dir/Util/myFunc.cpp.obj
megatron.exe: CMakeFiles/megatron.dir/Query_Processor/ExecutionEngine.cpp.obj
megatron.exe: CMakeFiles/megatron.dir/Query_Processor/Schema.cpp.obj
megatron.exe: CMakeFiles/megatron.dir/Query_Processor/Page.cpp.obj
megatron.exe: CMakeFiles/megatron.dir/Query_Processor/Record.cpp.obj
megatron.exe: CMakeFiles/megatron.dir/build.make
megatron.exe: CMakeFiles/megatron.dir/linkLibs.rsp
megatron.exe: CMakeFiles/megatron.dir/objects1.rsp
megatron.exe: CMakeFiles/megatron.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\BD2\Megatron\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable megatron.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\megatron.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/megatron.dir/build: megatron.exe
.PHONY : CMakeFiles/megatron.dir/build

CMakeFiles/megatron.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\megatron.dir\cmake_clean.cmake
.PHONY : CMakeFiles/megatron.dir/clean

CMakeFiles/megatron.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\BD2\Megatron D:\BD2\Megatron D:\BD2\Megatron\cmake-build-debug D:\BD2\Megatron\cmake-build-debug D:\BD2\Megatron\cmake-build-debug\CMakeFiles\megatron.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/megatron.dir/depend

