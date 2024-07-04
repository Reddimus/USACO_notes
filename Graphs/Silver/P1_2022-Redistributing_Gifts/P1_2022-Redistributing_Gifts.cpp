#include <bits/stdc++.h>

#define N_MAX 501

using namespace std;

int main() {
	// Read in first line: n = number of cows
	int n;
	cin >> n;
	// For the next N lines read each cow's gift preference
	int gifts[N_MAX][N_MAX] = {0};
	for (int cow = 1; cow <= n; ++cow) {
		for (int gi = 0; gi < n; ++gi) 
			cin >> gifts[cow][gi];
		// Compress preferences up to original gift
		for (int gi = n - 1; gi >= 0 && gifts[cow][gi] != cow; --gi) 
			gifts[cow][gi] = 0;
	}

	// Calculate reachable dfs
	bitset<N_MAX> reachable[N_MAX];	// 1-indexed
	for (int cow = 1; cow <= n; ++cow) {
		int currGift = cow;
		if (reachable[cow][currGift]) 
			continue;

		vector<int> frontier = {currGift};
		while(!frontier.empty()) {
			currGift = frontier.back();
			frontier.pop_back();
			reachable[cow][currGift] = true;
			for (int gi = 0; gi < n && gifts[currGift][gi]; ++gi) {
				const int& g = gifts[currGift][gi];
				if (!reachable[cow][g])
					frontier.push_back(g);
			}
		}
	}

	for (int cow = 1; cow <= n; ++cow) {
		for (int gi = 0; gi < n && gifts[cow][gi]; ++gi) {
			const int& g = gifts[cow][gi];
			if (reachable[g][cow]) {
				cout << g << endl;
				break;
			}
		}
	}
	return 0;
}