// Breadth First Search (BFS) w/ Connected Components detection Graph approach
// T & M: O(n + m) | O(V + E), where n = num of farms, m = num of friends

#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("milkvisits.in", "r", stdin);
	// Read in First line: n = num of farms, m = num of FJ's friends
	int n, m;
	cin >> n >> m;

	// Second line: string of farm types
	vector<char> milkTypes(n + 1);
	for (int idx = 1; idx <= n; ++idx)
		cin >> milkTypes[idx];

	// For the next n-1 lines read in the edges of the graph
	vector<vector<int>> farms(n + 1);
	for (int ln = 0; ln < n - 1; ++ln) {
		int x, y;
		cin >> x >> y;
		farms[x].push_back(y);
		farms[y].push_back(x);
	}

	// Process the tree & detect the different components
	vector<int> components(n + 1, -1);
	for (int farm = 1; farm <= n; ++farm) {
		// Don't process a farm if it's been visited already
		if (components[farm] != -1)
			continue;
		
		// BFS to find all the farms in the same subtree
		char type = milkTypes[farm];
		queue<int> q;
		q.push(farm);
		while (!q.empty()) {
			int qdFarm = q.front();
			q.pop();
			
			// Mark the queue'd farm as same path as current component (farm)
			components[qdFarm] = farm;

			// Visit a neighbor if it's new & is of the same type
			for (int& neighbor : farms[qdFarm])
				if (milkTypes[neighbor] == type && components[neighbor] == -1)
					q.push(neighbor);
		}
	}

	// For the next m lines read & check if friend's path satisfies them
	string ans = "";
	for (int ln = 0; ln < m; ++ln) {
		int start, end;
		char preference;
		cin >> start >> end >> preference;

		if (components[start] == components[end] && milkTypes[start] != preference)
			ans += '0';
		else
			ans += '1';
	}
	
	// Write satisfaction of each friend in sting form to output file
	freopen("milkvisits.out", "w", stdout);
	cout << ans << endl;
	return 0;
}

/* 
// Brute force DFS approach
// T: O(n * m) | O(V * E), M: O(n), where n = num of farms, m = num of friends

#include <bits/stdc++.h>

using namespace std;

vector<char> milkTypes;
unordered_map<int, vector<int>> farms;

// DFS to find path from start to end and return it
vector<int> dfs(int curr, int end, unordered_set<int>& visited) {
    vector<int> path;

    if (visited.find(curr) != visited.end())
        return path;

    visited.insert(curr);
    path.push_back(curr);

    if (curr == end)
        return path;

    for (int farm : farms[curr]) {
        vector<int> subPath = dfs(farm, end, visited);
        if (!subPath.empty()) {
            path.insert(path.end(), subPath.begin(), subPath.end());
            return path;
        }
    }

    path.pop_back(); // Remove the current node as it's not on the path to the end
    return {}; // Return an empty path as this branch doesn't lead to the end
}

bool isSatisfied(int& start, int& end, char& preference) {
	// Get path from start to end
	unordered_set<int> visited;
	vector<int> path = dfs(start, end, visited);

	// Check if path is satisfied
	unordered_set<char> milkTypesInPath;
	for (int idx = 0; idx < path.size() && milkTypesInPath.size() < 2; ++idx)
		milkTypesInPath.insert(milkTypes[path[idx]]);
	return milkTypesInPath.find(preference) != milkTypesInPath.end();
}

int main() {
	freopen("milkvisits.in", "r", stdin);
	// Read in First line: n = num of farms, m = FJ's friends
	int n, m;
	cin >> n >> m;
	// Second line: string of farm types
	milkTypes.resize(n + 1);
	for (int idx = 1; idx <= n; ++idx)
		cin >> milkTypes[idx];
	// For the next n-1 lines read in the edges of the graph
	for (int ln = 0; ln < n - 1; ++ln) {
		int x, y;
		cin >> x >> y;
		farms[x].push_back(y);
		farms[y].push_back(x);
	}
	// For the next m lines read & check if friend's path satisfies them
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
*/