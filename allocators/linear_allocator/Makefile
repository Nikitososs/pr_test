clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

linear_allocator.o: linear_allocator.c linear_allocator.h
	gcc -g -c linear_allocator.c -o linear_allocator.o
linear_allocator.a: linear_allocator.o
	ar rc linear_allocator.a linear_allocator.o
linear_allocator_test.o: linear_allocator_test.c
	gcc -g -c linear_allocator_test.c -o linear_allocator_test.o
linear_allocator_test: linear_allocator_test.o linear_allocator.a
	gcc -g -o linear_allocator_test linear_allocator_test.o linear_allocator.a 

test: linear_allocator_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "$$test"; \
		./$$test || exit 1; \
	done