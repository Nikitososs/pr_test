clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

#----linear locator
linear.o: linear.c linear.h
	gcc -g -c linear.c -o linear.o
linear.a: linear.o
	ar rc linear.a linear.o
linear_test.o: linear_test.c
	gcc -g -c linear_test.c -o linear_test.o
linear_test: linear_test.o linear.a
	gcc -g -o linear_test linear_test.o linear.a 
#------------

test: linear_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "$$test"; \
		./$$test || exit 1; \
	done
	