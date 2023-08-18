/*
USACO 2020 US Open Contest, Silver
Problem 1. Social Distancing

Farmer John is worried for the health of his cows after an outbreak of the highly contagious 
bovine disease COWVID-19.

In order to limit transmission of the disease, Farmer John's N cows (2≤N≤10^5) have decided 
to practice "social distancing" and spread themselves out across the farm. The farm is shaped 
like a 1D number line, with M mutually-disjoint intervals (1≤M≤10^5) in which there is grass 
for grazing. The cows want to locate themselves at distinct integer points, each covered in 
grass, so as to maximize the value of D, where D represents the distance between the closest 
pair of cows. Please help the cows determine the largest possible value of D.

INPUT FORMAT (file socdist.in):
The first line of input contains N and M. The next M lines each describe an interval in terms
of two integers a and b, where 0≤a≤b≤10^18. No two intervals overlap or touch at their endpoints. 
A cow standing on the endpoint of an interval counts as standing on grass.

OUTPUT FORMAT (file socdist.out):
Print the largest possible value of D such that all pairs of cows are D units apart. A solution 
with D>0 is guaranteed to exist.

SAMPLE INPUT:
5 3
0 2
4 7
9 9

SAMPLE OUTPUT:
2

One way to achieve D=2 is to have cows at positions 0, 2, 4, 6 and 9.

SCORING:
- Test cases 2-3 satisfy b≤10^5.
- Test cases 4-10 satisfy no additional constraints.
*/

// Binary search method
// T: O(N log D + M log M) = O((N+M)log(maxDist)), M: O(M), where N is the number of cows, M is the number of intervals, and D is the range of distance

//#include<bits/stdc++.h>   // non standard library

#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

typedef long long ll;

vector<pair<ll, ll>> intervals;
int n, m;

// Function to test if all cows can be placed maintaining a certain minimum distance
bool possible_placement(ll min_dist){
    // initialize previous cow location to be right before the first position
    ll prev_cow_loc = intervals[0].first - min_dist;
    int cows_cnt = n;
    // iterating through each sorted interval allows us to find cow placements faster
    for (pair<ll, ll> interval : intervals){
        // if next cow placement falls out of grassy area interval, prepare cow placement for while loop
        if (prev_cow_loc + min_dist < interval.first)
            prev_cow_loc = interval.first - min_dist;
        // maximize cow placement in current grassy area
        while (interval.first <= prev_cow_loc + min_dist && prev_cow_loc + min_dist <= interval.second){
            prev_cow_loc += min_dist;
            cows_cnt--;
            if (cows_cnt <= 0)
                return true;
        }
    }
    return false;
}

int main() {
    // Open input file
    ifstream in("socdist.in");
    // Read first line: n = number of cows, m = number of intervals
    in >> n >> m;
    // Create a vector of pairs for all the intervals in the next m lines
    intervals.resize(m);
    for (int interval = 0; interval < m; interval++)
        // start point, end point
        in >> intervals[interval].first >> intervals[interval].second;
    in.close();
    
    // Only sort intervals by start point; there are no overlapping intervals
    sort(intervals.begin(), intervals.end());

    // Binary search multiple answers
    // worst case = 1, best case = equally distant cows
    // 1 <= result <= equally distant cows
    ll lo = 1, hi = (intervals[m-1].second - intervals[0].first) / (n - 1);
    // Converge to a max feasible min distance
    while (lo < hi){
        ll mid = lo + (hi - lo + 1) / 2;
        // if min_dist/mid does fit in grassy areas we save lo and try for a larger minimum distance
        if (possible_placement(mid))
            lo = mid;
        // else min_dist/mid does not fit therefore we get rid of curr hi by lowering upper bound
        else
            hi = mid - 1;
    }

    // Write minimum distance of optimally distant cows to output file
    ofstream pw("socdist.out");
    pw << lo << "\n";
    pw.close();
    return 0;
}
