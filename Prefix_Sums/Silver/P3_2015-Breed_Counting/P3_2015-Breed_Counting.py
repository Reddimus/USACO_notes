# Prefix sums approach
# T & M: O(n + q), where n is num of cows, and q is num of queries

# Open input file
with open("bcount.in") as f:
	# first line: n = num of cows, q = num of queries
	n, q = map(int, f.readline().split())

	# For next n lines read cow breed IDs and create prefix sum lists
	holsteins = [0] * (n + 1)
	guernseys = [0] * (n + 1)
	jerseys = [0] * (n + 1)

	for idx in range(1, n+1):
		holsteins[idx] += holsteins[idx - 1]
		guernseys[idx] += guernseys[idx - 1]
		jerseys[idx] += jerseys[idx - 1]
		cow_id = int(f.readline().strip())
		if cow_id == 1:
			holsteins[idx] += 1
		elif cow_id == 2:
			guernseys[idx] += 1
		elif cow_id == 3:
			jerseys[idx] += 1

	# For next q lines solve num of cow breeds in query range
	queries_ids = []
	for ln in range(q):
		start, end = map(int, f.readline().split())
		queries_ids.append([holsteins[end] - holsteins[start-1], guernseys[end] - guernseys[start-1], jerseys[end] - jerseys[start-1]])
		
# Write query ids to output file
with open("bcount.out", "w") as f:
	for q_ids in queries_ids:
		f.write(" ".join(map(str, q_ids)) + "\n")
