/*
USACO 2017 January Contest, Silver
Problem 1. Cow Dance Show

After several months of rehearsal, the cows are just about ready to put on their annual dance 
performance; this year they are performing the famous bovine ballet "Cowpelia".

The only aspect of the show that remains to be determined is the size of the stage. A stage 
of size K can support K cows dancing simultaneously. The N cows in the herd (1≤N≤10,000) 
are conveniently numbered 1…N in the order in which they must appear in the dance. Each 
cow i plans to dance for a specific duration of time d(i). Initially, cows 1…K appear 
on stage and start dancing. When the first of these cows completes her part, she leaves 
the stage and cow K+1 immediately starts dancing, and so on, so there are always K cows 
dancing (until the end of the show, when we start to run out of cows). The show ends when 
the last cow completes her dancing part, at time T.

Clearly, the larger the value of K, the smaller the value of T. Since the show cannot last 
too long, you are given as input an upper bound Tmax specifying the largest possible value 
of T. Subject to this constraint, please determine the smallest possible value of K.

INPUT FORMAT (file cowdance.in):
The first line of input contains N and Tmax, where Tmax is an integer of value at most 1 million.

The next N lines give the durations d(1)…d(N) of the dancing parts for cows 1…N. Each d(i) 
value is an integer in the range 1…100,000.

It is guaranteed that if K=N, the show will finish in time.

OUTPUT FORMAT (file cowdance.out):
Print out the smallest possible value of K such that the dance performance will take no more 
than Tmax units of time.

SAMPLE INPUT:
5 8
4
7
8
6
4

SAMPLE OUTPUT:
4
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int n, t_max;
vector<int> dances;

// k represents the size of the stage to support n amount of cows dancing
bool within_contract(int k);

int main() {
    // open input file
    ifstream fin("cowdance.in");
    // first line: n = number of cows, t_max = max stage time
    fin >> n >> t_max;
    // for next n lines, read in cow dance times
    for (int i = 0; i < n; i++) {
        int t;
        fin >> t;
        dances.push_back(t);
    }
    fin.close();

    // Binary search for smallest possible stage size within contract time limit
    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (!within_contract(mid))
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
bool within_contract(int k) {
    // heapify first k cows
    priority_queue<int, vector<int>, greater<int>> stage(dances.begin(), dances.begin() + k);
    // elapse shortest dance time (root) to open dance spot and add next cow to stage
    for (int idx = k; idx < n; idx++) {
        int min_dance = stage.top();
        stage.pop();
        stage.push(min_dance + dances[idx]);
    }
    // dance remaining cows on stage
    while (!stage.empty()) {
        int max_dance = stage.top();
        stage.pop();
        if (max_dance > t_max)
            return false;
    }
    return true;
}

/*
// Binary search - Array approach
// T: O(n^2 log n), M: O(n), where n is the number of cows
bool within_contract(int k) {
    vector<int> stage(dances.begin(), dances.begin() + k);
    int t_cnt = 0, d_idx = k;
    while (d_idx < n) {
        // find the shortest dance time on stage
        int min_dance = *min_element(stage.begin(), stage.end());
        t_cnt += min_dance;
        if (t_cnt > t_max)
            return false;
        // elapse time by shorest dance time to open dance spot and add new cow to stage
        for (int i = 0; i < k; i++) {
            stage[i] -= min_dance;
            if (stage[i] == 0) {
                stage[i] = dances[d_idx];
                d_idx++;
            }
        }
    }
    return t_cnt + *max_element(stage.begin(), stage.end()) <= t_max;
}
*/