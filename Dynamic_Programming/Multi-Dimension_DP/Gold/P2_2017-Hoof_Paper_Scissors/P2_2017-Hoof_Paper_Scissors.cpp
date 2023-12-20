// 3-Dimensional Dynamic Programming approach
// T&M: O(n*k), where n is the number of games and k is the number of switches

#include <bits/stdc++.h>
// #include <iostream>		// cin, cout
// #include <algorithm>	// max function

using namespace std;

int main() {
	freopen("hps.in", "r", stdin);
	// Read first line: n = num of gestures, k = num of gesture switches
	int n, k;
	cin >> n >> k;
	// For the next n lines store gestures into a list
	int gestures[n];
	for (int idx = 0; idx < n; idx++) {
		char gesture;
		cin >> gesture;
		switch (gesture) {
			case 'H':
				gestures[idx] = 0;
				break;
			case 'P':
				gestures[idx] = 1;
				break;
			case 'S':
				gestures[idx] = 2;
				break;
		}
	}


	// Initialize 3D dp arr to store the maximum number of wins for each state 
	// dp[n][k+1][3] = dp[nIdx][kIdx][g]
	// where nIdx is the current game number, kIdx represents the current number of switches, and g represents the current gesture in the dp array
	int dp[n][k+1][3] = {};
	for (int nIdx = 0; nIdx < n; nIdx++) {
		for (int kIdx = 0; kIdx <= k; kIdx++) {
			for (int g = 0; g < 3; g++) {
				// Increment score if current gesture wins in this round
				if (g == gestures[nIdx])
					dp[nIdx][kIdx][g]++;
				
				if (nIdx+1 < n) {
					if (kIdx+1 <= k) {
						// Update future state if a switch is made
						// if at least one switch is available, then the max wins of the next state is the max wins of the current state plus the current gesture
						dp[nIdx+1][kIdx+1][0] = max(dp[nIdx+1][kIdx+1][0], dp[nIdx][kIdx][g]);
						dp[nIdx+1][kIdx+1][1] = max(dp[nIdx+1][kIdx+1][1], dp[nIdx][kIdx][g]);
						dp[nIdx+1][kIdx+1][2] = max(dp[nIdx+1][kIdx+1][2], dp[nIdx][kIdx][g]);
					}
					// Update future state without a switch
					dp[nIdx+1][kIdx][g] = max(dp[nIdx+1][kIdx][g], dp[nIdx][kIdx][g]);
				}
			}
		}
	}

	// Write the accumlated max wins of the last game to the output file
	int maxWins = max({dp[n-1][k][0], dp[n-1][k][1], dp[n-1][k][2]});
	freopen("hps.out", "w", stdout);
	cout << maxWins << endl;
}