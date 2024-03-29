cmake_minimum_required(VERSION 2.8)
project(kdtrees)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -g -O3 -fopenmp")

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND LIBRARIES_LIST ${Boost_LIBRARIES} )

find_package(OpenCV 2 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
list(APPEND LIBRARIES_LIST ${OpenCV_LIBRARIES} )

find_package(Eigen3 REQUIRED eigen3)
include_directories(${EIGEN_INCLUDE_DIRS})

include_directories(include)

add_library(kdtrees
	    	src/points.cpp
	    	src/csv_file_handler.cpp
	    	src/build_kd_tree.cpp
	    	src/nearest_nbr_kd_tree.cpp
	    	src/test.cpp
	    	)

target_link_libraries(kdtrees ${LIBRARIES_LIST})

add_executable(runTest src/run_test.cpp)
target_link_libraries(runTest kdtrees)

add_executable(runBuildKdTree src/run_build_kd_tree.cpp)
target_link_libraries(runBuildKdTree kdtrees)

add_executable(runNNSearch src/run_nn_search.cpp)
target_link_libraries(runNNSearch kdtrees)

	
