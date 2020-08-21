#!/usr/bin/env python
import numpy as np

'''
动态规划的问题都要考虑的比较清楚，思考这类问题不能以举例子找规律的方式去做，
而是直接对问题做假定，由n推导出n+1，不这么假定的话，所得到的信息很多都是没有
用的，反而干扰思维，动归思路应该是把问题由大变小或者由小变大，由底向上，由顶
向下或者由左向右，或者由右向左

例如在LIS里知道LIS(n-1)不能推导出LIS(n)，就是因为不确定n-1在不在LIS里面，如果
在好解，如果不在就有很多种可能性，问题就复杂化了，所以LIS里面直接假定n-1就在
LIS里面，这样LIS(n)就可以由LIS(1 ... n-1)推导出来，用DP解问题很多时候都不是线性
的复杂度，一般都是N^2或者更大

对于balance partition，不好界定位置就直接假定最后位置，然后问题变小，最后只需要
找到边界就能由底向上算出整个table
'''

# Edit Distance

'''
def edit_distance(s1, s2, l1, l2):
    if l1 == 0:
        return l2 * indel(' ')
    if l2 == 0:
        return l1 * indel(' ')

    op = []
    match = edit_distance(s1, s2, l1 - 1, l2 - 1) + match(s1[l1], s2[l2])
    insert = edit_distance(s1, s2, l1, l2 - 1) + indel(s2[l2])
    delete = edit_distance(s1, s3, l1 - 1, l2) + indel(s1[l1])

    return min(op)
'''

def match(a, b):
    if a == b:
        return 0
    else:
        return 1

def indel():
    return 1

def edit_distance(s1, s2, l1, l2):
    table = np.zeros(shape=(l1 + 1, l2 + 1), dtype=int)

    for i in range(1, l1 + 1):
        table[i][0] = i
    for i in range(1, l2 + 1):
        table[0][i] = i

    for i in range(1, l1 + 1):
        for j in range(1, l2 + 1):
            opt = []
            opt.append(table[i-1][j-1] + match(s1[i - 1], s2[j - 1]))
            opt.append(table[i][j-1] + indel())
            opt.append(table[i-1][j] + indel())

            table[i][j] = min(opt)

    print(table)

    return table[l1][l2]

#s1 = "you should not"
#s2 = "thou shalt not"
#print(edit_distance(s1, s2, len(s1), len(s2)))

###################################

# Longest Increasing Sequence
# 如果L(i)表示第i个数的时候LIS长度，则该信息无法做递推，
# 如果L(i)表示第i个数结尾的时候LIS长度，则L(i) = max(j = 0 -> i if data[i] > data[j])

def lis(data):
    L = [1] * len(data)

    for i in range(len(data)):
        max_l = 1
        for j in range(i):
            if data[i] > data[j] and L[j] + 1 > max_l:
                max_l = L[j] + 1
        L[i] = max_l

    print(L)

    return max(L)

#data = np.random.randint(low=0, high=100, size=(10,)).tolist()
#print(data)
#print(lis(data))

#######################################
# balanced K partition of N continuous numbers

def balanced_partition(data, K):
    length = len(data)
    table = np.zeros(shape=(length + 1, K + 1))

    for i in range(1, K + 1):
        table[1][i] = data[0]

    for i in range(1, length + 1):
        table[i][1] = sum(data[:i])

    print(table)

    for n in range(2, length + 1):
        for k in range(2, K + 1):
            cands = []
            for i in range(1, n):
                cands.append(max(table[i][k-1], sum(data[i : n+1])))
            table[n][k] = min(cands)
            print(n, k, "=>", table[n][k])
    print(table)

    return table[n][k]

#data = np.random.randint(low=1, high=100, size=(10,)).tolist()
data = [20, 60, 20, 64, 79, 2, 23, 46, 27, 47]
print(data)
print(balanced_partition(data, 3))
