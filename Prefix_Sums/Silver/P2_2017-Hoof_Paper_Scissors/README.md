# [USACO 2017 January Contest, Silver](http://www.usaco.org/index.php?page=jan17results)
## [Problem 2. Hoof, Paper, Scissors](http://www.usaco.org/index.php?page=viewproblem2&cpid=691)

You have probably heard of the game "Rock, Paper, Scissors". The cows like to play a similar game they call "Hoof, Paper, Scissors".  

The rules of "Hoof, Paper, Scissors" are simple. Two cows play against each-other. They both count to three and then each simultaneously makes a gesture that represents either a hoof, a piece of paper, or a pair of scissors. Hoof beats scissors (since a hoof can smash a pair of scissors), scissors beats paper (since scissors can cut paper), and paper beats hoof (since the hoof can get a papercut). For example, if the first cowmakes a "hoof" gesture and the second a "paper" gesture, then the second cow wins. Of course, it is also possible to tie, if both cows make the same gesture.  

Farmer John wants to play against his prize cow, Bessie, at N games of "Hoof, Paper, Scissors" `(1≤N≤100,000)`. Bessie, being an expert at the game, can predict each of FJ's gestures before he makes it. Unfortunately, Bessie, being a cow, is also very lazy. As a result, she tends to play the same gesture multiple times in a row. In fact, she is only willing to switch gestures at most once over the entire set of games. For example, she might play "hoof" for the first x games, then switch to "paper" for the remaining N-x games.  

Given the sequence of gestures FJ will be playing, please determine the maximum number of games that Bessie can win.

### Input Format (`hps.in`)
The first line contains N.  
The remaining N lines contain FJ's gestures, each either `H`, `P`, or `S`.  

### Output Format (`hps.out`)
Print the maximum number of games Bessie can win, considering she can only change gestures once.

### Sample Input
```
5
P
P
H
P
S
```

### Sample Output
```
4
```

# [Solutions](https://github.com/Reddimus/USACO_notes/tree/main/Prefix_Sums/Silver/P2_2017-Hoof_Paper_Scissors)

## Prefix sums approach

### Steps
1. Initialize prefix sum arrays for each gesture/action of size `N + 1` to account for the 0th index dummy value.
2. While reading input, populate the prefix sum arrays with the previous values and increment the current gesture/action based on the input read.
3. Using the prefix sums look at the subarrays `before (0 -> i)` and `after` the current iteration `(i -> n)` to determine the max wins possible.
4. Write the max wins to the output file.

### Time & Space complexity:
Time: `O(N)`
Space: `O(N)`

Where `N` is the number of games played or Fj's gestures/actions.

### Python Code:
```Python
# Gather list of fjs choices from input file
with open('hps.in', 'r') as f:
	# first line: n = amount of games played
	n = int(f.readline().strip())
	# Intialize prefix sum arrays with 0th index dummy value
	hooves = [0] * (n + 1)
	paper = [0] * (n + 1)
	scissors = [0] * (n + 1)
	# Populate the hooves, paper, and scissors prefix arrays (Notes down action wins for every iteration)
	for i in range(1, n + 1):
		# update prefix sums with prev vals
		hooves[i] += hooves[i - 1]
		paper[i] += paper[i - 1]
		scissors[i] += scissors[i - 1]
		# grab input & assign win to best choice
		action = f.readline().strip()
		if action == "H":
			paper[i] += 1
		elif action == "P":
			scissors[i] += 1
		elif action == "S":
			hooves[i] += 1
# Using prefix sums allows us to check all win combinations in O(n) time
max_wins = 0
for i in range(1, n + 1):
	# calculate max current wins
	before_wins = max(hooves[i], paper[i], scissors[i])
	# calculate max wins after current iteration to the end
	after_wins = max(hooves[n] - hooves[i], paper[n] - paper[i], scissors[n] - scissors[i])
	max_wins = max(max_wins, before_wins + after_wins)
# write max_wins answer to output file
print(max_wins, file=open("hps.out", "w"))
```

### C++ Code:
```cpp
#include <bits/stdc++.h>

int main(){
	ifstream in("hps.in");
	// first line: n = amount of games played
	int n;
	in >> n;
	// Intialize prefix sum arrays with 0th index dummy value
	vector<int> hooves(n+1);
	vector<int> paper(n+1);
	vector<int> scissors(n+1);
	// Populate the hooves, paper, and scissors prefix arrays (Notes down action wins for every iteration)
	for (int game = 1; game < n + 1; game++) {
		// update prefix sums with prev vals
		hooves[game] += hooves[game - 1];
		paper[game] += paper[game - 1];
		scissors[game] += scissors[game - 1];
		// grab input
		char fj_action;
		in >> fj_action;
		// assign win to best choice
		switch (fj_action) {
			case 'H':
				paper[game]++;
				break;
			case 'P':
				scissors[game]++;
				break;
			case 'S':
				hooves[game]++;
				break;
		}
	}
	// Using prefix sums allows us to check all win combinations in O(n) time
	int maxWins = 0;
	for (int i = 1; i < n + 1; i++) {
		// calculate max current wins
		int beforeWins = max(hooves[i], max(paper[i], scissors[i]));
		// calculate max wins after current iteration to the end
		int afterWins = max(hooves[n] - hooves[i], max(paper[n] - paper[i], scissors[n] - scissors[i]));
		maxWins = max(maxWins, beforeWins + afterWins);
	}
	// Write maxWins answer to output file
	ofstream pw("hps.out");
	pw << maxWins << "\n";
	pw.close();
	return 0;
}
```

### Java Code:
```java
import java.io.*;

public class HPS {
	public static void main(String[] args) throws Exception {
		BufferedReader in = new BufferedReader(new FileReader("hps.in"));
		// first line: n = amount of games played
		int n = Integer.parseInt(in.readLine());
		// Intialize prefix sum arrays with 0th index dummy value
		int[] hooves = new int[n + 1];
		int[] paper = new int [n + 1];
		int[] scissors = new int[n + 1];
		// Populate the hooves, paper, and scissors prefix arrays (Notes down action wins for every iteration)
		for (int idx = 1; idx <= n; idx++){
			// update prefix sums with prev vals
			hooves[idx] += hooves[idx - 1];
			paper[idx] += paper[idx - 1];
			scissors[idx] += scissors[idx - 1];
			// grab input & assign win to best choice
			char action = in.readLine().charAt(0);
			switch (action){
				case 'H':
					paper[idx]++;
					break;
				case 'P':
					scissors[idx]++;
					break;
				case 'S':
					hooves[idx]++;
					break;
			}
		}
		in.close();

		// Using prefix sums allows us to check all win combinations in O(n) time
		int maxWins = 0;
		for (int idx = 1; idx <= n; idx++) {
			// calculate max current wins
			int beforeWins = Math.max(hooves[idx], Math.max(paper[idx], scissors[idx]));
			// calculate max wins after current iteration to the end
			int afterWins = Math.max(hooves[n] - hooves[idx], Math.max(paper[n] - paper[idx], scissors[n] - scissors[idx]));
			maxWins = Math.max(maxWins, beforeWins + afterWins);
		}
		
		// write maxWins answer to output file
		PrintWriter out = new PrintWriter("hps.out");
		out.println(maxWins);
		out.close();
	}
}
```