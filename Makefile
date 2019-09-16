
all:
	$(MAKE) -C tests all

test:
	$(MAKE) -C tests test

bench:
	$(MAKE) -C benchmark benchmark

commitcheck: clean cleantest clean

latex:
	@doxygen libpq.doxyfile
	$(MAKE) -C docs/latex

veryclean: 
	@echo "Nothing to do"

clean_test:
	$(MAKE) -C tests clean

clean_bench:
	$(MAKE) -C benchmark clean

clean: clean_test clean_bench
