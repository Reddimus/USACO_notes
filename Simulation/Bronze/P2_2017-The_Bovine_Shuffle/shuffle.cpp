#include <bits/stdc++.h>
#define COW_MAX 101
#define SHUFFLE_NUM 3

using namespace std;

int main() {
	freopen("shuffle.in", "r", stdin);
	// Read in first line: n = # of cows
	int n;
	cin >> n;
	// Read in second line: shuffles for each cow
	int shuffles[COW_MAX];
	for (int cow = 1; cow <= n; cow++)
		cin >> shuffles[cow];
	// Read in third line: initial cow ids
	vector<int> ids(n + 1);
	for (int cow = 1; cow <= n; cow++)
		cin >> ids[cow];

	for (int i = 0; i < SHUFFLE_NUM; i++) {
		vector<int> pastOrder(n + 1);
		for (int cow = 1; cow <= n; cow++)
			pastOrder[cow] = ids[shuffles[cow]];

		ids = pastOrder;
	}

	freopen("shuffle.out", "w", stdout);
	for (int cow = 1; cow <= n; cow++)
		cout << ids[cow] << endl;
	return 0;
}

/*
1 3 4 5 2

Normal shuffle:

1234567 2222222 3333333 4444444 5555555

1234567 5555555 2222222 3333333 4444444

1234567 4444444 5555555 2222222 3333333

1234567 3333333 4444444 5555555 2222222

Reverse shuffle:

1234567 2222222 3333333 4444444 5555555

1234567 3333333 4444444 5555555 2222222

1234567 4444444 5555555 2222222 3333333

1234567 5555555 2222222 3333333 4444444
*/