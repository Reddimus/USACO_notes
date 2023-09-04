// Custom Comparators + Sort + Greedy approach
// T: O(n * m), M: O(n + m + r) 
// Where n is num of cows, m is num of shops, and r is num of neighbors

#include <bits/stdc++.h>
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
	int cached_price = 0;
	int jugs, temp_idx, last_sold;
	int cow_idx = 0, shop_idx = 0, rent_idx = 0;
	while (cow_idx < n) {
		// Initialize potential jugs price to 0 or previously unused price
		int jugs_price = cached_price;
		
		if (!cached_price) {
			jugs = milk[cow_idx], last_sold = 0;
			temp_idx = shop_idx;
			// Calculate potential revenue if cow were to be milked
			while (temp_idx < m) {
				int sold = min(jugs, shops[temp_idx].demand);
				jugs_price += sold * shops[temp_idx].rate;
				jugs -= sold;

				if (jugs == 0){
					last_sold = sold;
					break;
				}
				temp_idx++;
			}
		}

		// Compare rent a cow price to potential milked price
		if (rent_idx < r && rent[rent_idx] > jugs_price) {
			revenue += rent[rent_idx];
			cached_price = jugs_price;
			rent_idx++;
			n--;	// rent cow that produces least milk
		}
		else {
			revenue += jugs_price;
			shop_idx = temp_idx;
			if (temp_idx < m)
				shops[shop_idx].demand -= last_sold;
			cached_price = 0;
			cow_idx++;
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
	int cow_idx = 0, shop_idx = 0, rent_idx = 0;
	while (cow_idx < n) {
		// Calculate potential revenue if cow were to be milked
		int jugs = milk[cow_idx], jugs_price = 0, last_sold = 0;
		int temp_idx = shop_idx;
		while (temp_idx < m) {
			int sold = min(jugs, shops[temp_idx].demand);
			jugs_price += sold * shops[temp_idx].rate;
			jugs -= sold;

			if (jugs == 0){
				last_sold = sold;
				break;
			}
			temp_idx++;
		}

		// Compare rent a cow price to potential milked price
		if (rent_idx < r && rent[rent_idx] > jugs_price) {
			revenue += rent[rent_idx];
			rent_idx++;
			n--;	// rent cow that produces least milk
		}
		else {
			revenue += jugs_price;
			shop_idx = temp_idx;
			if (temp_idx < m)
				shops[shop_idx].demand -= last_sold;
			cow_idx++;
		}
	}

	// Write maximum profit to output file 
	freopen("rental.out", "w", stdout);
	cout << revenue << endl;
}
*/