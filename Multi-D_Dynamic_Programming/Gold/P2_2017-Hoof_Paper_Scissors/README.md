# USACO 2017 January Contest, Gold

## Problem 2. Hoof, Paper, Scissors

http://www.usaco.org/index.php?page=viewproblem2&cpid=694

You have probably heard of the game "Rock, Paper, Scissors". The cows like to play a similar game they call "Hoof, Paper, Scissors".

The rules of "Hoof, Paper, Scissors" are simple. Two cows play against each-other. They both count to three and then each simultaneously makes a gesture that represents either a hoof, a piece of paper, or a pair of scissors. Hoof beats scissors (since a hoof can smash a pair of scissors), scissors beats paper (since scissors can cut paper), and paper beats hoof (since the hoof can get a papercut). For example, if the first cow makes a "hoof" gesture and the second a "paper" gesture, then the second cow wins. Of course, it is also possible to tie, if both cows make the same gesture.

Farmer John wants to play against his prize cow, Bessie, at `N` games of "Hoof, Paper, Scissors" `(1 ≤ N ≤ 100,000)`. Bessie, being an expert at the game, can predict each of FJ's gestures before he makes it. Unfortunately, Bessie, being a cow, is also very lazy. As a result, she tends to play the same gesture multiple times in a row. In fact, she is only willing to switch gestures at most `K` times over the entire set of games `(0 ≤ K ≤ 20)`. For example, if `K = 2`, she might play "hoof" for the first few games, then switch to "paper" for a while, then finish the remaining games playing "hoof".

Given the sequence of gestures FJ will be playing, please determine the maximum number of games that Bessie can win.

### INPUT FORMAT (file hps.in):

The first line of the input file contains `N` and `K`.  

The remaining `N` lines contains FJ's gestures, each either H, P, or S.

### OUTPUT FORMAT (file hps.out):

Print the maximum number of games Bessie can win, given that she can only change gestures at most K times.

**SAMPLE INPUT:**  
```
5 1
P
P
H
P
S
```

**SAMPLE OUTPUT:**  
```
4
```

### Hints:
- Use a 3-Dimensional DP array to store the maximum number of wins for each state of the game (game number, number of switches, and current gesture) and then find the maximum number of wins for the last game.

# Solutions:

https://github.com/Reddimus/USACO_notes/tree/main/Multi-D_Dynamic_Programming/Gold/P2_2017-Hoof_Paper_Scissors

### Intuition:
- **Problem Essence**: The problem is a variant of Rock, Paper, Scissors, but with Hoof, Paper, Scissors (H, P, S). The aim is to find the maximum number of games you can win given a sequence of games and a limited number of gesture switches.
  
- **States and Transitions**: Use Dynamic Programming (DP) to navigate through different "states," each defined by:
    - The current game round
    - The number of switches made so far
    - The current gesture
  
- **Local and Global Decisions**: In each state, two key decisions are made:
    - Local: If the gesture for the current round will lead to a win, increment the score.
    - Global: Update the best score possible for future states, considering if you switch gestures or not.
  
- **Optimality**: Use the `max()` function to ensure that each DP state holds the best score you could have by that point, considering all past games and switches.
### Steps:
1. **Input**: Read the number of games `n` and the number of allowed switches `k`. Then read `n` gestures.
  
2. **DP Initialization**: Initialize a 3D DP array `dp[n][k+1][3]` or `dp[n+1][k+2][3]` to store the maximum number of wins for each state:
    - `dp[nIdx][kIdx][g]` = the maximum number of wins for the current game round `nIdx`, number of switches `kIdx`, and current gesture `g
  
3. **Looping Structure**: Implement a triple nested loop to iterate over:
    - `nIdx`: Current game round (0 to `n-1`)
    - `kIdx`: Number of switches made so far (0 to `k`)
    - `g`: Current gesture (H, P, S)
  
4. **State Transitions**:
    - If the current gesture wins this round, increment `dp[nIdx][kIdx][g]`.
    - Update the DP array for the next game round and number of switches, using `max()` to retain the best score.
  
5. **Result Extraction**: The maximum possible wins will be the maximum value among `dp[n-1][k][0]`, `dp[n-1][k][1]`, and `dp[n-1][k][2]`.

### Time & Space complexity:
**Time:** `O(n*k*3)` = `O(n*k)`  
**Space:** `O(n*k + n)` = `O(n*k)`

Where `n` is the number of games and `k` is the number of times Bessie can change gestures.

### C++ Code:
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("hps.in", "r", stdin);
	// Read first line: n = num of gestures, k = num of gesture switches
	int n, k;
	cin >> n >> k;
	// For the next n lines store gestures into a list
	int gestures[n];
	for (int idx = 0; idx < n; idx++) {
		char gesture;
		cin >> gesture;
		switch (gesture) {
			case 'H':
				gestures[idx] = 0;
				break;
			case 'P':
				gestures[idx] = 1;
				break;
			case 'S':
				gestures[idx] = 2;
				break;
		}
	}


	// Initialize 3D dp arr to store the maximum number of wins for each state 
	// dp[n][k+1][3] = dp[nIdx][kIdx][g]
	int dp[n][k+1][3] = {};
	for (int nIdx = 0; nIdx < n; nIdx++) {
		for (int kIdx = 0; kIdx <= k; kIdx++) {
			for (int g = 0; g < 3; g++) {
				// Increment score if current gesture wins in this round
				if (g == gestures[nIdx])
					dp[nIdx][kIdx][g]++;
				
				if (nIdx+1 < n) {
					if (kIdx+1 <= k) {
						// Update future state if a switch is made
						dp[nIdx+1][kIdx+1][0] = max(dp[nIdx+1][kIdx+1][0], dp[nIdx][kIdx][g]);
						dp[nIdx+1][kIdx+1][1] = max(dp[nIdx+1][kIdx+1][1], dp[nIdx][kIdx][g]);
						dp[nIdx+1][kIdx+1][2] = max(dp[nIdx+1][kIdx+1][2], dp[nIdx][kIdx][g]);
					}
					// Update future state without a switch
					dp[nIdx+1][kIdx][g] = max(dp[nIdx+1][kIdx][g], dp[nIdx][kIdx][g]);
				}
			}
		}
	}

	// Write the accumlated max wins of the last game to the output file
	int maxWins = max({dp[n-1][k][0], dp[n-1][k][1], dp[n-1][k][2]});
	freopen("hps.out", "w", stdout);
	cout << maxWins << endl;
}
```

### Java Code:
```java
import java.io.*;
import java.util.*;

public class HPS {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("hps.in"));
		// Read first line: n = num of gestures, k = num of gesture switches
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		// For the next n lines store gestures into a list
		int[] gestures = new int[n];
		for (int idx = 0; idx < n; ++idx) {
			char gesture = in.readLine().charAt(0);
			if (gesture == 'H') {
				gestures[idx] = 0;
			} else if (gesture == 'P') {
				gestures[idx] = 1;
			} else {
				gestures[idx] = 2;
			}
		}
		in.close();
		
		// Initialize 3D dp arr to store the maximum number of wins for each state 
		// dp[n][k+1][3] = dp[nIdx][kIdx][g]
		int[][][] dp = new int[n][k + 1][3];
		for (int nIdx = 0; nIdx < n; ++nIdx) {
			for (int kIdx = 0; kIdx <= k; ++kIdx) {
				for (int g = 0; g < 3; ++g) {
					// Increment score if current gesture wins in this round
					if (g == gestures[nIdx]) {
						++dp[nIdx][kIdx][g];
					}
					
					if (nIdx + 1 < n) {
						if (kIdx + 1 <= k) {
							// Update future state if a switch is made
							dp[nIdx + 1][kIdx + 1][0] = Math.max(dp[nIdx + 1][kIdx + 1][0], dp[nIdx][kIdx][g]);
							dp[nIdx + 1][kIdx + 1][1] = Math.max(dp[nIdx + 1][kIdx + 1][1], dp[nIdx][kIdx][g]);
							dp[nIdx + 1][kIdx + 1][2] = Math.max(dp[nIdx + 1][kIdx + 1][2], dp[nIdx][kIdx][g]);
						}
						// Update future state without a switch
						dp[nIdx + 1][kIdx][g] = Math.max(dp[nIdx + 1][kIdx][g], dp[nIdx][kIdx][g]);
					}
				}
			}
		}
		
		// Write the accumlated max wins of the last game to the output file
		int maxWins = Math.max(dp[n - 1][k][0], Math.max(dp[n - 1][k][1], dp[n - 1][k][2]));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("hps.out")));
		out.println(maxWins);
		out.close();
	}
}

```
