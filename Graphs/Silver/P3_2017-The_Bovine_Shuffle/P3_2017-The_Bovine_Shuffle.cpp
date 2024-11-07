#include <bits/stdc++.h>
#define MAX_COWS 100001

using namespace std;

int main() {
    freopen("shuffle.in", "r", stdin);
    // Read first line: n = number of cows
    int n;
    cin >> n;

    int cowShuffles[MAX_COWS];
    int afterShuffleCount[MAX_COWS] = {0}; // Initialize to zero

    for (int i = 1; i <= n; ++i) {
        cin >> cowShuffles[i];
        afterShuffleCount[cowShuffles[i]]++;
    }

    int constFilledPositions = n;
    queue<int> q;

    // Calculate positions that are empty after one shuffle
    for (int i = 1; i <= n; ++i) {
        if (afterShuffleCount[i] != 0)
            continue;

        q.push(i); // queue positions with 0 cows
        constFilledPositions--;
    }

    while (!q.empty()) {
        int pos = q.front();
        q.pop();

        if (--afterShuffleCount[cowShuffles[pos]] != 0)
            continue;

		// Branch out to find more empty shuffle counts
        q.push(cowShuffles[pos]);
        constFilledPositions--;
    }

    freopen("shuffle.out", "w", stdout);
    cout << constFilledPositions << endl;
}
