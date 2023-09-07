# USACO 2017 January Contest, Silver
## Problem 1. Cow Dance Show

http://www.usaco.org/index.php?page=viewproblem2&cpid=690

After several months of rehearsal, the cows are just about ready to put on their annual dance 
performance; this year they are performing the famous bovine ballet "Cowpelia".

The only aspect of the show that remains to be determined is the size of the stage. A stage 
of size `K` can support `K` cows dancing simultaneously. The `N` cows in the herd `(1≤N≤10,000)` 
are conveniently numbered `1…N` in the order in which they must appear in the dance. Each 
cow i plans to dance for a specific duration of time d(i). Initially, cows `1…K` appear 
on stage and start dancing. When the first of these cows completes her part, she leaves 
the stage and cow `K+1` immediately starts dancing, and so on, so there are always `K` cows 
dancing (until the end of the show, when we start to run out of cows). The show ends when 
the last cow completes her dancing part, at time `T`.

Clearly, the larger the value of `K`, the smaller the value of `T`. Since the show cannot last 
too long, you are given as input an upper bound Tmax specifying the largest possible value 
of `T`. Subject to this constraint, please determine the smallest possible value of `K`.

INPUT FORMAT (file cowdance.in):
The first line of input contains `N` and `Tmax`, where `Tmax` is an integer of value at most 1 million.

The next `N` lines give the durations `d(1)…d(N)` of the dancing parts for cows `1…N`. Each `d(i)` 
value is an integer in the range `1…100,000`.

It is guaranteed that if K=N, the show will finish in time.

OUTPUT FORMAT (file cowdance.out):
Print out the smallest possible value of `K` such that the dance performance will take no more 
than `Tmax` units of time.

SAMPLE INPUT:
```
5 8
4
7
8
6
4
```
SAMPLE OUTPUT:
```
4
```

## Steps to Solve the Problem:

1. **Input Reading**:
   - Read the first line to obtain `N` (number of cows) and `Tmax` (maximum permissible duration of the show).
   - For the next `N` lines, retrieve each cow's dance duration and store them in a vector.

2. **Determine Stage Size Using Binary Search**:
   - Perform a binary search to identify the smallest possible stage size that adheres to the contract's time constraints.
     - Utilize a `Minimum Heap-Priority Queue` Algorithm to keep track of cows on stage and calculate total time elapsed to determine if within contract time limit:
       - Initialize a priority queue (Heap) with a capacity of `K` to represent the stage.
       - Rather than decrementing time for each dancing cow, monitor the elapsed time by adding the incoming cow's dance duration to the dance time of the cow that exits the stage (with the shortest dance time).
       - Maintain a record of the longest `MaxDance` duration to compute the total time spent on stage.

3. **Output Generation**:
   - Write the determined stage size value to the output file.


## Solution:

https://github.com/Reddimus/USACO_notes/tree/main/Binary_Search/Silver/P1_2017-Cow_Dance_Show

### Time Complexity: `O(n * log n)`
### Space Compleixty: `O(n)`
Where `n` is the number of cows.

#### Python Code:
```python
import heapq

# open input file
with open("cowdance.in") as r:
	# first line n = cows, t_max = maximum time for all cows to dance
	n, t_max = map(int, r.readline().split())
	# for the next n lines read each cow's dance time
	dances = [int(r.readline()) for ln in range(n)]

# k represents the size of the stage to support n amount of cows dancing
def within_contract(k):
	stage = dances[:k]
	heapq.heapify(stage)
	# elapse (heappop) shortest dance time and add next cow to dance
	for idx in range(k, n):
		min_dance = heapq.heappop(stage)
		heapq.heappush(stage, min_dance + dances[idx])
	return max(stage) <= t_max

# Search for smallest possible stage size within contract limit using binary search
lo, hi = 1, n
while lo < hi:
	mid = (lo + hi) // 2
	if not within_contract(k = mid):
		lo = mid + 1    # increase stage size to reduce time on stage and be within contract time limit
	else:
		hi = mid

# Write searched item into output file
print(hi, file=open("cowdance.out", "w"))
```


#### C++ Code:
```C++
#include <bits/stdc++.h>

using namespace std;

int n, tMax;
vector<int> dances;

// k represents the size of the stage to support n amount of cows dancing
bool withinContract(int k) {
	// heapify first k cows
	priority_queue<int, vector<int>, greater<int>> stage(dances.begin(), dances.begin() + k);
	// elapse shortest dance time (root) to open dance spot and add next cow to stage
	int maxDance = 0;
	for (int idx = k; idx < n; idx++) {
		int minDance = stage.top();
		stage.pop();
		stage.push(minDance + dances[idx]);
		maxDance = max(maxDance, minDance + dances[idx]);
	}
	// dance remaining cows on stage by searching max dance time
	return maxDance <= tMax;
}

int main() {
	// open input file
	ifstream fin("cowdance.in");
	// first line: n = number of cows, tMax = max stage time
	fin >> n >> tMax;
	// for next n lines, read in cow dance times
	for (int ln = 0; ln < n; ln++) {
		int t;
		fin >> t;
		dances.push_back(t);
	}
	fin.close();

	// Binary search for smallest possible stage size within contract time limit
	int lo = 1, hi = n;
	while (lo < hi) {
		int mid = lo + (hi - lo) / 2;
		if (!withinContract(mid))
			lo = mid + 1;   // increase stage size to reduce time on stage and be within contract time limit
		else
			hi = mid;
	}

	// write smallest possible stage size to output file
	ofstream pw("cowdance.out");
	pw << lo << endl;
	pw.close();
}
```

#### Java Code:
```Java
import java.io.*;
import java.util.*;

public class CowDanceShow {
	// Make values accessible by all methods
	private static int n, tMax;
	private static List<Integer> dances = new ArrayList<Integer>();

	// k represents the size of the stage to support n amount of cows dancing
	private static boolean withinContract(int k) {
		PriorityQueue<Integer> stage = new PriorityQueue<Integer>(dances.subList(0, k));
		int maxDance = 0;
		// elapse shortest dance time to open dance spot and add next cow to stage
		for (int idx = k; idx < n; idx++) {
			int minDance = stage.poll();
			maxDance = Math.max(maxDance, minDance + dances.get(idx));
			stage.add(minDance + dances.get(idx));
		}
		// elapse remaining dance time
		return maxDance <= tMax;
	}

	public static void main(String[] args) throws IOException {
		// open input file
		BufferedReader in = new BufferedReader(new FileReader("cowdance.in"));
		StringTokenizer st = new StringTokenizer(in.readLine());
		// first line: n = number of cows, tmax = max stage time
		n = Integer.parseInt(st.nextToken());
		tMax = Integer.parseInt(st.nextToken());
		// for the next n lines read each cow's dance time
		for (int i = 0; i < n; i++)
			dances.add(Integer.parseInt(in.readLine()));
		in.close();
		
		// Binary Search for smallest possible stage size within contract time limit
		int lo = 1, hi = n;
		while (lo < hi) {
			int mid  = lo + (hi - lo) / 2;
			if (!withinContract(mid))
				lo = mid + 1;   // increase stage size to reduce time on stage and be within contract time limit
			else
				hi = mid;
		}

		// Write smallest possible stage size to output file
		PrintWriter out = new PrintWriter("cowdance.out");
		out.println(hi);
		out.close();
	}
}
```