cmake_minimum_required(VERSION 3.4)
project(video_buffer_dec)

set(CMAKE_BUILD_TYPE "Debug")

IF (CMAKE_BUILD_TYPE STREQUAL Debug)
    ADD_DEFINITIONS(-DDEBUG)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -w")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
ENDIF()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -std=c++14")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Opencv
set(OpenCV_DIR "/home/ubuntu/newspace/3th-party/opencv-3.4.9/build")
find_package(OpenCV 3 REQUIRED)

add_executable(${PROJECT_NAME}
    test_video_dec_buf.cpp
    )
target_link_libraries(${PROJECT_NAME}
    ${OpenCV_LIBS}
    avformat avutil avcodec swscale
    pthread
    )

