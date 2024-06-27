#include <bits/stdc++.h>

#define N_MAX 501

using namespace std;

int main() {
	// Read in first line: n = number of cows
	int n;
	cin >> n;
	// For the next N lines read each cow's preference
	vector<int> gifts[N_MAX];
	for (int cow = 1; cow <= n; ++cow) {
		gifts[cow].resize(n);
		for (int& g : gifts[cow])
			cin >> g;
		// Compress preferences up to original gift
		while (gifts[cow].back() != cow) 
			gifts[cow].pop_back();
	}

	// Calculate reachable dfs
	bitset<N_MAX> reachable[N_MAX];
	for (int cow = 1; cow <= n; ++cow) {
		int currGift = cow;
		if (reachable[cow][currGift]) 
			continue;

		vector<int> frontier = {currGift};
		while(!frontier.empty()) {
			currGift = frontier.back();
			frontier.pop_back();
			reachable[cow][currGift] = true;
			for (int& preferredGift : gifts[currGift]) 
				if (!reachable[cow][preferredGift]) 
					frontier.push_back(preferredGift);
		}
	}

	for (int cow = 1; cow <= n; ++cow) {
		for (int g : gifts[cow]) {
			if (reachable[g][cow]) {
				cout << g << endl;
				break;
			}
		}
	}
	return 0;
}