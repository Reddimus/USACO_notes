// Graphs - Minimum Spanning Tree (MST) approach
// T: O(n^2), M: O(n), where n is the number of cows

import java.io.*;
import java.util.*;

class DisjointSetUnion {
	// Initialize nodes to single sized node graphs
	private int[] parents, sizes;
	public DisjointSetUnion(int n) {
		sizes = new int[n];
		Arrays.fill(sizes, 1);
		parents = new int[n];
		for (int node = 0; node < n; ++node) 
			parents[node] = node;
	}

	// Recursively find and assign parent of current node (path compression)
	private int findParent(int v) {
		if (parents[v] == v) 
			return v;
		return findParent(parents[v]);
	}

	// Attempt to union two components
	public boolean unionComponents(int a, int b) {
		a = findParent(a);
		b = findParent(b);
		if (a == b) // If nodes are already in same component
			return false;
		// Union by size optimization
		if (sizes[a] < sizes[b]) {
			int temp = a;
			a = b;
			b = temp;
		}
		// Merge smaller component (b) into larger component (a)
		parents[b] = a;
		sizes[a] += sizes[b];
		return true;
	}
}

public class MooCast {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("moocast.in"));
		// First line: n = number of cows
		int n = Integer.parseInt(in.readLine());
		// For the next n lines read in coordinates of cows
		StringTokenizer st;
		int[][] coordinates = new int[n][2];
		for (int idx = 0; idx < n; ++idx) {
			st = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			coordinates[idx] = new int[]{x, y};
		}
		in.close();

		// Store edges and calculated distance between cows
		List<int[]> edges = new ArrayList<>();
		for (int i = 0; i < n - 1; ++i) {
			// Calculate distance between cow i and all other cows
			for (int j = i + 1; j < n; ++j) {
				int dx = coordinates[i][0] - coordinates[j][0];
				int dy = coordinates[i][1] - coordinates[j][1];
				edges.add(new int[]{i, j, (dx * dx) + (dy * dy)});
			}
		}

		// Sort edges by their distance
		Collections.sort(edges, (a, b) -> a[2] - b[2]);

		// Union closest cows until all cows are connected
		int lastDistance = 0;
		DisjointSetUnion dsu = new DisjointSetUnion(n);
		for (int[] e : edges) {
			if (dsu.unionComponents(e[0], e[1])) {
				lastDistance = e[2];
				if (--n == 1) 	// If all cows are connected
					break;
			}
		}

		// The distance of the last unioned edge is the minimum amount to spend
		PrintWriter out = new PrintWriter("moocast.out");
		out.println(lastDistance);
		out.close();
	}
}