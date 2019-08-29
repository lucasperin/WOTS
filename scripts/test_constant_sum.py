from constant_sum import *

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

def test_binomial():
    assert(binomial(512,80) == 113719551425878050452830187150740787820353332954058668336647175220291899316436868900912110998880)

if __name__ == '__main__':

    test_sum_equals_maxi(original_T_len)
    test_sum_equals_maxi(T_len)
    test_sum_larger_than_maxi(T_len)
    test_binomial()
