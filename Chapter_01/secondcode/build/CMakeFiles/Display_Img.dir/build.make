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
CMAKE_SOURCE_DIR = /home/zgx/opencv2_practicecode/secondcode

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zgx/opencv2_practicecode/secondcode/build

# Include any dependencies generated for this target.
include CMakeFiles/Display_Img.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Display_Img.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Display_Img.dir/flags.make

CMakeFiles/Display_Img.dir/Display_Img.cpp.o: CMakeFiles/Display_Img.dir/flags.make
CMakeFiles/Display_Img.dir/Display_Img.cpp.o: ../Display_Img.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zgx/opencv2_practicecode/secondcode/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Display_Img.dir/Display_Img.cpp.o"
	/usr/lib/ccache/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Display_Img.dir/Display_Img.cpp.o -c /home/zgx/opencv2_practicecode/secondcode/Display_Img.cpp

CMakeFiles/Display_Img.dir/Display_Img.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Display_Img.dir/Display_Img.cpp.i"
	/usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zgx/opencv2_practicecode/secondcode/Display_Img.cpp > CMakeFiles/Display_Img.dir/Display_Img.cpp.i

CMakeFiles/Display_Img.dir/Display_Img.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Display_Img.dir/Display_Img.cpp.s"
	/usr/lib/ccache/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zgx/opencv2_practicecode/secondcode/Display_Img.cpp -o CMakeFiles/Display_Img.dir/Display_Img.cpp.s

CMakeFiles/Display_Img.dir/Display_Img.cpp.o.requires:
.PHONY : CMakeFiles/Display_Img.dir/Display_Img.cpp.o.requires

CMakeFiles/Display_Img.dir/Display_Img.cpp.o.provides: CMakeFiles/Display_Img.dir/Display_Img.cpp.o.requires
	$(MAKE) -f CMakeFiles/Display_Img.dir/build.make CMakeFiles/Display_Img.dir/Display_Img.cpp.o.provides.build
.PHONY : CMakeFiles/Display_Img.dir/Display_Img.cpp.o.provides

CMakeFiles/Display_Img.dir/Display_Img.cpp.o.provides.build: CMakeFiles/Display_Img.dir/Display_Img.cpp.o

# Object files for target Display_Img
Display_Img_OBJECTS = \
"CMakeFiles/Display_Img.dir/Display_Img.cpp.o"

# External object files for target Display_Img
Display_Img_EXTERNAL_OBJECTS =

Display_Img: CMakeFiles/Display_Img.dir/Display_Img.cpp.o
Display_Img: CMakeFiles/Display_Img.dir/build.make
Display_Img: /usr/local/lib/libopencv_calib3d.so.3.2.0
Display_Img: /usr/local/lib/libopencv_core.so.3.2.0
Display_Img: /usr/local/lib/libopencv_features2d.so.3.2.0
Display_Img: /usr/local/lib/libopencv_flann.so.3.2.0
Display_Img: /usr/local/lib/libopencv_highgui.so.3.2.0
Display_Img: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
Display_Img: /usr/local/lib/libopencv_imgproc.so.3.2.0
Display_Img: /usr/local/lib/libopencv_ml.so.3.2.0
Display_Img: /usr/local/lib/libopencv_objdetect.so.3.2.0
Display_Img: /usr/local/lib/libopencv_photo.so.3.2.0
Display_Img: /usr/local/lib/libopencv_shape.so.3.2.0
Display_Img: /usr/local/lib/libopencv_stitching.so.3.2.0
Display_Img: /usr/local/lib/libopencv_superres.so.3.2.0
Display_Img: /usr/local/lib/libopencv_video.so.3.2.0
Display_Img: /usr/local/lib/libopencv_videoio.so.3.2.0
Display_Img: /usr/local/lib/libopencv_videostab.so.3.2.0
Display_Img: /usr/local/lib/libopencv_viz.so.3.2.0
Display_Img: /usr/local/lib/libopencv_objdetect.so.3.2.0
Display_Img: /usr/local/lib/libopencv_calib3d.so.3.2.0
Display_Img: /usr/local/lib/libopencv_features2d.so.3.2.0
Display_Img: /usr/local/lib/libopencv_flann.so.3.2.0
Display_Img: /usr/local/lib/libopencv_highgui.so.3.2.0
Display_Img: /usr/local/lib/libopencv_ml.so.3.2.0
Display_Img: /usr/local/lib/libopencv_photo.so.3.2.0
Display_Img: /usr/local/lib/libopencv_video.so.3.2.0
Display_Img: /usr/local/lib/libopencv_videoio.so.3.2.0
Display_Img: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
Display_Img: /usr/local/lib/libopencv_imgproc.so.3.2.0
Display_Img: /usr/local/lib/libopencv_core.so.3.2.0
Display_Img: CMakeFiles/Display_Img.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Display_Img"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Display_Img.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Display_Img.dir/build: Display_Img
.PHONY : CMakeFiles/Display_Img.dir/build

CMakeFiles/Display_Img.dir/requires: CMakeFiles/Display_Img.dir/Display_Img.cpp.o.requires
.PHONY : CMakeFiles/Display_Img.dir/requires

CMakeFiles/Display_Img.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Display_Img.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Display_Img.dir/clean

CMakeFiles/Display_Img.dir/depend:
	cd /home/zgx/opencv2_practicecode/secondcode/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zgx/opencv2_practicecode/secondcode /home/zgx/opencv2_practicecode/secondcode /home/zgx/opencv2_practicecode/secondcode/build /home/zgx/opencv2_practicecode/secondcode/build /home/zgx/opencv2_practicecode/secondcode/build/CMakeFiles/Display_Img.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Display_Img.dir/depend

