'''
USACO 2017 January Contest, Silver
Problem 1. Cow Dance Show

After several months of rehearsal, the cows are just about ready to put on their annual dance 
performance; this year they are performing the famous bovine ballet "Cowpelia".

The only aspect of the show that remains to be determined is the size of the stage. A stage 
of size K can support K cows dancing simultaneously. The N cows in the herd (1≤N≤10,000) 
are conveniently numbered 1…N in the order in which they must appear in the dance. Each 
cow i plans to dance for a specific duration of time d(i). Initially, cows 1…K appear 
on stage and start dancing. When the first of these cows completes her part, she leaves 
the stage and cow K+1 immediately starts dancing, and so on, so there are always K cows 
dancing (until the end of the show, when we start to run out of cows). The show ends when 
the last cow completes her dancing part, at time T.

Clearly, the larger the value of K, the smaller the value of T. Since the show cannot last 
too long, you are given as input an upper bound Tmax specifying the largest possible value 
of T. Subject to this constraint, please determine the smallest possible value of K.

INPUT FORMAT (file cowdance.in):
The first line of input contains N and Tmax, where Tmax is an integer of value at most 1 million.

The next N lines give the durations d(1)…d(N) of the dancing parts for cows 1…N. Each d(i) 
value is an integer in the range 1…100,000.

It is guaranteed that if K=N, the show will finish in time.

OUTPUT FORMAT (file cowdance.out):
Print out the smallest possible value of K such that the dance performance will take no more 
than Tmax units of time.

SAMPLE INPUT:
5 8
4
7
8
6
4

In the sample input provided, the time each cow dances for is specified as follows:

- Cow 1 dances for 4 units of time
- Cow 2 dances for 7 units of time
- Cow 3 dances for 8 units of time
- Cow 4 dances for 6 units of time
- Cow 5 dances for 4 units of time

t_max = 8

initialized
[4, 7, 8, 6] | len(stage) = 4 | t = 0

[0, 3, 4, 2] | len(stage) = 4 | t = 4
added cow 5 in idx 0
[4, 3, 4, 2] | len(stage) = 4 | t = 4

Dance remaining time
[0, 0, 0, 0] | len(stage) = 4 | t = 8

SAMPLE OUTPUT:
4
'''

# Binary Search - Heap approach
# T: O(n * log n), M: O(n), where n is number of cows

import heapq

# open input file
with open("cowdance.in") as r:
    # first line n = cows, t_max = maximum time for all cows to dance
    n, t_max = map(int, r.readline().split())
    # for the next n lines read each cow's dance time
    dances = [int(r.readline()) for ln in range(n)]

# k represents the size of the stage to support n amount of cows dancing
def within_contract(k):
    stage = dances[:k]
    heapq.heapify(stage)
    # elapse (heappop) shortest dance time and add next cow to dance
    for d_idx in range(k, n):
        min_dance = heapq.heappop(stage)
        heapq.heappush(stage, min_dance + dances[d_idx])
    return max(stage) <= t_max

# Search for smallest possible stage size within contract limit using binary search
lo, hi = 1, n
while lo < hi:
    mid = (lo + hi) // 2
    if not within_contract(k = mid):
        lo = mid + 1    # increase stage size to reduce time on stage and be within contract time limit
    else:
        hi = mid

# Write searched item into output file
print(hi, file=open("cowdance.out", "w"))

'''
# Binary Search - Array approach
# T: O(n^2 * log n), M: O(n), where n is number of cows

# open input file
with open("cowdance.in") as r:
    # first line n = cows, t_max = maximum time for all cows to dance
    n, t_max = map(int, r.readline().split())
    # for the next n lines read each cow's dance time
    dances = [int(r.readline()) for ln in range(n)]

# k represents the size of the stage to support n amount of cows dancing
def within_contract(k):
    stage = dances[:k]
    t_cnt = 0
    d_idx = k
    while d_idx < n:
        min_dance = min(stage)
        t_cnt += min_dance
        if t_cnt > t_max:
            return False
        # elapse time by shortest dance time to open dance spot and add next cow to dance
        for s_idx, s_time in enumerate(stage):
            stage[s_idx] -= min_dance
            if stage[s_idx] == 0:
                stage[s_idx] = dances[d_idx]
                d_idx += 1
    # let cows dance remaining time
    return t_cnt + max(stage) <= t_max

# Search for smallest possible stage size within contract limit using binary search
lo, hi = 1, n
while lo < hi:
    mid = (lo + hi) // 2
    if not within_contract(k = mid):
        lo = mid + 1    # increase stage size to reduce time on stage and be within contract time limit
    else:
        hi = mid
# Write searched item into output file
print(hi, file=open("cowdance.out", "w"))
'''
