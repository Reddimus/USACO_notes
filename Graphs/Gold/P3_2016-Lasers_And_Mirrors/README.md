# [USACO 2016 December Contest, Gold](http://www.usaco.org/index.php?page=dec16results)
## [Problem 3. Lasers and Mirrors](http://www.usaco.org/index.php?page=viewproblem2&cpid=671)

For some reason, Farmer John's cows always seem to be running laser light shows.

For their latest show, the cows have procured a large powerful laser -- so large, in fact, that they cannot seem to move it easily from the location where it was delivered. They would like to somehow send the light from the laser to the barn on the other side of FJ's property. Both the laser and the barn can be considered to be located at points in the 2D plane on a map of FJ's farm. The cows plan to point the laser so that it sends a beam of light out either horizontally or vertically (i.e., aligned with the x or y axes). They will then bounce this beam off a number of mirrors to direct it to the barn.

On the farm there are `N` fence posts `(1≤N≤100,000)` located at distinct 2D points (also distinct from the laser and the barn) at which the cows can mount mirrors. The cows can choose not to mount a mirror on a fence post, in which case the laser would simply pass straight over the top of the post without changing direction. If the cows do mount a mirror on a fence post, they align it diagonally like / or \ so that it will re-direct a horizontal beam of light in a vertical direction or vice versa.

Please compute the minimum possible number of mirrors the cows need to use in order to re-direct the laser to the barn.

### INPUT FORMAT (file lasers.in):
The first line of input contains 5 space-separated integers: `N`, `x_L`, `y_L`, `x_B`, and `y_B`, where `(x_L,y_L)` is the location of the laser and `(x_B,y_B)` is the location of the barn. All coordinates are between `0` and `1,000,000,000`.

The next `N` lines each contain `x` and `y` locations of a fence post, both integers in the range `0…1,000,000,000`.

### OUTPUT FORMAT (file lasers.out):

Please output the minimum number of mirrors needed to direct the laser to the barn, or `-1` if this is impossible to do.

### SAMPLE INPUT
```
4 0 0 7 2
3 2
0 2
1 6
3 0
```

### SAMPLE OUTPUT
```
1
```

# [Solutions](https://github.com/Reddimus/USACO_notes/tree/main/Graphs/Gold/P3_2016-Lasers_And_Mirrors)

## Adjacency list graphs - Breadth-first search approach

### Steps
1. For the first line gather the number of mirrors, starting position, and goal.
    - n = number of mirrors/fence posts
    - x_L, y_L = starting position of laser
    - x_B, y_B = goal position of barn
2. For the next n lines, map the x & y coordinates of the mirrors/fence posts for quick lookup.
    - Structured with a hash map of x coordinates to a vector of y coordinates and vice versa.
3. Breadth-first search intercepting mirrors or goals.
    - Use a queue to store the coordinates of the mirrors/fence posts.
    - For each level of the queue, check if the current coordinate intercepts the goal. If so, break out of the loop and set the final count to the current level.
    - If not, find the intercepting mirrors/fence posts and add them to the queue.
    - Mark the current coordinate as visited by erasing it from the hash map.
4. Write -1 if no solution, else write the minimum number of mirrors.

### Time & Space complexity:
Time: `O(N)`
Space: `O(N)`

Where `N` is the number of fence posts/mirrors/vertices/nodes.

### C++ Code:
```cpp
#include <bits/stdc++.h>

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
    int count = -1;
    queue<coordinates> q;
    q.push(laser);
    for (int level = 0; !q.empty(); ++level) {
        const int qSize = q.size();
        for (int qNum = 0; qNum < qSize; ++qNum) {
            coordinates mirror = q.front();
            q.pop();

            // Check for goal
            if (mirror.x == barn.x || mirror.y == barn.y) {
                count = level;
                q = queue<coordinates>();   // Clear queue
                break;
            }

            // Find intercepting mirrors
            for (const int& y : xToY[mirror.x])
                q.push({mirror.x, y});
            for (const int& x : yToX[mirror.y])
                q.push({x, mirror.y});

            // Mark all mirrors/coordinates subset as visited
            xToY.erase(mirror.x),
            yToX.erase(mirror.y);
        }
    }

    // Write -1 if no solution, else write the minimum number of mirrors
    freopen("lasers.out", "w", stdout);
    cout << count << endl;

    return 0;
}
```

### Java Code:
```java
import java.io.*;
import java.util.*;

public class LasersMirrors {
    static class Coordinates {
        int x, y;
        Coordinates(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("lasers.in"));

        // First line: n = number of mirrors, laser coordinates, barn coordinates
        StringTokenizer st = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(st.nextToken());
        Coordinates laser = new Coordinates(
            Integer.parseInt(st.nextToken()), 
            Integer.parseInt(st.nextToken()));
        Coordinates barn = new Coordinates(
            Integer.parseInt(st.nextToken()), 
            Integer.parseInt(st.nextToken()));
        
        // For the next n lines, map mirror x & y coordinates for quick lookup
        Map<Integer, ArrayList<Integer>> xToY = new HashMap<>(), yToX = new HashMap<>();
        for (int mirror = 0; mirror < n; mirror++) {
            st = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(st.nextToken()), y = Integer.parseInt(st.nextToken());

            xToY.putIfAbsent(x, new ArrayList<>());
            xToY.get(x).add(y);

            yToX.putIfAbsent(y, new ArrayList<>());
            yToX.get(y).add(x);
        }
        in.close();

        // Breadth-first search intercepting mirrors or goals for shortest path
        int count = -1;
        Queue<Coordinates> q = new LinkedList<>();
        q.add(laser);
        for (int level = 0; !q.isEmpty(); ++level) {
            final int qSize = q.size();
            for (int qNum = 0; qNum < qSize; ++qNum) {
                Coordinates mirror = q.poll();

                // Check for goal
                if (mirror.x == barn.x || mirror.y == barn.y) {
                    count = level;
                    q = new LinkedList<>(); // Clear queue
                    break;
                }

                // Find intercepting mirrors
                for (int y : xToY.getOrDefault(mirror.x, new ArrayList<>()))
                    q.add(new Coordinates(mirror.x, y));
                for (int x : yToX.getOrDefault(mirror.y, new ArrayList<>()))
                    q.add(new Coordinates(x, mirror.y));

                // Mark all mirrors/coordinates subset as visited
                xToY.remove(mirror.x);
                yToX.remove(mirror.y); 
            }
        }

        // Write -1 if no solution, else write the minimum number of mirrors
        PrintWriter out = new PrintWriter("lasers.out");
        out.println(count);
        out.close();
    }
}
```