#include <bits/stdc++.h>

using namespace std;

#define N_MAX 1001

int main() {
	int n;
	cin >> n;

	struct Cow { int x, y, id; };
	vector<Cow> northCows;
	vector<Cow> eastCows;

	for (int idx = 0; idx < n; ++idx) {
		char direction;
		int x, y;
		cin >> direction >> x >> y;
		if (direction == 'N') 
			northCows.push_back({x, y, idx});
		else 
			eastCows.push_back({x, y, idx});
	}

	sort(northCows.begin(), northCows.end(), 
	[](const Cow &a, const Cow &b) {
		if (a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	});
	sort(eastCows.begin(), eastCows.end(), 
	[](const Cow &a, const Cow &b) {
		if (a.y == b.y)
			return a.x < b.x;
		return a.y < b.y;
	});

	bool stopped[N_MAX] = {false};
	unsigned int blame[N_MAX] = {0};

	for (Cow &eastCow : eastCows) {
		for (Cow &northCow : northCows) {
			// Checks whether they intersect
			if (!stopped[eastCow.id] &&
			!stopped[northCow.id] &&
			eastCow.x <= northCow.x && 
			eastCow.y >= northCow.y) {
				int xlen = northCow.x - eastCow.x;
				int ylen = eastCow.y - northCow.y;

				// checks which cow will block the other
				if (xlen > ylen) {
					stopped[eastCow.id] = true;
					blame[northCow.id] += 1 + blame[eastCow.id];
				} else if (xlen < ylen) {
					stopped[northCow.id] = true;
					blame[eastCow.id] += 1 + blame[northCow.id];
				}
			}
		}
	}

	for (int idx = 0; idx < n; ++idx)
		cout << blame[idx] << endl;

	return 0;
}
