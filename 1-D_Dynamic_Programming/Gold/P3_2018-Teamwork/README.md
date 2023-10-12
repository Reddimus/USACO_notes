# USACO 2018 December Contest, Gold
## Problem 3. Teamwork

http://www.usaco.org/index.php?page=viewproblem2&cpid=863

For his favorite holiday, Farmer John wants to send presents to his friends. Since he isn't very good at wrapping presents, he wants to enlist the help of his cows. As you might expect, cows are not much better at wrapping presents themselves, a lesson Farmer John is about to learn the hard way.

Farmer John's `N` cows `(1 <= N <= 10^4)` are all standing in a row, conveniently numbered `1...N` in order. Cow `i` has skill level `s_i` at wrapping presents. These skill levels might vary quite a bit, so FJ decides to combine his cows into teams. A team can consist of any consecutive set of up to `K` cows `(1 <= K <= 10^3)`, and no cow can be part of more than one team. Since cows learn from each other, the skill level of each cow on a team can be replaced by the skill level of the most-skilled cow on that team.

Please help FJ determine the highest possible sum of skill levels he can achieve by optimally forming teams.

### Input Format (file teamwork.in):

The first line of input contains `N` and `K`. The next N lines contain the skill levels of the N cows in the order in which they are standing. Each skill level is a positive integer at most 10^5.

### Output Format (file teamwork.out):

Please print the highest possible sum of skill levels FJ can achieve by grouping appropriate consecutive sets of cows into teams.

### Sample Input

```
7 3
1
15
7
9
2
5
10
```

### Sample Output

```
84
```

In this example, the optimal solution is to group the first three cows and the last three cows, leaving the middle cow on a team by itself (remember that it is fine to have teams of size less than `K`). This effectively boosts the skill levels of the 7 cows to 15, 15, 15, 9, 10, 10, 10, which sums to 84.

### Hints:
1. **Constraint Considerations**: Given the input size constraints, an O(N * K) algorithm is feasible. This means for each of the N cows, you can afford to calculate the most optimal sums of skill levels for each possible team size up to K.
  
2. **Dynamic Programming Strategy**: Focus on finding the best possible sum of skill levels for the first `i` cows as you iterate from `i=1` to `N`. The need to check up to `K` sizes for each cow arises when considering potential team sizes ranging from 1 to K. Utilize the `dp` array to keep track of the best sums and update it as you consider new cows and team configurations.

# 1-D Dynamic Programming w/ vector + Bottom-Up Solution:

https://github.com/Reddimus/USACO_notes/tree/main/1-D_Dynamic_Programming/Gold/P3_2018-Teamwork

### Intuition:
To maximize the overall skill level, we strategically group cows into teams of up to K consecutive members. The skill level of each team is determined by its most skilled cow. A dynamic programming approach helps us explore all possible team configurations efficiently. 

We utilize two indices: `rIdx` to scan through cows in the current window and `lIdx` to backtrack and explore various team sizes within that window. We continuously update a `dp` array that stores the highest skill sum achievable up to the current index. Specifically, the `dp` value at `rIdx` is calculated by considering all possible team formations ending at `rIdx`, and adding the maximum skill level in the current group to the maximum skill sum of the previous groups.

This way, by the time we reach the end, the `dp` array will contain the maximum skill level sum achievable for the entire herd.

### Steps:
1. Read `n` and `k` from the input file.
2. Store each cow's skill level.
3. Initialize `dp` array with size `n`.
4. Loop through cows with `rIdx`, and for each `rIdx`, backtrack with `lIdx` to find the optimal team.
  - Update the maximum skill within the current `lIdx` to `rIdx` window.
  - Update `dp[rIdx]` by comparing it with the sum of the maximum skill of the current window and `dp[lIdx - 1]`.

*Note: You can optimize the runtime if you build the skills array and dp array at the same time.*

### Time & Space Complexity:
- **Time:** O(n * k)
- **Space:** O(n)

Where `n` is the number of cows and `k` is the max size of a team.

### C++ Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("teamwork.in", "r", stdin);
	// Read First line: n = num of cows, k = max size of team(s)
	int n, k;
	cin >> n >> k;
	// For the next n lines store cow's skill
	int skills[n];
	for (int cow = 0; cow < n; ++cow)
		cin >> skills[cow];
	
	// Stockpile the sum of max skills by checking every possible team size
	vector<int> dp(n, -1);
	for (int rIdx = 0; rIdx < n; ++rIdx) {
		// Constantly update the max skill of the current team
		int maxSkill = skills[rIdx];
		for (int lIdx = rIdx; lIdx >= 0; --lIdx) {
			int currSize = rIdx - lIdx + 1;
			if (currSize > k)
				break;
			maxSkill = max(maxSkill, skills[lIdx]);
			// Check if there is a previous team
			if (lIdx == 0)
				dp[rIdx] = max(dp[rIdx], maxSkill * currSize);
			else
				dp[rIdx] = max(dp[rIdx], dp[lIdx - 1] + maxSkill * currSize);
		}
	}

	// Print stockpiled sum of max skills to output file
	freopen("teamwork.out", "w", stdout);
	cout << dp[n-1] << endl;
}
```

### Java Code:
```java
import java.io.*;
import java.util.*;

public class Teamwork {
	public static void main(String[] args) throws IOException {
		// Open input file
		BufferedReader in = new BufferedReader(new FileReader("teamwork.in"));
		// Read First line: n = num of cows, k = max size of team(s)
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());

		// Stockpile the sum of max skills by checking every possible team size
		int skills[] = new int[n];
		int dp[] = new int[n];
		for (int rIdx = 0; rIdx < n; ++rIdx) {
			// For the next n lines store cow's skill
			skills[rIdx] = Integer.parseInt(in.readLine());
			// Constantly update the max skill of the current team
			int maxSkill = skills[rIdx];
			for (int lIdx = rIdx; 0 <= lIdx; --lIdx) {
				int currSize = rIdx - lIdx + 1;
				if (currSize > k)
					break;
				maxSkill = Math.max(maxSkill, skills[lIdx]);
				// Check if there is a previous team
				if (lIdx > 0)
					dp[rIdx] = Math.max(dp[rIdx], dp[lIdx - 1] + maxSkill * currSize);
				else
					dp[rIdx] = Math.max(dp[rIdx], maxSkill * currSize);
			}
		}
		in.close();

		// Print stockpiled sum of max skills to output file
		PrintWriter out = new PrintWriter("teamwork.out");
		out.println(dp[n - 1]);
		out.close();
	}
}
```
