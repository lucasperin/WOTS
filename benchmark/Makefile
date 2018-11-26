LIBOBJECT = ../libpq.so

INCLUDES = -I. -I../pqcrypto
CC = g++
CPPFLAGS = -std=c++11 -DDEBUG --coverage
CXXFLAGS = -g -O0
COVFLAGS = -fprofile-arcs -ftest-coverage -lgcov --coverage
EXECUTABLE = test.out
LIBS = -pthread -lbenchmark $(LIBOBJECT)
SRC_DIR = src
TEST_SRCS += $(wildcard $(SRC_DIR)/*.cpp)
OBJS += $(TEST_SRCS:.cpp=.o)

%.o: %.cpp
	@echo 'Building file: $<'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

all: check-lib $(OBJS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJS) $(LIBS)
	@echo 'Build complete!'
	@echo ' '

check-lib:
	@test -s $(LIBOBJECT) || { echo "You should compile the lib first!"; exit 1; }
	
test:	all
	@echo 'Executing tests...'
	./$(EXECUTABLE)
	@echo 'Done!'

clean:
	rm -rf ./$(SRC_DIR)/*.o ./$(SRC_DIR)/*.gc* $(EXECUTABLE) *.gc*


