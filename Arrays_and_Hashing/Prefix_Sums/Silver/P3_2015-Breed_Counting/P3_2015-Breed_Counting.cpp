// Prefix sums approach
// T: O(n + q), M: O(n), where n is num of cows, and q is num of queries

// #include <bits/stdc++.h>

#include <iostream>

using namespace std;

int main() {
	// Open input file
	freopen("bcount.in", "r", stdin);
	// first line: n = num of cows, q = num of queries
	int n, q;
	cin >> n >> q;

	// For next n lines read cow breed IDs and create prefix sum lists
	int holsteins[n+1] = {}, guernseys[n+1] = {}, jerseys[n+1] = {};
	for (int idx = 1; idx < n + 1; idx++) {
		holsteins[idx] += holsteins[idx-1];
		guernseys[idx] += guernseys[idx-1];
		jerseys[idx] += jerseys[idx-1];
		int cow_id;
		cin >> cow_id;
		switch (cow_id) {
			case 1:
				holsteins[idx]++;
				break;
			case 2:
				guernseys[idx]++;
				break;
			case 3:
				jerseys[idx]++;
				break;
		}
	}

	// For next q lines solve num of cow breeds in query range and write queries ids to output file
	freopen("bcount.out", "w", stdout);
	for (int ln = 0; ln < q; ln++) {
		int start, end;
		cin >> start >> end;
		cout << holsteins[end] - holsteins[start-1] << " "
			<< guernseys[end] - guernseys[start-1] << " "
		    << jerseys[end] - jerseys[start-1] << endl;
	}
}
