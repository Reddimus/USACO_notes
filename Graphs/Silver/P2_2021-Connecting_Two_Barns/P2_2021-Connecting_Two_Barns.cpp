#include <bits/stdc++.h>
#define T_MAX 21
#define N_MAX 100001

using namespace std;

vector<int> paths[N_MAX];
int fieldComponents[N_MAX];
vector<int> componentFields[N_MAX];

int main() {
	// Read first line: t = sub test cases
	// freopen("test.in", "r", stdin);
	int t;
	cin >> t;
	long long subTestAnswers[T_MAX] = {0};
	// For the next t lines solve each sub test
	for (uint8_t tIdx = 0; tIdx < t; ++tIdx) {
		int n, m;
		cin >> n >> m;
		fill(paths, paths + n + 1, vector<int>());
		// For the next M lines read in connected paths (i, j)
		for (int ln = 0; ln < m; ++ln) {
			int i, j;
			cin >> i >> j;
			paths[i].push_back(j);
			paths[j].push_back(i);
		}

		// Flood Fill / Depth First search connected components
		fill(fieldComponents, fieldComponents + n + 1, -1);
		int latestComponent = 0;	// 1-indexed
		for (int field = 1; field <= n; ++field) {
			if (fieldComponents[field] != -1) 
				continue;

			++latestComponent;

			vector<int> frontier = {field};
			while (!frontier.empty()) {
				int currField = frontier.back();
				frontier.pop_back();
				fieldComponents[currField] = latestComponent;
				for (int& connectedField : paths[currField]) 
					if (fieldComponents[connectedField] == -1) 
						frontier.push_back(connectedField);
			}
		}

		if (fieldComponents[1] == fieldComponents[n]) {
			subTestAnswers[tIdx] = 0;
			continue;
		}

		// Gather component fields next to other different component fields
		fill(componentFields, componentFields + latestComponent + 1, vector<int>());
		componentFields[fieldComponents[1]].push_back(1);
		for (int field = 2; field < n; ++field) 
			if (fieldComponents[field] != fieldComponents[field + 1] ||
			fieldComponents[field - 1] != fieldComponents[field])
				componentFields[fieldComponents[field]].push_back(field);
		componentFields[fieldComponents[n]].push_back(n);

		function<long long(int, int)> searchMinCost = [&](int compA, int compB) -> long long {
			if (compA == compB) 
				return 0;
			
			long long minCost = LONG_LONG_MAX;
			for (int i = 0; i < componentFields[compA].size() && minCost > 1; ++i) {
				long long field1 = componentFields[compA][i];
				// Binary search for closest field in component B
				int lo = 0, hi = componentFields[compB].size() - 1;
				while (lo <= hi) {
					int mid = lo + (hi - lo) / 2;
					long long field2 = componentFields[compB][mid];
					minCost = min(minCost, (field1 - field2) * (field1 - field2));
					if (field1 < field2) 
						hi = mid - 1;
					else 
						lo = mid + 1;
				}
			}
			return minCost;
		};

		long long cost = LONG_LONG_MAX;
		for (int component = 1; component <= latestComponent && cost > 1; ++component)
			cost = min(
				cost, searchMinCost(1, component) + searchMinCost(component, fieldComponents[n])
			);

		subTestAnswers[tIdx] = cost;
	}

	for (uint8_t idx = 0; idx < t; ++idx) 
		cout << subTestAnswers[idx] << endl;
	return 0;
}