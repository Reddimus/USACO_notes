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

	int sum0 = 0, sum1 = 0, nodes0 = 0, nodes1 = 0;
	function<void(int, int, int)> dfs = [&](int i, int color, int parent) {
		// Update color/sum
		if (color == 0) {
			nodes0++;
			sum0 += clocks[i];
		} else {
			nodes1++;
			sum1 += clocks[i];
		}

		for (int nxt : adjList[i])
			if (nxt != parent)
				dfs(nxt, 1 - color, i);	// Swap colors for the child node
	};

	dfs(1, 0, -1);	// Start from room 1, color 0

	freopen("clocktree.out", "w", stdout);
	// Same mod means you can start anywhere
	if (sum0 % 12 == sum1 % 12)
		cout << n << endl;
	// if group0 is 1 smaller than group1, we must start from group1
	else if ((sum0 + 1) % 12 == sum1 % 12)
		cout << nodes1 << endl;
	// if group1 is 1 smaller than group0, we must start from group0
	else if (sum0 % 12 == (sum1 + 1) % 12)
		cout << nodes0 << endl;
	// no way to get all clocks pointing to 12
	else
		cout << 0 << endl;
	return 0;
}
