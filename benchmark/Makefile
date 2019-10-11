CC = g++ -fopenmp
INCLUDES = -I. -I../pqcrypto
CPPFLAGS = -std=c++17
CXXFLAGS = -g -O3 -Wall
EXECUTABLE = test.out
LIBS = -pthread -lbenchmark -lcrypto -lgmpxx -lgmp
SRC_DIR = src
SRCS += $(wildcard $(SRC_DIR)/*.cpp)
APPS = $(SRCS:$(SRC_DIR)/%.cpp=%.out)

%.out: $(SRC_DIR)/%.cpp
	@echo 'Building file: $@'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -o "$@" "$<" $(LIBS)
	@echo 'Finished building: $@'
	@echo ' '

all: $(APPS)
	@echo 'Build complete!'
	@echo ' '

benchmark: all
	@echo 'Running ALL benchmarks'
	$(foreach var, $(APPS), ./$(var);)
	@echo 'Done!'

encoding: Encoding_bench.out
	./Encoding_bench.out
	@echo 'Done!'

binomials: binomials_bench.out
	./binomials_bench.out
	@echo 'Done!'

plot_encoding: Plot_Encoding_bench.out
	./Plot_Encoding_bench.out
	@echo 'Done!'

gen_plot:
	@python gen_plot_bench.py > src/Plot_Encoding_bench.cpp
	@echo 'Done!'

wots: ClassicWots_bench.out
	./ClassicWots_bench.out
	@echo 'Done!'

constantsum: ConstantSumWots_bench.out
	./ConstantSumWots_bench.out
	@echo 'Done!'

runlen: RunLength_bench.out
	./RunLength_bench.out
	@echo 'Done!'

openssl: OpenSSL_bench.out
	./OpenSSL_bench.out
	@echo 'Done!'

clean:
	rm -f $(APPS)
	find $(SRC_DIR) -type f -name "*.o" -delete
	find $(SRC_DIR) -type f -name "*.gc*" -delete


