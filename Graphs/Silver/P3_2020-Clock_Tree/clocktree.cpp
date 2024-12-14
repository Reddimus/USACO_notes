// Depth-first search Biparte - Graph approach
// T: O(V + E) ≈ O(n), S: O(1)
// Where V = n = # of rooms, E = # of corridors and clocks/adjacency list is not counted as extra space

#include <bits/stdc++.h>
#define MAX_ROOMS 2501

using namespace std;

int main() {
	freopen("clocktree.in", "r", stdin);
	// Read in first line: n = number of rooms
	int n;
	cin >> n;
	// Read in second line: clock times of each room
	int clocks[MAX_ROOMS];
	for (int i = 1; i <= n; i++)
		cin >> clocks[i];
	// For the next n-1 lines, read in corridor edges connecting rooms
	vector<int> adjList[MAX_ROOMS];
	for (int ln = 0; ln < n-1; ln++) {
		int a, b;
		cin >> a >> b;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}

	// Depth-first search group 0 and group 1 nodes and their sums
	int sum0 = 0, sum1 = 0, nodeCount0 = 0, nodeCount1 = 0;
	function<void(int, int, int)> dfs = [&](int room, bool group, int parent) {
		// Update sums and node counts based on the group
		if (group == 0) {
			sum0 += clocks[room];
			nodeCount0++;
		} else {
			sum1 += clocks[room];
			nodeCount1++;
		}

		for (int nxtRoom : adjList[room])
			if (nxtRoom != parent)	// if next room has not been visited
				dfs(nxtRoom, !group, room);	// Swap groups for next room
	};

	dfs(1, 0, -1);	// Start from room 1, group 0, no parent

	freopen("clocktree.out", "w", stdout);
	// Same mod means you can start anywhere
	if (sum0 % 12 == sum1 % 12)
		cout << n << endl;
	// if group0 is 1 smaller than group1, we must start from group1
	else if ((sum0 + 1) % 12 == sum1 % 12)
		cout << nodeCount1 << endl;
	// if group1 is 1 smaller than group0, we must start from group0
	else if (sum0 % 12 == (sum1 + 1) % 12)
		cout << nodeCount0 << endl;
	// no way to get all clocks pointing to 12
	else
		cout << 0 << endl;
	return 0;
}
