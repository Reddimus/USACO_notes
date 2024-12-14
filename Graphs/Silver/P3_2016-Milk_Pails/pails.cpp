#include <bits/stdc++.h>
#define PAIL_MAX 101
#define K_MAX 101

using namespace std;

int main() {
	ifstream fin("pails.in");
	int x, y, k, m;
	cin >> x >> y >> k >> m;
	
	int solution = m;
	bitset<K_MAX> visited[PAIL_MAX][PAIL_MAX];

	queue<pair<int, int>> q;
	q.push({0, 0});
	visited[0][0][0] = 1;

	while (!q.empty()) {
		auto [x, y] = q.front();
		q.pop();

		

	return 0;
}