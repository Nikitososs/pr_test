clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

stack.o: stack.c stack.h
	gcc -g -c stack.c -o stack.o
stack.a: stack.o
	ar rc stack.a stack.o
stack_test.o: stack.c stack.h
	gcc -g -c stack_test.c -o stack_test.o
stack_test: stack_test.o stack.a
	gcc -g -o stack_test stack_test.o stack.a

test: stack_test 
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "$$test"; \
		./$$test || exit 1; \
	done