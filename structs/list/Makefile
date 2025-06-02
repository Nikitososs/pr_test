clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

list.o: list.c list.h
	gcc -g -c list.c -o list.o
list.a: list.o
	ar rc list.a list.o
list_test.o: list_test.c
	gcc -g -c list_test.c -o list_test.o
list_test: list_test.o list.a
	gcc -g -o list_test list_test.o list.a

test: list_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "$$test"; \
		./$$test || exit 1; \
	done