OS=$(shell uname)
CC=gcc
CFLAGS = -std=c11 -Werror -Wextra -Wall -g
ifeq ($(OS), Darwin)
 CHECK= -lcheck -lpthread -lm
else
 CHECK= -lcheck -lpthread -lm -lsubunit
endif
SOURCE = *.c
SRC = $(wildcard s21_*.c)

all: clean gcov_report 

main: s21_matrix.a test

s21_matrix.o:
	$(CC) $(CFLAGS) -c $(SRC)

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_*.o
	ranlib s21_matrix.a

test: s21_matrix.a
	$(CC) $(CFLAGS) tests_s21_matrix.c s21_matrix.a $(CHECK) -o test -lcheck
	./test

rebuild: clean main

gcov_report: s21_matrix.o s21_matrix.a
	$(CC) $(CFLAGS) --coverage $(SOURCE) s21_matrix.a -L. s21_matrix.a $(CHECK) -o ./test 
	./test
	mkdir report
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	rm -rf *.gcda *.gcno *.out *.o

check:
	clang-format -style=Google -i *.c *.h
	clang-format -style=Google -n *.c *.h
	leaks --atExit -- ./test

clean:
	rm -rf *.o *.gcda *.gcno *.a *.out *.info *.dSYM report test
