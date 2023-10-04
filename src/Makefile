CC = gcc -Wall -Werror -Wextra -std=c++17 -g
L = -lstdc++ -lgtest -lgtest_main
GCOVF = -fprofile-arcs -ftest-coverage
LF = -lrt -lm -lsubunit -lpthread
LW = ../lib/

OS := $(shell uname)
ifeq ($(OS), Linux)
	UL = $(L) $(LF)
else
	UL = $(L)
endif

all: build

lib:
	$(CC) -static-libgcc polish_notation_plus.cc -o $(LW)libpolishnotation.a $(UL)
	ar rc ../lib/libmatrix.a *.o
	$(CC)  -shared polish_notation_plus.cc -o ../lib/libpolishnotation.so *.o
test:
	$(CC) ../tests/*.cc polish_notation_plus.cc -o res_test $(UL)
	./res_test

leaks: 
	$(CC) ../tests/*.cc polish_notation_plus.cc -o res_test $(UL)
	leaks -atExit -- ./res_test

clang_format: clang-format

clang-format: 
	cp ../materials/linters/.clang-format ../src
	clang-format -n calculator/*.cc
	clang-format -n calculator/view/*.h
	clang-format -n calculator/view/*.cc
	clang-format -n calculator/model/*.h
	clang-format -n calculator/model/*.cc
	clang-format -n calculator/controller/*.h
	clang-format -n calculator/controller/*.cc
	clang-format -i calculator/*.cc
	clang-format -i calculator/view/*.h
	clang-format -i calculator/view/*.cc
	clang-format -i calculator/model/*.h
	clang-format -i calculator/model/*.cc
	clang-format -i calculator/controller/*.h
	clang-format -i calculator/controller/*.cc


valgrind: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./res_test

clang_format:
	cp ../materials/linters/.clang-format ../src
	# clang-format -n headers/*.h patterns/*.tpp tests/*.cc
	# clang-format -i headers/*.h patterns/*.tpp tests/*.cc
	rm -rf .clang-format

build: lib, test

unistall: clean

rebuild: clean build

clear: clean

clean:
	rm -rf *.dSYM *.o *.out
	rm -rf res_test
	rm -rf ../build*
