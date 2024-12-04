#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("cowsignal.in", "r", stdin);
	freopen("cowsignal.out", "w", stdout);
	// First line: m = rows, n = cols, k = multiplier
	int m, n, k;
	cin >> m >> n >> k;
	// For the next m lines, read in n chars and multiply each char by k
	for (int r = 0; r < m; ++r) {
		string currRow;
		for (int c = 0; c < n; ++c) {
			char ch;
			cin >> ch;
			// Multiply each char by k for the current row
			for (int mc = 0; mc < k; ++mc)
				currRow += ch;
		}
		// Multiply the current row by k
		for (int mr = 0; mr < k; ++mr)
			cout << currRow << endl;
	}
	return 0;
}
