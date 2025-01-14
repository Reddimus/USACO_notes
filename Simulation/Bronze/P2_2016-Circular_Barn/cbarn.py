with open("cbarn.in", "r") as fin:
	# Read in total number of rooms (N)
	N = int(fin.readline())
	# Read in the number of cows in each room
	rooms = [int(fin.readline()) for _ in range(N)]

# Try each room as the first room to unlock
min_dist = float("inf")
for unlock in range(N):
	dist = 0
	for r in range(N):
		dist += rooms[(unlock + r) % N] * r
	min_dist = min(min_dist, dist)

print(min_dist, file=open("cbarn.out", "w"))
