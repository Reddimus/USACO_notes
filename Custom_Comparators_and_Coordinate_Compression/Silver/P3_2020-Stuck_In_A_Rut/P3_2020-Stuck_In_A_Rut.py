# Run file with: Get-Content sample.in | python P3_2020-Stucn_idx_In_A_Rut.py

class Cow_Coordinate:
	def __init__(self, x: int, y: int) -> None:
		self.x, self.y = x, y

# Read first line: n = number of cows
n = int(input().strip())
# For the next n lines: store initial direction, x & y coordinates of each cow
east_idxs, north_idxs = [], []	# indexes of east and north cows; can be less than n
cow_coords = [None] * n
for idx in range(n):
	direction, x, y = input().split()

	if direction == 'E':
		east_idxs.append(idx)
	elif direction == 'N':
		north_idxs.append(idx)

	cow_coords[idx] = Cow_Coordinate(int(x), int(y))

# Sort east and north cow indexes by their y or x coordinates respectively
east_idxs.sort(key=lambda idx: cow_coords[idx].y)
north_idxs.sort(key=lambda idx: cow_coords[idx].x)

# print(f'East cow indexes: {east_idxs}')
# print(f'North cow indexes: {north_idxs}')
# print('Cow coordinates:', end=' ')
# for cow_coord in cow_coords:
# 	print(f'({cow_coord.x}, {cow_coord.y})', end=' ')
# print()

stopped = [False] * n
amount_stopped = [0] * n

# For each east cow, check if it will stop any north cow
for e_idx in east_idxs:
	for n_idx in north_idxs:
		# If both cows are not stopped and the north cow is to the north-east of the east cow
		if (not stopped[e_idx]) and (not stopped[n_idx]) and (cow_coords[n_idx].x > cow_coords[e_idx].x) and (cow_coords[e_idx].y > cow_coords[n_idx].y):

			x_dist = cow_coords[n_idx].x - cow_coords[e_idx].x
			y_dist = cow_coords[e_idx].y - cow_coords[n_idx].y

			if x_dist > y_dist:
				stopped[e_idx] = True
				amount_stopped[n_idx] += (1 + amount_stopped[e_idx])
			elif x_dist < y_dist:
				stopped[n_idx] = True
				amount_stopped[e_idx] += (1 + amount_stopped[n_idx])
			
for amnt_stp in amount_stopped:
	print(amnt_stp)