# USACO 2018 January Contest, Silver
## Problem 1. Lifeguards

http://www.usaco.org/index.php?page=viewproblem2&cpid=786

Farmer John has opened a swimming pool for his cows, figuring it will help them relax and produce more milk.
To ensure safety, he hires `N` cows as lifeguards, each of which has a shift that covers some contiguous interval of time during the day. For simplicity, the pool is open from time `t=0` until time `t=1,000,000,000` on a daily basis, so each shift can be described by two integers, giving the time at which a cow starts and ends her shift. For example, a lifeguard starting at time `t=4` and ending at time t=7 covers three units of time (note that the endpoints are "points" in time).

Unfortunately, Farmer John hired 1 more lifeguard than he has the funds to support. Given that he must fire exactly one lifeguard, what is the maximum amount of time that can still be covered by the shifts of the remaining lifeguards? An interval of time is covered if at least one lifeguard is present.

#### INPUT FORMAT (file lifeguards.in):
The first line of input contains `N` `(1≤N≤100,000)`. Each of the next `N` lines describes a lifeguard in terms of two integers in the range `0…1,000,000,000`, giving the starting and ending point of a lifeguard's shift. All such endpoints are distinct. Shifts of different lifeguards might overlap.

#### OUTPUT FORMAT (file lifeguards.out):
Please write a single number, giving the maximum amount of time that can still be covered if Farmer John fires 1 lifeguard.

#### SAMPLE INPUT:
```
3  
5 9  
1 4  
3 7
```
#### SAMPLE OUTPUT:
```
7
```

## Solution

https://github.com/Reddimus/USACO_notes/tree/main/Custom_Comparators_and_Coordinate_Compression/Silver/P1_2018-LifeGuards

### Custom Comparators + Sorting + Sweep Line Approach

#### Time Complexity: O(n log n)
#### Space Complexity: O(n)
Where n is amount of shifts

### Python Code:
```Python
class Shift_Event:
	def __init__(self, time = int, lifeguard_id = int, is_start = bool):
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
```

### C++ Code:
```C++
#include <bits/stdc++.h>

using namespace std;

struct ShiftEvent {
	int time, lifeguardID;
	bool isStart;
};

int main() {
	// Open input file
	freopen("lifeguards.in", "r", stdin);
	// First line: n = number of cow lifeguards
	int n;
	cin >> n;
	// For the next n lines assign start/end shifts with lifeguard IDs (ID is based on idx)
	vector<ShiftEvent> shifts;
	for (int lg_id = 0; lg_id < n; lg_id++) {
		int start, end;
		cin >> start >> end;
		shifts.push_back({start, lg_id, true});
		shifts.push_back({end, lg_id, false});
	}

	// Sort the shifts by time only
	sort(shifts.begin(), shifts.end(), [](ShiftEvent a, ShiftEvent b) {return a.time < b.time;});

	int aloneTime[n] = {};				// idx is lifeguard id, value is total alone time
	unordered_set<int> onDuty;			// tracked by lifeguard id
	int prevTime = 0, totalTime = 0;
	// iterate through shift events calculating result using sweep line approach
	for (ShiftEvent &se : shifts) {
		if (onDuty.size() == 1)
			aloneTime[*onDuty.begin()] += se.time - prevTime;
		
		if (onDuty.size() > 0)
			totalTime += se.time - prevTime;
		
		if (se.isStart)
			onDuty.insert(se.lifeguardID);
		else
			onDuty.erase(se.lifeguardID);

		prevTime = se.time;
	}

	// Write total time - life guard with least alone time to output file
	freopen("lifeguards.out", "w", stdout);
	cout << totalTime - *min_element(aloneTime, aloneTime + n) << endl;
}
```

### Java Code:
```Java
import java.io.*;
import java.util.*;

public class LifeGuards {
	
	static class ShiftEvent {
		public int time, lifeguardID;
		public boolean isStart;
		
		public ShiftEvent(int time, int lifeguardID, boolean isStart) {
			this.time = time;
			this.lifeguardID = lifeguardID;
			this.isStart = isStart;
		}
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("lifeguards.in"));
		// First line: n = number of cow lifeguards
		int n = Integer.parseInt(br.readLine());
		// For the next n lines track start/end times + lifeguard IDs (id is based on idx)
		ShiftEvent[] shifts = new ShiftEvent[2 * n];
		for (int idx = 0; idx < n; idx++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int start = Integer.parseInt(st.nextToken());
			int end = Integer.parseInt(st.nextToken());
			shifts[2*idx] = new ShiftEvent(start, idx, true);
			shifts[2*idx+1] = new ShiftEvent(end, idx, false);
		}
		br.close();

		// Sort events by time only
		Arrays.sort(shifts, Comparator.comparingInt(a -> a.time));

		int totalTime = 0, prevTime = 0;
		int[] aloneTime = new int[n];			// idx is lifeguard id, value is total alone time
		Set<Integer> onDuty = new HashSet<Integer>();	// tracked by lifeguard id
		// iterate through shift events calculating result using sweep line approach
		for (ShiftEvent se : shifts) {
			if (onDuty.size() == 1)
				aloneTime[onDuty.iterator().next()] += se.time - prevTime;

			if (onDuty.size() > 0)
				totalTime += se.time - prevTime;

			if (se.isStart)
				onDuty.add(se.lifeguardID);
			else
				onDuty.remove(se.lifeguardID);

			prevTime = se.time;
		}

		// Write total time - life guard with least alone time to output file
		PrintWriter out = new PrintWriter("lifeguards.out");
		out.println(totalTime - Arrays.stream(aloneTime).min().getAsInt());
		out.close();
	}
}
```
