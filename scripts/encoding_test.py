from constant_sum import *

if __name__ == "__main__":
    t = 56
    n = 510
    s = 510


    for i in range(500):
        l = (T_len(t,n-i,s))
        if l>0:
            print(log(l,2),t, n-i, s, t*n - s+i, t*n )

    #for b in range(t, 1, -1):
    #    p = 0
    #    k = min(n*(t - b + 1), s)
    #    #k = s
    #    print("b\ts\tlen\tbj\tbj")
    #    for i in range(0, k+1):   
    #        aux = T_len(b-1, n, s- i)
    #        p += aux
    #        bjota =  bj(i, b-1, n, s)
    #        zjota =  zj(i, b-1, n, s)
    #        print("%d\t%d\t%d\t%d\t%d\t%d"%(b-1,  s-i, aux,  p, bjota, zjota))


"""
t(45,145,952) 
Cv = 952
Cs = 
Cg = 

vs

t(45, 72, 1006)
Cv = 1006
Cs = 
Cg = 




"""
