'''
USACO 2018 January Contest, Bronze
Problem 2. Lifeguards

Farmer John has opened a swimming pool for his cows, figuring it will help them relax and 
produce more milk.

To ensure safety, he hires N cows as lifeguards, each of which has a shift that covers some 
contiguous interval of time during the day. For simplicity, the pool is open from time t=0
until time t=1000 on a daily basis, so each shift can be described by two integers, giving 
the time at which a cow starts and ends her shift. For example, a lifeguard starting at time 
t=4 and ending at time t=7 covers three units of time 
(note that the endpoints are "points" in time).

Unfortunately, Farmer John hired 1 more lifeguard than he has the funds to support. Given 
that he must fire exactly one lifeguard, what is the maximum amount of time that can still 
be covered by the shifts of the remaining lifeguards? An interval of time is covered if at 
least one lifeguard is present.

INPUT FORMAT (file lifeguards.in):
The first line of input contains N
(1≤N≤100). Each of the next N lines describes a lifeguard in terms of two integers in the 
range 0…1000, giving the starting and ending point of a lifeguard's shift. All such endpoints 
are distinct. Shifts of different lifeguards might overlap.

OUTPUT FORMAT (file lifeguards.out):
Please write a single number, giving the maximum amount of time that can still be covered if 
Farmer John fires 1 lifeguard.

SAMPLE INPUT:
3
5 9
1 4
3 7

SAMPLE OUTPUT:
7
'''

"""
This approach is less intuitive but the most efficient. The approach sorts all the 
events (start and end of each lifeguard's shift) and then processes them in order. 
It keeps track of the total time covered and the time covered by each lifeguard. 
It then determines the maximum coverage possible after removing one lifeguard by 
subtracting that lifeguard's alone time from the total time.

This approach in big O notation is the most time optimal. However since our shifts data 
structure is the size of O(2n+) the preformance is close to the other solutions after
sorting and iterating/calculating through the shifts array.

Keep in mind creating methods/functions takes up extra memory. 
For the purporse of competitive programming a method will not be used as there isnt repetitive code.
Keep in mind using a function over repeating code is still preffered.

- Greedy: In this problem, we are trying to maximize the coverage of lifeguard shifts even after 
firing one lifeguard. The greedy aspect here is that we always consider the current situation and 
make the most beneficial decision - we always fire the lifeguard that will result in the least loss 
of total coverage.

- Intervals: Each lifeguard's shift is represented as an interval of time. We have to deal with 
potential overlaps of these intervals and compute properties like total coverage and the alone 
time for each lifeguard.
"""
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