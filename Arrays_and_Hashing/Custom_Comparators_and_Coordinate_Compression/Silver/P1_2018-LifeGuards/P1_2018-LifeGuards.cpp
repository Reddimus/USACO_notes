// Custom Comparators + Sorting + Sweep Line Approach
// T: O(n log n), M: O(n), where n is amount of shifts

// #include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
class ShiftEvent {
public:
	int time, lifeguardID;
	bool isStart;
	ShiftEvent(int time, int lifeguardID, bool isStart) {
		this->time = time;
		this->lifeguardID = lifeguardID;
		this->isStart = isStart;
	}
};
*/

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
	for (int lifeguardID = 0; lifeguardID < n; lifeguardID++) {
		int start, end;
		cin >> start >> end;
		shifts.push_back({start, lifeguardID, true});
		shifts.push_back({end, lifeguardID, false});
	}

	// Sort the shifts by time only
	sort(shifts.begin(), shifts.end(), [](ShiftEvent a, ShiftEvent b) {return a.time < b.time;});

	vector<int> aloneTime(n);			// idx is lifeguard id, value is total alone time
	unordered_set<int> onDuty;			// tracked by lifeguard id
	int prevTime = 0, totalTime = 0;
	// Iterate through shift events calculating result using sweep line approach
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
	cout << totalTime - *min_element(aloneTime.begin(), aloneTime.end()) << endl;
}
