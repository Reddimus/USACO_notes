#include <bits/stdc++.h>

using namespace std;

vector<char> milkTypes;
unordered_map<int, vector<int>> farms;
vector<vector<char>> cachedSatisfied;

// DFS to find path from start to end
bool dfs(int curr, int& end, unordered_set<int>& visited, vector<int>& path) {
	if (visited.find(curr) != visited.end())
		return false;

	visited.insert(curr);
	path.push_back(curr);

	if (curr == end)
		return true;

	for (int farmNum : farms[curr])
		if (dfs(farmNum, end, visited, path))
			return true;

	path.pop_back();
	return false;
}

bool isSatisfied(int& start, int& end, char& preference) {
	if (cachedSatisfied[start][end] == preference || cachedSatisfied[start][end] == 'B')
		return true;

	// Get path from start to end
	unordered_set<int> visited;
	vector<int> path;
	dfs(start, end, visited, path);

	// cout << "Start: " << start << " End: " << end << " Preference: " << preference << endl;
	// cout << "Path: ";
	// for (int farmNum : path)
	// 	cout << farmNum << " ";
	// cout << endl;
	// for (int r = 1; r < cachedSatisfied.size(); ++r) {
	// 	for (int c = 1; c < cachedSatisfied[r].size(); ++c)
	// 		cout << cachedSatisfied[r][c] << " ";
	// 	cout << endl;
	// }

	// Check if path is satisfied
	unordered_set<char> milkTypesInPath;
	for (int idx = 0; idx < path.size(); ++idx)
		milkTypesInPath.insert(milkTypes[path[idx]]);

	if (milkTypesInPath.size() == 2) {
		cachedSatisfied[start][end] = 'B';
		cachedSatisfied[end][start] = 'B';
		return true;
	}

	// cout << "Milk Types in Path: (" << milkTypesInPath.size() << ") ";
	// for (char milkType : milkTypesInPath)
	// 	cout << milkType << " ";
	// cout << endl << endl;

	char milkType = *milkTypesInPath.begin();
	cachedSatisfied[start][end] = milkType;
	cachedSatisfied[end][start] = milkType;
	return milkType == preference;
}

int main() {
	freopen("milkvisits.in", "r", stdin);
	int n, m;
	cin >> n >> m;

	milkTypes.resize(n + 1);
	for (int idx = 1; idx <= n; ++idx)
		cin >> milkTypes[idx];
	
	cachedSatisfied.resize(n + 1, vector<char>(n + 1));

	for (int ln = 0; ln < n - 1; ++ln) {
		int x, y;
		cin >> x >> y;
		farms[x].push_back(y);
		farms[y].push_back(x);

		if (milkTypes[x] == milkTypes[y]) {
			cachedSatisfied[x][y] = milkTypes[x];
			cachedSatisfied[y][x] = milkTypes[y];
		}
		else {
			cachedSatisfied[x][y] = 'B';
			cachedSatisfied[y][x] = 'B';
		}
	}

	string ans = "";
	for (int ln = 0; ln < m; ++ln) {
		int start, end;
		char preference;
		cin >> start >> end >> preference;
		if (isSatisfied(start, end, preference))
			ans += '1';
		else
			ans += '0';
	}
	
	freopen("milkvisits.out", "w", stdout);
	cout << ans << endl;
	return 0;
}