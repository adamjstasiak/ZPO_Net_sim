cmake_minimum_required(VERSION 3.17)
project(ZPO_Net_sim)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)

include_directories(include)


set(SOURCE_FILES
        src/nodes.cpp
        src/helpers.cpp
        src/factory.cpp
        src/package.cpp
        src/storage_types.cpp
        src/storage_types.cpp
        src/simulation.cpp
        src/reports.cpp
        )

add_executable(ZPO_Net_sim_debug ${SOURCE_FILES} )

set(SOURCES_FILES_TESTS
        test/main_gtest.cpp
        test/test_nodes.cpp
        test/test_package.cpp
        test/test_reports.cpp
        test/test_simulate.cpp
        test/test_Factory.cpp
        test/test_factory_io.cpp
        test/test_storage_types.cpp
        )

add_executable(my_project_test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)

target_include_directories(my_project_test PUBLIC
        googletest-master/googlemock/include
        googletest-master/googletest/include
        mocks
        )

add_subdirectory(googletest-master)


target_link_libraries(my_project_test gmock)
target_compile_definitions(my_project_test PUBLIC EXERCISE_ID=REPORTING)