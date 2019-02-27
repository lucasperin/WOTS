from math import ceil, floor, log2

def t_1(m, w):
    return ceil(m/log2(w))

def t_2(m, w):
    t1 = t_1(m,w)
    return ceil(log2(t1*(w-1))/(log2(w)))

if __name__ == '__main__':
    print("NHAAA")
