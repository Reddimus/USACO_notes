'''
USACO 2016 January Contest, Silver
Problem 2. Subsequences Summing to Sevens

Farmer John's N cows are standing in a row, as they have a tendency to do from time to 
time. Each cow is labeled with a distinct integer ID number so FJ can tell them apart. 
FJ would like to take a photo of a contiguous group of cows but, due to a traumatic 
childhood incident involving the numbers 1…6, he only wants to take a picture of a group 
of cows if their IDs add up to a multiple of 7.

Please help FJ determine the size of the largest group he can photograph.

INPUT FORMAT (file div7.in):
The first line of input contains N (1≤N≤50,000). The next N lines each contain the N 
integer IDs of the cows (all are in the range 0…1,000,000).

OUTPUT FORMAT (file div7.out):
Please output the number of cows in the largest consecutive group whose IDs sum to a 
multiple of 7. If no such group exists, output 0.

You may want to note that the sum of the IDs of a large group of cows might be too large 
to fit into a standard 32-bit integer. If you are summing up large groups of IDs, you 
may therefore want to use a larger integer data type, like a 64-bit "long long" in C/C++.

SAMPLE INPUT:
7
3
5
1
6
2
14
10

SAMPLE OUTPUT:
5

In this example, 5+1+6+2+14 = 28.
'''

# Prefix sums - Array approach
# T: O(n), M: O(1), where n is the number of cows

with open("div7.in") as f:
	# First line: n = num of cows
	n = int(f.readline())
	# For the next n lines create curr/temp prefix sum mod 7 variable
	curr_mod_ps = 0
	best_photo = 0
	first_occ = [0] + [-1] * 6
	for idx in range(n):
		curr_mod_ps = (curr_mod_ps + int(f.readline())) % 7

		# Update first occurence list if mod 7 prefix sum not in first occurences list
		if first_occ[curr_mod_ps] == -1:
			first_occ[curr_mod_ps] = idx
		# Update best photo if pair exists in first occurences list
		else:
			best_photo = max(best_photo, idx - first_occ[curr_mod_ps])

# Write updated best photo to div7 output file
print(best_photo, file=open("div7.out", "w"))

'''
# Prefix sums - Dictionary approach
# T: O(n), M: O(1), where n is the number of cows

# Open input file
with open('div7.in', 'r') as f:
	# First line: n = num of cows
	n = int(f.readline())
	# For the next n lines create curr prefix sum mod 7 variable
	curr_mod_ps = 0
	mod_map = {}	# map mod 7'ed prefix sums; up to 7 possible values
	best_photo = 0
	for idx in range(n):
		curr_mod_ps = (curr_mod_ps + int(f.readline())) % 7

		# Update best photo if pair exists
		if curr_mod_ps in mod_map:
			mod_map[curr_mod_ps][1] = idx
			best_photo = max(best_photo, mod_map[curr_mod_ps][1] - mod_map[curr_mod_ps][0])
		else:
			mod_map[curr_mod_ps] = [idx, idx]

print(best_photo, file=open('div7.out', 'w'))
'''

'''
# Prefix sums - Dictionary expanded approach
# T: O(n), M: O(n), where n is the number of cows

# Open input file
with open('Prefix_Sums\Silver_P2_2016-Subsequences_Summing_to_Sevens\div7.in', 'r') as f:
	# First line: n = num of cows
	n = int(f.readline())
	# For the next n lines create prefix sum list
	prefix_sums = [0] * (n + 1)
	for idx in range(1, n + 1):
		prefix_sums[idx] = prefix_sums[idx - 1] + int(f.readline())

# Mod 7 prefix sum list
mod_prefix_sums = [prefix_sums[idx] % 7 for idx in range(1, n + 1)]

# Create dictionary of mod 7 prefix sums
mod_map = {}	# map mod 7'ed prefix sums; up to 7 possible values
for idx, mod_num in enumerate(mod_prefix_sums):
	mod_map[mod_num] = mod_map.get(mod_num, []) + [idx]

# Find largest photo
best_photo = 0
for mod_num, idx_list in mod_map.items():
	if len(idx_list) > 1:
		best_photo = max(best_photo, idx_list[-1] - idx_list[0])

print(best_photo, file=open('Prefix_Sums\Silver_P2_2016-Subsequences_Summing_to_Sevens\div7.out', 'w'))
'''