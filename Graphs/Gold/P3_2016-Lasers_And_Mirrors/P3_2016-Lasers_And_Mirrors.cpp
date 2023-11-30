// Adjacency list graphs - Breadth-first search approach
// T & M: O(n), where n is the number of fence posts/vertices/nodes.

// #include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

int main() {
    struct coordinates {int x, y;};

    freopen("lasers.in", "r", stdin);
    // First line: n = number of mirrors, laser coordinates, barn coordinates
    int n;
    coordinates laser, barn;
    cin >> n >> laser.x >> laser.y >> barn.x >> barn.y;
    
    // For the next n lines, map mirror x & y coordinates for quick lookup
    unordered_map<int, vector<int>> xToY, yToX;
    for (int mirror = 0; mirror < n; ++mirror) {
        int x, y;
        cin >> x >> y;
        xToY[x].push_back(y), yToX[y].push_back(x);
    }

    // Breadth-first search intercepting mirrors or goals for shortest path
    int finalCount = -1;
    queue<coordinates> q;
    q.push(laser);
    for (int level = 0; !q.empty(); ++level) {
        const int qSize = q.size();
        for (int qNum = 0; qNum < qSize; ++qNum) {
            coordinates mirror = q.front();
            q.pop();

            // Check for goal
            if (mirror.x == barn.x || mirror.y == barn.y) {
                finalCount = level;
                q = queue<coordinates>();   // Clear queue
                break;
            }

            // Find intercepting mirrors
            for (const int& y : xToY[mirror.x])
                q.push({mirror.x, y});
            for (const int& x : yToX[mirror.y])
                q.push({x, mirror.y});

            // Mark current mirror/coordinate as visited
            xToY.erase(mirror.x),
            yToX.erase(mirror.y);
        }
    }

    // Write -1 if no solution, else write the minimum number of mirrors
    freopen("lasers.out", "w", stdout);
    cout << finalCount << endl;

    return 0;
}