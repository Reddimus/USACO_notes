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
with open('div7.in', 'r') as f:
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
	best_photo = max(best_photo, idx_list[-1] - idx_list[0])

print(best_photo, file=open('div7.out', 'w'))
'''