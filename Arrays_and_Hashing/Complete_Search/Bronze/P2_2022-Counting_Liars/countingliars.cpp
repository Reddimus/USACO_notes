#include <bits/stdc++.h>
#define N_MAX 1000

using namespace std;

int main() {
	// Read in 1st line: n = # of other cows
	int n;
	cin >> n;
	// For the next n lines, read in the cow's statement and position
	pair<char, int> cowInformation[N_MAX];
	for (int i = 0; i < n; i++)
		cin >> cowInformation[i].first >> cowInformation[i].second;

	// sort by position, then by statement
	sort(
		cowInformation, cowInformation + n,
		[](const pair<char, int>& a, const pair<char, int>& b) {
			return a.second != b.second ? a.second < b.second : a.first < b.first;
		}
	);

	// lying_left[i] stores the number of cows to the left of cow i
	// that must be lying given that Bessie is at the position of cow i.
	int lyingLeft[N_MAX] = {0};
	for (int i = 1; i < n; i++) {
		// Add up all the cows that are lying to the left of our position.
		lyingLeft[i] += lyingLeft[i - 1];

		/*
		* If the cow before says our position is to the left
		* but their position is strictly less than our position,
		* they're lying.
		*/
		if (cowInformation[i - 1].first == 'L')
			lyingLeft[i]++;
	}

	// lying_right stores the same thing, but does it so for the cows
	// to the *right* of i.
	int lyingRight[N_MAX] = {0};
	// Fill it up in much the same way.
	for (int i = n - 2; i >= 0; i--) {
		lyingRight[i] += lyingRight[i + 1];

		if (cowInformation[i + 1].first == 'G')
			lyingRight[i]++;
	}

	int minLiars = n;
	for (int i = 0; i < n; i++)
		minLiars = min(minLiars, lyingLeft[i] + lyingRight[i]);

	cout << minLiars << endl;
	return 0;
}
