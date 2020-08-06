#!/usr/bin/env python
import random

# simple example to mimic gradient descent

def foo(x):
    return x * x + 1

def gradient(f, x):
    h = 1e-8
    g = (f(x + h) - f(x)) / h
    return g

stop_step = 1e-6

start_point = random.randint(-100, 100)
print("start: ", start_point)

lr = 1e-3

x = start_point
while True:
    print("x:", x)
    print("f(x):", foo(x))
    if lr * gradient(foo, x) < stop_step:
        print("optim find: %s x: %s" % (foo(x), x))
        break
    x = x - lr * gradient(foo, x)
    print("=" * 30)

