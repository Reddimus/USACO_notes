// #include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Prefix sums approach
// T & M: O(n), where n is size of Fjs actions
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