INCLUDES = -I. -I../pqcrypto
CC = g++
CPPFLAGS = -std=c++11 -DDEBUG --coverage
CXXFLAGS = -g -O0
COVFLAGS = -fprofile-arcs -ftest-coverage -lgcov --coverage
EXECUTABLE = test.out
LIBS = -pthread -lcrypto

GTEST_DIR = gtest
SRC_DIR = src
LIBOBJECT = ../libpq.so

TEST_SRCS += $(wildcard $(SRC_DIR)/*.cpp)
OBJS += $(TEST_SRCS:.cpp=.o)

%.o: %.cpp
	@echo 'Building file: $<'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

all: check-lib gtest $(OBJS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJS) $(LIBOBJECT) ./$(GTEST_DIR)/gtest-all.o $(LIBS) -rdynamic
	@echo 'Build complete!'
	@echo ' '

check-lib:
	@test -s $(LIBOBJECT) || { echo "You should compile/install the lib first!"; exit 1; }
	
gtest: ./$(GTEST_DIR)/gtest-all.o

test:	all
	@echo 'Executing tests...'
	./$(EXECUTABLE)
	@echo 'Done!'

clean:
	rm -rf ./$(SRC_DIR)/*.o ./$(SRC_DIR)/*.gc* $(EXECUTABLE) *.gc*

veryclean: clean
	rm -f /tmp/$(MOCKED_SO)
	rm -rf ./$(GTEST_DIR)/*.o ./$(GTEST_DIR)/*.gc*


