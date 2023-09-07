FLAGS = -Wall -Werror -Wextra -std=c11

all: matrix.a

matrix.a:
	gcc -c $(FLAGS) *.c
	ar rc matrix.a *.o
	ranlib matrix.a

test: matrix.a
	gcc -c $(FLAGS) test_matrix.c
	gcc -c $(FLAGS) main.c
	gcc -lcheck -fprofile-arcs -g -ftest-coverage *.c matrix.a -o tests
	./tests 

gcov_report:	test
	gcov -i *.gcda	
	lcov -t "matrix1" -o matrix1.info -c -d .
	genhtml -o report matrix1.info
	cd report/ && open index.html
	# gcovr --html-details -o report.html
	# open report.html

clean:
	rm -rf *.o *.a *.gcno  *.gcda *.gcov *.css *.html *.dSYM report *.info *.gz
	rm -rf tests

leaks:
	leaks -atExit -- ./tests
