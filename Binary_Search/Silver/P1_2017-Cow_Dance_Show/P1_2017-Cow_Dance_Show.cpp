// #include <bits/stdc++.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

int n, tMax;
vector<int> dances;

// k represents the size of the stage to support n amount of cows dancing
bool withinContract(int k);

int main() {
    // open input file
    ifstream fin("cowdance.in");
    // first line: n = number of cows, tMax = max stage time
    fin >> n >> tMax;
    // for next n lines, read in cow dance times
    for (int ln = 0; ln < n; ln++) {
        int t;
        fin >> t;
        dances.push_back(t);
    }
    fin.close();

    // Binary search for smallest possible stage size within contract time limit
    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (!withinContract(mid))
            lo = mid + 1;   // increase stage size to reduce time on stage and be within contract time limit
        else
            hi = mid;
    }

    // write smallest possible stage size to output file
    ofstream pw("cowdance.out");
    pw << lo << endl;
    pw.close();
}

// Binary search - Heap/prority queue approach
// T: O(n * log n), M: O(n), where n is the number of cows
bool withinContract(int k) {
    // heapify first k cows
    priority_queue<int, vector<int>, greater<int>> stage(dances.begin(), dances.begin() + k);
    // elapse shortest dance time (root) to open dance spot and add next cow to stage
    int maxDance = numeric_limits<int>::min();
    for (int idx = k; idx < n; idx++) {
        int minDance = stage.top();
        stage.pop();
        stage.push(minDance + dances[idx]);
        maxDance = max(maxDance, minDance + dances[idx]);
    }
    // dance remaining cows on stage by searching max dance time
    return maxDance <= tMax;
}

/*
// Binary search - Array approach
// T: O(n^2 log n), M: O(n), where n is the number of cows
bool within_contract(int k) {
    vector<int> stage(dances.begin(), dances.begin() + k);
    int t_cnt = 0, d_idx = k;
    while (d_idx < n) {
        // find the shortest dance time on stage
        int minDance = *min_element(stage.begin(), stage.end());
        t_cnt += minDance;
        if (t_cnt > tMax)
            return false;
        // elapse time by shorest dance time to open dance spot and add new cow to stage
        for (int i = 0; i < k; i++) {
            stage[i] -= minDance;
            if (stage[i] == 0) {
                stage[i] = dances[d_idx];
                d_idx++;
            }
        }
    }
    return t_cnt + *max_element(stage.begin(), stage.end()) <= tMax;
}
*/