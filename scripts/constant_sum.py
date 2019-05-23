from math import factorial as fac, sqrt, floor, log
from functools import reduce

"""
Math basics for ma computations
"""

def binomial(n, k):
    """
    Binomial computed with factorial
    n >= k >= 0
    """
    #if n<0 or k <0 or n-k<0: return 0
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

def T_len(blocks, maxi, block_sum = None):
    """
    New equation for |T_{t,w}|, if block_sum is not given, will assume 
    original behavior with maxi = block_sum
    @param blocks is the number of blocks the map has
    @param maxi is the largest integer inside a block (0, ..., maxi)
    @param block_sum is the sum of the blocks
    TODO: Assert maxi <= block_sum?
    """
    if block_sum is None: block_sum = maxi
    kmax = min(blocks, floor(block_sum/(maxi+1)))
    return reduce(lambda t, k: t + binomial(blocks,k)*binomial(block_sum-(maxi+1)*k+blocks-1,blocks-1 )*(-1)**k, [0] + list(range(0,kmax+1)))

def original_bk(k, blocks,maxi):
    """
    Original Bk algorithm, returning boundries for mapping integers
    into constant sum blocks
    @param blocks is the number of blocks the map has
    @param maxi is the largest integer inside a block (0, ..., maxi)
    """
    assert(k>=0)
    if k is 0: return 0
    return original_bk(k-1, blocks,maxi)+T_len(blocks-1, k-1)

def bj(j, blocks, maxi, block_sum = None):
    """
    New Bk algorithm, returning boundries for mapping integers
    into constant sum blocks
    @param blocks is the number of blocks the map has
    @param maxi is the largest integer inside a block (0, ..., maxi)
    @param block_sum is the sum of the blocks
    """
    assert(j>=0)
    if block_sum is None: block_sum = maxi
    kmax = min(blocks, floor(block_sum/(maxi+1)))
    return reduce(lambda t, k: t + binomial(blocks,k)*
            (
            binomial(block_sum-(maxi+1)*k+blocks,blocks)
            - binomial(block_sum-(maxi+1)*k+blocks-1-j,blocks)
            )*(-1)**k, [0] + list(range(0,kmax+1)))

def original_map_to_const_sum(i, blocks, maxi):
    if blocks is 1: return [maxi]
    k = 0
    a = 1
    bleft = 0
    bright = original_bk(k+1, blocks,maxi)
    while( not (i >= bleft and i < bright)):
        k = k + 1
        bleft=bright
        bright = original_bk(k+1, blocks,maxi)
    return [maxi-k] + original_map_to_const_sum(i-bleft, blocks-1,k)

def map_to_const_sum(i, blocks, maxi, block_sum=None):
    if block_sum is None: block_sum = maxi
    if blocks is 1: return [block_sum]
    k = 0
    bleft = 0
    bright = T_len(blocks-1, maxi, block_sum)
    while( not (i >= bleft and i < bright)):
        k = k + 1
        bleft=bright
        bright += T_len(blocks-1,maxi,block_sum-k)
    return [k] + map_to_const_sum(i-bleft,blocks-1,maxi,block_sum-(k))

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
    assert(reduce(lambda x,y: x+func(2,3,y), [0] + list(range(3,7))) == 10)
    assert(func(3,3,8) == 3)
    assert(reduce(lambda x,y: x+func(2,3,y), [0] + list(range(5,9))) == 3)
    assert(func(20,10,20) == 68785126410)
    assert(reduce(lambda x,y: x+func(19,10,y), [0] + list(range(10,21))) == 68785126410)

if __name__ == '__main__':

    test_sum_equals_maxi(original_T_len)
    test_sum_equals_maxi(T_len)
    test_sum_larger_than_maxi(T_len)

    blocks = 70
    maxi = 255
    block_max = 255
    #block_sum = floor((blocks*block_max)*0.5)
    block_sum = 313
    print(block_sum)
    print(log(T_len(blocks, maxi, block_sum), 2))
    print(floor(log(T_len(blocks, maxi, block_sum),2)), block_sum, (blocks*block_max) - block_sum, block_sum + (blocks*block_max) - block_sum)

    #for i in range(1,20):
        #print(map_to_const_sum(i, blocks, maxi, block_sum))


    print("Done!")
