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
- What **combinations** of orange(s), lemon(s), and water can you use to achieve the maximum fullness?
	* You **cannot** eat another fruit that surpasses the maximum fullness `T`.
- Use Dynamic programming with bit manipulation to keep track of which states you have already visited.
- Think of a better test case than the one given in the sample input.

# Solutions:

https://github.com/Reddimus/USACO_notes/tree/main/Multi-D_Dynamic_Programming/Gold/P2_2015-Fruit_Feast

### Intuition:
The problem is akin to a specialized knapsack problem where Bessie aims to maximize her fullness without exceeding a given limit. A 2D dynamic programming array, `dp`, serves a dual purpose: `dp[0][x]` tracks maximum fullness without water, while `dp[1][x]` does so after drinking water. Bit manipulation flags visited states to avoid redundancy. Starting from a prior fullness level, we iteratively update `dp` based on the additional fullness from consuming orange(s) or lemon(s), and by halving the fullness after drinking water. The highest fullness level marked 'true' in the final state represents Bessie's maximum achievable fullness.

### Steps:
1. Read single line from input file
	* `t` = max fullness, `a` = orange fullness, `b` = lemon fullness
2. Initialize 2D dynamic programming array, `dp`, with `dp[0][0] = true` as the base case for 0 fullness
3. Iterate through `dp` columns/fullness once mainly focusing on `dp[0]` / bessie's fullness without water.
	* Find fullness of orange(s) and lemon(s) without water referencing prior fullness levels with `dp[0][idx] |= dp[0][idx-fruits]`
		* `dp[0][idx] |= dp[0][idx-a]` if `0 <= idx - a`
		* `dp[0][idx] |= dp[0][idx-b]` if `0 <= idx - b`
	* Find fullness after drinking water referencing prior fullness levels with `dp[1][idx/2] |= dp[0][idx]`
4. Iterate through `dp` columns/fullness once mainly focusing on `dp[1]` / bessie's fullness after drinking water.
	* Find fullness of orange(s) and lemon(s) after drinking water referencing prior fullness levels with `dp[1][idx] |= dp[1][idx-fruits]`
		* `dp[1][idx] |= dp[1][idx-a]` if `0 <= idx - a`
		* `dp[1][idx] |= dp[1][idx-b]` if `0 <= idx - b`
4. Find max fullness/last true fullness value

### Time & Space complexity:
**Time:** `O(t)`  
**Space:** `O(t)`  

Where `T` is the maximum given fullness, `A` is the fullness gained from eating an orange, and `B` is the fullness gained from eating a lemon.

C++ Notes: 
1. `bool dp[2][TMAX+1]` allocated on the stack will cause a stack overflow error. Use `vector<vector<int>> dp(2, vector<int>(t+1, 0))` instead or initialize `dp` as a global variable allocated on the heap.
2. `vector<vector<bool>> dp(2, vector<bool>(t+1, false))` is optomized for space and doesn't actually store `bool` objects, but rather bits. This leads to issues when you try to take a reference to an element, as the reference is actually a proxy object, not a regular bool&. This is why operators like |= don't behave as you'd expect.
3. *Heap memory is slower than Stack memory, however Heap memory is much larger than Stack memory*. If you need a large amount of memory, you should use the heap. If you need a small amount of memory, you should use the Stack. If you need a large amount of memory, but you don't know how much you will need at compile time, you should use the heap.

### C++ Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("feast.in", "r", stdin);
	// Read single line from input file
	// t = max fullness, a = orange fullness, b = lemon fullness
	int t, a, b;
	cin >> t >> a >> b;

    // dp[drinkedWater?][fullness], where 1 = true, 0 = false
	vector<vector<int>> dp(2, vector<int>(t+1, 0));	// allocated on the heap
	dp[0][0] = true;	// base case 0 fullness
	for (int idx = 0; idx <= t; ++idx) {
        // Find fullness of orange(s) and lemon(s) without water
		if (idx - a >= 0)
			dp[0][idx] |= dp[0][idx-a];
		if (idx - b >= 0)
			dp[0][idx] |= dp[0][idx-b];
        // Find fullness after drinking water
		dp[1][idx/2] |= dp[0][idx];
	}

    // Using fullness after drinking water find new fullness'
	for (int idx = 0; idx <= t; ++idx) {
		if (idx - a >= 0)
			dp[1][idx] |= dp[1][idx-a];
		if (idx - b >= 0)
			dp[1][idx] |= dp[1][idx-b];
	}

    // Find max fullness/last true fullness value
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
import java.util.*;
import java.io.*;

public class FruitFeast {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("feast.in"));
		// Read single line from input file
		// t = max fullness, a = orange fullness, b = lemon fullness
		StringTokenizer st = new StringTokenizer(in.readLine());
		int t = Integer.parseInt(st.nextToken());
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		in.close();

		// dp[drinkedWater?][fullness], where 1 = true, 0 = false
		boolean[][] dp = new boolean[2][t+1];
		dp[0][0] = true;	// base case 0 fullness
		for (int idx = 0; idx <= t; ++idx) {
			// Find fullness of orange(s) and lemon(s) without water
			if (0 <= idx - a)
				dp[0][idx] |= dp[0][idx-a];
			if (0 <= idx - b)
				dp[0][idx] |= dp[0][idx-b];
			// Find fullness after drinking water
			dp[1][idx/2] |= dp[0][idx];
		}

		// Using fullness after drinking water find new fullness
		// Find max fullness/last true fullness value
		int maxFullness = 0;
		for (int idx = 0; idx <= t; ++idx) {
			if (0 <= idx - a)
				dp[1][idx] |= dp[1][idx-a];
			if (0 <= idx - b)
				dp[1][idx] |= dp[1][idx-b];
			if (dp[1][idx])
				maxFullness = idx;
		}
		
		PrintWriter out = new PrintWriter("feast.out");
		out.println(maxFullness);
		out.close();
	}
}
```
