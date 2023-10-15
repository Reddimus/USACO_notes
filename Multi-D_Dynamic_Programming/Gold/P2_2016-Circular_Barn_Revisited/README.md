# USACO 2016 February Contest, Gold
## Problem 2. Circular Barn Revisited

http://www.usaco.org/current/index.php?page=viewproblem2&cpid=622

After the last debacle involving Farmer John's circular barn, one would think he had learned his lesson about non-traditional architecture. However, he thinks he can still make his circular barn function properly by allowing multiple cows into each room. To recap, the barn consists of a ring of `n` rooms, numbered clockwise from `1...n` around the perimeter of the barn `(3 <= n <= 100)`. Each room has doors to its two neighboring rooms, and also a door opening to the exterior of the barn.

Farmer John wants exactly `ri` cows to end up in room `i` `(1 <= ri <= 1,000,000)`. To herd the cows into the barn in an orderly fashion, he plans to unlock `k` exterior doors `(1 <= k <= 7)`, allowing the cows to enter through only those doors. Each cow then walks clockwise through the rooms until she reaches a suitable destination. Farmer John wants to unlock the exterior doors that will cause his cows to collectively walk a minimum total amount of distance after entering the barn.

### Input Format (file cbarn2.in):

The first line of input contains `n` and `k`. Each of the remaining `n` lines contain `r1...rn`.

### Output Format (file cbarn2.out):

Please write out the minimum amount of distance the cows need to travel.

### Sample Input
```
6 2
2
5
4
2
6
2
```

### Sample Output
```
14
```

Farmer John can unlock doors 2 and 5. 11 cows enter at door 2 and walk a total distance of 8 to get to rooms 2, 3, and 4. 10 cows enter at door 5 and walk a total distance of 6 to get to rooms 5, 6 and 1.

### Hints:
- Utilize a deque to efficiently manage the circular barn.
- Initialize all DP values to infinity, except for the base case.
- Make sure to optimize your loops to keep the time complexity within acceptable bounds, specifically O(k * n^3).

# Solutions:

https://github.com/Reddimus/USACO_notes/tree/main/Multi-D_Dynamic_Programming/Gold/P1_2020-Time_Is_Mooney

#### Intuition

The problem might initially seem daunting due to the circular arrangement of the barn. However, the key insight is to temporarily disregard the circular nature by fixing the position of the first door then rotating the positions of the barn later. This transforms the barn into a linear array of rooms, making it more manageable. With a fixed starting point, you can focus on unlocking up to k doors to minimize the distance cows need to travel. Dynamic Programming (DP) becomes a viable strategy here, using a DP table to capture the minimum distance based on the number of unlocked doors and their positions. The base case starts with no unlocked doors, meaning no distance traveled, and iteratively builds upon this to find the optimal solution. After each DP calculation, rotate the fixed starting position to the end of the barn to explore different starting positions calulations.


### Steps
1. **Initialization**: 
    - Read n, the number of rooms, and k, the number of unlocked exterior doors.
    - Use a deque to store the number of cows in each room.
  
2. **Dynamic Programming**:
    - Utilize a DP table, `dp[unlockedDoors][newDoorPos]`, to record the minimum distance for various configurations of unlocked doors and their positions.
    - Set `dp[0][n] = 0` as the base case. This represents zero distance traveled with zero doors unlocked.
    - Populate the DP table according to the given transition formula.
  
3. **Rotation**: 
    - After each DP calculation, rotate the deque to explore different starting positions for the rooms.
  
4. **Answer**: 
    - The final answer is the minimum value of dp[k][0] after considering all possible starting room configurations.

### Time & Space complexity:
**Time:** `O(n^3 * k)`  
**Space:** `O(k * n)`  

Where `n` is the number of rooms, `k` is the number of doors to unlock

### C++ Code:
```cpp
#include <bits/stdc++.h>

#define ll long long

using namespace std;

int main() {
	freopen("cbarn2.in", "r", stdin);
	// Read first line: n = rooms, k = unlocked exterior doors
	int n, k;
	cin >> n >> k;
	// For the next n lines, read in the desired number of cows in each room (r_i)
	deque<int> rooms(n);
	for (int &r : rooms)
		cin >> r;

	ll minDist = INT64_MAX;
	// Rotate through all the starting position of the rooms for each dp table
	for (int startPos = 0; startPos < n; ++startPos) {
		vector<vector<ll>> dp(k + 1, vector<ll>(n + 1, INT64_MAX));
		dp[0][n] = 0;   // 0 doors unlocked base case
		// Iterate through all possible number of doors unlocked
		for (int unlockedDoors = 1; unlockedDoors <= k; ++unlockedDoors) {
			// Iterate through all possible positions to place this new door
			for (int newDoorPos = 0; newDoorPos < n; ++newDoorPos) {
				if (unlockedDoors >= k && newDoorPos >= 1)  // If dp[k][0] is done calculating
					break;
				// Calculate distance for rooms between new and last door
				ll partialDist = 0;
				// Loop through last door positions
				for (int lastDoorPos = newDoorPos + 1; lastDoorPos <= n; ++lastDoorPos) {
					// Add distance needed to fill the new room at lastDoorPos - 1
					partialDist += rooms[lastDoorPos - 1] * (lastDoorPos - newDoorPos - 1);
					ll newDist = dp[unlockedDoors - 1][lastDoorPos];
					if (newDist < INT64_MAX)
						newDist += partialDist;
					dp[unlockedDoors][newDoorPos] = min(dp[unlockedDoors][newDoorPos], newDist);
				}
			}
		}
		// Update the best answer using the current dp with current starting position
		minDist = min(minDist, dp[k][0]);
		// Rotate first room to end
		rooms.push_back(rooms.front());
		rooms.pop_front();
	}

	// Write the minDist accross all starting positions, with all possible doors unlocked
	freopen("cbarn2.out", "w", stdout);
	cout << minDist << endl;
}
```

### Java Code:
```java
import java.io.*;
import java.util.*;

public class CircularBarn {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("cbarn2.in"));
		/// Read first line: n = rooms, k = unlocked exterior doors
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		// For the next n lines, read in the number of desired cows in each room (r_i)
		Deque<Integer> rooms = new ArrayDeque<Integer>();
		for (int i = 0; i < n; ++i)
			rooms.add(Integer.parseInt(in.readLine()));
		in.close();

		long minDist = Long.MAX_VALUE;
		// Rotate through all the starting position of the rooms for each dp table
		for (int startPos = 0; startPos < n; ++startPos) {
			long[][] dp = new long[k+1][n+1];
			for (long[] row : dp)
				Arrays.fill(row, Long.MAX_VALUE);
			dp[0][n] = 0;	// 0 doors unlocked base case

			Integer[] roomsArr = rooms.toArray(new Integer[0]);	// Make rotated rooms callable by index
			// Iterate through number of doors used
			for (int unlockedDoors = 1; unlockedDoors <= k; ++unlockedDoors) {
				// Iterate through all possible number of doors unlocked
				for (int newDoorPos = 0; newDoorPos < n; ++newDoorPos) {
					if (unlockedDoors >= k && newDoorPos >= 1)
						break;
					// Calculate distance for rooms between new and last door
					long partialDist = 0;
					// Loop through last door positions
					for (int lastDoorPos = newDoorPos + 1; lastDoorPos <= n; ++lastDoorPos) {
						// Add distance needed to fill the new room at lastDoorPos - 1
						partialDist += roomsArr[lastDoorPos - 1] * (lastDoorPos - newDoorPos - 1);
						long newDist = dp[unlockedDoors - 1][lastDoorPos];
						if (newDist < Long.MAX_VALUE)
							newDist += partialDist;
						dp[unlockedDoors][newDoorPos] = Math.min(dp[unlockedDoors][newDoorPos], newDist);
					}
				}
			}
			// Update the best answer using the current dp with current starting position
			minDist = Math.min(minDist, dp[k][0]);
			// Rotate first room to end
			rooms.add(rooms.removeFirst());
		}

		// Write the minDist accross all starting positions, with all possible doors unlocked
		PrintWriter out = new PrintWriter("cbarn2.out");
		out.println(minDist);
		out.close();
	}
}
```
