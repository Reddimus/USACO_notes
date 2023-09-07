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
	for idx in range(k, n):
		min_dance = heapq.heappop(stage)
		heapq.heappush(stage, min_dance + dances[idx])
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
