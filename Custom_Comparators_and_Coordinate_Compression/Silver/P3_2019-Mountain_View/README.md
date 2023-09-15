# USACO 2019 January Contest, Silver
## Problem 3. Mountain View

http://www.usaco.org/index.php?page=viewproblem2&cpid=896

### Problem Description
From her pasture on the farm, Bessie the cow has a wonderful view of a mountain range on the horizon. There are N mountains in the range `(1≤N≤10^5)`. If we think of Bessie's field of vision as the xy plane, then each mountain is a triangle whose base rests on the x axis. The two sides of the mountain are both at 45 degrees to the base, so the peak of the mountain forms a right angle. Mountain i is therefore precisely described by the location `(xi,yi)` of its peak. No two mountains have exactly the same peak location.

Bessie is trying to count all of the mountains, but since they all have roughly the same color, she cannot see a mountain if its peak lies on or within the triangular shape of any other mountain.

Please determine the number of distinct peaks, and therefore mountains, that Bessie can see.

### INPUT FORMAT (file mountains.in)
The first line of input contains N. Each of the remaining N lines contains xi `(0≤xi≤10^9)` and yi `(1≤yi≤10^9)` describing the location of one mountain's peak.

### OUTPUT FORMAT (file mountains.out)
Please print the number of mountains that Bessie can distinguish.

### SAMPLE INPUT
```
3
4 6
7 2
2 5
```

### SAMPLE OUTPUT
```
2
```

### Explanation
In this example, Bessie can see the first and last mountain. The second mountain is obscured by the first.

# Solutions:

https://github.com/Reddimus/USACO_notes/tree/main/Custom_Comparators_and_Coordinate_Compression/Silver/P3_2019-Mountain_View

### Intuition
We want to count the first mountain and the visably bigger mountains. The tricky part is the fact that Bessie cannot see a mountain if its peak lies on or within the triangular shape of any other mountain. This means if we calculate the x initial/start `(xi)` and x final/end `(xf)` of a mountain and they have the same xi value, we can only count the bigger mountain.

The way to calculate `(xi)` and `(xf)` is by using parts of traingle geometry formulas. Using the peak point of a mountain of a triagle with two 45 degree angles and a 90 degree angle. 

After gathering all the information needed we simply sort the mountains by their `(xi)` value. Then we loop through the mountains and count the first mountain and the visably bigger mountains using by either coordinate compression or comparing the `(xf)` value of the current mountain and the previous mountain.

## Custom Comparator Sorting Solution

### Steps
1. Read the input file and store mountain(s) data
	- Read first line: `n = number of mountains`
	- For the next `n` lines calculate the `xi`, `xf` coordinates of each mountain. When given the right triangle point we can find the remaining 45 degree angle points by using the `xi = x - y` and `xf = x + y` formulas.
2. Sort mountains by first appearing mountains and biggest mountains
3. Count the first mountain and the visably bigger mountains
	- If the current mountain's `xf` value is bigger than the previous biggest mountain's `xf` value, the current mountain is bigger and count it as visable.
	- In cases where curr `xi` == prev `xi`, we can only count the bigger mountain. This is because Bessie cannot see 1 of the 2 mountains if its peak lies on the trainglular shape of the other mountain.
4. Write number of visable mountains to `mountains.out` output file

### Time & Space complexity:
Time: `O(NlogN)`\
Space: `O(N)`

Where `N` is the number of mountains.

### Python Code:
```python
class Mountain:
	def __init__(self, x_init: int, x_final: int) -> None:
		self.x_init = x_init
		self.x_final = x_final

# Read input file
with open('mountains.in', 'r') as f:
	# Read first line: n = number of mountains
	n = int(f.readline())
	# For the next n lines calculate the xi, xf coordinates of each mountain
	mountains = []
	for ln in range(n):
		x, y = map(int, f.readline().split())
		mountains.append(Mountain(x-y, x+y))

# sort by first appearing mountains and biggest mountains
mountains.sort(key=lambda m: (m.x_init, -m.x_final))

# Count how many visible peaks Bessie can see
visible = 1
prev_biggest = mountains[0]
for mountain in mountains:
	if mountain.x_final > prev_biggest.x_final:
		visible += 1
		prev_biggest = mountain

# Write amount of visible peaks to output file
print(visible, file=open('mountains.out', 'w'))
```

### C++ Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	// Read input file
	freopen("mountains.in", "r", stdin);
	// Read first line: n = number of mountains
	int n;
	cin >> n;
	// For the next n lines calculate the xi, xf coordinates of each mountain
	struct Mountain { int xInit, xFinal; };
	vector<Mountain> mountains(n);
	for (int ln = 0; ln < n; ln++) {
		int x, y;
		cin >> x >> y;
		mountains[ln].xInit = x-y, mountains[ln].xFinal = x+y;
	}

	// sort by first appearing mountains and biggest mountains
	sort(mountains.begin(), mountains.end(), 
		[](Mountain &a, Mountain &b) {
			if (a.xInit != b.xInit)
				return a.xInit < b.xInit;
			return a.xFinal > b.xFinal;
		});
	
	// Count how many visible peaks Bessie can see
	int visible = 1;
	Mountain prevBiggest = mountains[0];
	for (Mountain mountain : mountains) {
		if (mountain.xFinal > prevBiggest.xFinal) {
			++visible;
			prevBiggest = mountain;
		}
	}

	// Write amount of visible peaks to output file
	freopen("mountains.out", "w", stdout);
	cout << visible << endl;
}
```

### Java Code:
```java
import java.io.*;
import java.util.*;

public class MountainView {
	static class Mountain {
		int xInit, xFinal;
		Mountain(int xInit, int xFinal) {
			this.xInit = xInit;
			this.xFinal = xFinal;
		}
	}

	public static void main(String[] args) throws IOException {
		// Read input file
		BufferedReader in = new BufferedReader(new FileReader("mountains.in"));
		// Read first line: n = number of mountains
		int n = Integer.parseInt(in.readLine());
		// For the next n lines calculate the xi, xf coordinates of each mountain
		Mountain[] mountains = new Mountain[n];
		for (int ln = 0; ln < n; ln++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			mountains[ln] = new Mountain(x-y, x+y);
		}
		in.close();

		// sort by first appearing mountains and biggest mountains
		Arrays.sort(mountains, Comparator.comparingInt((Mountain m) -> m.xInit).thenComparingInt(m -> -m.xFinal));

		// Count how many visible peaks Bessie can see
		int visible = 1;
		Mountain prevBiggest = mountains[0];
		for (Mountain mountain : mountains) {
			if (mountain.xFinal > prevBiggest.xFinal) {
				visible++;
				prevBiggest = mountain;
			}
		}

		// Write amount of visible peaks to output file
		PrintWriter out = new PrintWriter("mountains.out");
		out.println(visible);
		out.close();
	}
}
```

## Custom Comparators and Coordinate Compression Solution

### Steps
1. Read the input file and store mountain(s) data
	- Read first line: `n = number of mountains`
	- For the next `n` lines calculate the `xi`, `xf` coordinates of each mountain. When given the right triangle point we can find the remaining 45 degree angle points by using the `xi = x - y` and `xf = x + y` formulas.
	- If we find mountains with duplicate `xi` values, we can forget about the smaller mountain. This is because Bessie cannot see 1 of the 2 mountains if its peak lies on the trainglular shape of the other mountain.
2. Sort mountains by first appearing mountains.
3. Count the first mountain and the visably bigger mountains
	- If the current mountain's `xf` value is bigger than the previous biggest mountain's `xf` value, the current mountain is bigger and count it as visable.
	- There are no cases where curr `xi` == prev `xi` due to earlier coordinate compression.
4. Write number of visable mountains to `mountains.out` output file

### Time & Space complexity:
Time: `O(NlogN)`\
Space: `O(N)`

Where `N` is the number of mountains.

### Python Code:
```python
class Mountain:
	def __init__(self, x_init: int, x_final: int) -> None:
		self.x_init = x_init
		self.x_final = x_final

# Read input file
with open('mountains.in', 'r') as f:
	# Read first line: n = number of mountains
	n = int(f.readline())
	# For the next n lines calculate the xi, xf coordinates of each mountain
	mountains = {}
	for ln in range(n):
		x, y = map(int, f.readline().split())
		if x-y not in mountains:
			mountains[x-y] = Mountain(x-y, x+y)
		else:	# forget about the smaller mountain (compress data)
			xf = max(mountains[x-y].x_final, x+y)
			mountains[x-y] = Mountain(x-y, xf)

# sort mountains by first appearing mountains
mountains = list(mountains.values())
mountains.sort(key=lambda m: m.x_init)

# Count how many visible peaks Bessie can see
visible = 1
prev_biggest = mountains[0]
for mountain in mountains:
	if mountain.x_final > prev_biggest.x_final:
		visible += 1
		prev_biggest = mountain

# Write amount of visible peaks to output file
print(visible, file=open('mountains.out', 'w'))
```

### C++ Code:
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
	// Read input file
	freopen("mountains.in", "r", stdin);
	// Read first line: n = number of mountains
	int n;
	cin >> n;
	// For the next n lines calculate the xi, xf coordinates of each mountain
	struct Mountain { int xInit, xFinal; };
	unordered_map<int, int> seenXInit;
	vector<Mountain> mountains;
	for (int ln = 0; ln < n; ln++) {
		int x, y;
		cin >> x >> y;
		if (seenXInit.find(x-y) == seenXInit.end()) {
			seenXInit[x-y] = mountains.size();
			mountains.push_back({x-y, x+y});
		}
		// Forget about the smaller mountain (compress data)
		else {
			int prevIdx = seenXInit[x-y];
			mountains[prevIdx].xFinal = max(mountains[prevIdx].xFinal, x+y);
		}
	}

	// sort by first appearing mountains and biggest mountains
	sort(mountains.begin(), mountains.end(), 
		[](Mountain &a, Mountain &b) {
			if (a.xInit != b.xInit)
				return a.xInit < b.xInit;
			return a.xFinal > b.xFinal;
		});
	
	// Count how many visible peaks Bessie can see
	int visible = 1;
	Mountain prevBiggest = mountains[0];
	for (Mountain mountain : mountains) {
		if (mountain.xFinal > prevBiggest.xFinal) {
			++visible;
			prevBiggest = mountain;
		}
	}

	// Write amount of visible peaks to output file
	freopen("mountains.out", "w", stdout);
	cout << visible << endl;
}
```

### Java Code:
```java
import java.io.*;
import java.util.*;

public class MountainView {
	static class Mountain {
		int xInit, xFinal;
		Mountain(int xInit, int xFinal) {
			this.xInit = xInit;
			this.xFinal = xFinal;
		}
	}

	public static void main(String[] args) throws IOException {
		// Read input file
		BufferedReader in = new BufferedReader(new FileReader("mountains.in"));
		// Read first line: n = number of mountains
		int n = Integer.parseInt(in.readLine());
		// For the next n lines calculate the xi, xf coordinates of each mountain
		HashMap<Integer, Integer> seenXinit = new HashMap<Integer, Integer>();
		ArrayList<Mountain> mountains = new ArrayList<>();
		for (int ln = 0; ln < n; ln++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			if (!seenXinit.containsKey(x-y)) {
				seenXinit.put(x-y, mountains.size());
				mountains.add(new Mountain(x-y, x+y));
			}
			// Forget about the smaller mountain (compress data) 
			else {
				int prevIdx = seenXinit.get(x-y);
				mountains.get(prevIdx).xFinal = Math.max(mountains.get(prevIdx).xFinal, x+y);
			}
		}
		in.close();

		// Sort mountains by first appearing mountains only
		Collections.sort(mountains, Comparator.comparingInt((Mountain m) -> m.xInit));

		// Count how many visible peaks Bessie can see
		int visible = 1;
		Mountain prevBiggest = mountains.get(0);
		for (Mountain mountain : mountains) {
			if (mountain.xFinal > prevBiggest.xFinal) {
				visible++;
				prevBiggest = mountain;
			}
		}

		// Write amount of visible peaks to output file
		PrintWriter out = new PrintWriter("mountains.out");
		out.println(visible);
		out.close();
	}
}
```