#include <bits/stdc++.h>
#define N_MAX 101

using namespace std;

int main() {
    freopen("measurement.in", "r", stdin);
    // Read 1st line: number of measurements
    int n;
    cin >> n;
    int bessieTimestamp[N_MAX] = {0};
    int elsieTimestamp[N_MAX] = {0};
    int mildredTimestamp[N_MAX] = {0};
    int firsTimestamp = N_MAX, lastTimestamp = 0;
    // For the next N lines create bucket sorted arrays for each cow
    for (int i = 0; i < n; i++) {
        int timestamp, change;
        string cow;
        cin >> timestamp >> cow >> change;

        if (cow == "Bessie") bessieTimestamp[timestamp] += change;
        else if (cow == "Elsie") elsieTimestamp[timestamp] += change;
        else mildredTimestamp[timestamp] += change;

        firsTimestamp = min(firsTimestamp, timestamp);
        lastTimestamp = max(lastTimestamp, timestamp);
    }

    int displayChanges = 0;
    unordered_set<char> leadCows = {'B', 'E', 'M'};
    int bessieMilk = 7, elsieMilk = 7, mildredMilk = 7;
    // For each milk production change
    for (int i = firsTimestamp; i <= lastTimestamp; i++) {
        if (bessieTimestamp[i] == 0 &&
        elsieTimestamp[i] == 0 &&
        mildredTimestamp[i] == 0)
            continue;

        // Re-calculate the milk production for each cow change
        bessieMilk += bessieTimestamp[i];
        elsieMilk += elsieTimestamp[i];
        mildredMilk += mildredTimestamp[i];

        int maxMilk = max(bessieMilk, max(elsieMilk, mildredMilk));
        unordered_set<char> currLeadCows;
        if (bessieMilk == maxMilk) currLeadCows.insert('B');
        if (elsieMilk == maxMilk) currLeadCows.insert('E');
        if (mildredMilk == maxMilk) currLeadCows.insert('M');

        // If the lead cows have changed, increment the display changes
        if (currLeadCows != leadCows) {
            displayChanges++;
            leadCows = currLeadCows;
        }
    }

    freopen("measurement.out", "w", stdout);
    cout << displayChanges << endl;
    return 0;
}