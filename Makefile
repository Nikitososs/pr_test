clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

#--- pool allocator
pool_aloc.o: pool_aloc.c pool_aloc.h
	gcc -g -c pool_aloc.c -o pool_aloc.o
pool_aloc.a: pool_aloc.o
	ar rc pool_aloc.a pool_aloc.o
pool_aloc_test.o: pool_aloc_test.c
	gcc -g -c pool_aloc_test.c -o pool_aloc_test.o
pool_aloc_test: pool_aloc_test.o pool_aloc.a
	gcc -g -o pool_aloc_test pool_aloc_test.o pool_aloc.a
#---

test: pool_aloc_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "$$test"; \
		./$$test || exit 1; \
	done
	