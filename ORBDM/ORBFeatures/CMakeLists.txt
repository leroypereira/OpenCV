cmake_minimum_required(VERSION 2.8)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

project( ORBDM )

#Add openCV to the project
find_package(OpenCV REQUIRED)

#additional include directories
include_directories("$(PROJECT_SOURCE_DIR)/inc")

add_executable( ORBDM src/ORBDemo.cpp src/ORBExtractor.cpp
					  src/ORBFileReader.cpp)
target_link_libraries( ORBDM ${OpenCV_LIBS})
