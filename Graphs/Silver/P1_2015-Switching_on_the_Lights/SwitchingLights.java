// Graphs - Breadth First Search (DFS) | Flood fill approach
// T & M: O(n^2 + m) 
// Where n is the number of rows and columns in the switches graph and m is the number of switches

import java.io.*;
import java.util.*;

public class SwitchingLights {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("lightson.in"));
		// First line: n = graph side length, m = # of switches
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		// For the next m lines map x, y room to room a, b that can be lit
		ArrayList<int[]>[][] switches = (ArrayList<int[]>[][]) new ArrayList[n][n];
		for (int r = 0; r < n; ++r)
			for (int c = 0; c < n; ++c) 
				switches[r][c] = new ArrayList<int[]>();
		for (int ln = 0; ln < m; ++ln) {
			st = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(st.nextToken()) - 1;
			int y = Integer.parseInt(st.nextToken()) - 1;
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			switches[x][y].add(new int[] {a, b});
		}
		in.close();
		
		int litCount = 1;
		int[][] directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
		boolean[][] seen = new boolean[n][n], lit = new boolean[n][n];
		lit[0][0] = true;
		Queue<int[]> q = new LinkedList<int[]>();
		q.add(new int[] {0, 0});

		// Breadth First Search (BFS) lit rooms
		while (!q.isEmpty()) {
			int[] qdIdxs = q.poll();
			final int r = qdIdxs[0], c = qdIdxs[1];
			if (seen[r][c])
				continue;
			seen[r][c] = true;

			// Turn on new lights of current room
			for (int[] swIdxs : switches[r][c]) {
				final int sr = swIdxs[0], sc = swIdxs[1];
				if (lit[sr][sc])
					continue;
				lit[sr][sc] = true;
				++litCount;
				// Check if the newly lit room can be connected and hasn't been visited
				for (int[] d : directions) {
					final int asr = sr + d[0], asc = sc + d[1];
					if ((-1 < asr && asr < n) &&
					(-1 < asc && asc < n) &&
					seen[asr][asc] &&
					!seen[sr][sc])
						q.add(swIdxs);
				}
			}

			// Explore valid adjacent rooms
			for (int[] d : directions) {
				final int ar = r + d[0], ac = c + d[1];
				if ((-1 < ar && ar < n) &&
				(-1 < ac && ac < n) &&
				lit[ar][ac] &&
				!seen[ar][ac])
					q.add(new int[]{ar, ac});
			}
		}

		// Write number of lit rooms accessible from (1, 1) to output file
		PrintWriter out = new PrintWriter("lightson.out");
		out.println(litCount);
		out.close();
	}
}
