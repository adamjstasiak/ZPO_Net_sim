cmake_minimum_required(VERSION 3.17)
project(ZPO_Net_sim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)

include_directories(include)

add_executable(ZPO_Net_sim
        include/package.hpp
        include/storage_types.hpp
        include/types.hpp
        src/package.cpp
        src/storage_types.cpp
        include/nodes.hpp
        include/helpers.hpp
        include/factory.hpp
        src/nodes.cpp
        src/helpers.cpp
        src/factory.cpp)
