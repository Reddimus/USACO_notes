# USACO 2020 January Contest, Gold
## Problem 1. Time is Mooney

http://www.usaco.org/index.php?page=viewproblem2&cpid=993

### Problem Statement

Bessie is conducting a business trip in Bovinia, where there are `N` `(2 <= N <= 1000)` cities labeled `1...N`
connected by `M` `(1 <= M <= 2000)` one-way roads. Every time Bessie visits city `i`,
Bessie earns `mi` moonies `(0 <= mi <= 1000)`. Starting at city 1 Bessie wants to visit cities to make as much mooney as she can, ending back at city 1. To avoid confusion, `m1 = 0`.

Mooving between two cities via a road takes one day. Preparing for the trip is expensive; it costs `C * T^2`
moonies to travel for `T` days `(1 <= C <= 1000)`.

What is the maximum amount of moonies Bessie can make in one trip? Note that it may be optimal for Bessie to visit no cities aside from city 1, in which case the answer would be zero.

### Input Format (file time.in):

- The first line contains three integers `N`, `M`, and `C`.
- The second line contains the `N` integers `m1, m2,...,mN`.

The next `M` lines each contain two space-separated integers `a` and `b (a != b)` denoting a one-way road from city `a` to city `b`.

### Output Format (file time.out):

A single line with the answer.

### Sample Input

```
3 3 1
0 10 20
1 2
2 3
3 1
```

### Sample Output

```
24
```

The optimal trip is `1 -> 2 -> 3 -> 1 -> 2 -> 3 -> 1`.  
Bessie makes `10 + 20 + 10 + 20 - 1 * 6^2 = 24` moonies in total.

### Hints:
- Use at least a 2-D DP array along with other variables to keep track of the state of the problem.


# Solutions:

https://github.com/Reddimus/USACO_notes/tree/main/Multi-D_Dynamic_Programming/Gold/P1_2020-Time_Is_Mooney

### Intuition:

### Steps:
1. 

### Time & Space complexity:
**Time:** `O(
**Space:** `O(

Where `n` is 

### C++ Code:
```cpp
#define MAX_DAYS 1000

#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("time.in", "r", stdin);
	// First line: n = num cities, m = num of one way roads, c = cost multiplier
	int n, m, c;
	cin >> n >> m >> c;

    // Second line: moonies[i] = moonies earned in city i
	int moonies[n];
	for (int cityIdx = 0; cityIdx < n; ++cityIdx)
		cin >> moonies[cityIdx];

	// For the next m lines create adjacency list for one way roads between cities
	// index = city, value(s) = cities it connects to
	vector<vector<int>> adj(n);
	for (int ln = 0; ln < m; ++ln) {
		int cityA, cityB;
		cin >> cityA >> cityB;
		adj[--cityA].push_back(--cityB);
	}

    // dp[day][city], where maxDays = 1000
	vector<vector<int>> dp(MAX_DAYS + 1, vector<int>(n, -1));
	dp[0][0] = 0;   // base case

	// For each day, stockpile moonies in each city visited using one way roads
	int maxMoony = 0;
	for (int day = 0; day < MAX_DAYS; ++day) {
		for (int city = 0; city < n; ++city) {
			// if dp[day][city] is -1, then there is no path to that city
			if (dp[day][city] != -1) {
				for (int nextCity : adj[city])
					dp[day + 1][nextCity] = max(dp[day + 1][nextCity], dp[day][city] + moonies[nextCity]);
			}
		}
		
		// We are only looking for maxMoony that loops back to city 1
		if (dp[day][0] != -1) {
			int tempMoony = dp[day][0] - (c * day * day);
			// If all potential maxMoony values have been calculated, break
			if (tempMoony < 0 && maxMoony != 0)
				break;
			maxMoony = max(maxMoony, tempMoony);
		}
	}

	// Write maxMoony generated from visiting cities to output file
	freopen("time.out", "w", stdout);
	cout << maxMoony << endl;
}
```

### Java Code:
```java
```
