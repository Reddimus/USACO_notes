// #include <bits/stdc++.h>

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Binary Search - Two Pointers approach
// T: O(n log n), M: O(n), where n = num of cows

int n, m, c;
vector<int> arrivals;

// check if max waiting time is valid under busses (m) and bus capacity (c) constraints
bool valid_waiting(int max_wait) {
    int buses = 0, cowRidx = 0, cowLidx = 0;
    while (cowRidx < n) {
        // if first cow in bus (overlapping idxs); increment buses counter
        if (cowLidx == cowRidx) 
            buses++;
        
        // if bus waiting time out of range; update prev idx to curr idx (move to next bus)
        if (arrivals[cowRidx] - arrivals[cowLidx] > max_wait) {
            cowLidx = cowRidx;
        }
        // else if bus capacity (c) reached with new placement; update idxs to move on to next bus
        else if (cowRidx + 1 - cowLidx == c) {
            cowRidx++;
            cowLidx = cowRidx;
        }
        // else cow time is valid for bus placement
        else {
            cowRidx++;
        }
    }
    return buses <= m;
}

int main() {
    freopen("convention.in", "r", stdin);
    // first line: n = num of cows, m = num of busses, c = bus capacity
    cin >> n >> m >> c;
    // Second line: arrival time of all cows
    arrivals.resize(n);
    for (int cow = 0; cow < n; cow++)
        cin >> arrivals[cow];

    // Sort to group bus pairs easily
    sort(arrivals.begin(), arrivals.end());
    
    // Binary search min max waiting time
    int lo = 0, hi = arrivals[n - 1] - arrivals[0];
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (!valid_waiting(mid))
            lo = mid + 1;
        else
            hi = mid;
    }

    // Write converged answer hi [..false, false, TRUE(hi), true...] representing min max arrival time
    freopen("convention.out", "w", stdout);
    cout << lo << endl;
}