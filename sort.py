#!/usr/bin/env python
import numpy as np
import math

'''
SelectionSort(A)
    For i = 1 to n do
	Sort[i] = Find-Minimum from A
	Delete-Minimum from A Return(Sort)
    Return(Sort)
'''

def SelectionSort(data):
    dup = data[:]
    sort = []
    while len(dup) > 0:
        min_ = min(dup)
        sort.append(min_)
        dup.remove(min_)

    return sort

#data = np.random.randint(low=0, high=100, size=(10,)).tolist()
#print(data)
#print(SelectionSort(data))

######################################################
'''
Heap Sort, parent is always smaller and greater than children
Heap is always implemented with array, eg
2,6,4,10,8,12,11
imagine heap is a tree like structure, deep or broad search through
a heap, output is not sorted
heap array like implement has too import features:
    1. parent_index = child_index / 2
    2. left_child_index = parent_index * 2
'''

class Heap:
    def __init__(self):
        self.elements = []
        # a place holder, so index start with 1
        self.elements.append(-1)
        self.count = 0

    def parent(self, idx):
        if idx == 1:
            return -1
        else:
            return int(idx / 2)

    def left_child(self, idx):
        if idx * 2 <= self.count:
            return idx * 2
        else:
            return -1

    def insert(self, item):
        self.elements.append(item)
        self.count += 1
        self.bubble_up(self.count)

    def bubble_up(self, idx):
        if self.parent(idx) == -1:
            return

        if self.elements[self.parent(idx)] > self.elements[idx]:
            self.elements[self.parent(idx)], self.elements[idx] = self.elements[idx], self.elements[self.parent(idx)]
            self.bubble_up(self.parent(idx))

    def make_heap(self, data):
        for d in data:
            self.insert(d)

    def print(self):
        for i in range(1, self.count + 1):
            print(self.elements[i],)

    def empty(self):
        return (self.count == 0)

    def pop(self):
        if self.empty():
            return None
        min_ = self.elements[1]
        self.elements[1] = self.elements[self.count]
        self.count -= 1
        self.elements.pop(-1)
        self.bubble_down(1)

        return min_

    def bubble_down(self, idx):
        c = self.left_child(idx)
        if c < 0:
            return
        if c + 1 <= self.count and self.elements[c] > self.elements[c + 1]:
            min_idx = c + 1
        else:
            min_idx = c

        if self.elements[idx] > self.elements[min_idx]:
            self.elements[idx], self.elements[min_idx] = self.elements[min_idx], self.elements[idx]
            self.bubble_down(min_idx)

def HeapSort(data):
    heap = Heap()
    heap.make_heap(data)

    sort = []
    while not heap.empty():
        sort.append(heap.pop())

    return sort

#data = np.random.randint(low=0, high=100, size=(10,)).tolist()
#print(data)
#print(HeapSort(data))

#################################################

'''
InsertionSort(A)
    A[0] = −∞
    for i = 2 to n do
        j=i
        while (A[j] < A[j − 1]) do
            swap(A[j], A[j − 1])
            j=j−1
'''

################################################

'''
MergeSort(data, low, high):
    if low < hign:
        middel = (low + high) / 2
        MergeSort(data, low, middle)
        MergeSort(data, middle + 1, high)
        Merge(data, low, midel, high)
'''

##############################################

'''
QuickSort(data, low, high):
    if high > low:
        p = partition(data, low, high)
        QuickSort(data, low, p - 1)
        QuickSort(data, p + 1, high)

partition每次找pivot，比pivot小的在pivot的左边，比pivot大的在pivot右边
quick sort因为不需要多余的存储空间，操作简单，所以实际上要比heap sort和
merge sort要快
'''

############################################


