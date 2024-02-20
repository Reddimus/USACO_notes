#include <bits/stdc++.h>

using namespace std;

class MilkingOrder {
public:
	MilkingOrder(vector<vector<int>>& observations, int& n, int& m) : 
	observations(observations), n(n), m(m) {}

	// Binary search for maximum number of observations that can be satisfied
	vector<int> search_max_conditions(void) {
		int lo = 0, hi = m;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			check_x_conditions(mid) ? lo = mid + 1 : hi = mid;
		}
		return answer;
	}
private:
	vector<vector<int>> observations;
	vector<int> answer;
	int n, m;

	// Topological sort the x-observations graph to check if all cows can be visited
	bool check_x_conditions(int& x) {
		// Using up to x observations build adjacency list & count edges per node
		vector<vector<int>> graph(n + 1);
		vector<int> inDegree(n + 1, 0);
		for (int i = 0; i < x; ++i) {
			// Map observation path by pairs
			for (int j = 0; j < observations[i].size() - 1; ++j) {
				graph[observations[i][j]].push_back(observations[i][j + 1]);
				++inDegree[observations[i][j + 1]];
			}
		}

		// Queue non-dependent cows in lexicographical order
		priority_queue<int, vector<int>, greater<int>> pq;
		for (int cow = 1; cow <= n; ++cow)
			if (inDegree[cow] == 0) 
				pq.push(cow);

		// Traverse non-dependent cows in lexicographical order from graph
		vector<int> tempAnswer(n);
		int visits = 0;
		for (visits = 0; !pq.empty(); ++visits) {
			int cow = pq.top(); pq.pop();
			tempAnswer[visits] = cow;

			for (int& adj : graph[cow]) {
				--inDegree[adj];	// Remove the edge from the adjacent cow/node
				if (inDegree[adj] == 0) 
					pq.push(adj);
			}
		}

		// Check if all cows/nodes were visited
		if (visits < n) 
			return false;
		answer = tempAnswer;
		return true;
	}
};

int main(void) {
	freopen("milkorder.in", "r", stdin);
	// First line: n = # of cows, m = # of observations
	int n, m;
	cin >> n >> m;
	// For the next m lines, read in the observation paths
	vector<vector<int>> observations(m);
	for (int i = 0; i < m; ++i) {
		int mi;
		cin >> mi;
		vector<int> observation(mi);
		for (int j = 0; j < mi; ++j) 
			cin >> observation[j];
		observations[i] = observation;
	}

	// Binary search & topological sort to find the maximum number of observations
	MilkingOrder mo(observations, n, m);
	const vector<int>& answer = mo.search_max_conditions();

	// Write the maximum number of x-ordered observations to the output file
	freopen("milkorder.out", "w", stdout);
	for (int idx = 0; idx < n - 1; ++idx) 
		cout << answer[idx] << " ";
	cout << answer[n - 1] << endl;
	return 0;
}