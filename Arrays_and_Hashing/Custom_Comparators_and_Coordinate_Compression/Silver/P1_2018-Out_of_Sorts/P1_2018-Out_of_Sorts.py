import typing, functools

class Entry(typing.NamedTuple):
	value: int
	index: int

with open("sort.in", "r") as fin:
	# Read in first line: n = length of array
	n = int(fin.readline())
	# For the next n lines, record the value & index of each entry
	entries = [Entry(int(fin.readline()), i) for i in range(n)]

# Sort the array in ascending order, breaking ties by initial index
comparator = (
	lambda a, b: a.index - b.index 
	if a.value == b.value 
	else a.value - b.value
)
entries.sort(key=functools.cmp_to_key(comparator))

# Using initial indeces count the # of bubbles needed to sort the array
print(
	max(entries[i].index - i + 1 for i in range(n)), 
	file=open("sort.out", "w")
)
