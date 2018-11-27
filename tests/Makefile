LIBOBJECT = ../libpq.so

INCLUDES = -I. -I../pqcrypto
CC = g++
CPPFLAGS = -std=c++11 -DDEBUG --coverage
#CPPFLAGS = -std=c++11 -Wall -Wextra  -Wstrict-aliasing -pedantic -fmax-errors=5 -Werror -Wunreachable-code -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
CXXFLAGS = -g -O0
COVFLAGS = -fprofile-arcs -ftest-coverage -lgcov --coverage
EXECUTABLE = test.out
LIBS = -pthread -lgtest $(LIBOBJECT)
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
	rm -f $(EXECUTABLE)
	find $(SRC_DIR) -type f -name "*.o" -delete
	find $(SRC_DIR) -type f -name "*.gc*" -delete


