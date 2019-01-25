cmake_minimum_required(VERSION 2.8)
set (CMAKE_CXX_STANDARD 14)
project( DisplayImage )

find_package(OpenMP)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -O3")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
message(${CMAKE_CXX_FLAGS})

include_directories("/home/sdh/Downloads/local/include/")
link_directories("/home/sdh/Downloads/local/lib/")
add_executable( DisplayImage lineParallelIter.cpp f.cpp)
target_link_libraries( DisplayImage lept tesseract)
