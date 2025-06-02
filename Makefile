clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

#--- Hash table
hash_table.o: hash_table.c hash_table.h
	gcc -g -c hash_table.c -o hash_table.o
hash_table.a: hash_table.o
	ar rc hash_table.a hash_table.o
hash_table_test.o: hash_table_test.c
	gcc -g -c hash_table_test.c -o hash_table_test.o
hash_table_test: hash_table_test.o hash_table.a pool_allocator.a linear_allocator.a
	gcc -g -o hash_table_test hash_table_test.o hash_table.a pool_allocator.a linear_allocator.a
#---

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

#--- linear allocator
linear_allocator.o: linear_allocator.c linear_allocator.h
	gcc -g -c linear_allocator.c -o linear_allocator.o
linear_allocator.a: linear_allocator.o
	ar rc linear_allocator.a linear_allocator.o
linear_allocator_test.o: linear_allocator_test.c
	gcc -g -c linear_allocator_test.c -o linear_allocator_test.o
linear_allocator_test: linear_allocator_test.o linear_allocator.a
	gcc -g -o linear_allocator_test linear_allocator_test.o linear_allocator.a 
#--- 

#--- Array list
array_list.o: array_list.c array_list.h
	gcc -g -c array_list.c -o array_list.o
array_list.a: array_list.o
	ar rc array_list.a array_list.o
array_list_test.o: array_list_test.c
	gcc -g -c array_list_test.c -o array_list_test.o
array_list_test: array_list_test.o array_list.a linear_allocator.a
	gcc -g -o array_list_test array_list_test.o array_list.a linear_allocator.a
#--- 

#--- stack
stack.o: stack.c stack.h
	gcc -g -c stack.c -o stack.o
stack.a: stack.o
	ar rc stack.a stack.o
stack_test.o: stack.c stack.h
	gcc -g -c stack_test.c -o stack_test.o
stack_test: stack_test.o stack.a
	gcc -g -o stack_test stack_test.o stack.a
#---

#--- list
list.o: list.c list.h
	gcc -g -c list.c -o list.o
list.a: list.o
	ar rc list.a list.o
list_test.o: list_test.c
	gcc -g -c list_test.c -o list_test.o
list_test: list_test.o list.a
	gcc -g -o list_test list_test.o list.a
#---

#--- integ
integ.o: integ.c integ.h
	gcc -g -c integ.c -o integ.o
integ.a: integ.o
	ar rc integ.a integ.o
integ_test.o: integ.c integ.h
	gcc -g -c integ_test.c -o integ_test.o
integ_test: integ_test.o integ.a
	gcc -g -o integ_test integ_test.o integ.a -lm
#---

test: integ_test list_test stack_test linear_allocator_test pool_allocator_test array_list_test hash_table_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "$$test"; \
		./$$test || exit 1; \
	done
	