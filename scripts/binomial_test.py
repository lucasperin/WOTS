from constant_sum import *
from functools import reduce



if __name__ == "__main__":


    a = 10
    b = 20
    j = 20

    bsum = reduce((lambda x, y: x + y), [binomial(a+b-i,a) for i in range(j+1)]) 
    print(bsum)

    first = binomial(a+b+1, a+1)
    second = binomial(a+b-j, a+1)
    bsum2 = first - second

    assert(bsum == bsum2)

    print(bsum2, first, second)
