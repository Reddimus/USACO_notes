#include <bits/stdc++.h>

#define N_MAX 100001

using namespace std;

struct Entry {
	int value, index;
};

int main() {
	freopen("sort.in", "r", stdin);
	// Read in first line: n = length of array
	int n;
	cin >> n;
	// For the next n lines, record the value & index of each entry
	Entry entries[N_MAX];
	for (int idx = 0; idx < n; idx++) {
		cin >> entries[idx].value;
		entries[idx].index = idx;
	}

	// Sort the array in ascending order, breaking ties by initial index
	sort(entries, entries + n, 
		[](const Entry &a, const Entry &b) {
			if (a.value == b.value) 
				return a.index < b.index;
			return a.value < b.value;
		}
	);

	// Using initial indeces count the # of bubbles needed to sort the array
	int mooCount = 1;
	for (int i = 0; i < n; i++) 
		mooCount = max(mooCount, entries[i].index - i + 1);
		// add 1 to account for the final iteration of the algorithm
	// Write the number of "moos"/bubbles needed to sort the array
	freopen("sort.out", "w", stdout);
	cout << mooCount << endl;
}
