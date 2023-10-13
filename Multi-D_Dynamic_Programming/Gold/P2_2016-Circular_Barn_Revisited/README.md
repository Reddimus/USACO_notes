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
- 

# Solutions:

https://github.com/Reddimus/USACO_notes/tree/main/Multi-D_Dynamic_Programming/Gold/P1_2020-Time_Is_Mooney

### Intuition:


### Steps:
1. 

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
	// For the next n lines, read the number of cows in each room (r_i)
	deque<int> rooms(n);
	for (int &r : rooms)
		cin >> r;
	
	ll minDist = INT64_MAX;
	// Iterate through all possible starting rooms
	for (int startPos = 0; startPos < n; ++startPos) {
		vector<vector<ll>> dp(k + 1, vector<ll>(n + 1, INT64_MAX));
		// With no door used, the distance is 0 if there is no room filled
		dp[0][n] = 0;
		// Iterate through number of doors used
		for (int usedDoor = 1; usedDoor <= k; ++usedDoor) {
			// Iterate through all possible positions to place this new door
			for (int newDoorPos = 0; newDoorPos < n; ++newDoorPos) {
				if (usedDoor >= k && newDoorPos >= 1)
					break;
				// partialDist stores the sum of distance to fill rooms [newDoorPos, lastDoorPos - 1]
				ll partialDist = 0;
				// Iterate through all possible positions to place the last door
				// Find the minimum distance if we use this placement with our new door
				for (int lastDoorPos = newDoorPos + 1; lastDoorPos <= n; ++lastDoorPos) {
					// Add the amount of distance needed to fill the new room at lastDoorPos - 1
					partialDist += rooms[lastDoorPos - 1] * (lastDoorPos - newDoorPos - 1);
					ll newDist = dp[usedDoor - 1][lastDoorPos];
					if (newDist < INT64_MAX)
						newDist += partialDist;
					dp[usedDoor][newDoorPos] = min(dp[usedDoor][newDoorPos], newDist);
				}

			}
		}
		// Update the best answer using the current dp answer
		minDist = min(minDist, dp[k][0]);
		// Put the first room to the end of the deque so that the first door would be placed at the second room
		int firstRoom = rooms.front();
		rooms.pop_front();
		rooms.push_back(firstRoom);
	}

	freopen("cbarn2.out", "w", stdout);
	cout << minDist << endl;
}
```

### Java Code:
```java
```
