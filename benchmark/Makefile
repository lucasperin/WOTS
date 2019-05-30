LIBOBJECT = ../libpq.so
CC = g++ -fopenmp
INCLUDES = -I. -I../pqcrypto
CPPFLAGS = -std=c++11
CXXFLAGS = -g -O3 -Wall
EXECUTABLE = test.out
LIBS = -pthread -lbenchmark -lcrypto $(LIBOBJECT)
SRC_DIR = src
SRCS += $(wildcard $(SRC_DIR)/*.cpp)
APPS = $(SRCS:$(SRC_DIR)/%.cpp=%.out)

%.out: $(SRC_DIR)/%.cpp
	@echo 'Building file: $@'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -o "$@" "$<" $(LIBS)
	@echo 'Finished building: $@'
	@echo ' '

all: check-lib $(APPS)
	@echo 'Build complete!'
	@echo ' '

check-lib:
	@test -s $(LIBOBJECT) || { echo "You should compile the lib first!"; exit 1; }
	
benchmark: all
	@echo 'Running Tests'
	$(foreach var, $(APPS), ./$(var);)

encoding: Encoding_bench.out
	./Encoding_bench.out

wots: Wots_bench.out
	./Wots_bench.out

clean:
	rm -f $(APPS)
	find $(SRC_DIR) -type f -name "*.o" -delete
	find $(SRC_DIR) -type f -name "*.gc*" -delete


