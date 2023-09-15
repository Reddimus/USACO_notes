# Custom Comparator Sorting approach
# T: O(nlogn), M: O(n), where n is the number of mountains

class Mountain:
	def __init__(self, x_init: int, x_final: int) -> None:
		self.x_init = x_init
		self.x_final = x_final

with open('mountains.in', 'r') as f:
	# Read first line: n = number of mountains
	n = int(f.readline())
	# For the next n lines calculate the xi, xf coordinates of each mountain
	mountains = []
	for ln in range(n):
		x, y = map(int, f.readline().split())
		mountains.append(Mountain(x-y, x+y))

# sort by first appearing mountains and biggest mountains
mountains.sort(key=lambda m: (m.x_init, -m.x_final))

visable = 1
prev_biggest = mountains[0]

for mountain in mountains:
	if mountain.x_final > prev_biggest.x_final:
		visable += 1
		prev_biggest = mountain

print(visable, file=open('mountains.out', 'w'))

'''
# Custom Comparators and Coordinate Compression approach
# T: O(nlogn), M: O(n), where n is the number of mountains

class Mountain:
	def __init__(self, x_init: int, x_final: int) -> None:
		self.x_init = x_init
		self.x_final = x_final

with open('mountains.in', 'r') as f:
	# Read first line: n = number of mountains
	n = int(f.readline())
	# For the next n lines calculate the xi, xf coordinates of each mountain
	mountains = {}
	for ln in range(n):
		x, y = map(int, f.readline().split())
		if x-y not in mountains:
			mountains[x-y] = Mountain(x-y, x+y)
		else:	# forget about the smaller mountain (compress data)
			xf = max(mountains[x-y].x_final, x+y)
			mountains[x-y] = Mountain(x-y, xf)

# sort mountains by first appearing mountains
mountains = list(mountains.values())
mountains.sort(key=lambda m: m.x_init)

visable = 1
prev_biggest = mountains[0]

for mountain in mountains:
	if mountain.x_final > prev_biggest.x_final:
		visable += 1
		prev_biggest = mountain

print(visable, file=open('mountains.out', 'w'))
'''