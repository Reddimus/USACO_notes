#include <bits/stdc++.h>

using namespace std;

// Greddy DFS/Backtrack approach
// Time complexity: O(n * log(max(personalityA, personalityB)))
// Space complexity: O(log(max(personalityA, personalityB)))
// Where n is number of pairs of cows

long long minOperations(long long num, long long target) {
	if (num == target)
		return 0;
	// Divide a greedily until a <= b, add 1 in case a is odd to enable division.
	if (num > target) {
		long long isNumOdd = num % 2;
		return 1 + isNumOdd + minOperations((num + isNumOdd) / 2, target);
	}

	// Otherwise, work on b to reach a by division.
	// Alternatively, if it's better, perform subtraction until a is reached.
	long long isTargetOdd = target % 2;
	return min(target - num, 1 + isTargetOdd + minOperations(num, target / 2));
}

int main() {
	// Read in first lines: n = pairs of cows
	int n;
	cin >> n;
	// For the next n solve min change operations per pair
	for (int ln = 0; ln < n; ++ln) {
		long long personalityA, personalityB;
		cin >> personalityA >> personalityB;
		
		cout << minOperations(personalityA, personalityB) << endl;
	}

	return 0;
}

/*
// Backtack using BFS w/ memoization approach
// Time complexity: O(3^log(n)) = O(n^log(3))
// Space complexity: O(3^L)
// Where n is number of pairs of cows and L is the min operations

unsigned long bfs(long long start, long long target) {
	unordered_set<long long> visited;
	queue<long long> q;
	q.push(start);
	visited.insert(start);
	for (unsigned long lvl = 0; !q.empty(); ++lvl) {
		unsigned long qSize = q.size();
		for (unsigned long i = 0; i < qSize; ++i) {
			long long num = q.front();
			q.pop();

			if (num == target)
				return lvl;

			// Perform operations, avoid revisiting nodes
			if (num < LLONG_MAX / 2 && visited.find(num * 2) == visited.end()) {
				q.push(num * 2);
				visited.insert(num * 2);
			}
			if (num % 2 == 0 && visited.find(num / 2) == visited.end()) {
				q.push(num / 2);
				visited.insert(num / 2);
			}
			if (visited.find(num + 1) == visited.end()) {
				q.push(num + 1);
				visited.insert(num + 1);
			}
		}
	}
	return ULONG_MAX;
}

int main() {
	// Read in first lines: n = pairs of cows
	int n;
	cin >> n;
	// For the next n solve min change operations per pair
	for (int ln = 0; ln < n; ++ln) {
		long long personalityA, personalityB;
		cin >> personalityA >> personalityB;
		
		cout << bfs(personalityA, personalityB) << endl;
	}

	return 0;
}
*/