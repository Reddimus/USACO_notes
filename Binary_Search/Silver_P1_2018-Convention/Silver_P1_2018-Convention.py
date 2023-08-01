'''
USACO 2018 December Contest, Silver
Problem 1. Convention

Farmer John is hosting a new bovine grass-eating convention at his farm!

Cows from all over the world are arriving at the local airport to attend the 
convention and eat grass. Specifically, there are N cows arriving at the airport 
(1≤N≤10^5) and cow i arrives at time ti (0≤ti≤10^9). Farmer John has arranged M 
(1≤M≤10^5) buses to transport the cows from the airport. Each bus can hold up to 
C cows in it (1≤C≤N). Farmer John is waiting with the buses at the airport and 
would like to assign the arriving cows to the buses. A bus can leave at the time 
when the last cow on it arrives. Farmer John wants to be a good host and so does 
not want to keep the arriving cows waiting at the airport too long. What is the 
smallest possible value of the maximum waiting time of any one arriving cow if 
Farmer John coordinates his buses optimally? A cow's waiting time is the difference 
between her arrival time and the departure of her assigned bus.

It is guaranteed that MC≥N.

INPUT FORMAT (file convention.in):
The first line contains three space separated integers N, M, and C. The next line 
contains N space separated integers representing the arrival time of each cow.

OUTPUT FORMAT (file convention.out):
Please write one line containing the optimal minimum maximum waiting time for any 
one arriving cow.

SAMPLE INPUT:
6 3 2
1 1 10 14 4 3

SAMPLE OUTPUT:
4

If the two cows arriving at time 1 go in one bus, cows arriving at times 3 and 4 
in the second, and cows arriving at times 10 and 14 in the third, the longest time 
a cow has to wait is 4 time units (the cow arriving at time 10 waits from time 10 
to time 14)
'''

# Binary Search - Two Pointers approach
# T: O(n log n), M: O(n), where n = num of cows

# Read input file
with open('convention.in', 'r') as f:
    # First line: n = num of cows, m = num of buses, c = capacity of each bus
    n, m, c = map(int, f.readline().split())
    # Second line: cow arrival times
    arrivals = list(map(int, f.readline().split()))

# Sort cow arrival times to group cows that arrive close together
arrivals.sort()

def valid_waiting(max_wait: int) -> bool:
    buses = cow_Lidx = cow_Ridx = 0
    while cow_Ridx < n:
        # if first cow in bus (overlapping indexes); increment buses counted
        if cow_Lidx == cow_Ridx:
            buses += 1
        # if bus waiting time out of range; update prev idx to curr idx (move to next bus)
        if arrivals[cow_Ridx] - arrivals[cow_Lidx] > max_wait:
            cow_Lidx = cow_Ridx
        # if bus capacity (c) reached with new placement; update idxs to move on to next bus
        elif cow_Ridx - cow_Lidx + 1 == c:
            cow_Ridx += 1
            cow_Lidx = cow_Ridx
        # else cow time is valid for bus placement
        else:
            cow_Ridx += 1
    return buses <= m;

# Binary search for min max waiting time
lo, hi = 0, arrivals[-1] - arrivals[0]
while lo < hi:
    mid = (lo + hi) // 2
    if not valid_waiting(max_wait = mid):
        lo = mid + 1
    else:
        hi = mid

# Write converged answer hi [..false, false, TRUE, true...] representing min max arrival time
print(hi, file=open("convention.out", "w"))