CC=g++
CFLAGS=-Wall -Werror -Wextra -g -lstdc++ -std=c++17
TFLAGS=-g -c -Wall -Werror -Wextra -g -lstdc++ -std=c++17 -lgtest -Wuninitialized -pedantic
GTEST=-lgtest -lgtest_main -pthread
ASAN=-fsanitize=address
COVER=-fprofile-arcs -ftest-coverage

# # # # # ----------------------------------------------------------
all: test

test: clean
	@ g++ $(CFLAGS) $(ASAN) $(COVER) ./tests/s21_array_test.cc ./tests/s21_vector_test.cc ./tests/s21_set_test.cc \
									./tests/s21_multiset_test.cc ./tests/s21_list_test.cc ./tests/s21_map_test.cc \
									./tests/s21_queue_test.cc ./tests/s21_stack_test.cc -o test_full $(GTEST)
	./test_full

gcov_report: test
	geninfo --ignore-errors mismatch . -b . -o ./coverage.info --no-external 
	genhtml coverage.info -o ./coverage
	open coverage/index.html

leaks:
	@ g++ -fsanitize=address -g $(TFLAGS) s21_vector.h s21_array.h s21_set.h s21_multiset.h s21_list.h s21_map.h s21_queue.h s21_stack.h \
									./tests/s21_array_test.cc ./tests/s21_vector_test.cc ./tests/s21_set_test.cc \
									./tests/s21_multiset_test.cc ./tests/s21_list_test.cc ./tests/s21_map_test.cc \
									./tests/s21_queue_test.cc ./tests/s21_stack_test.cc -c
	g++ -fsanitize=address -g *.o -o test_full -lgtest
	leaks -atExit -- ./test_full

test_CMake: build 
	./build/CPP2_s21_containers_0

build: CMakeLists.txt *.h ./tests/s21_array_test.cc ./tests/s21_vector_test.cc ./tests/s21_set_test.cc \
							./tests/s21_multiset_test.cc ./tests/s21_list_test.cc ./tests/s21_map_test.cc \
							./tests/s21_queue_test.cc ./tests/s21_stack_test.cc
	mkdir -p build
	cd build && cmake .. && make

clean:
	rm -rf build/ test_full
	rm -rf *.a *.o *.out
	rm -rf *.info *.gcda *.gcno *.gcov *.gch *.dSYM
	rm -rf coverage
	rm -rf gcov_report report

clang_format:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config */*.cc *.h
	cp ../materials/linters/.clang-format ../.clang-format
	clang-format -i *.h
	clang-format -i tests/*.cc
	clang-format -n *.h
	clang-format -n tests/*.cc
	rm -rf ../.clang-format
