#include <bits/stdc++.h>

#define N_MAX 101

using namespace std;

int main() {
    freopen("mowing.in", "r", stdin);
    int n;
    cin >> n;
    pair<char, int> instructions[N_MAX];
    for (int i = 0; i < n; i++)
        cin >> instructions[i].first >> instructions[i].second;

    pair<int, int> currCord = {0, 0};
    map<pair<int, int>, int> visited;
    int time = 0;
    int maxRegrow = INT_MAX;

    // Process each movement command
    for (auto [direction, steps] : instructions) {
        // Determine movement delta based on direction
        int dx = 0, dy = 0;
        switch (direction) {
            case 'N':
                dy = 1;
                break;
            case 'S':
                dy = -1;
                break;
            case 'E':
                dx = 1;
                break;
            case 'W':
                dx = -1;
                break;
        }

        // Move in the specified direction for numSteps
        for (int si = 0; si < steps; si++) {
            currCord.first += dx;
            currCord.second += dy;
            time++;

            // Check if the cell was visited before
            if (visited.find(currCord) != visited.end()) {
                int lastVisitTime = visited[currCord];
                maxRegrow = min(maxRegrow, time - lastVisitTime);
            }

            // Update the last visit time for the current cell
            visited[currCord] = time;
        }
    }

    // Output the result, -1 if no revisit occurred
    freopen("mowing.out", "w", stdout);
    cout << (maxRegrow != INT_MAX ? maxRegrow : -1) << endl;
    return 0;
}
