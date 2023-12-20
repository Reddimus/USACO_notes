// 2-D Dynamic Programming + Graph Traversal approach
// T: O(MAX_DAYS * n * m), M: O(MAX_DAYS * n)
// Where n = num cities, m = num of one way roads, MAX_DAYS = 1000

#define MAX_DAYS 1000

#include <bits/stdc++.h>
// #include <iostream>
// #include <vector>

using namespace std;

int main() {
	freopen("time.in", "r", stdin);
	// First line: n = num cities, m = num of one way roads, c = cost multiplier
	int n, m, c;
	cin >> n >> m >> c;

	// Second line: moonies[i] = moonies earned in city i
	int moonies[n];
	for (int cityIdx = 0; cityIdx < n; ++cityIdx)
		cin >> moonies[cityIdx];

	// For the next m lines create adjacency list for one way roads between cities
	// index = city, value(s) = cities it connects to
	vector<vector<int>> adj(n);
	for (int ln = 0; ln < m; ++ln) {
		int cityA, cityB;
		cin >> cityA >> cityB;
		adj[--cityA].push_back(--cityB);
	}

	// dp[day][city], where maxDays = 1000
	vector<vector<int>> dp(MAX_DAYS + 1, vector<int>(n, -1));
	dp[0][0] = 0;	// base case

	// For each day, stockpile moonies in each city visited using one way roads
	int maxMoony = 0;
	for (int day = 0; day < MAX_DAYS; ++day) {
		for (int city = 0; city < n; ++city) {
			// if dp[day][city] is -1, then there is no path to that city
			if (dp[day][city] != -1) {
				for (int nextCity : adj[city]) {
					dp[day + 1][nextCity] = max(dp[day + 1][nextCity], dp[day][city] + moonies[nextCity]);

					// Print sample input 1 DP table
					// if (day <= 13) {
					// 	cout << "Day: " << day << " City: " << city << endl;
					// 	for (int d = 0; d < 13; ++d) {
					// 		for (int c = 0; c < n; ++c) {
					// 			cout << dp[d][c] << " ";
					// 		}
					// 		cout << endl;
					// 	}
					// 	cout << endl;
					// }
				}
			}
		}
		
		// We are only looking for maxMoony that loops back to city 1
		if (dp[day][0] != -1) {
			int tempMoony = dp[day][0] - (c * day * day);
			// cout << "Potential Mooney: " << tempMoony << endl;
			// If all potential maxMoony values have been calculated, break
			if (tempMoony < 0 && maxMoony != 0)
				break;
			maxMoony = max(maxMoony, tempMoony);
			// cout << "Max Mooney: " << maxMoony << endl << endl;
		}
	}

	// Write maxMoony generated from visiting cities to output file
	freopen("time.out", "w", stdout);
	cout << maxMoony << endl;
}
