# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build

# Include any dependencies generated for this target.
include CMakeFiles/MyProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyProject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyProject.dir/flags.make

generated/chat.pb.cc: /home/gevor/Desktop/messenger/proto/chat.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating generated/chat.pb.cc, generated/chat.pb.h"
	/usr/local/bin/protoc --proto_path=/home/gevor/Desktop/messenger/proto --cpp_out=/home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/generated /home/gevor/Desktop/messenger/proto/chat.proto

generated/chat.pb.h: generated/chat.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate generated/chat.pb.h

generated/chat.grpc.pb.cc: /home/gevor/Desktop/messenger/proto/chat.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating generated/chat.grpc.pb.cc, generated/chat.grpc.pb.h"
	/usr/local/bin/protoc --proto_path=/home/gevor/Desktop/messenger/proto --grpc_out=/home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/generated --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin /home/gevor/Desktop/messenger/proto/chat.proto

generated/chat.grpc.pb.h: generated/chat.grpc.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate generated/chat.grpc.pb.h

ui_mainwindow.h: ../mainwindow.ui
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Generating ui_mainwindow.h"
	/usr/lib/qt5/bin/uic -o /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/ui_mainwindow.h /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/mainwindow.ui

CMakeFiles/MyProject.dir/main.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/main.cpp.o: ../main.cpp
CMakeFiles/MyProject.dir/main.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MyProject.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/main.cpp.o -MF CMakeFiles/MyProject.dir/main.cpp.o.d -o CMakeFiles/MyProject.dir/main.cpp.o -c /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/main.cpp

CMakeFiles/MyProject.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/main.cpp > CMakeFiles/MyProject.dir/main.cpp.i

CMakeFiles/MyProject.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/main.cpp -o CMakeFiles/MyProject.dir/main.cpp.s

CMakeFiles/MyProject.dir/mainwindow.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/mainwindow.cpp.o: ../mainwindow.cpp
CMakeFiles/MyProject.dir/mainwindow.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MyProject.dir/mainwindow.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/mainwindow.cpp.o -MF CMakeFiles/MyProject.dir/mainwindow.cpp.o.d -o CMakeFiles/MyProject.dir/mainwindow.cpp.o -c /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/mainwindow.cpp

CMakeFiles/MyProject.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/mainwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/mainwindow.cpp > CMakeFiles/MyProject.dir/mainwindow.cpp.i

CMakeFiles/MyProject.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/mainwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/mainwindow.cpp -o CMakeFiles/MyProject.dir/mainwindow.cpp.s

CMakeFiles/MyProject.dir/validatorfactory.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/validatorfactory.cpp.o: ../validatorfactory.cpp
CMakeFiles/MyProject.dir/validatorfactory.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MyProject.dir/validatorfactory.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/validatorfactory.cpp.o -MF CMakeFiles/MyProject.dir/validatorfactory.cpp.o.d -o CMakeFiles/MyProject.dir/validatorfactory.cpp.o -c /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/validatorfactory.cpp

CMakeFiles/MyProject.dir/validatorfactory.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/validatorfactory.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/validatorfactory.cpp > CMakeFiles/MyProject.dir/validatorfactory.cpp.i

CMakeFiles/MyProject.dir/validatorfactory.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/validatorfactory.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/validatorfactory.cpp -o CMakeFiles/MyProject.dir/validatorfactory.cpp.s

CMakeFiles/MyProject.dir/generated/chat.pb.cc.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/generated/chat.pb.cc.o: generated/chat.pb.cc
CMakeFiles/MyProject.dir/generated/chat.pb.cc.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/MyProject.dir/generated/chat.pb.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/generated/chat.pb.cc.o -MF CMakeFiles/MyProject.dir/generated/chat.pb.cc.o.d -o CMakeFiles/MyProject.dir/generated/chat.pb.cc.o -c /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/generated/chat.pb.cc

CMakeFiles/MyProject.dir/generated/chat.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/generated/chat.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/generated/chat.pb.cc > CMakeFiles/MyProject.dir/generated/chat.pb.cc.i

CMakeFiles/MyProject.dir/generated/chat.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/generated/chat.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/generated/chat.pb.cc -o CMakeFiles/MyProject.dir/generated/chat.pb.cc.s

CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.o: generated/chat.grpc.pb.cc
CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.o -MF CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.o.d -o CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.o -c /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/generated/chat.grpc.pb.cc

CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/generated/chat.grpc.pb.cc > CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.i

CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/generated/chat.grpc.pb.cc -o CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.s

# Object files for target MyProject
MyProject_OBJECTS = \
"CMakeFiles/MyProject.dir/main.cpp.o" \
"CMakeFiles/MyProject.dir/mainwindow.cpp.o" \
"CMakeFiles/MyProject.dir/validatorfactory.cpp.o" \
"CMakeFiles/MyProject.dir/generated/chat.pb.cc.o" \
"CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.o"

# External object files for target MyProject
MyProject_EXTERNAL_OBJECTS =

MyProject: CMakeFiles/MyProject.dir/main.cpp.o
MyProject: CMakeFiles/MyProject.dir/mainwindow.cpp.o
MyProject: CMakeFiles/MyProject.dir/validatorfactory.cpp.o
MyProject: CMakeFiles/MyProject.dir/generated/chat.pb.cc.o
MyProject: CMakeFiles/MyProject.dir/generated/chat.grpc.pb.cc.o
MyProject: CMakeFiles/MyProject.dir/build.make
MyProject: /usr/lib/x86_64-linux-gnu/libQt5WebSockets.so.5.15.3
MyProject: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
MyProject: /usr/local/lib/libgrpc++.a
MyProject: /usr/local/lib/libgrpc++_reflection.a
MyProject: /usr/local/lib/libprotobuf.a
MyProject: /usr/lib/x86_64-linux-gnu/libQt5Network.so.5.15.3
MyProject: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
MyProject: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
MyProject: /usr/local/lib/libgrpc++.a
MyProject: /usr/local/lib/libprotobuf.a
MyProject: /usr/local/lib/libgrpc.a
MyProject: /usr/local/lib/libssl.a
MyProject: /usr/local/lib/libcrypto.a
MyProject: /usr/local/lib/libz.a
MyProject: /usr/local/lib/libcares.a
MyProject: /usr/local/lib/libre2.a
MyProject: /usr/local/lib/libabsl_status.a
MyProject: /usr/local/lib/libabsl_cord.a
MyProject: /usr/local/lib/libabsl_hash.a
MyProject: /usr/local/lib/libabsl_bad_variant_access.a
MyProject: /usr/local/lib/libabsl_city.a
MyProject: /usr/local/lib/libabsl_raw_hash_set.a
MyProject: /usr/local/lib/libabsl_bad_optional_access.a
MyProject: /usr/local/lib/libabsl_hashtablez_sampler.a
MyProject: /usr/local/lib/libabsl_exponential_biased.a
MyProject: /usr/local/lib/libgpr.a
MyProject: /usr/local/lib/libabsl_synchronization.a
MyProject: /usr/local/lib/libabsl_stacktrace.a
MyProject: /usr/local/lib/libabsl_symbolize.a
MyProject: /usr/local/lib/libabsl_debugging_internal.a
MyProject: /usr/local/lib/libabsl_demangle_internal.a
MyProject: /usr/local/lib/libabsl_graphcycles_internal.a
MyProject: /usr/local/lib/libabsl_time.a
MyProject: /usr/local/lib/libabsl_civil_time.a
MyProject: /usr/local/lib/libabsl_time_zone.a
MyProject: /usr/local/lib/libabsl_malloc_internal.a
MyProject: /usr/local/lib/libabsl_str_format_internal.a
MyProject: /usr/local/lib/libabsl_strings.a
MyProject: /usr/local/lib/libabsl_strings_internal.a
MyProject: /usr/local/lib/libabsl_int128.a
MyProject: /usr/local/lib/libabsl_throw_delegate.a
MyProject: /usr/local/lib/libabsl_base.a
MyProject: /usr/local/lib/libabsl_raw_logging_internal.a
MyProject: /usr/local/lib/libabsl_dynamic_annotations.a
MyProject: /usr/local/lib/libabsl_log_severity.a
MyProject: /usr/local/lib/libabsl_spinlock_wait.a
MyProject: /usr/lib/x86_64-linux-gnu/librt.a
MyProject: /usr/local/lib/libaddress_sorting.a
MyProject: /usr/local/lib/libupb.a
MyProject: CMakeFiles/MyProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable MyProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyProject.dir/build: MyProject
.PHONY : CMakeFiles/MyProject.dir/build

CMakeFiles/MyProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyProject.dir/clean

CMakeFiles/MyProject.dir/depend: generated/chat.grpc.pb.cc
CMakeFiles/MyProject.dir/depend: generated/chat.grpc.pb.h
CMakeFiles/MyProject.dir/depend: generated/chat.pb.cc
CMakeFiles/MyProject.dir/depend: generated/chat.pb.h
CMakeFiles/MyProject.dir/depend: ui_mainwindow.h
	cd /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build /home/gevor/Desktop/messenger/src/MESSENGER/registrarion_page/build/CMakeFiles/MyProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyProject.dir/depend

