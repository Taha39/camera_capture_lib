cmake_minimum_required(VERSION 3.7)

set(OPENCV_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/opencv411_vc15/include)
#set(OPENCV_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/opencv411_vc15/lib)

add_library(cam_capture 
	Capturer.h
	camera_capture.h
	camera_capture.cpp
	)
	
target_include_directories(cam_capture PUBLIC 
	$<BUILD_INTERFACE:${OPENCV_INCLUDE_PATH}>
	#$<BUILD_INTERFACE:${OPENCV_LIB_PATH}>
)

#target_link_directories( cam_capture PUBLIC
#	$<BUILD_INTERFACE:${OPENCV_LIB_PATH}>
#)

#target_link_libraries( cam_capture
#	opencv_world411d.lib
#)

set_target_properties(cam_capture PROPERTIES 
	CXX_STANDARD 17
)