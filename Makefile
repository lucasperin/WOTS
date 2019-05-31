SHELL ?= /bin/bash
CC = g++ -fopenmp
CPPFLAGS += -std=c++11
CXXFLAGS += -O3 -shared -fPIC -Wall

LIBS = -lcrypto 
INCLUDES = -I./pqcrypto

EXECUTABLE = libpq.so

SRC_DIR = src
INCLUDE_DIR =pqcrypto
DOC_DIR = docs

SRCS = $(shell find $(SRC_DIR) -name "*.cpp")
OBJS = $(SRCS:.cpp=.o)

RM = rm

%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Compiler'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -c -o "$@" "$<" $(LIBS)
	@echo 'Finished building: $<'
	@echo ' '

all: $(OBJS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJS) $(LIBS) 
	@echo 'Build complete!'
	@echo ' '

.PHONY: test
test: all
	$(MAKE) -C tests test

.PHONY: bench
bench: all
	$(MAKE) -C benchmark benchmark

commitcheck: clean cleantest clean

latex:
	@doxygen libpq.doxyfile
	$(MAKE) -C docs/latex

clean: 
	find $(SRC_DIR) -type f -name "*.o" -delete
	find $(SRC_DIR) -type f -name "*.gc*" -delete
	$(RM) -f $(EXECUTABLE)
	$(RM) -rf $(DOC_DIR)

clean_test:
	$(MAKE) -C tests clean

clean_bench:
	$(MAKE) -C benchmark clean

veryclean: clean clean_test clean_bench
