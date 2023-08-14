'''
USACO 2017 February Contest, Silver
Problem 2. Why Did the Cow Cross the Road II

The long road through Farmer John's farm has N crosswalks across it, conveniently numbered 1…N 
(1≤N≤100,000). To allow cows to cross at these crosswalks, FJ installs electric crossing signals, 
which light up with a green cow icon when it is ok for the cow to cross, and red otherwise. 
Unfortunately, a large electrical storm has damaged some of his signals. Given a list of the 
damaged signals, please compute the minimum number of signals that FJ needs to repair in order 
for there to exist some contiguous block of at least K working signals.

INPUT FORMAT (file maxcross.in):
The first line of input contains N, K, and B (1≤B,K≤N). The next B lines each describe the ID 
number of a broken signal.

OUTPUT FORMAT (file maxcross.out):
Please compute the minimum number of signals that need to be repaired in order for there to be 
a contiguous block of K working signals somewhere along the road.

SAMPLE INPUT:
10 6 5
2
10
1
5
9

SAMPLE OUTPUT:
1
'''

# Sliding window approach
# T & M: O(n), where n is number of crosswalks

# Open input file
with open('maxcross.in', 'r') as f:
	# First line: n = crosswalks, k = contiguous working signals goal, b = broken signals
	n, k, b = map(int, f.readline().split())
	# For the next b lines, mark broken signals in list; signal_id = index, 1 = broken
	broken = [0] * (n+1)
	for signal_id in range(b):
		broken[int(f.readline())] = 1

# Initialize first set of k working signals within index window range
tmp_fixed = 0
l_idx, r_idx = 1, k+1
for idx in range(l_idx, r_idx):
	tmp_fixed += broken[idx]

# Slide window across broken signals lists using previous initialization values
min_fix = tmp_fixed
while r_idx <= n:
	# Constantly update min num of signals that need to be fixed using curr window
	tmp_fixed += broken[r_idx] - broken[l_idx]
	min_fix = min(min_fix, tmp_fixed)
	l_idx, r_idx = l_idx + 1, r_idx + 1

# Write min num of signals that need to be repaired for k contiguous working signals
print(min_fix, file=open('maxcross.out', 'w'))