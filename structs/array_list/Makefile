clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

linear_allocator.o: ../../allocators/linear_allocator/linear_allocator.c ../../allocators/linear_allocator/linear_allocator.h
	gcc -g -c ../../allocators/linear_allocator/linear_allocator.c -linear_allocator.h
linear_allocator.a: linear_allocator.o
	ar rc linear_allocator.a linear_allocator.o

array_list.o: array_list.c array_list.h
	gcc -g -c array_list.c -o array_list.o
array_list.a: array_list.o
	ar rc array_list.a array_list.o
array_list_test.o: array_list_test.c
	gcc -g -c array_list_test.c -o array_list_test.o
array_list_test: array_list_test.o array_list.a linear_allocator.a
	gcc -g -o array_list_test array_list_test.o array_list.a linear_allocator.a

test: array_list_test 
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "$$test"; \
		./$$test || exit 1; \
	done