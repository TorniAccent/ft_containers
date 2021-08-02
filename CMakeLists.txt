cmake_minimum_required(VERSION 3.19)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_containers main.cpp
        vector/Vector.hpp vector/Vector.ipp
        vector/VectorIterator.hpp vector/VectorIterator.ipp
        map/Map.hpp map/Map.ipp
#        map/MapIterator.hpp map/MapIterator.ipp
        map/MapIterator.hpp map/MapIterator.ipp)