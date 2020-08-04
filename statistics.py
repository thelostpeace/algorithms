#!/usr/bin/env python
import numpy as np
import random
import math
import matplotlib.pyplot as plt

# poisson distribution
# if events is independently happened and with a constant rate in a period, then poisson distribution can
# be used to model these events.
def knuth_poisson(lam=1):
    L = math.e ** -lam
    k = 0
    p = 1

    while True:
        k += 1
        p = p * random.uniform(0, 1)
        if p <= L:
            break

    return k - 1

if 1:
    numbers = [knuth_poisson(lam=20) for i in range(10000)]
    #print(numbers)
    plt.hist(numbers)
    plt.savefig("poisson.png")
