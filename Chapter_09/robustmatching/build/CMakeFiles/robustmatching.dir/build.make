# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/zgx/opencv2_practicecode/Chapter_09/robustmatching

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zgx/opencv2_practicecode/Chapter_09/robustmatching/build

# Include any dependencies generated for this target.
include CMakeFiles/robustmatching.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/robustmatching.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/robustmatching.dir/flags.make

CMakeFiles/robustmatching.dir/robustmatching.cpp.o: CMakeFiles/robustmatching.dir/flags.make
CMakeFiles/robustmatching.dir/robustmatching.cpp.o: ../robustmatching.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zgx/opencv2_practicecode/Chapter_09/robustmatching/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/robustmatching.dir/robustmatching.cpp.o"
	/usr/lib/ccache/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/robustmatching.dir/robustmatching.cpp.o -c /home/zgx/opencv2_practicecode/Chapter_09/robustmatching/robustmatching.cpp

CMakeFiles/robustmatching.dir/robustmatching.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/robustmatching.dir/robustmatching.cpp.i"
	/usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zgx/opencv2_practicecode/Chapter_09/robustmatching/robustmatching.cpp > CMakeFiles/robustmatching.dir/robustmatching.cpp.i

CMakeFiles/robustmatching.dir/robustmatching.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/robustmatching.dir/robustmatching.cpp.s"
	/usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zgx/opencv2_practicecode/Chapter_09/robustmatching/robustmatching.cpp -o CMakeFiles/robustmatching.dir/robustmatching.cpp.s

CMakeFiles/robustmatching.dir/robustmatching.cpp.o.requires:
.PHONY : CMakeFiles/robustmatching.dir/robustmatching.cpp.o.requires

CMakeFiles/robustmatching.dir/robustmatching.cpp.o.provides: CMakeFiles/robustmatching.dir/robustmatching.cpp.o.requires
	$(MAKE) -f CMakeFiles/robustmatching.dir/build.make CMakeFiles/robustmatching.dir/robustmatching.cpp.o.provides.build
.PHONY : CMakeFiles/robustmatching.dir/robustmatching.cpp.o.provides

CMakeFiles/robustmatching.dir/robustmatching.cpp.o.provides.build: CMakeFiles/robustmatching.dir/robustmatching.cpp.o

# Object files for target robustmatching
robustmatching_OBJECTS = \
"CMakeFiles/robustmatching.dir/robustmatching.cpp.o"

# External object files for target robustmatching
robustmatching_EXTERNAL_OBJECTS =

robustmatching: CMakeFiles/robustmatching.dir/robustmatching.cpp.o
robustmatching: CMakeFiles/robustmatching.dir/build.make
robustmatching: /usr/local/opencv2/lib/libopencv_videostab.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_video.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_ts.a
robustmatching: /usr/local/opencv2/lib/libopencv_superres.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_stitching.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_photo.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_ocl.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_objdetect.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_nonfree.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_ml.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_legacy.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_imgproc.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_highgui.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_gpu.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_flann.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_features2d.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_core.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_contrib.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_calib3d.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_nonfree.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_ocl.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_gpu.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_photo.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_objdetect.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_legacy.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_video.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_ml.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_calib3d.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_features2d.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_highgui.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_imgproc.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_flann.so.2.4.13
robustmatching: /usr/local/opencv2/lib/libopencv_core.so.2.4.13
robustmatching: CMakeFiles/robustmatching.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable robustmatching"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/robustmatching.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/robustmatching.dir/build: robustmatching
.PHONY : CMakeFiles/robustmatching.dir/build

CMakeFiles/robustmatching.dir/requires: CMakeFiles/robustmatching.dir/robustmatching.cpp.o.requires
.PHONY : CMakeFiles/robustmatching.dir/requires

CMakeFiles/robustmatching.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/robustmatching.dir/cmake_clean.cmake
.PHONY : CMakeFiles/robustmatching.dir/clean

CMakeFiles/robustmatching.dir/depend:
	cd /home/zgx/opencv2_practicecode/Chapter_09/robustmatching/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zgx/opencv2_practicecode/Chapter_09/robustmatching /home/zgx/opencv2_practicecode/Chapter_09/robustmatching /home/zgx/opencv2_practicecode/Chapter_09/robustmatching/build /home/zgx/opencv2_practicecode/Chapter_09/robustmatching/build /home/zgx/opencv2_practicecode/Chapter_09/robustmatching/build/CMakeFiles/robustmatching.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/robustmatching.dir/depend

