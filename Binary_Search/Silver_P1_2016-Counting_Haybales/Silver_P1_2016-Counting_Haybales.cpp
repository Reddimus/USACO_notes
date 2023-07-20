/*
Counting Haybales - USACO Silver P1 2016 prompt:

Farmer John has just arranged his N haybales (1≤N≤100,000) at various points along 
the one-dimensional road running across his farm. To make sure they are spaced out 
appropriately, please help him answer Q queries (1≤Q≤100,000), each asking for the 
number of haybales within a specific interval along the road.

INPUT FORMAT (file haybales.in):
The first line contains N and Q.

The next line contains N distinct integers, each in the range 0…1,000,000,000, 
indicating that there is a haybale at each of those locations.

Each of the next Q lines contains two integers A and B (0≤A≤B≤1,000,000,000) 
giving a query for the number of haybales between A and B, inclusive.

OUTPUT FORMAT (file haybales.out):
You should write Q lines of output. For each query, output the number of haybales 
in its respective interval.

SAMPLE INPUT:
4 6
3 2 7 5
2 3
2 4
2 5
2 7
4 6
8 10

SAMPLE OUTPUT:
2
2
3
4
1
0
*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Binary search method
// T: O((n + q) log n)), M: O(n), where n is number of haybales, and q is num of intervals
/*
// From scratch
int lowerBound(vector<int>& arr, int target){
    int l_idx = 0, r_idx = arr.size();
    while (l_idx < r_idx){
        int m_idx = l_idx + (r_idx - l_idx) / 2;
        if (arr[m_idx] >= target)
            r_idx = m_idx;
        else
            l_idx = m_idx + 1;
    }
    return l_idx;   // if target not found returns out of bounds idx (n)
}

int upperBound(vector<int>& arr, int target){
    int l_idx = 0, r_idx = arr.size();
    while (l_idx < r_idx){
        int m_idx = l_idx + (r_idx - l_idx) / 2;
        if (arr[m_idx] > target)
            r_idx = m_idx;
        else
            l_idx = m_idx + 1;
    }
    return r_idx;
}
*/
int main(){
    // Read/Open input/output files
    ifstream in("haybales.in");
    ofstream pw("haybales.out");

    // first line: n = num of haybales, q = num of intervals
    int n, q;
    in >> n >> q;

    // second line: list of haybale placements
    vector<int> haybale_locs(n);
    for (int i = 0; i < n; i++)
        in >> haybale_locs[i];
    
    // Sort to binary search answers
    sort(haybale_locs.begin(), haybale_locs.end());

    // For the next q lines, process the intervals
    for (int ln = 0; ln < q; ln++){
        int start, end;
        in >> start >> end;
        // binary search lower/upper bound area of answers
        auto l_idx = lower_bound(haybale_locs.begin(), haybale_locs.end(), start);
        auto r_idx = upper_bound(haybale_locs.begin(), haybale_locs.end(), end);
        /*
        // From scratch
        int l_idx = lowerBound(haybale_locs, start);
        int r_idx = upperBound(haybale_locs, end);
        */
        // Write the number of haybales in the respective interval to the output file
        pw << (r_idx - l_idx) << "\n";
    }
    // close files
    in.close();
    pw.close();
    return 0;
}
