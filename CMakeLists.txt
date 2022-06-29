cmake_minimum_required(VERSION 3.22)
project(SimilarityComparison)

set(CMAKE_CXX_STANDARD 14)

add_executable(SimilarityComparison main.cpp ContentComparison.h ContentComparison.cpp ASTComparison.h ASTComparison.cpp)
