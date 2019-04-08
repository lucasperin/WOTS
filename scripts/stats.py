from math import factorial as fac, sqrt
from scipy.integrate import quad
import numpy as np

def integrand(t):
    """
    Integrand of the cumulative function, used to compute phi(Z).
    """
    return np.exp(-(t**2)/2)

def phi(z):
    """
    Cumulative function as described in Wikipedia, for the computation
    of the probability of a statistic being less than  Z.
    """
    return (1/(sqrt(2*np.pi))) * quad(integrand, -np.inf, z)[0]

def complementary_cumulative(z):
    """
    Returns the complementary cumulative probability for @param Z-score.
    This gives the odds for an event X > Z in the Standard Normal Table.
    """
    return 1 - phi(z)

def r_to_z(r, mu, std):
    """
    Returns the Z-score of some value 'r', normalized with the Standard
    Normal Table.
    """
    return (r - mu) / std

def z_to_r(z, mu, std):
    """
    Returns the 'r' value, corresponding to the original distribution,
    given from a Z-score in the Standard Normal Table.
    """
    return z*std + mu

def chance_exactly_k(k, n, p):
    """
    Returns the success chance of an event with probability 'p' to
    occur exactly 'k' in 'n' trials.
    """
    return (fac(n)/(fac(k)*fac(n-k))) * p**k * (1-p)**(n-k)

def chance_exactly_once(n,p):
    """
    Returns the chance of an event with probability 'p' to occur EXACLTY
    once in 'n' trials.
    """
    chance_exaclty_k(1,n,p)

def at_least_one_in_n(p, n):
    """
    Returns the success probability of an event with independent 
    probability 'p' in 'n' trials.
    to
    """
    assert(p > 0 and p < 1 and n > 0)
    return 1 - (1-p)**n

def at_least_one_with_prob(event_p, success_p, threshold=20000):
    """
    Returns the number of trials needed for an independent event with 
    probability 'event_p' to occur at least one time with a probability
    of 'success_p'.
    """
    assert(event_p >0 and event_p < 1 and success_p > 0 and success_p < 1)
    n = 1
    while(at_least_one_in_n(event_p, n) < success_p):
        n += 1
    if n == threshold:
        return -1
    return n


def average_chance(p):
    return 1/p


if __name__ == "__main__":

    w = 2**16
    mu = 32774
    std = 4730

    print("mean = %d"%(mu))
    print("std = %d"%(std))
    mui = mu*1.2

    print("For 20 increase, mean = %f"%(mui))
    z = r_to_z(mui,mu,std)
    print("%d to z = %f)"%(mui, z))
    p = complementary_cumulative(z)
    print("p( mu > %d ) = %f"%(mui, p))
    print("In average, event will occur after %f trials"%(average_chance(p)))
    print("The event will occur at least once, with 95 chance, after %d trials"%(at_least_one_with_prob(p, 0.95)))
    print("The event will occur at least once, with 99 chance, after %d trials"%(at_least_one_with_prob(p, 0.99)))

    print("\n ================= \n")
    mui = mu*1.435
    print("For 30 increase, mean = %f"%(mui))
    z = r_to_z(mui,mu,std)
    print("%d to z = %f)"%(mui, z))
    p = complementary_cumulative(z)
    print("p( mu > %d ) = %f"%(mui, p))
    print("In average, event will occur after %f trials"%(average_chance(p)))
    print("The event will occur at least once, with 95 chance, after %d trials"%(at_least_one_with_prob(p, 0.95)))
    print("The event will occur at least once, with 99 chance, after %d trials"%(at_least_one_with_prob(p, 0.99)))

