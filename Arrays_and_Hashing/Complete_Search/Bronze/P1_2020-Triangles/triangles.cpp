#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("triangles.in", "r", stdin);
    // Read 1st line: n = Distinct points
    int n;
    cin >> n;
    
    // For the next n lines, read in x and y coordinates
    unordered_map<int, vector<int>> horizontalIntersects, verticalIntersects;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;

        horizontalIntersects[y].push_back(x);
        verticalIntersects[x].push_back(y);
    }

    // Find all possible triangles
    int maxArea = 0;
    for (const auto& [yBase, xBases] : horizontalIntersects) {
        for (int i = 0; i < xBases.size() - 1; i++) {
            for (int j = i + 1; j < xBases.size(); j++) {
                const int baseLength = abs(xBases[i] - xBases[j]);

                // Find the height/area of the triangle from each base point
                for (const int yHeight : verticalIntersects[xBases[i]])
                    maxArea = max(maxArea, baseLength * abs(yHeight - yBase));
                for (const int yHeight : verticalIntersects[xBases[j]])
                    maxArea = max(maxArea, baseLength * abs(yHeight - yBase));
            }
        }
    }

    freopen("triangles.out", "w", stdout);
    cout << maxArea << endl;
    return 0;
}