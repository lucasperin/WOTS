from constant_sum import *

if __name__ == "__main__":
    t = 34
    n = 255
    s = 3106

    l = (T_len(t,n,s))
    print ( "T(3,3,4) = %d"% l)

    #for i in range(l):
    #    print(i, map_to_const_sum(i, t,n,s))

    for b in range(t, 1, -1):
        p = 0
        k = min(n*(t - b + 1), s)
        #k = s
        print("b\ts\tlen\tbj\tbj")
        for i in range(0, k+1):   
            aux = T_len(b-1, n, s- i)
            p += aux
            bjota =  bj(i, b-1, n, s)
            print("%d\t%d\t%d\t%d\t%d"%(b-1,  s-i, aux,  p, bjota))

        print()
    

