# USACO 2015 December Contest, Gold
## Problem 2. Fruit Feast

http://www.usaco.org/index.php?page=viewproblem2&cpid=574

Bessie has broken into Farmer John's house again! She has discovered a pile of lemons and a pile of oranges in the kitchen (effectively an unlimited number of each), and she is determined to eat as much as possible.

Bessie has a maximum fullness of `T` `(1 <= T <= 5,000,000)`. Eating an orange increases her fullness by `A`, and eating a lemon increases her fullness by `B` `(1 <= A, B <= T)`. Additionally, if she wants, Bessie can drink water at most one time, which will instantly decrease her fullness by half (and will round down).

Help Bessie determine the maximum fullness she can achieve!

### Input Format (file feast.in):

The first (and only) line has three integers `T`, `A`, and `B`.

### Output Format (file feast.out):

A single integer, representing the maximum fullness Bessie can achieve.

### Sample Input
```
8 5 6
```


### Sample Output
```
8
```

### Hints:
- Use bit manipulation to keep track of which states you have already visited.
- 

# Solutions:

https://github.com/Reddimus/USACO_notes/tree/main/Multi-D_Dynamic_Programming/Gold/P2_2015-Fruit_Feast

### Intuition:

### Steps:
1. 

### Time & Space complexity:
**Time:** `O(t)`
**Space:** `O(t)`

Where `T` is the maximum given fullness, `A` is the fullness gained from eating an orange, and `B` is the fullness gained from eating a lemon.

### C++ Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("feast.in", "r", stdin);
	int t, a, b;
	cin >> t >> a >> b;

    // dp[drinkedWater?][fullness], where 1 = true, 0 = false
	vector<vector<int>> dp(2, vector<int>(t+1, 0));	// allocated on the heap
	dp[0][0] = true;	// base case 0 fullness
	for (int idx = 0; idx <= t; ++idx) {
        // Find individual fullness without drinking water
		if (idx - a >= 0)
			dp[0][idx] |= dp[0][idx-a];
		if (idx - b >= 0)
			dp[0][idx] |= dp[0][idx-b];
        // Find fullness after drinking water
		dp[1][idx/2] |= dp[0][idx];
	}

    // Using fullness after drinking water find new fullness
	for (int idx = 0; idx <= t; ++idx) {
		if (idx - a >= 0)
			dp[1][idx] |= dp[1][idx-a];
		if (idx - b >= 0)
			dp[1][idx] |= dp[1][idx-b];
	}

    // Find the maximum fullness
	freopen("feast.out", "w", stdout);
	for (int idx = t; idx >= 0; --idx) {
		if (dp[1][idx]) {
			cout << idx << endl;
			break;
		}
	}

	return 0;
}
```

### Java Code:
```java
```
