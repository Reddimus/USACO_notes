'''
Counting Haybales - USACO Silver P1 2016 prompt:

Farmer John has just arranged his N haybales (1≤N≤100,000) at various points along 
the one-dimensional road running across his farm. To make sure they are spaced out 
appropriately, please help him answer Q queries (1≤Q≤100,000), each asking for the 
number of haybales within a specific interval along the road.

INPUT FORMAT (file haybales.in):
The first line contains N and Q.

The next line contains N distinct integers, each in the range 0…1,000,000,000, 
indicating that there is a haybale at each of those locations.

Each of the next Q lines contains two integers A and B (0≤A≤B≤1,000,000,000) 
giving a query for the number of haybales between A and B, inclusive.

OUTPUT FORMAT (file haybales.out):
You should write Q lines of output. For each query, output the number of haybales 
in its respective interval.

SAMPLE INPUT:
4 6
3 2 7 5
2 3
2 4
2 5
2 7
4 6
8 10

SAMPLE OUTPUT:
2
2
3
4
1
0
'''

import bisect

# Binary search method
# T: O((n + q) log n)), M: O(n + q), where n is number of haybales, and q is num of intervals
'''
# From scratch
def lower_bound(arr, target):
    l_idx, r_idx = 0, len(arr)
    while l_idx < r_idx:
        m_idx = (l_idx + r_idx) // 2
        if arr[m_idx] < target:
            l_idx = m_idx + 1
        else:
            r_idx = m_idx
    return l_idx    # if target not found returns out of bounds idx (n)

def upper_bound(arr, target):
    l_idx, r_idx = 0, len(arr)
    while l_idx < r_idx:
        m_idx = (l_idx + r_idx) // 2
        if arr[m_idx] <= target:
            l_idx = m_idx + 1
        else:
            r_idx = m_idx
    return r_idx
'''
# open/read input file
with open('haybales.in', 'r') as f:
    # first line: n = num haybales, q = num of intervals
    n, q = map(int, f.readline().split())
    # second line: haybale placements
    haybale_locs = list(map(int, f.readline().split()))
    haybale_locs.sort()
    # for the next q lines process intervals
    interval_placements = []
    for ln in range(q):
        start, end = map(int, f.readline().split())
        # Binary search lower/upper bound of answers
        l_idx = bisect.bisect_left(haybale_locs, start)
        r_idx = bisect.bisect_right(haybale_locs, end)
        '''
        # From scratch
        l_idx = lower_bound(haybale_locs, start)
        r_idx = upper_bound(haybale_locs, end)
        '''
        interval_placements.append(str(r_idx - l_idx))

# Write all results at once
with open('haybales.out', 'w') as f:
    f.write('\n'.join(interval_placements))
