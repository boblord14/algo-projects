cmake_minimum_required(VERSION 4.1.2)
project(algo_projects)

set(CMAKE_CXX_STANDARD 14)

add_executable(prb1 "hw3/problem 1/Donut.cpp"
        "hw3/problem 3/LongestIncreasingSubseqRecursive.cpp"
        "hw3/problem 3/LongestIncreasingSubseqDP.cpp")