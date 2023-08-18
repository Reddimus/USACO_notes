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

# check if max waiting time is valid under busses (m) and bus capacity (c) constraints
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