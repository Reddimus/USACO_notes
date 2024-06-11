#include <bits/stdc++.h>
#define N_MAX 100001

using namespace std;

int main() {
	freopen("wormsort.in", "r", stdin);
	// Read in first line: n = # of cows, m = # of wormholes
	int n, m;
	cin >> n >> m;
	// Read in cow locations in second line of size n
	int cowLocations[N_MAX];
	for (int cow = 1; cow <= n; ++cow) 
		cin >> cowLocations[cow];
	// For the next m lines map the wormholes with their widths
	unsigned int maxWidth = 0;
	vector<vector<pair<unsigned int, unsigned int>>> wormholes(n + 1);
	for (int ln = 0; ln < m; ++ln) {
		unsigned int locationA, locationB, width;
		cin >> locationA >> locationB >> width;
		wormholes[locationA].push_back({locationB, width});
		wormholes[locationB].push_back({locationA, width});
		maxWidth = max(maxWidth, width);
	}

	// Binary search the maximum minimal wormhole width
	unsigned int lo = 1, hi = maxWidth + 1;
	long minSwapWidth = -1;
	while (lo <= hi) {
		unsigned int mid = (lo + hi) / 2;

		// Depth first search connected components with a minimum (mid) width
		vector<int> components(n + 1, -1);
		int currComponent = 0;
		for (int cowLocation = 1; cowLocation <= n; ++cowLocation) {
			if (components[cowLocation] != -1) 
				continue;
			
			vector<int> frontier = {cowLocation};
			while (!frontier.empty()) {
				int locationA = frontier.back();
				frontier.pop_back();
				components[locationA] = currComponent;
				for (const auto& [locationB, width] : wormholes[locationA])
					if (components[locationB] == -1 && width >= mid) 
						frontier.push_back(locationB);
			}
			++currComponent;
		}

		// Cows are sorted if component is mapped to itself or the cow has a network to swap into
		bool sortable = true;
		for(int cowLocation = 1; cowLocation <= n && sortable; ++cowLocation) 
			if (components[cowLocation] != components[cowLocations[cowLocation]]) 
				sortable = false;
		
		if (sortable) {
			minSwapWidth = mid;	// update answer
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}
	freopen("wormsort.out", "w", stdout);
	// If the minSwapWidth is an impossible value, cowLocations are already sorted
	cout << (minSwapWidth == maxWidth + 1 ? -1 : minSwapWidth) << endl;
	return 0;
}