#include <bits/stdc++.h>

using namespace std;

#define N_MAX 1001

struct Cow {
	pair<int, int> coordinate;
	int id;
};

int main() {
	// Read in first line: n = number of cows
	int n;
	cin >> n;
	vector<Cow> northCows;
	vector<Cow> eastCows;
	// For the next n lines, store coordinates and direction of each cow based on direction
	for (int idx = 0; idx < n; ++idx) {
		char direction;
		int x, y;
		cin >> direction >> x >> y;
		if (direction == 'N') 
			northCows.push_back({{x, y}, idx});
		else 
			eastCows.push_back({{x, y}, idx});
	}

	// Sort north cows by x coordinate & east cows by y coordinate to check in order of intersection
	sort(northCows.begin(), northCows.end(), 
	[](const Cow &a, const Cow &b) {
		if (a.coordinate.first == b.coordinate.first) 
			return a.coordinate.second < b.coordinate.second;
		return a.coordinate.first < b.coordinate.first;
	});
	sort(eastCows.begin(), eastCows.end(), 
	[](const Cow &a, const Cow &b) {
		if (a.coordinate.second == b.coordinate.second) 
			return a.coordinate.first < b.coordinate.first;
		return a.coordinate.second < b.coordinate.second;
	});

	// Initialize stopped and blame arrays where indices are cow ids
	bool stopped[N_MAX] = {false};
	int blame[N_MAX] = {0};

	// For each cow that can potentially intersect with another cow
	for (Cow &eastCow : eastCows) {
		for (Cow &northCow : northCows) {
			// If both pairs of cows has not intersected
			if (!stopped[eastCow.id] &&
			!stopped[northCow.id] &&
			eastCow.coordinate.first <= northCow.coordinate.first &&
			eastCow.coordinate.second >= northCow.coordinate.second) {
				int xlen = northCow.coordinate.first - eastCow.coordinate.first;
				int ylen = eastCow.coordinate.second - northCow.coordinate.second;

				// Using the distance between the two cows which cow will stop
				if (xlen > ylen) {
					stopped[eastCow.id] = true;
					blame[northCow.id] += blame[eastCow.id] + 1;
				} else if (xlen < ylen) {
					stopped[northCow.id] = true;
					blame[eastCow.id] += blame[northCow.id] + 1;
				}
			}
		}
	}

	// For each cow, print the number of cows that it has stopped for our answer
	for (int idx = 0; idx < n; ++idx)
		cout << blame[idx] << endl;

	return 0;
}
