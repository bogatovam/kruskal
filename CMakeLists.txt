cmake_minimum_required(VERSION 3.17)
project(kruskal)

set(CMAKE_CXX_STANDARD 14)

add_executable(kruskal src/main.cpp src/disjoint_set_union.cpp include/disjoint_set_union.h src/kruskal_algorithm.cpp include/kruskal_algorithm.h src/utils.cpp include/utils.h include/csv_writer.h src/csv_writer.cpp)