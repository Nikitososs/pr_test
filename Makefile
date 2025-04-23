clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

#--- Pool allocator
pool_allocator.o: pool_allocator.c pool_allocator.h
	gcc -g -c pool_allocator.c -o pool_allocator.o
pool_allocator.a: pool_allocator.o
	ar rc pool_allocator.a pool_allocator.o
pool_allocator_test.o: pool_allocator_test.c
	gcc -g -c pool_allocator_test.c -o pool_allocator_test.o
pool_allocator_test: pool_allocator_test.o pool_allocator.a
	gcc -g -o pool_allocator_test pool_allocator_test.o pool_allocator.a 
#--- 	

test: pool_allocator_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "$$test"; \
		./$$test || exit 1; \
	done
	