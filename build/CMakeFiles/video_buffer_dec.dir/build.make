# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/newspace/ocr/003src/video_codec/ffmpeg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/newspace/ocr/003src/video_codec/ffmpeg/build

# Include any dependencies generated for this target.
include CMakeFiles/video_buffer_dec.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/video_buffer_dec.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/video_buffer_dec.dir/flags.make

CMakeFiles/video_buffer_dec.dir/test_video_dec_buf.cpp.o: CMakeFiles/video_buffer_dec.dir/flags.make
CMakeFiles/video_buffer_dec.dir/test_video_dec_buf.cpp.o: ../test_video_dec_buf.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/newspace/ocr/003src/video_codec/ffmpeg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/video_buffer_dec.dir/test_video_dec_buf.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/video_buffer_dec.dir/test_video_dec_buf.cpp.o -c /home/ubuntu/newspace/ocr/003src/video_codec/ffmpeg/test_video_dec_buf.cpp

CMakeFiles/video_buffer_dec.dir/test_video_dec_buf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/video_buffer_dec.dir/test_video_dec_buf.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/newspace/ocr/003src/video_codec/ffmpeg/test_video_dec_buf.cpp > CMakeFiles/video_buffer_dec.dir/test_video_dec_buf.cpp.i

CMakeFiles/video_buffer_dec.dir/test_video_dec_buf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/video_buffer_dec.dir/test_video_dec_buf.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/newspace/ocr/003src/video_codec/ffmpeg/test_video_dec_buf.cpp -o CMakeFiles/video_buffer_dec.dir/test_video_dec_buf.cpp.s

# Object files for target video_buffer_dec
video_buffer_dec_OBJECTS = \
"CMakeFiles/video_buffer_dec.dir/test_video_dec_buf.cpp.o"

# External object files for target video_buffer_dec
video_buffer_dec_EXTERNAL_OBJECTS =

../bin/video_buffer_dec: CMakeFiles/video_buffer_dec.dir/test_video_dec_buf.cpp.o
../bin/video_buffer_dec: CMakeFiles/video_buffer_dec.dir/build.make
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_dnn.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_highgui.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_ml.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_objdetect.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_shape.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_stitching.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_superres.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_videostab.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_calib3d.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_features2d.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_flann.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_photo.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_video.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_videoio.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_imgcodecs.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_imgproc.so.3.4.9
../bin/video_buffer_dec: /home/ubuntu/newspace/3th-party/opencv-3.4.9/build/lib/libopencv_core.so.3.4.9
../bin/video_buffer_dec: CMakeFiles/video_buffer_dec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/newspace/ocr/003src/video_codec/ffmpeg/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/video_buffer_dec"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/video_buffer_dec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/video_buffer_dec.dir/build: ../bin/video_buffer_dec

.PHONY : CMakeFiles/video_buffer_dec.dir/build

CMakeFiles/video_buffer_dec.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/video_buffer_dec.dir/cmake_clean.cmake
.PHONY : CMakeFiles/video_buffer_dec.dir/clean

CMakeFiles/video_buffer_dec.dir/depend:
	cd /home/ubuntu/newspace/ocr/003src/video_codec/ffmpeg/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/newspace/ocr/003src/video_codec/ffmpeg /home/ubuntu/newspace/ocr/003src/video_codec/ffmpeg /home/ubuntu/newspace/ocr/003src/video_codec/ffmpeg/build /home/ubuntu/newspace/ocr/003src/video_codec/ffmpeg/build /home/ubuntu/newspace/ocr/003src/video_codec/ffmpeg/build/CMakeFiles/video_buffer_dec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/video_buffer_dec.dir/depend

