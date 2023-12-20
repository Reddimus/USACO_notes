#include <bits/stdc++.h>
// #define ui unsigned int

using namespace std;

pair<int, int> setFarmerPriority(pair<int, int>& farmer, int& goal, unordered_map<int, vector<int>>& tunnels);
bool caughtBessy(int& k, unordered_set<int>& blocked, unordered_set<int>& exits, unordered_map<int, vector<int>>& tunnels);

int main() { 
    freopen("atlarge.in", "r", stdin);

    // Read first line: n = barns, k = Bessie starting barn
    int n, k;
    cin >> n >> k;

    unordered_map<int, vector<int>> tunnels;
    for (int ln = 0; ln < n-1; ++ln) {
        int t1, t2;
        cin >> t1 >> t2;
        tunnels[t1].push_back(t2);
        tunnels[t2].push_back(t1);
    }

    // Find all farmer exit positions
    // farmers.first = starting position
    // farmers.second = priority
    vector<pair<int, int>> farmersPriority;
    for (auto& barnTunnels : tunnels) {
        if (barnTunnels.second.size() == 1) {
            farmersPriority.push_back(make_pair(barnTunnels.first, barnTunnels.first));
        }
    }
    // Sort all possible farmers in optimum positions
    for (pair<int, int>& farmer: farmersPriority)
        farmer = setFarmerPriority(farmer, k, tunnels);
    sort(farmersPriority.begin(), farmersPriority.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });
    sort(farmersPriority.begin(), farmersPriority.end());
    vector<int> fs;
    for (pair<int, int>& farmer: farmersPriority)
        fs.push_back(farmer.first);
    unordered_set<int> exits(fs.begin(), fs.end());

    // Binary search minimum farmers to catch bessie
    int lo = 1, hi = farmersPriority.size();
    while (lo < hi) {
        // Change amount of farmers
        int mid = lo + (hi - lo) / 2;
        unordered_set<int> farmers(fs.begin(), fs.begin() + mid);

        if (caughtBessy(k, farmers, exits, tunnels))
            hi = mid;
        else
            lo = mid + 1;
    }
    
    freopen("atlarge.out", "w", stdout);
    cout << lo << endl;

    return 0;
}

// Breadth first search shortest path length
pair<int, int> setFarmerPriority(pair<int, int>& farmer, int& goal, unordered_map<int, vector<int>>& tunnels) {
    unordered_set<int> visited;
    visited.insert(farmer.first);

    queue<int> q;
    q.push(farmer.first);

    // While there is a valid path or goal not reached
    for (int length = 0; !q.empty(); ++length) {
        const int qSize = q.size();
        for (int qNum = 0; qNum < qSize; ++qNum) {
            int barn = q.front();
            q.pop();

            if (barn == goal)
                return make_pair(farmer.first, length);

            // Traverse neighboring barns at the same time
            for (const int& nghbrBarn : tunnels[barn]) {
                if (visited.find(nghbrBarn) == visited.end()) {
                    visited.insert(nghbrBarn);
                    q.push(nghbrBarn);
                }
            }
        }
    }

    return make_pair(farmer.first, -1); // goal not found
}

bool caughtBessy(int& k, unordered_set<int>& blocked, unordered_set<int>& exits, unordered_map<int, vector<int>>& tunnels) {
    queue<int> farmers;
    for (const int& farmerBarn : blocked)
        farmers.push(farmerBarn);

    queue<int> bessie;
    bessie.push(k);
    blocked.insert(k);

    while (!bessie.empty()) {
        // Expand all farmer paths at once
        const int allFarmers = farmers.size();
        for (int fNum = 0; fNum < allFarmers; ++fNum) {
            int fBarn = farmers.front();
            farmers.pop();
            for (const int& nghbrBarn : tunnels[fBarn]) {
                farmers.push(nghbrBarn);
                blocked.insert(nghbrBarn);
            }
        }

        // Expand all bessie paths at once
        const int lvlPaths = bessie.size();
        for (int path = 0; path < lvlPaths; ++path) {
            int bBarn = bessie.front();
            bessie.pop();
            if (exits.find(bBarn) != exits.end())
                return false;   // bessie got away
            for (const int& nghbrBarn : tunnels[bBarn]) {
                if (blocked.find(nghbrBarn) == blocked.end()) {
                    bessie.push(nghbrBarn);
                    blocked.insert(nghbrBarn);
                }
            }
        }
    }

    return true;    // bessie caught
}
