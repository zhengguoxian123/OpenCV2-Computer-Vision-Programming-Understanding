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
CMAKE_SOURCE_DIR = /home/zgx/opencv2_practicecode/Chapter_10/tracking

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zgx/opencv2_practicecode/Chapter_10/tracking/build

# Include any dependencies generated for this target.
include CMakeFiles/tracking.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tracking.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tracking.dir/flags.make

CMakeFiles/tracking.dir/tracking.cpp.o: CMakeFiles/tracking.dir/flags.make
CMakeFiles/tracking.dir/tracking.cpp.o: ../tracking.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zgx/opencv2_practicecode/Chapter_10/tracking/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tracking.dir/tracking.cpp.o"
	/usr/lib/ccache/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tracking.dir/tracking.cpp.o -c /home/zgx/opencv2_practicecode/Chapter_10/tracking/tracking.cpp

CMakeFiles/tracking.dir/tracking.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tracking.dir/tracking.cpp.i"
	/usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zgx/opencv2_practicecode/Chapter_10/tracking/tracking.cpp > CMakeFiles/tracking.dir/tracking.cpp.i

CMakeFiles/tracking.dir/tracking.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tracking.dir/tracking.cpp.s"
	/usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zgx/opencv2_practicecode/Chapter_10/tracking/tracking.cpp -o CMakeFiles/tracking.dir/tracking.cpp.s

CMakeFiles/tracking.dir/tracking.cpp.o.requires:
.PHONY : CMakeFiles/tracking.dir/tracking.cpp.o.requires

CMakeFiles/tracking.dir/tracking.cpp.o.provides: CMakeFiles/tracking.dir/tracking.cpp.o.requires
	$(MAKE) -f CMakeFiles/tracking.dir/build.make CMakeFiles/tracking.dir/tracking.cpp.o.provides.build
.PHONY : CMakeFiles/tracking.dir/tracking.cpp.o.provides

CMakeFiles/tracking.dir/tracking.cpp.o.provides.build: CMakeFiles/tracking.dir/tracking.cpp.o

# Object files for target tracking
tracking_OBJECTS = \
"CMakeFiles/tracking.dir/tracking.cpp.o"

# External object files for target tracking
tracking_EXTERNAL_OBJECTS =

tracking: CMakeFiles/tracking.dir/tracking.cpp.o
tracking: CMakeFiles/tracking.dir/build.make
tracking: /usr/local/opencv2/lib/libopencv_videostab.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_video.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_ts.a
tracking: /usr/local/opencv2/lib/libopencv_superres.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_stitching.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_photo.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_ocl.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_objdetect.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_nonfree.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_ml.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_legacy.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_imgproc.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_highgui.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_gpu.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_flann.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_features2d.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_core.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_contrib.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_calib3d.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_nonfree.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_ocl.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_gpu.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_photo.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_objdetect.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_legacy.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_video.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_ml.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_calib3d.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_features2d.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_highgui.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_imgproc.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_flann.so.2.4.13
tracking: /usr/local/opencv2/lib/libopencv_core.so.2.4.13
tracking: CMakeFiles/tracking.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable tracking"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tracking.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tracking.dir/build: tracking
.PHONY : CMakeFiles/tracking.dir/build

CMakeFiles/tracking.dir/requires: CMakeFiles/tracking.dir/tracking.cpp.o.requires
.PHONY : CMakeFiles/tracking.dir/requires

CMakeFiles/tracking.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tracking.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tracking.dir/clean

CMakeFiles/tracking.dir/depend:
	cd /home/zgx/opencv2_practicecode/Chapter_10/tracking/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zgx/opencv2_practicecode/Chapter_10/tracking /home/zgx/opencv2_practicecode/Chapter_10/tracking /home/zgx/opencv2_practicecode/Chapter_10/tracking/build /home/zgx/opencv2_practicecode/Chapter_10/tracking/build /home/zgx/opencv2_practicecode/Chapter_10/tracking/build/CMakeFiles/tracking.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tracking.dir/depend

