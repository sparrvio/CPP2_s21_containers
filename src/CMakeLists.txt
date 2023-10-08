cmake_minimum_required(VERSION 3.22)
project(CPP2_s21_containers_0)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
       googletest
       URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(.)

add_executable(CPP2_s21_containers_0
       ../s21_vector.h
       ./tests/s21_vector_test.cc
       ../s21_array.h
       ./tests/s21_array_test.cc
       ../s21_set.h
       ./tests/s21_set_test.cc
       ../s21_multiset.h
       ./tests/s21_multiset_test.cc
       ../s21_list.h
       ./tests/s21_list_test.cc
       ../s21_map.h
       ./tests/s21_map_test.cc
       ../s21_queue.h
       ./tests/s21_queue_test.cc
       ../s21_stack.h
       ./tests/s21_stack_test.cc
       
)

set_target_properties(CPP2_s21_containers_0 PROPERTIES LINKER_LANGUAGE CXX)

target_compile_options(CPP2_s21_containers_0 PRIVATE -g -std=c++17 -Wall -Werror -Wextra -Wpedantic -O3)

target_link_libraries(
       CPP2_s21_containers_0
       GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(CPP2_s21_containers_0)
