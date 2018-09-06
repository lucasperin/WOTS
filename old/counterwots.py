from time import sleep
import hashlib
from os import urandom
import numpy as np
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

def digest(alg, bytearr):
    dig = getattr(hashlib, alg)
    return dig(bytearr).hexdigest()

def get_exponents(dig, w):
    mask = 0
    for _ in range(w):
        mask = (mask << 1) | 0x1
    n = len(dig) * 4
    exp = []
    shift = 0
    d = int(dig, base=16)
    while(shift < n):
        exp.append( ( d >> shift) & mask )
        shift += w
    return exp

def str_to_bytes(string):
    return bytearray(string, 'utf8')

def mean(arr):
    return np.mean(arr)

def find_largest(msg, w, h, t, plot=False):
    bytearr = bytearray(msg)
    bytearr.append(0)
    l = len(bytearr)-1
    s = []
    avg = []
    for i in range(t):
        bytearr[l] = i
        d = digest(h, bytearr)
        exps = get_exponents(d,w)
        s.append(sum(exps))
        avg.append(mean(exps))
    if plot:
        plot_dist(avg)
    return mean(s), min(s), max(s)

def find_same_magnitude(msg, w, h, t, magnitude=2):
    bytearr = bytearray(msg)
    ret = {}
    for i in range(t):
        bytearr = bytearray(msg)
        bytearr.extend(urandom(32))
        d = digest(h, bytearr)
        exps = get_exponents(d,w)
        for k in range(1, magnitude+1):
            z = 2**(w-k)
            if min([e-z for e in exps]) > 0 :
                ret[i] = exps
    return ret

def test_runner(w, h, t, title=""):
    TEST_RUNS = 1000
    AVG = []
    MIN = []
    MAX = []
    for _ in range(TEST_RUNS):
        msg = urandom(1024)
        (a, mi, ma) = find_largest(msg, w, h, t)
        AVG.append(a)
        MIN.append(mi)
        MAX.append(ma)
    return int(mean(AVG)), min(MIN), max(MAX)

def plot_dist(sample, title=""):
    _, bins, patches = plt.hist(sample, 32,  normed=1, facecolor='green', alpha=0.75)

    y = mlab.normpdf(bins, np.mean(sample), np.std(sample))

    l = plt.plot(bins, y, 'r--', linewidth=1, 
            label=r"$\mu'={} \quad \sigma=${}".format(int(np.mean(sample)), int(np.std(sample) )))
    plt.xlabel(r'$\mu(B_r)$')
    plt.ylabel('Probability')
    plt.grid(True)
    plt.legend()
    plt.show()


def plot_t():
    t1 = [1 - (1-0.1587)**n for n in range (0, 210, 10)]
    t2 = [1 - (1-0.0228)**n for n in range (0, 210, 10)]
    t3 = [1 - (1-0.0013)**n for n in range (0, 210, 10)]

    print(t1)
    print(t2)
    plt.plot(range(0,210,10), t1, label=r"$P( \mu(B_r) > \mu' + \sigma)$")
    plt.plot(range(0,210,10), t2, label=r"$P( \mu(B_r) > \mu' + 2\sigma)$", linestyle='--')
    plt.plot(range(0,210,10), t3, label=r"$P( \mu(B_r) > \mu' + 3\sigma)$", linestyle='-.')
    plt.xlabel(r'$R$')
    plt.ylabel('Probability')
    plt.legend()
    plt.grid(True)
    plt.show()

def run_w16_t50():
    w = 16
    h = "sha256"
    t = 50
    print("Running test with w 16 and t 50", test_runner(w, h, t, "w16t50"))
    
def run_w16_t100():
    w = 16
    h = "sha256"
    t = 100
    print("Running test with w 16 and t 100", test_runner(w, h, t, "w16t100"))

def run_w16_t150():
    w = 16
    h = "sha256"
    t = 150
    print("Running test with w 16 and t 150", test_runner(w, h, t, "w16t150"))

def run_w16_t200():
    w = 16
    h = "sha256"
    t = 200
    print("Running test with w 16 and t 200", test_runner(w, h, t, "w16t200"))

def run_w16_t256():
    w = 16
    h = "sha256"
    t = 256
    print("Running test with w 16 and t 256", test_runner(w, h, t, "w16t256"))

def histogram():
    w = 16
    h = "blake2s"
    t = 10000
    msg = urandom(1024)
    
    avg = []
    indexes = {}
    for i in range(t):
        bytearr = bytearray(msg)
        bytearr.extend(urandom(32))
        d = digest(h, bytearr)
        exps = get_exponents(d,w)
        avg.append(mean(exps))
        if(sum(exps) > 700000):
            indexes[i] = sum(exps)

    plot_dist(avg)
    print(indexes)

def magnitude_test():
    w = 16
    h = "blake2s"
    t = 100000
    msg = urandom(1024)
    for k,v in find_same_magnitude(msg, w, h, t, 1).items():
        print(k, v, mean(v))

if __name__ == '__main__':
    magnitude_test()
    #plot_t()
    #histogram()
    #run_w16_t50()
    #run_w16_t100()
    #run_w16_t150()
    #run_w16_t200()
    #run_w16_t256()
