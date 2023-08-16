/*
USACO 2015 December Contest, Silver
Problem 3. Breed Counting

Farmer John's N cows, conveniently numbered 1…N, are all standing in a row (they seem to 
do so often that it now takes very little prompting from Farmer John to line them up). 
Each cow has a breed ID: 1 for Holsteins, 2 for Guernseys, and 3 for Jerseys. Farmer John 
would like your help counting the number of cows of each breed that lie within certain 
intervals of the ordering.

INPUT FORMAT (file bcount.in):
The first line of input contains N and Q (1≤N≤100,000, 1≤Q≤100,000).

The next N lines contain an integer that is either 1, 2, or 3, giving the breed ID of a 
single cow in the ordering.

The next Q lines describe a query in the form of two integers a,b (a≤b).

OUTPUT FORMAT (file bcount.out):
For each of the Q queries (a,b), print a line containing three numbers: the number of 
cows numbered a…b that are Holsteins (breed 1), Guernseys (breed 2), and Jerseys (breed 3).

SAMPLE INPUT:
6 3
2
1
1
3
2
1
1 6
3 3
2 4

SAMPLE OUTPUT:
3 2 1
1 0 0
2 0 1
*/

// Prefix sums approach
// T: O(n + q), M: O(n), where n is num of cows, and q is num of queries

// #include <bits/stdc++.h>

#include <iostream>

using namespace std;

int main() {
	// Open input file
	freopen("bcount.in", "r", stdin);
	// first line: n = num of cows, q = num of queries
	int n, q;
	cin >> n >> q;

	// For next n lines read cow breed IDs and create prefix sum lists
	int holsteins[n+1] = {}, guernseys[n+1] = {}, jerseys[n+1] = {};
	for (int idx = 1; idx < n + 1; idx++) {
		holsteins[idx] += holsteins[idx-1];
		guernseys[idx] += guernseys[idx-1];
		jerseys[idx] += jerseys[idx-1];
		int cow_id;
		cin >> cow_id;
		switch (cow_id) {
			case 1:
				holsteins[idx]++;
				break;
			case 2:
				guernseys[idx]++;
				break;
			case 3:
				jerseys[idx]++;
				break;
		}
	}

	// For next q lines solve num of cow breeds in query range and write queries ids to output file
	freopen("bcount.out", "w", stdout);
	for (int ln = 0; ln < q; ln++) {
		int start, end;
		cin >> start >> end;
		cout << holsteins[end] - holsteins[start-1] << " "
			<< guernseys[end] - guernseys[start-1] << " "
		    << jerseys[end] - jerseys[start-1] << endl;
	}
}
