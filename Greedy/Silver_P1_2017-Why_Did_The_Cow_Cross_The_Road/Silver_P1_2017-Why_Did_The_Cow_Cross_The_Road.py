'''
USACO 2017 February Contest, Silver
Problem 1. Why Did the Cow Cross the Road

Farmer John's cows are trying to learn to cross the road effectively. Remembering 
the old "why did the chicken cross the road?" joke, they figure the chickens must 
be experts on crossing the road, and go off in search of chickens to help them.

As it turns out, chickens are very busy creatures and have limited time to help 
the cows. There are C chickens on the farm (1≤C≤20,000), conveniently numbered 
1…C, and each chicken i is only willing to help a cow at precisely time Ti. The 
cows, never in a hurry, have more flexibility in their schedules. There are N 
cows on the farm (1≤N≤20,000), conveniently numbered 1…N, where cow j is able to 
cross the road between time Aj and time Bj. Figuring the "buddy system" is the 
best way to proceed, each cow j would ideally like to find a chicken i to help 
her cross the road; in order for their schedules to be compatible, i and j must 
satisfy Aj≤Ti≤Bj.

If each cow can be paired with at most one chicken and each chicken with at most 
one cow, please help compute the maximum number of cow-chicken pairs that can be 
constructed.

INPUT FORMAT (file helpcross.in):
The first line of input contains C and N. The next C lines contain T1…TC, and the 
next N lines contain Aj and Bj (Aj≤Bj) for j=1…N. The A's, B's, and T's are all 
non-negative integers (not necessarily distinct) of size at most 1,000,000,000.

OUTPUT FORMAT (file helpcross.out):
Please compute the maximum possible number of cow-chicken pairs.

SAMPLE INPUT:
5 4
7
8
6
2
9
2 5
4 9
0 3
8 13

SAMPLE OUTPUT:
3
'''

# Sorting - Heap approach
# T: O(n log n + c log c), M: O(n + c), where n is number of cows

import heapq

# Read input file
with open("Binary_Search\Silver_P1_2017-Why_Did_The_Cow_Cross_The_Road\helpcross.in") as f:
    # First line: c = number of chickens, n = number of cows
    c, n = map(int, f.readline().split())
    # For the next c lines read Chicken's schedule
    chick_sched = [int(f.readline()) for time in range(c)]
    # For the next n lines read Cow's schedule
    cow_sched = [list(map(int, f.readline().split())) for time in range(n)]

chick_sched.sort()
cow_sched.sort()

cnt_pairs = 0
cow_idx = 0
available_cows = []
for chick_time in chick_sched:
    # add all the cows whos start times now include the chicken's time
    while cow_idx < n and cow_sched[cow_idx][0] <= chick_time:
        heapq.heappush(available_cows, cow_sched[cow_idx][1])
        cow_idx += 1
    """
    remove all the ending times that end too early for the chicken
    since available_cows is a heap, the first element is the smallest
    """
    while available_cows and available_cows[0] < chick_time:
        heapq.heappop(available_cows)
    
    # have the cow help the chicken w/ the earliest end time
    if available_cows:
        cnt_pairs += 1
        heapq.heappop(available_cows)
# open output file and write answer
print(cnt_pairs, file=open("Binary_Search\Silver_P1_2017-Why_Did_The_Cow_Cross_The_Road\helpcross.out", "w"))

'''
# Sorting - Binary Search approach
# T: O(c log c + n log n + n * c * log c), M: O(n + c), where n is number of cows

# Read input file
with open("helpcross.in") as f:
    # First line: c = number of chickens, n = number of cows
    c, n = map(int, f.readline().split())
    # For the next c lines read Chicken's schedule
    chick_sched = [int(f.readline()) for time in range(1, c+1)]
    # For the next n lines read Cow's schedule
    cow_sched = [list(map(int, f.readline().split())) for time in range(1, n+1)]

# sort by cow's end time; priority goes to cows with earlier schedules but smaller range times
cow_sched.sort(key=lambda x: x[1])
chick_sched.sort()

cnt_pairs = 0
# iterate through cow schedule and Binary search chicken pair
for start, end in cow_sched:
    l_idx, r_idx = 0, len(chick_sched)
    while l_idx < r_idx:
        m_idx = (l_idx + r_idx) // 2
        if chick_sched[m_idx] < start:
            l_idx = m_idx + 1
        else:
            r_idx = m_idx
    # if pair found count it and remove chicken from list
    if r_idx < len(chick_sched) and start <= chick_sched[r_idx] <= end:
        cnt_pairs += 1
        chick_sched.pop(r_idx)
# open output file and write answer
print(cnt_pairs, file=open("helpcross.out", "w"))
'''