# WOTS
WOTS implementations for fun and experiments

The goal is to have a reliable and fast implementation that
I can benchmark using a few modifications to the algorithm.

# Security Remark

Do not attempt to use this for cryptographic purposes. This 
implementation does not take any security common practices
into consideration.

# Build Requirements
- GNU MP
- openMP

# Build Command
```
gcc -ggdb main.c -lcrypto -Wall -DPARALLEL -fopenmp -lgmp && time ./a.out
```

- PARALLEL is a flag to run the computations of each iteration over the
signature key (or the signature) using multiple cores with OpenMP.

- -fopenmp is required even without PARALLEL flag, due to benchmark
outputs I have placed in the code. I use `omp_get_wtime()` to get
better precision than `clock()` when using multiple cores.

- ggdb is for debugging with gdb

