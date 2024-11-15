#include <bits/stdc++.h>
#define MAX_PORTS 1001
#define MAX_SEQ 501

using namespace std;

// Floyd's cycle detection algorithm
// Time complexity: O(n * m + k)
// Space complexity: O(n)
int main() {
    // Read in first line: n = # of ports, m = size of sequence, k = # to repeat sequence
    freopen("cruise.in", "r", stdin);
    int n, m, k;
    cin >> n >> m >> k;
    // For the next n lines, map port graph
    // graph[i].first == left connection, graph[i].second == right connection
    pair<int, int> adjPair[MAX_PORTS];
    for (int portNum = 1; portNum <= n; portNum++)
        cin >> adjPair[portNum].first >> adjPair[portNum].second;
    // For the next m lines, record sequence of directions
    char seq[MAX_SEQ];
    for (int i = 0; i < m; i++)
        cin >> seq[i];

    // Compute nextPort for each port after applying the sequence once
    int nextPort[MAX_PORTS];
    for (int startPort = 1; startPort <= n; ++startPort) {
        int currPort = startPort;
        for (int i = 0; i < m; ++i) {
            if (seq[i] == 'L')
                currPort = adjPair[currPort].first;
            else
                currPort = adjPair[currPort].second;
        }
        nextPort[startPort] = currPort;
    }

    // Use Floyd's cycle detection algorithm to find cycle starting from port 1
    int slow = nextPort[1], fast = nextPort[nextPort[1]];
    while (slow != fast) {
        slow = nextPort[slow];
        fast = nextPort[nextPort[fast]];
    }

    // Find the starting point of the cycle
    slow = 1;
    while (slow != fast) {
        slow = nextPort[slow];
        fast = nextPort[fast];
    }
    int cycleStart = slow;

    // Find the length of the cycle
    int cycleLength = 1;
    fast = nextPort[slow];
    while (slow != fast) {
        fast = nextPort[fast];
        ++cycleLength;
    }

    // Calculate steps before entering the cycle
    int stepsToCycle = 0;
    int currPort = 1;
    while (currPort != cycleStart) {
        currPort = nextPort[currPort];
        ++stepsToCycle;
    }

    // Adjust k to account for the cycle
    if (k <= stepsToCycle) {
        // Simulate k steps
        currPort = 1;
        for (int i = 0; i < k; ++i) {
            currPort = nextPort[currPort];
        }
    } else {
        k -= stepsToCycle;
        k %= cycleLength;
        currPort = cycleStart;
        for (int i = 0; i < k; ++i) {
            currPort = nextPort[currPort];
        }
    }

    // Output the final port
    freopen("cruise.out", "w", stdout);
    cout << currPort << endl;
    return 0;
}

/*
// Simulate Solution
// Time complexity: O(k * m)
// Space complexity: O(1) (excluding input)
int main() {
    // Read in first line: n = # of ports, m = size of sequence, k = # to repeat sequence
	freopen("cruise.in", "r", stdin);
    int n, m, k;
    cin >> n >> m >> k;
    // For the next n lines, map port graph
    // graph[i].first == left connection, graph[i].second == right connection
    pair<int, int> adjPair[MAX_PORTS];
    for (int portNum = 1; portNum <= n; portNum++)
        cin >> adjPair[portNum].first >> adjPair[portNum].second;
    // For the next m lines, record sequence
    char seq[MAX_SEQ];
    for (int i = 0; i < m; i++)
        cin >> seq[i];
    
    int currPort = 1;
    // Repeat sequence k times
    for (int i = 0; i < k; ++i) {
        // Traverse through sequence of directions
        for (int j = 0; j < m; ++j) {
            if (seq[j] == 'L')  // If left, go to left connection
                currPort = adjPair[currPort].first;
            else    // Go to right connection
                currPort = adjPair[currPort].second;
        }
    }

    // Output final port
    freopen("cruise.out", "w", stdout);
    cout << currPort << endl;
    return 0;
}
*/