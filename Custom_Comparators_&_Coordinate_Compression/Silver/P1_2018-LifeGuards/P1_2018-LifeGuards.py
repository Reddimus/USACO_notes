# Sorting/Sweep Line/greedy/intervals method
# T: O(n log n), O(n), where n is amount of shifts

# Open input file
with open('lifeguards.in', 'r') as f:
	# First line: n = num of cow lifeguards
	n = int(f.readline())
	# For the next n lines assign start/end shifts with lifeguard ids
	shifts = []
	for lg_id in range(n):
		start, end = map(int, f.readline().split())
		shifts.append((start, True, lg_id))
		shifts.append((end, False, lg_id))

# Sort by time only
shifts.sort(key=lambda x: x[0])

total_time = 0
on_duty = set()			# tracked by lifeguard id
alone_time = [0] * n	# idx is lifeguard id, value is total alone time
prev_time = 0
# calculate variables in a sweep line/greedy method
for time, is_start, lg_id in shifts:
	if len(on_duty) == 1:	# if lifeguard has alone time
		alone_time[list(on_duty)[0]] += time - prev_time
	if len(on_duty) > 0:
		total_time += time - prev_time
	if is_start:
		on_duty.add(lg_id)
	else:
		on_duty.remove(lg_id)
	prev_time = time

# Write total time - life guard with least alone time to output file
print(total_time - min(alone_time), file=open('lifeguards.out', 'w'))