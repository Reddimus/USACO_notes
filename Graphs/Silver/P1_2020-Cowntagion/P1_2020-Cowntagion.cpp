#include <bits/stdc++.h>
#define MAX_FARMS 100001

using namespace std;

int main() {
	// Read in first line: n = # of farms
	int n;
	cin >> n;
	vector<vector<int>> adjList(n + 1);
	// For next n-1 lines, map adjacenct farms
	for (int ln = 0; ln < n - 1; ++ln) {
		int a, b;
		cin >> a >> b;
		adjList[a].push_back(b);
		adjList[b].push_back(a);
	}

	// Breadth first search to find min days to infect all farms
	int days = 0;
	bitset<MAX_FARMS> visited;
	queue<int> q;
	q.push(1);	// Start at farm 1

	while (!q.empty()) {
		int farm = q.front();
		q.pop();

		if (visited[farm])
			continue;

		visited[farm] = true;

		int farmsToInfect = 0;
		for (int neighbor : adjList[farm]) {
			if (!visited[neighbor]) {
				q.push(neighbor);
				++farmsToInfect;
			}
		}

		// Add days for superspreader events
		int infectedCount = 1;
		while (infectedCount < farmsToInfect + 1) {
			infectedCount *= 2;
			++days;
		}

		days += farmsToInfect;
	}

	cout << days << endl;
}
