INCLUDES = -I../pqcrypto
CC = g++
CPPFLAGS = -std=c++17 -DDEBUG --coverage
CXXFLAGS = -g -O0
EXECUTABLE = test.out
LIBS = -pthread -lgtest -lcrypto -lgmpxx -lgmp
SRC_DIR = src
TEST_SRCS += $(wildcard $(SRC_DIR)/*.cpp)
OBJS += $(TEST_SRCS:.cpp=.o)

%.o: %.cpp
	@echo 'Building file: $<'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

all: $(OBJS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJS) $(LIBS)
	@echo 'Build complete!'
	@echo ' '
	
test:	all
	@echo 'Executing tests...'
	./$(EXECUTABLE)
	@echo 'Done!'

clean:
	rm -f $(EXECUTABLE)
	find $(SRC_DIR) -type f -name "*.o" -delete
	find $(SRC_DIR) -type f -name "*.gc*" -delete


