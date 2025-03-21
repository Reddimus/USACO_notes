#include <bits/stdc++.h>
#define N_MAX 100

using namespace std;

int main() {
    freopen("cownomics.in", "r", stdin);
    // First line: N = cows with and without spots, M = length of genome
    int n, m;
    cin >> n >> m;
    // Each genome and the individual characters in each genome
    // Use [N_MAX] if variable-length arrays aren't supported
    string spottedCows[n], plainCows[n];
    for (int i = 0; i < n; i++)
        cin >> spottedCows[i];
    for (int i = 0; i < n; i++)
        cin >> plainCows[i];

    int possPositions = 0;
    for (int charIdx = 0; charIdx < m; charIdx++) {
        bitset<26> seen;
        for (int cow1 = 0; cow1 < n; cow1++) 
            seen[spottedCows[cow1][charIdx] - 'A'] = true;

        bool duplicate = false;
        for (int cow2 = 0; cow2 < n; cow2++) {
            if (seen[plainCows[cow2][charIdx] - 'A']) {
                duplicate = true;
                break;
            }
        }

        if (!duplicate)
            possPositions++;
    }

    freopen("cownomics.out", "w", stdout);
    cout << possPositions << endl;
    return 0;
}