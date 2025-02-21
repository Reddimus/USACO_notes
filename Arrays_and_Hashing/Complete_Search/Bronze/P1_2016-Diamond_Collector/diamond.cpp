#include <bits/stdc++.h>
#define N_MAX 1001

using namespace std;

// Sliding window approach
// T: O(n log n), S: O(1) if not counting the input array
int main() {
    freopen("diamond.in", "r", stdin);
    // Read in 1st line: N = # of diamonds, K = max difference in size
    int N, K;
    cin >> N >> K;
    // For the next N lines, read in the sizes of the diamonds
    int diamonds[N_MAX];
    for (int i = 0; i < N; i++)
        cin >> diamonds[i];

    // Sort the array of diamond sizes
    sort(diamonds, diamonds + N);

    int most = 0;
    int start = 0;

    // Sliding window approach; Expand the window from the right
    for (int end = 0; end < N; end++) {
        while (diamonds[end] - diamonds[start] > K)
            start++; // Shrink the window from the left
        // Update the maximum number of fittable diamonds
        most = max(most, end - start + 1);
    }

    freopen("diamond.out", "w", stdout);
    cout << most << endl;
    return 0;
}
