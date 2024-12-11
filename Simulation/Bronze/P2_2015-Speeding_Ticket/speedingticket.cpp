#include <bits/stdc++.h>
#define ROAD_LENGTH 100

using namespace std;

int main() {
	freopen("speeding.in", "r", stdin);
	// Read first line: n = road segments, m = bessie's segments
	int n, m;
	cin >> n >> m;

	// For the next n lines read in road segments
	int speedLimits[ROAD_LENGTH];
	int lastPosition = 0;
	for (int ln = 0; ln < n; ++ln) {
		int length, speedLimit;
		cin >> length >> speedLimit;
		for (int idx = lastPosition; idx < lastPosition + length; ++idx)
			speedLimits[idx] = speedLimit;

		lastPosition += length;
	}

	// For the next m lines read in Bessie's segments
	int bessieSpeeds[ROAD_LENGTH];
	lastPosition = 0;
	for (int ln = 0; ln < m; ++ln) {
		int length, speed;
		cin >> length >> speed;
		for (int idx = lastPosition; idx < lastPosition + length; ++idx)
			bessieSpeeds[idx] = speed;

		lastPosition += length;
	}

	// For the length of the road, find the max difference between speed limits and Bessie's speed
	int maxOver = 0;
	for (int idx = 0; idx < ROAD_LENGTH; ++idx) 
		maxOver = max(maxOver, bessieSpeeds[idx] - speedLimits[idx]);

	// Write the max over speed to the output file
	freopen("speeding.out", "w", stdout);
	cout << maxOver << endl;
	return 0;	
}
