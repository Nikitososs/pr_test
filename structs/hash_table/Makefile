clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

pool_allocator.o: ../../allocators/pool_allocator/pool_allocator.c ../../allocators/pool_allocator/pool_allocator.h
	gcc -g -c ../../allocators/pool_allocator/pool_allocator.c -o pool_allocator.o
pool_allocator.a: pool_allocator.o
	ar rc pool_allocator.a pool_allocator.o

linear_allocator.o: ../../allocators/linear_allocator/linear_allocator.c ../../allocators/linear_allocator/linear_allocator.h
	gcc -g -c ../../allocators/linear_allocator/linear_allocator.c -linear_allocator.h
linear_allocator.a: linear_allocator.o
	ar rc linear_allocator.a linear_allocator.o

hash_table.o: hash_table.c hash_table.h
	gcc -g -c hash_table.c -o hash_table.o
hash_table.a: hash_table.o
	ar rc hash_table.a hash_table.o
hash_table_test.o: hash_table_test.c
	gcc -g -c hash_table_test.c -o hash_table_test.o
hash_table_test: hash_table_test.o hash_table.a pool_allocator.a linear_allocator.a
	gcc -g -o hash_table_test hash_table_test.o hash_table.a pool_allocator.a linear_allocator.a

test: hash_table_test 
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "$$test"; \
		./$$test || exit 1; \
	done