from math import ceil, floor, log2
from wots import t_1, t_2

def c_max(m, w):
    return t_1(m, w)*(w-1)

def n_c(m, w):
    return ceil(log2(c_max(m,w)))

def n_u(m, w):
    return t_2(m,w) * log2(w) - n_c(m,w)

if __name__ == '__main__':
    W = [ 4, 16, 256, 65536 ]
    M = [ 128, 192, 256, 512 ]


    print("w \t m \t t2lgw \t n_c \t n_u")
    for w in W:
        for m in M:
                print(str(w) + "\t& " +  str(m) + "\t& " + str(t_2(m,w)*log2(w)) + "\t& " + str(n_c(m,w)) + "\t& " + str(n_u(m,w)))
