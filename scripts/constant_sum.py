from math import factorial as fac, sqrt, floor
from functools import reduce

"""
Math basics for ma computations
"""

def binomial(n, k):
    """
    Binomial computed with factorial
    n >= k >= 0
    """
    return fac(n)/(fac(k)*fac(n-k))



"""
Map Functions
"""

def original_T_len(blocks, maxi):
    """
    Original computation for |T_{t,w}| from the Constant-sum paper.
    @param blocks is the number of blocks the map has
    @param maxi is largest integer inside a block (0, ..., maxi)
    """
    return binomial(maxi + blocks -1, maxi)

def T_len(blocks, maxi, block_sum=0):
    """
    New equation for |T_{t,w}|, if block_sum is not given, will assume 
    original behavior with maxi = block_sum
    @param blocks is the number of blocks the map has
    @param maxi is the largest integer inside a block (0, ..., maxi)
    @param block_sum is the sum of the blocks
    TODO: Assert maxi <= block_sum?
    """
    if block_sum == 0: block_sum = maxi
    kmax = min(blocks, floor(block_sum/(maxi+1)))
    return reduce(lambda t, k: t + binomial(blocks,k)*binomial(block_sum-(maxi+1)*k+blocks-1,blocks-1 )*(-1)**k, [0] + list(range(0,kmax+1)))


def test_sum_equals_maxi(func):
    assert(func(1,0) == 1)
    assert(func(2,0) == 1)
    assert(func(20,0) == 1)
    assert(func(2,1) == 2)
    assert(func(2,3) == 4)
    assert(func(3,3) == 10)
    assert(reduce(lambda x,y: x+func(2,y), [0,0,1,2,3]) == 10)
    assert(func(3,4) == 15)
    assert(reduce(lambda x,y: x+func(2,y), [0,0,1,2,3,4]) == 15)
    assert(func(4,4) == 35)
    assert(reduce(lambda x,y: x+func(3,y), [0,0,1,2,3,4]) == 35)
    assert(func(20,10) == 20030010)
    assert(reduce(lambda x,y: x+func(19,y), [0] + list(range(0,11))) == 20030010)

def test_sum_larger_than_maxi(func):
    assert(func(1,0,1) == 0)
    assert(func(1,0,20) == 0)
    assert(func(20,0,20) == 0)
    assert(func(20,0,0) == 1)
    assert(func(3,3,9) == 1)
    assert(func(3,3,6) == 10)


    assert(func(20,10,20) == 68785126410)
    #assert(reduce(lambda x,y: x+func(19,y,20), [0] + list(range(0,11))) == 68785126410)

if __name__ == '__main__':

    print(T_len(3,3,6))
    print(reduce(lambda x,y: x+T_len(2,y,6), [0] + list(range(0,4))))
    """
    A soma dos carinhas de menos blocos, quando o somatório é maior que maxi,
    não funciona igual ao caso classico. O somatório talvez tenha que ser ajustado
    junto.
    """


    test_sum_equals_maxi(original_T_len)
    test_sum_equals_maxi(T_len)
    test_sum_larger_than_maxi(T_len)
    """
    Assert if T_len beha
    """

    print("Done!")
