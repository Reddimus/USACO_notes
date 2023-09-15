// Custom Comparator Sorting approach
// T: O(nlogn), M: O(n), where n is the number of mountains

//#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	// Read input file
	freopen("mountains.in", "r", stdin);
	// Read first line: n = number of mountains
	int n;
	cin >> n;
	// For the next n lines calculate the xi, xf coordinates of each mountain
	struct Mountain { int xInit, xFinal; };
	vector<Mountain> mountains(n);
	for (int ln = 0; ln < n; ln++) {
		int x, y;
		cin >> x >> y;
		mountains[ln].xInit = x-y, mountains[ln].xFinal = x+y;
	}

	// sort by first appearing mountains and biggest mountains
	sort(mountains.begin(), mountains.end(), 
		[](Mountain &a, Mountain &b) {
			if (a.xInit != b.xInit)
				return a.xInit < b.xInit;
			return a.xFinal > b.xFinal;
		});
	
	// Count how many visible peaks Bessie can see
	int visible = 1;
	Mountain prevBiggest = mountains[0];
	for (Mountain mountain : mountains) {
		if (mountain.xFinal > prevBiggest.xFinal) {
			++visible;
			prevBiggest = mountain;
		}
	}

	// Write amount of visible peaks to output file
	freopen("mountains.out", "w", stdout);
	cout << visible << endl;
}

/*
// Custom Comparator and Coordinate Compression approach
// T: O(nlogn), M: O(n), where n is the number of mountains

#include <bits/stdc++.h>
// #include <fstream>
// #include <iostream>
// #include <unordered_map>
// #include <vector>
// #include <algorithm>

using namespace std;

int main() {
	// Read input file
	freopen("mountains.in", "r", stdin);
	// Read first line: n = number of mountains
	int n;
	cin >> n;
	// For the next n lines calculate the xi, xf coordinates of each mountain
	struct Mountain { int xInit, xFinal; };
	unordered_map<int, int> seenXInit;
	vector<Mountain> mountains;
	for (int ln = 0; ln < n; ln++) {
		int x, y;
		cin >> x >> y;
		if (seenXInit.find(x-y) == seenXInit.end()) {
			seenXInit[x-y] = mountains.size();
			mountains.push_back({x-y, x+y});
		}
		// Forget about the smaller mountain (compress data)
		else {
			int prevIdx = seenXInit[x-y];
			mountains[prevIdx].xFinal = max(mountains[prevIdx].xFinal, x+y);
		}
	}

	// sort by first appearing mountains and biggest mountains
	sort(mountains.begin(), mountains.end(), 
		[](Mountain &a, Mountain &b) {
			if (a.xInit != b.xInit)
				return a.xInit < b.xInit;
			return a.xFinal > b.xFinal;
		});
	
	// Count how many visible peaks Bessie can see
	int visible = 1;
	Mountain prevBiggest = mountains[0];
	for (Mountain mountain : mountains) {
		if (mountain.xFinal > prevBiggest.xFinal) {
			++visible;
			prevBiggest = mountain;
		}
	}

	// Write amount of visible peaks to output file
	freopen("mountains.out", "w", stdout);
	cout << visible << endl;
}
*/