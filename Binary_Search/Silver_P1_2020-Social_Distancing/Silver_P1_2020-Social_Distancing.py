'''
USACO 2020 US Open Contest, Silver
Problem 1. Social Distancing

Farmer John is worried for the health of his cows after an outbreak of the highly contagious 
bovine disease COWVID-19.

In order to limit transmission of the disease, Farmer John's N cows (2≤N≤10^5) have decided 
to practice "social distancing" and spread themselves out across the farm. The farm is shaped 
like a 1D number line, with M mutually-disjoint intervals (1≤M≤10^5) in which there is grass 
for grazing. The cows want to locate themselves at distinct integer points, each covered in 
grass, so as to maximize the value of D, where D represents the distance between the closest 
pair of cows. Please help the cows determine the largest possible value of D.

INPUT FORMAT (file socdist.in):
The first line of input contains N and M. The next M lines each describe an interval in terms
of two integers a and b, where 0≤a≤b≤10^18. No two intervals overlap or touch at their endpoints. 
A cow standing on the endpoint of an interval counts as standing on grass.

OUTPUT FORMAT (file socdist.out):
Print the largest possible value of D such that all pairs of cows are D units apart. A solution 
with D>0 is guaranteed to exist.

SAMPLE INPUT:
5 3
0 2
4 7
9 9

SAMPLE OUTPUT:
2

One way to achieve D=2 is to have cows at positions 0, 2, 4, 6 and 9.

SCORING:
- Test cases 2-3 satisfy b≤10^5.
- Test cases 4-10 satisfy no additional constraints.
'''

# Binary search method
# T: O(N log D + M log M), M: O(M), where N is the number of cows, M is the number of intervals, and D is the range of distance

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

def possible_placement(min_dist):
    remaining_cows = cows
    prev_cow_loc = intervals[0][0] - min_dist

    for start, end in intervals:
        if prev_cow_loc + min_dist < start:
            prev_cow_loc = start - min_dist

        while start <= prev_cow_loc + min_dist <= end:
            prev_cow_loc += min_dist
            remaining_cows -= 1

    return remaining_cows <= 0

start_pos, end_pos = intervals[0][0], intervals[-1][1]
# optimal distance if all grass areas are equally distant
equally_dist = int((end_pos - start_pos) / (cows - 1))
# Use binary search to logarithmically solve for min dist
left, right = 1, equally_dist
while left < right:
    mid = (left + right + 1) // 2
    if possible_placement(mid):
        left = mid
    else: # decrease min dist
        right = mid - 1
            
min_dist = left
print(min_dist, file=open("socdist.out", "w"))

'''
# Local Practice solution
class Solution:
    def optimal_distancing(self, sample_in: list[list]) -> int:
        # cows and grassy areas are defined in first line of input file (n & m)
        cows, grassy_areas = sample_in[0][0], sample_in[0][1]
        self.cows = cows
        # for the next m lines there are pairs of intervals we want to append to a list
        intervals = sample_in[1::]
        intervals.sort()
        self.intervals = intervals
        first_pos, last_pos = intervals[0][0], intervals[-1][1]
        if cows == 2:
            return last_pos - first_pos
        optimal_dist = int((last_pos - first_pos) / (cows - 1))
        print(last_pos, first_pos, cows)
        print(optimal_dist)
        left, right = 1, optimal_dist
        # Binary search for the minimum distance
        while left < right:
            mid = (left + right + 1) // 2
            if self.possible_placement(mid):
                left = mid          # increase min dist
            else:
                right = mid - 1     # decrease min dist
        return left
    
    def possible_placement(self, min_dist: int) -> bool:
        remaining_cows = self.cows
        # Initialize the previous cow's location to be before the first interval
        prev_cow_loc = self.intervals[0][0] - min_dist
        
        # Go through each interval
        for start, end in self.intervals:
            # If the previous cow location plus the minimum distance is before the start of the interval,
            # Move the previous cow location to the start of the interval minus the minimum distance
            if prev_cow_loc + min_dist < start:
                prev_cow_loc = start - min_dist

            # While we can fit a cow in the interval, place the cow and decrease the number of remaining cows
            while start <= prev_cow_loc + min_dist <= end:
                prev_cow_loc += min_dist
                remaining_cows -= 1

        # Return whether we were able to place all cows
        return remaining_cows <= 0
    
sol = Solution()    

# Hypothetical socdist.in file represented as an array
sample_in = [[5, 3],
            [0, 2],
            [4, 7],
            [9, 9]]
ex = sol.optimal_distancing(sample_in)
assert ex == 2, f'Expected 2 but got {ex}'

# Hypothetical socdist.in file represented as an array
sample_in = [[3, 3],
            [0, 0],
            [5, 5],
            [15, 15]]
ex = sol.optimal_distancing(sample_in)
assert ex == 5, f'Expected 7 but got {ex}'

# Hypothetical socdist.in file represented as an array
sample_in = [[4, 2],
            [0, 10],
            [20, 30]]
ex = sol.optimal_distancing(sample_in)
assert ex == 10, f'Expected 10 but got {ex}'
'''