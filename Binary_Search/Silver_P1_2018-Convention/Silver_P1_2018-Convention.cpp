/*
USACO 2018 December Contest, Silver
Problem 1. Convention

Farmer John is hosting a new bovine grass-eating convention at his farm!

Cows from all over the world are arriving at the local airport to attend the 
convention and eat grass. Specifically, there are N cows arriving at the airport 
(1≤N≤10^5) and cow i arrives at time ti (0≤ti≤10^9). Farmer John has arranged M 
(1≤M≤10^5) buses to transport the cows from the airport. Each bus can hold up to 
C cows in it (1≤C≤N). Farmer John is waiting with the buses at the airport and 
would like to assign the arriving cows to the buses. A bus can leave at the time 
when the last cow on it arrives. Farmer John wants to be a good host and so does 
not want to keep the arriving cows waiting at the airport too long. What is the 
smallest possible value of the maximum waiting time of any one arriving cow if 
Farmer John coordinates his buses optimally? A cow's waiting time is the difference 
between her arrival time and the departure of her assigned bus.

It is guaranteed that MC≥N.

INPUT FORMAT (file convention.in):
The first line contains three space separated integers N, M, and C. The next line 
contains N space separated integers representing the arrival time of each cow.

OUTPUT FORMAT (file convention.out):
Please write one line containing the optimal minimum maximum waiting time for any 
one arriving cow.

SAMPLE INPUT:
6 3 2
1 1 10 14 4 3

SAMPLE OUTPUT:
4

If the two cows arriving at time 1 go in one bus, cows arriving at times 3 and 4 
in the second, and cows arriving at times 10 and 14 in the third, the longest time 
a cow has to wait is 4 time units (the cow arriving at time 10 waits from time 10 
to time 14)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Binary Search - Two Pointers approach
// T: O(n log n), M: O(n), where n = num of cows

int n, m, c;
vector<int> arrivals;

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