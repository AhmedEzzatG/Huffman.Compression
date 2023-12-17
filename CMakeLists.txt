cmake_minimum_required(VERSION 3.27)
project(CompressionTool)

set(CMAKE_CXX_STANDARD 17)

add_executable(CompressionTool main.cpp
        bitstream.cpp
        bitstream.hpp
        huffman.cpp
        huffman.hpp
        priority_queue.cpp
        my_priority_queue.hpp
)
