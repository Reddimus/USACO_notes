#include <bits/stdc++.h>
#define N_MAX 101

using namespace std;

struct Board {
	string sideA, sideB;
};

vector<int> getCharCount(const string& side) {
	vector<int> charCount(26, 0);
	for (const char c : side)
		charCount[c - 'a']++;
	return charCount;
}

int main() {
	freopen("blocks.in", "r", stdin);
	int n;
	cin >> n;
	int maxBlocks[26] = {0};
	for (int ln = 0; ln < n; ln++) {
		string sideA, sideB;
		cin >> sideA >> sideB;
		vector<int> charCountA = getCharCount(sideA), charCountB = getCharCount(sideB);
		for (int ci = 0; ci < 26; ci++)
			maxBlocks[ci] += max(charCountA[ci], charCountB[ci]);
	}
	
	freopen("blocks.out", "w", stdout);
	for (int ci = 0; ci < 26; ci++)
		cout << maxBlocks[ci] << endl;
	return 0;
}
