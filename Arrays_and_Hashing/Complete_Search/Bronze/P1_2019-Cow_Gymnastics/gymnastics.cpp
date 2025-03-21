#include <bits/stdc++.h>
#define K_MAX 10
#define N_MAX 21

using namespace std;

int main() {
    freopen("gymnastics.in", "r", stdin);
    // Read in 1st line: K = practice sessions, N = # of cows
    int k, n;
    cin >> k >> n;
    // For the next K lines, read in the cows' rankings
    int dayCowRankings[k][n + 1];   // Use [K_MAX][N_MAX] if variable-length arrays aren't supported
    for (int day = 0; day < k; day++) {
        for (int ranking = 0; ranking < n; ranking++) {
            int cow;
            cin >> cow;
            dayCowRankings[day][cow] = ranking;
        }
    }

    int distinctCows = 0;
    for (int cow1 = 1; cow1 <= n; cow1++) {
        for (int cow2 = 1; cow2 <= n; cow2++) {
            if (cow1 == cow2)
                continue;

            int distinctDays = 0;
            for (int day = 0; day < k && dayCowRankings[day][cow1] < dayCowRankings[day][cow2]; day++)
                distinctDays++;
            
            if (distinctDays == k)
                distinctCows++;
        }
    }

    freopen("gymnastics.out", "w", stdout);
    cout << distinctCows << endl;
    return 0;
}