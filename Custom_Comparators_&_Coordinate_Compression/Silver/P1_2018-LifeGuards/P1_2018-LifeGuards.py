# Sorting/Sweep Line/greedy/intervals method
# T: O(n log n), O(n), where n is amount of shifts

class Shift_Event:
	def __init__(self, time = int, lifeguard_id = int, is_start = bool) -> None:
		self.time = time
		self.lifeguard_id = lifeguard_id
		self.is_start = is_start

# Open input file
with open('lifeguards.in', 'r') as f:
	# First line: n = num of cow lifeguards
	n = int(f.readline())
	# For the next n lines assign start/end shifts with lifeguard ids
	shifts = []
	for lg_id in range(n):
		start, end = map(int, f.readline().split())
		shifts.append(Shift_Event(start, lg_id, True))
		shifts.append(Shift_Event(end, lg_id, False))

# Sort by time only
shifts.sort(key=lambda se: se.time)

total_time = 0
on_duty = set()			# tracked by lifeguard id
alone_time = [0] * n	# idx is lifeguard id, value is total alone time
prev_time = 0
# iterate through shift events calculating result using sweep line approach
for se in shifts:
	if len(on_duty) == 1:	# if current lifeguard is alone
		alone_time[next(iter(on_duty))] += se.time - prev_time
	if len(on_duty) > 0:
		total_time += se.time - prev_time
	if se.is_start:
		on_duty.add(se.lifeguard_id)
	else:
		on_duty.remove(se.lifeguard_id)
	prev_time = se.time
# Write total time - life guard with least alone time to output file
print(total_time - min(alone_time), file=open('lifeguards.out', 'w'))