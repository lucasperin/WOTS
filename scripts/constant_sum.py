from math import factorial as fac, sqrt, floor, log, ceil
from functools import reduce, lru_cache
import hashlib

from scipy.special import comb


def binomial(n, k):
    return comb(n, k, exact=True)


def original_T_len(blocks, maxi):
    """
    Original computation for |T_{t,w}| from the Constant-sum paper.
    @param blocks is the number of blocks the map has
    @param maxi is largest integer inside a block (0, ..., maxi)
    """
    return binomial(maxi + blocks - 1, maxi)


@lru_cache(maxsize=None)
def T_len(blocks, maxi, block_sum=None):
    """
    New equation for |T_{t,w}|, if block_sum is not given, will assume
    original behavior with maxi = block_sum
    @param blocks is the number of blocks the map has
    @param maxi is the largest integer inside a block (0, ..., maxi)
    @param block_sum is the sum of the blocks
    TODO: Assert maxi <= block_sum?
    """
    if block_sum is None:
        block_sum = maxi

    kmax = min(blocks, floor(block_sum / (maxi + 1)))
    t = 0
    for k in range(kmax + 1):
        t += (
            (-1) ** k
            * binomial(blocks, k)
            * binomial(block_sum - (maxi + 1) * k + blocks - 1, blocks - 1)
        )

    return t

@lru_cache(maxsize=None)
def T_len_test(blocks, maxi, block_sum=None):
    """
    New equation for |T_{t,w}|, if block_sum is not given, will assume
    original behavior with maxi = block_sum
    @param blocks is the number of blocks the map has
    @param maxi is the largest integer inside a block (0, ..., maxi)
    @param block_sum is the sum of the blocks
    TODO: Assert maxi <= block_sum?
    """
    if block_sum is None:
        block_sum = maxi

    kmax = min(blocks, floor(block_sum / (maxi + 1)))
    t = 0

    for k in range(kmax + 1):
        t +=  binomial(block_sum - (maxi + 1) * k + blocks - 1, block_sum - (maxi+1) * k) * ((( -1) ** kmax)  * binomial(blocks-1, kmax))

    return t


def original_bk(k, blocks, maxi):
    """
    Original Bk algorithm, returning boundries for mapping integers
    into constant sum blocks
    @param blocks is the number of blocks the map has
    @param maxi is the largest integer inside a block (0, ..., maxi)
    """
    assert k >= 0
    if k is 0:
        return 0
    return original_bk(k - 1, blocks, maxi) + T_len(blocks - 1, k - 1)


def bj(j, blocks, maxi, block_sum=None):
    """
    New Bk algorithm, returning boundries for mapping integers
    into constant sum blocks
    @param blocks is the number of blocks the map has
    @param maxi is the largest integer inside a block (0, ..., maxi)
    @param block_sum is the sum of the blocks
    """
    assert j >= 0
    if block_sum is None:
        block_sum = maxi
    kmax = min(blocks, floor((block_sum) / (maxi + 1)))

    t = 0
    for k in range(0, kmax + 1):
        t+= ((-1)**k) * binomial(blocks, k) * (
              binomial(block_sum - (maxi + 1) * k + blocks, blocks)
            - binomial(block_sum - (maxi + 1) * k + blocks - 1 - j, blocks)
        )

    return t

def magic(j, blocks, maxi, block_sum, k):
    """
    This here is the equivalent to bj internal binomial difference, maybe a little faster..?
    """
    if (block_sum-(maxi+1)*k+blocks-1-j < blocks or blocks < 0):
        return binomial(block_sum - (maxi + 1) * k + blocks, blocks)
    first = binomial(block_sum - (maxi + 1) * k + blocks - 1 - j, blocks)
    top = reduce((lambda x,y:x*y),[block_sum-(maxi+1)*k +blocks -i for i in range(0,j+1)])
    bot =  reduce((lambda x,y:x*y),[block_sum-(maxi+1)*k -i for i in range(0,j+1)])
    #if bot == 0:
    #    return 10000000
    return first*(top/bot - 1)


def zj(j, blocks, maxi, block_sum=None):
    assert j >= 0
    if block_sum is None:
        block_sum = maxi
    kmax = min(blocks, floor((block_sum) / (maxi + 1)))

    t = 0
    for k in range(0, kmax + 1):
        t+= ((-1)**k) * binomial(blocks, k)*magic(j,blocks,maxi,block_sum, k)

    return t

def original_map_to_const_sum(i, blocks, maxi):
    if blocks is 1:
        return [maxi]
    k = 0
    a = 1
    bleft = 0
    bright = original_bk(k + 1, blocks, maxi)
    while not (i >= bleft and i < bright):
        k = k + 1
        bleft = bright
        bright = original_bk(k + 1, blocks, maxi)
    return [maxi - k] + original_map_to_const_sum(i - bleft, blocks - 1, k)


@lru_cache(maxsize=None)
def map_to_const_sum(i, blocks, maxi, block_sum=None):
    if block_sum is None:
        block_sum = maxi
    if blocks is 1:
        return [block_sum]
    k = 0
    bleft = 0
    bright = T_len(blocks - 1, maxi, block_sum)
    while not (i >= bleft and i < bright):
        k = k + 1
        bleft = bright
        bright += T_len(blocks - 1, maxi, block_sum - k)
    return [k] + map_to_const_sum(i - bleft, blocks - 1, maxi, block_sum - (k))


if __name__ == "__main__":

    # t
    blocks = 66
    # n
    maxi = 255
    # s
    block_sum = 35

    #tlen = T_len(blocks, maxi, block_sum)
    #print(int(tlen))
    #print(log(tlen, 2))
    #for i in range(10):
        #m = maxi + i
        #tlen = T_len(blocks, m, m)
        #print(m, log(tlen, 2))

    for i in range(1, 1000):
        I = int.from_bytes(hashlib.sha256(bytes(i)).digest(), byteorder='big')
        #print(map_to_const_sum(I, blocks, maxi, block_sum))
        map_to_const_sum(I, blocks, maxi, block_sum)

    print("Done!")
