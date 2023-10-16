// Knapsack + 2-D Dynamic Programming + Bit-manipulation approach
// T & M: O(t), where t = maximum given fullness

#include <bits/stdc++.h>

#define T_MAX	5000000

using namespace std;

// print 2D array function
// void printArr(vector<vector<int>> arr) {
// 	for (int i = 0; i < arr.size(); ++i) {
// 		for (int j = 0; j < arr[0].size(); ++j)
// 			cout << arr[i][j] << " ";
// 		cout << endl;
// 	}
// 	cout << endl;
// }

int main() {
	freopen("feast.in", "r", stdin);
	int t, a, b;
	cin >> t >> a >> b;

	// dp[drinkedWater?][fullness], where 1 = true, 0 = false
	vector<vector<int>> dp(2, vector<int>(t+1, 0));	// allocated on the heap
	dp[0][0] = true;	// base case 0 fullness
	// printArr(dp);
	for (int idx = 0; idx <= t; ++idx) {
		// Find individual fullness without drinking water
		if (idx - a >= 0)
			dp[0][idx] |= dp[0][idx-a];
		if (idx - b >= 0)
			dp[0][idx] |= dp[0][idx-b];
		// Find fullness after drinking water
		dp[1][idx/2] |= dp[0][idx];
	}
	// printArr(dp);

	// Using fullness after drinking water find new fullness
	for (int idx = 0; idx <= t; ++idx) {
		if (idx - a >= 0)
			dp[1][idx] |= dp[1][idx-a];
		if (idx - b >= 0)
			dp[1][idx] |= dp[1][idx-b];
	}
	// printArr(dp);

	// Find the maximum fullness
	freopen("feast.out", "w", stdout);
	for (int idx = t; idx >= 0; --idx) {
		if (dp[1][idx]) {
			cout << idx << endl;
			break;
		}
	}

	return 0;
}
