# Binary search on multiple answers method
# T: O(N log D + M log M) = O((N+M)log(maxDist)), M: O(M), where N is the number of cows, M is the number of intervals, and D is the range of distance

# Read input file
with open('socdist.in', 'r') as f:
    # read the number of cows and grassy areas from the first line
    cows, grassy_areas = map(int, f.readline().split())
    intervals = []
    # Read each interval pair and store them
    for interval in range(grassy_areas):
        start, end = map(int, f.readline().split())
        intervals.append((start, end))

# sort so we can read location of each grass area chronologically
intervals.sort()

# Function to test if all cows can be placed maintaining a certain minimum distance
def possible_placement(min_dist: int) -> bool:
    remaining_cows = cows
    prev_cow_loc = intervals[0][0] - min_dist
    # iterating through each sorted interval allows us to find cow placements faster
    for start, end in intervals:
        # if next cow placement falls out of grassy area interval, prepare cow placement for while loop
        if prev_cow_loc + min_dist < start:
            prev_cow_loc = start - min_dist
        # maximize cow placement in current grassy area
        while start <= prev_cow_loc + min_dist <= end:
            prev_cow_loc += min_dist
            remaining_cows -= 1
            if remaining_cows <= 0:
                return True
    return False

# Binary search multiple answers
# worst case = 1, best case = equally distant cows
# 1 <= result <= equally distant cows
lo = 1
hi = int((intervals[-1][1] - intervals[0][0]) / (cows - 1))
# Converge to a max feasible min distance
while (lo < hi):
    mid = (lo + hi + 1) // 2
    # if min_dist/mid does fit in grassy areas we save lo and try for a larger minimum distance
    if possible_placement(mid):
        lo = mid
    # else min_dist/mid does not fit therefore we get rid of curr hi by lowering upper bound
    else:
        hi = mid - 1
# Write minimum distance of optimally distant cows to output file
print(lo, file=open('socdist.out', 'w'))
