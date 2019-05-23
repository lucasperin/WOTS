import matplotlib
import matplotlib.pyplot as plt
from constant_sum import T_len
import numpy as np
from math import log, floor

def has_len(length, array):
    for a in array:
        if a >= length:
            return True
    return False


for maxi in [3, 7, 256]:
    L = []
    for blocks in range(16,100):
        L += [log(T_len(blocks, maxi, maxi),2)]
    if has_len(256,L):
        plt.plot(range(16,100), L, label="T(t,%d,%d)"%(maxi,maxi))
        plt.legend()

    L = []
    for blocks in range(16,100):
        L += [log(T_len(blocks, maxi, floor(maxi*blocks*0.1)),2)]
    if has_len(256,L):
        plt.plot(range(16,100), L, label="T(t,%d,%d)"%(maxi,maxi*blocks*0.1))
        plt.legend()

    L = []
    for blocks in range(16,100):
        L += [log(T_len(blocks, maxi, floor(maxi*blocks*0.2)),2)]
    if has_len(256,L):
        plt.plot(range(16,100), L, label="T(t,%d,%d)"%(maxi,maxi*blocks*0.2))
        plt.legend()

    L = []
    for blocks in range(16,100):
        L += [log(T_len(blocks, maxi, floor(maxi*blocks*0.3)),2)]
    if has_len(256,L):
        plt.plot(range(16,100), L, label="T(t,%d,%d)"%(maxi,maxi*blocks*0.3))
        plt.legend()

    L = []
    for blocks in range(16,100):
        L += [log(T_len(blocks, maxi, floor(maxi*blocks*0.4)),2)]
    if has_len(256,L):
        plt.plot(range(16,100), L, label="T(t,%d,%d)"%(maxi,maxi*blocks*0.4))
        plt.legend()

#    L = []
#    for blocks in range(16,100):
#        L += [log(T_len(blocks, maxi, floor(maxi*blocks*0.5)),2)]
#    if has_len(256,L):
#        plt.plot(range(16,100), L, label="T(t,%d,%d)"%(maxi,maxi*blocks*0.5))
#        plt.legend()

plt.plot(range(0,100), [256]*100, "--")
plt.xlabel('Num Blocks')
plt.ylabel('|T_len|')
plt.show()
