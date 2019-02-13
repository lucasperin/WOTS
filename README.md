# WOTS
WOTS implementations for fun and experiments

The goal is to have a valid and fast implementation of the Winternitz OTS so that
I can benchmark and easily modify/extend the algorithms.

Mainly, the library will contain a classical WOTS implementation with some
other variations available in the literature. The second goal will be to
implement tree-based algorithms (such as XMSS) and parallel hashes with SIMD.

# Security Remark

Do not attempt to use this for cryptographic purposes. This 
implementation does not take any security common practices
into consideration.

# Build 


*Requires OpenSSL*

Later I will be adding avx (will require compatible intel processor) and OpenMP 

```
make
make test
make bench
```

The benchmark and test applications are available with their own makefiles
and require to have `libgtest` and `libbenchmark` (from  Google).

