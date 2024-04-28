#include <bits/stdc++.h>

using namespace std;

#define N_MAX 100001
#define MOD 1000000007

struct Fence {
	long long heightSum, baseSum;
};

int main() {
	freopen("triangles.in", "r", stdin);
	// Read in first line: n = fence posts
	int n;
	cin >> n;
	// For the next n lines, read in the x and y coordinates of the fence posts
	unordered_map<int, vector<pair<int, int>>> xcoords, ycoords;
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;

		xcoords[x].push_back({y, i});
		ycoords[y].push_back({x, i});
	}

	Fence fences[N_MAX];

	for (auto& [x, vec] : xcoords) {
		long long curr = 0;
		// sort all y positions of all points w/ the same x pos
		sort(vec.begin(), vec.end());
		/*
		* then we compute the value s_1 of this set:
		* the sum of the heights of all the triangles that
		* have their anchor point at (i, xcoords[i][0].first)
		*/
		for (int j = 1; j < vec.size(); j++) 
			curr += vec[j].first - vec[0].first;
		fences[vec[0].second].heightSum = curr;
		for (int j = 1; j < vec.size(); j++) {
			curr += (2 * j - vec.size()) *
					(vec[j].first - vec[j - 1].first);
			fences[vec[j].second].heightSum = curr;
		}
	}

	// we do the sums of bases in exactly the same way
	for (auto& [y, vec] : ycoords) {
		long long curr = 0;
		sort(vec.begin(), vec.end());
		for (int j = 1; j < vec.size(); j++) 
			curr += vec[j].first - vec[0].first;
		fences[vec[0].second].baseSum = curr;
		for (int j = 1; j < vec.size(); j++) {
			curr += (2 * j - vec.size()) *
					(vec[j].first - vec[j - 1].first);
			fences[vec[j].second].baseSum = curr;
		}
	}

	long long totalArea = 0;
	for (int i = 0; i < n; ++i) {
		totalArea += fences[i].heightSum * fences[i].baseSum % MOD;
		totalArea %= MOD;
	}

	freopen("triangles.out", "w", stdout);
	cout << totalArea << endl;
	return 0;
}