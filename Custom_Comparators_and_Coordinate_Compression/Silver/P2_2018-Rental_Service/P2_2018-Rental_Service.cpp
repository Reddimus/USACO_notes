// Custom Comparators + Sort + Greedy approach
// T: O(n * m), M: O(n + m + r) 
// Where n is num of cows, m is num of shops, and r is num of neighbors

#include <bits/stdc++.h>
// #include <vector>
// #include <iostream>
// #include <algorithm>

#define ll long long

using namespace std;

int main() {
	struct Shop {
		int demand, rate;
	};

	// Open input file
	freopen("rental.in", "r", stdin);
	// Read first line: n = num of cows, m = num of shops, r = num of neighbors
	int n, m, r;
	cin >> n >> m >> r;
	// For the next n lines track milk produced per cow
	vector<int> milk(n);
	for (int cow = 0; cow < n; cow++)
		cin >> milk[cow];
	// For the next m lines track demand and rate of each shop
	vector<Shop> shops(m);
	for (int customer = 0; customer < m; customer++)
		cin >> shops[customer].demand >> shops[customer].rate;
	// For the next r lines track neighbor rent a cow rate
	vector<int> rent(r);
	for (int neighbor = 0; neighbor < r; neighbor++)
		cin >> rent[neighbor];

	// Sort in reverse; we always want to milk the cow that produces the most milk
	sort(milk.begin(), milk.end(), greater<int>());
	sort(shops.begin(), shops.end(), [](Shop a, Shop b) {return a.rate > b.rate;});
	sort(rent.begin(), rent.end(), greater<int>());

	// Calculate maximum revenue
	ll revenue = 0;
	int cachedPrice = 0;
	int jugs, tempIdx, lastSold;
	int cowIdx = 0, shopIdx = 0, rentIdx = 0;
	while (cowIdx < n) {
		// Initialize potential jugs price to 0 or previously unused price
		int jugsPrice = cachedPrice;
		
		if (!cachedPrice) {
			jugs = milk[cowIdx], lastSold = 0;
			tempIdx = shopIdx;
			// Calculate potential revenue if cow were to be milked
			while (tempIdx < m) {
				int sold = min(jugs, shops[tempIdx].demand);
				jugsPrice += sold * shops[tempIdx].rate;
				jugs -= sold;

				if (jugs == 0){
					lastSold = sold;
					break;
				}
				tempIdx++;
			}
		}

		// Compare rent a cow price to potential milked price
		if (rentIdx < r && rent[rentIdx] > jugsPrice) {
			revenue += rent[rentIdx];
			cachedPrice = jugsPrice;
			rentIdx++;
			n--;	// rent cow that produces least milk
		}
		else {
			revenue += jugsPrice;
			shopIdx = tempIdx;
			if (tempIdx < m)
				shops[shopIdx].demand -= lastSold;
			cachedPrice = 0;
			cowIdx++;
		}
	}

	// Write maximum profit to output file 
	freopen("rental.out", "w", stdout);
	cout << revenue << endl;
}

/*
// Custom Comparators + Sort + Greedy approach | without cached value
// T: O(n * m), M: O(n + m + r) 
// Where n is num of cows, m is num of shops, and r is num of neighbors

int main() {
	struct Shop {
		int demand, rate;
	};

	// Open input file
	freopen("rental.in", "r", stdin);
	// Read first line: n = num of cows, m = num of shops, r = num of neighbors
	int n, m, r;
	cin >> n >> m >> r;
	// For the next n lines track milk produced per cow
	int milk[n];
	for (int cow = 0; cow < n; cow++)
		cin >> milk[cow];
	// For the next m lines track demand and rate of each shop
	Shop shops[m];
	for (int customer = 0; customer < m; customer++)
		cin >> shops[customer].demand >> shops[customer].rate;
	// For the next r lines track neighbor rent a cow rate
	int rent[r];
	for (int neighbor = 0; neighbor < r; neighbor++)
		cin >> rent[neighbor];

	// Sort in reverse; we always want to milk the cow that produces the most milk
	sort(milk, milk + n, greater<int>());
	sort(shops, shops + m, [](Shop a, Shop b) {return a.rate > b.rate;});
	sort(rent, rent + r, greater<int>());

	// Calculate maximum revenue
	ll revenue = 0;
	int cowIdx = 0, shopIdx = 0, rentIdx = 0;
	while (cowIdx < n) {
		// Calculate potential revenue if cow were to be milked
		int jugs = milk[cowIdx], jugsPrice = 0, lastSold = 0;
		int tempIdx = shopIdx;
		while (tempIdx < m) {
			int sold = min(jugs, shops[tempIdx].demand);
			jugsPrice += sold * shops[tempIdx].rate;
			jugs -= sold;

			if (jugs == 0){
				lastSold = sold;
				break;
			}
			tempIdx++;
		}

		// Compare rent a cow price to potential milked price
		if (rentIdx < r && rent[rentIdx] > jugsPrice) {
			revenue += rent[rentIdx];
			rentIdx++;
			n--;	// rent cow that produces least milk
		}
		else {
			revenue += jugsPrice;
			shopIdx = tempIdx;
			if (tempIdx < m)
				shops[shopIdx].demand -= lastSold;
			cowIdx++;
		}
	}

	// Write maximum profit to output file 
	freopen("rental.out", "w", stdout);
	cout << revenue << endl;
}
*/