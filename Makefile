clear:
	@for dir in $(shell find . -maxdepth 3 -type d -not -path "." -not -path "./.git" -not -path "./.github"); do \
		$(MAKE) -C $$dir clear; \
	done

check_fmt:
	@for dir in $(shell find . -maxdepth 3 -type d -not -path "." -not -path "./.git" -not -path "./.github"); do \
			$(MAKE) -C $$dir check_fmt; \
	done

fmt:
	@for dir in $(shell find . -maxdepth 3 -type d -not -path "." -not -path "./.git" -not -path "./.github"); do \
			$(MAKE) -C $$dir fmt; \
	done

test: 
	@for dir in $(shell find . -maxdepth 3 -type d -not -path "." -not -path "./.git" -not -path "./.github"); do \
		$(MAKE) -C $$dir test; \
	done
	