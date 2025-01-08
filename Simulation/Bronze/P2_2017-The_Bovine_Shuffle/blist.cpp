#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("blist.in", "r", stdin);
	// Read in first line: n = # of buckets
	int n;
	cin >> n;
	// For the next n lines, read in the start, end, and buckets needed
	int inUse[1001] = {0};
	for (int i = 0; i < n; i++) {
		int start, end, bucketsNeeded;
		cin >> start >> end >> bucketsNeeded;
		for (int j = start; j <= end; j++)
			inUse[j] += bucketsNeeded;
	}

	int totalBuckets = 0;
	for (int i = 0; i < 1001; i++)
		totalBuckets = max(totalBuckets, inUse[i]);
	freopen("blist.out", "w", stdout);
	cout << totalBuckets << endl;
	return 0;
}
