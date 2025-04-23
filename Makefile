clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

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

test: integ_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "$$test"; \
		./$$test || exit 1; \
	done
	