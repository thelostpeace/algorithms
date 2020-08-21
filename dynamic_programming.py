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
#print(data)
#print(balanced_partition(data, 3))

###########################################
# Longest Common Subsequence
# LCS Problem Statement: Given two sequences, find the length of longest subsequence present in both of them. A subsequence is a sequence that appears in the same relative order, but not necessarily contiguous. For example, “abc”, “abg”, “bdf”, “aeg”, ‘”acefg”, .. etc are subsequences of “abcdefg”.
# eg. "ABCDGH", "AEDFHR" is "ADH" is 3.
# eg. "AGGTAB", "GXTXAYB" is "GTAB" is 4.

def LCS(s1, s2):
    def lcs_match(a, b):
        if a == b:
            return 1
        else:
            return 0

    l1 = len(s1)
    l2 = len(s2)

    table = np.zeros(shape=(l1 + 1, l2 + 1), dtype=int)

    for i in range(1, l1 + 1):
        for j in range(1, l2 + 1):
            table[i][j] = max([table[i - 1][j], table[i][j - 1], table[i - 1][j - 1] + lcs_match(s1[i - 1], s2[j - 1])])

    print(table)

    return table[i][j]

#s1 = "ABCDGH"
#s2 = "AEDFHR"
#s1 = "AGGTAB"
#s2 = "GXTXAYB"
#print(LCS(s1, s2))

###########################################
# A person starts walking from position X = 0, find the probability to reach exactly on X = N if she can only take either 2 steps or 3 steps. Probability for step length 2 is given i.e. P, probability for step length 3 is 1 – P.
# N = 5, p2 = 0.2, p3=0.8, output = 0.32
# 挺有意思，其实这个是两个状态的Markov Chain，最终会趋近一个稳定值

def step_probility(N, p2):
    table = np.zeros(shape=(N + 1, ))
    table[2] = p2
    table[3] = 1 - p2

    for i in range(4, N + 1):
        table[i] = table[i - 2] * p2 + table[i - 3] * (1 - p2)

    print(table)

    return table[N]

#print(step_probility(1000, 0.006309101))

#######################################
# Count number of ways to cover a distance
# Given a distance ‘dist, count total number of ways to cover the distance with 1, 2 and 3 steps.

def step_ways(N):
    table = np.zeros(shape=(N + 1,), dtype=int)
    table[1] = 1
    table[2] = 2
    table[3] = 4

    for i in range(4, N + 1):
        table[i] = table[i - 3] + table[i - 2] + table[i - 1]

    print(table)

    return table[N]

#print(step_ways(50))

#####################################
# Find the longest path in a matrix with given constraints
# Given a n*n matrix where all numbers are distinct, find the maximum length path (starting from any cell) such that all cells along the path are in increasing order with a difference of 1.
#We can move in 4 directions from a given cell (i, j), i.e., we can move to (i+1, j) or (i, j+1) or (i-1, j) or (i, j-1) with the condition that the adjacent cells have a difference of 1.

def longest_path_imp(mat, i, j, rows, cols):
    cands = [1]
    if i > 0 and mat[i][j] + 1 == mat[i-1][j]:
        cands.append(longest_path_imp(mat, i - 1, j, rows, cols) + 1)
    if i + 1 < rows and mat[i][j] + 1 == mat[i + 1][j]:
        cands.append(longest_path_imp(mat, i + 1, j, rows, cols) + 1)
    if j > 0 and mat[i][j] + 1 == mat[i][j - 1]:
        cands.append(longest_path_imp(mat, i, j - 1, rows, cols) + 1)
    if j + 1 < cols and mat[i][j] + 1 == mat[i][j + 1]:
        cands.append(longest_path_imp(mat, i, j + 1, rows, cols) + 1)

    return max(cands)

def longest_path(mat):
    rows = mat.shape[0]
    cols = mat.shape[1]

    table = np.ones(shape=(rows + 1, cols + 1), dtype=int)

    for i in range(1, rows + 1):
        for j in range(1, cols + 1):
            table[i][j] = longest_path_imp(mat, i - 1, j - 1, rows, cols)

    print(table)
    return np.max(table)


#mat = np.array([[1,2,9],[5,3,8],[4,6,7]])
mat = np.random.randint(low=1, high=100, size=(10, 12), dtype=int)
print(mat)
print(longest_path(mat))
