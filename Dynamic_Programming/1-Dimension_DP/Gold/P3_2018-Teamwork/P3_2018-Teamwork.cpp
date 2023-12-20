// 1-D Dynamic Programming w/ vector + Bottom-Up Approach
// T: O(n*k), M: O(n)
// Where n is the number of cows and k is the max size of team(s)

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
	/*
	cout << "skills: " << endl;
	for (int i = 0; i < n; ++i)
		cout << skills[i] << " ";
	cout << endl << endl;
	*/
	
	// cout << "dp: " << endl;
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
			// If there was a previous team
			if (lIdx == 0)
				dp[rIdx] = max(dp[rIdx], maxSkill * currSize);
			else
				dp[rIdx] = max(dp[rIdx], dp[lIdx - 1] + maxSkill * currSize);
			
			/*
			cout << "lIdx: " << lIdx << " rIdx: " << rIdx << " currSize: " << currSize << " maxSkill: " << maxSkill << " dp[rIdx]: " << dp[rIdx] << endl;
			cout << "[ ";
			for (int i = 0; i < n; ++i)
				cout << dp[i] << " ";
			cout << "]" << endl << endl;
			*/
		}
	}

	// Print stockpiled sum of max skills to output file
	freopen("teamwork.out", "w", stdout);
	cout << dp[n-1] << endl;
}