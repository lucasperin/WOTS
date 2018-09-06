SHELL = /bin/bash
CC = g++
CPPFLAGS = -std=c++11 --coverage
CXXFLAGS = -g -O0 -shared -fPIC

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
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<" $(LIBS)
	@echo 'Finished building: $<'
	@echo ' '

all: $(OBJS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJS) $(LIBS) 
	@echo 'Build complete!'
	@echo ' '

clean_test_files:
	$(MAKE) -C tests veryclean

.PHONY: test
test: all
	$(MAKE) -C tests test

cleantest: clean_test_files test

commitcheck: clean cleantest clean

latex:
	@doxygen libpq.doxyfile
	$(MAKE) -C docs/latex

clean: 
	$(RM) -f $(SRC_DIR)/*.o
	$(RM) -f $(SRC_DIR)/*.gc*
	$(RM) -f $(EXECUTABLE)
	$(RM) -rf $(DOC_DIR)
