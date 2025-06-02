DIRS := $(shell find . -maxdepth 3 -type d -not -path "." -not -path "./.git" -not -path "./.github")

clear:
	@for dir in $(DIRS); do \
		$(MAKE) -C $$dir clear; \
	done

check_fmt:
	@for dir in $(DIRS); do \
			$(MAKE) -C $$dir check_fmt; \
	done

fmt:
	@for dir in $(DIRS); do \
			$(MAKE) -C $$dir fmt; \
	done

test: 
	@for dir in $(DIRS); do \
		$(MAKE) -C $$dir test; \
	done
	
mem_test: test
	@for test in $(shell find . -maxdepth 3 -type f -regex '.*_test$$'); do \
		valgrind --leak-check=full ./$$test; \
	done