// Depth First Search (DFS) | Flood Fill Graph approach
// T & M: O(n^2), where n is the side length of the grid

import java.io.*;
import java.util.*;

public class CowCrossIII {
	private static class Road {
		int sr, sc, er, ec;
		Road(int sr, int sc, int er, int ec) {
			this.sr = sr;
			this.sc = sc;
			this.er = er;
			this.ec = ec;
		}

		@Override
		public int hashCode() {
			return Objects.hash(sr, sc, er, ec);
		}

		@Override
		public boolean equals(Object o) {
			if (!(o instanceof Road)) { return false; }
			Road r = (Road)o;
			return sr == r.sr && sc == r.sc && er == r.er && ec == r.ec;
		}
	}

	private static int n, k, r;
	private static Set<Road> roads = new HashSet<>();
	private static boolean[][] cows, visited;

	// Depth first search number of cows that can be reached without crossing a road
	private static int dfs(int r, int c, int prevR, int prevC) {
		if (r < 0 || n <= r ||
		c < 0 || n <= c ||
		visited[r][c] ||
		roads.contains(new Road(r, c, prevR, prevC)))
			return 0;

		visited[r][c] = true;
		int cowCount = cows[r][c] ? 1 : 0;

		return (cowCount +
		dfs(r + 1, c, r, c) +
		dfs(r - 1, c, r, c) +
		dfs(r, c + 1, r, c) +
		dfs(r, c - 1, r, c));
	}

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("countcross.in"));
		// Read in first line: n = grid side length, k = # of cows, r = # of roads
		StringTokenizer st = new StringTokenizer(in.readLine());
		n = Integer.parseInt(st.nextToken());
		k = Integer.parseInt(st.nextToken());
		r = Integer.parseInt(st.nextToken());
		// Read in start (r, c) and end (r', c') positions of two-way roads
		for (int ln = 0; ln < r; ++ln) {
			st = new StringTokenizer(in.readLine());
			int sr = Integer.parseInt(st.nextToken()) - 1;
			int sc = Integer.parseInt(st.nextToken()) - 1;
			int er = Integer.parseInt(st.nextToken()) - 1;
			int ec = Integer.parseInt(st.nextToken()) - 1;
			roads.add(new Road(sr, sc, er, ec));
			roads.add(new Road(er, ec, sr, sc));
		}
		// Read in start (r, c) positions of cows
		cows = new boolean[n][n];
		for (int ln = 0; ln < k; ++ln) {
			st = new StringTokenizer(in.readLine());
			int cr = Integer.parseInt(st.nextToken()) - 1;
			int cc = Integer.parseInt(st.nextToken()) - 1;
			cows[cr][cc] = true;
		}

		visited = new boolean[n][n];

		// Group size of cow components to calculate distant pairs
		List<Integer> cowComponents = new ArrayList<>();
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < n; ++c) {
				int cowCount = dfs(r, c, r, c);
				if (cowCount > 0)
					cowComponents.add(cowCount);
			}
		}

		// Sum product of pairs from distinct cow groups for distant pairs
		int distantPairs = 0;
		for (int i = 0; i < cowComponents.size(); ++i)
			for (int j = i + 1; j < cowComponents.size(); ++j)
				distantPairs += cowComponents.get(i) * cowComponents.get(j);

		// Write number of distant pairs to output file
		PrintWriter out = new PrintWriter("countcross.out");
		out.println(distantPairs);
		out.close();
	}
}
