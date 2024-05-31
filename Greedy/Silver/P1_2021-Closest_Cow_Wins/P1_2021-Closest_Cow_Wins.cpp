// Greedy Algorithms with Sorting approach

#include <bits/stdc++.h>

using namespace std;

int main() {
	// Read in first line: k = # of grassy patches, m = # of cows, n = # of cows that can be placed
	int k, m, n;
	cin >> k >> m >> n;

	// Store the positions & tastiness of patches & the positions of Nhoj's cows
	vector<pair<int, int>> patches(k+m);	// patches and Nhoj's cows
	for (int i = 0; i < k; ++i) {
		cin >> patches[i].first >> patches[i].second;
	}
	for (int i = k; i < k + m; ++i) {
		cin >> patches[i].first;	// Read positions of Nhoj's cows
		patches[i].second = -1;	// Mark these positions with -1 to distinguish them
	}

	sort(begin(patches), end(patches));	// Sort the patches by position

	vector<unsigned long> increases;    // to store the increase in tastiness we can achieve
	int lastI = -1;
	unsigned long sumRange = 0; // to store the sum of tastiness in the current interval

	// Process each patch & cow
	for (int i = 0; i < patches.size(); ++i) {
		if (patches[i].second == -1) {	// If its a cow position
			if (lastI == -1) {	// If its the leftmost cow
				increases.push_back(sumRange); // add the sum of tastiness to increases
			} else {
				// Sliding window approach to find the maximum tastiness that can be claimed with one cow
				unsigned long currAns1 = 0; // current sum of the sliding window
				unsigned long bestAns1 = 0; // best sum found over all windows
				for (int j = lastI + 1, r = lastI; j < i; ++j) {
					// Slide the window to the right
					while (r + 1 < i && 
					(patches[r + 1].first - patches[j].first) * 2 < (patches[i].first - patches[lastI].first)) {
						currAns1 += patches[++r].second;
					}
					// Update the best sum found
					bestAns1 = max(bestAns1, currAns1);
					currAns1 -= patches[j].second;	// remove the leftmost patch from the window
				}
				// Store the best sum for one cow
				increases.push_back(bestAns1);

				// Store the difference between the sum of the interval & the best sum for one cow
				increases.push_back(sumRange - bestAns1);
			}
			// Update the last cow position
			lastI = i;
			sumRange = 0; // reset the sum for the next interval
		} else {
			// Add the tastiness to the current interval sum
			sumRange += patches[i].second;
		}
	}

	// Try placing to the right of Nhoj's rightmost cow
	increases.push_back(sumRange);

	// Sort the increases in decreasing order
	sort(rbegin(increases), rend(increases));

	// We only need the first N increases
	increases.resize(n);

	// Sum & ouput the largerst N increases
	unsigned long sum = accumulate(begin(increases), end(increases), 0UL);
	cout << sum << endl;
	return 0;
}