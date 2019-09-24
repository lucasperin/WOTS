from math import ceil, floor, log2
from functools import reduce
from bitstring import BitArray
import hashlib

def t_1(m, w):
    return ceil(m/log2(w))

def t_2(m, w):
    t1 = t_1(m,w)
    return ceil(log2(t1*(w-1))/(log2(w)))

def fingerprint(message, algorithm='sha256'):
    md = hashlib.new(algorithm)
    md.update(message)
    return md.digest()

def fingerprint_r(message, w, R, algorithm='sha256'):
    """
    Returns the fingerprint and r (counter value) that yields the
    largest block average in R trials.
    """
    ret_fp = b'\x00'
    ret_fp_avg = 0
    ret_r = 0
    for r in range(R):
        fp = fingerprint(message + bytes(r), algorithm)
        fp_avg = block_average(w,fp)
        if fp_avg > ret_fp_avg: ret_fp, ret_fp_avg, ret_r = fp, fp_avg, r
    return ret_fp, ret_r

def fingerprint_rt(message, w, R, T,  algorithm='sha256'):
    """
    Returns the FIRST fingerprint and r (counter value) that yields a
    block average larger than T in R trials (stops when found).
    """
    ret_fp = b'\x00'
    ret_fp_avg = 0
    ret_r = 0
    for r in range(R):
        fp = fingerprint(message + bytes(r), algorithm)
        fp_avg = block_average(w,fp)
        if fp_avg > ret_fp_avg: ret_fp, ret_fp_avg, ret_r = fp, fp_avg, r
        if ret_fp_avg >= T: break
    return ret_fp, ret_r

def mean(array):
    return reduce(lambda a, b: a + b, array)/float(len(array))

def block_average(w, fp):
    bst = BitArray(hex=fp.hex()).bin[2:]
    l = int(log2(w))
    blocks = [ int(bst[i:i+l],2) for i in range(0,len(bst), l) ]
    print(blocks)
    return mean(blocks)
    

if __name__ == '__main__':
    assert(t_1(256,2**16) == 16)
    assert(t_2(256,2**16) == 2)

    w = 16
    mu = 2**7
    m = 512


    avgs = [ block_average(w, fingerprint(bytes(h))) for h in range(1000)]
    print(min(avgs), mean(avgs), max(avgs))
    print(t_1(m,w))
    print(t_2(m,w))

    #Print the min, mean and max averages for fingerprint_r
    #avgs = [ block_average(w, fingerprint_r(bytes(h), w, 1000)[0]) for h in range(1000)]
    #print(min(avgs), mean(avgs), max(avgs))

    #avgs = [ fingerprint_r(bytes(h), w, 1000)[1] for h in range(1000)]
    #print(min(avgs), mean(avgs), max(avgs))

    #avgs = [ block_average(w, fingerprint_rt(bytes(h), w, 1000, mu*1.3)[0]) for h in range(1000)]
    #print(min(avgs), mean(avgs), max(avgs))
    #avgs = [ fingerprint_rt(bytes(h), w, 1000, mu*1.3)[1] for h in range(1000)]
    #print(min(avgs), mean(avgs), max(avgs))
