#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("lostcow.in", "r", stdin);
	int x, y;
	cin >> x >> y;

	bool left = false, right = true;
	int totalDistance = 0, directionDistance = 1;
	// While our x +- directionDistance is not in the range of Y
	while ((right && x > y || y > x + directionDistance) ||
	(left && x < y || y < x - directionDistance)) {
		// Double the distance and toggle the direction
		directionDistance *= 2;
		totalDistance += directionDistance;
		left = !left, right = !right;	// Toggle the direction
	}
	totalDistance += abs(x - y);	// Add the remaining distance

	freopen("lostcow.out", "w", stdout);
	cout << totalDistance << endl;
	return 0;
}
