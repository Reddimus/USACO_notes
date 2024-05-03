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
	// For the next n lines, read in the x & y coordinates into coordinate intercept maps
	unordered_map<int, vector<pair<int, int>>> xcoords, ycoords;
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;

		xcoords[x].push_back({y, i});
		ycoords[y].push_back({x, i});
	}

	Fence fences[N_MAX];

	for (auto& [x, xintercepts] : xcoords) {
		long long curr = 0;
		// sort all y positions of all points w/ the same x pos
		sort(xintercepts.begin(), xintercepts.end());
		// calculate the sum of heights for the first fence post
		for (int j = 1; j < xintercepts.size(); j++) 
			curr += xintercepts[j].first - xintercepts[0].first;
		fences[xintercepts[0].second].heightSum = curr;
		// calculate the sum of heights for the rest of the fence posts
		for (int j = 1; j < xintercepts.size(); j++) {
			curr += (2 * j - xintercepts.size()) * (xintercepts[j].first - xintercepts[j - 1].first);
			fences[xintercepts[j].second].heightSum = curr;
		}
	}

	// Same algorithm as above, but for y coordinates & base sum
	for (auto& [y, yintercepts] : ycoords) {
		long long curr = 0;
		// sort all x positions of all points w/ the same y pos
		sort(yintercepts.begin(), yintercepts.end());
		// calculate the sum of bases for the first fence post
		for (int j = 1; j < yintercepts.size(); j++) 
			curr += yintercepts[j].first - yintercepts[0].first;
		fences[yintercepts[0].second].baseSum = curr;
		// calculate the sum of bases for the rest of the fence posts
		for (int j = 1; j < yintercepts.size(); j++) {
			curr += (2 * j - yintercepts.size()) * (yintercepts[j].first - yintercepts[j - 1].first);
			fences[yintercepts[j].second].baseSum = curr;
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