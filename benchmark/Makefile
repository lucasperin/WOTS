LIBOBJECT = ../libpq.so
CC = g++
INCLUDES = -I. -I../pqcrypto
CPPFLAGS = -std=c++11 -DDEBUG --coverage
CXXFLAGS = -g -O3 -Wall
COVFLAGS = -fprofile-arcs -ftest-coverage -lgcov --coverage
EXECUTABLE = test.out
LIBS = -pthread -lbenchmark $(LIBOBJECT)
SRC_DIR = src
TEST_SRCS += $(wildcard $(SRC_DIR)/*.cpp)
OBJS += $(TEST_SRCS:.cpp=.o)

%.o: %.cpp
	@echo 'Building file: $<'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -c -o "$@" "$<"
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
	rm -f $(EXECUTABLE)
	find $(SRC_DIR) -type f -name "*.o" -delete
	find $(SRC_DIR) -type f -name "*.gc*" -delete


