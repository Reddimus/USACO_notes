// Breadth First Search (BFS) | Flood fill Graph approach
// T & M: O(n^2) where n is the side length of the grid

import java.io.*;
import java.util.*;

public class IcyPerimeter {
	static int n;
	static char[][] graph;
	static int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("perimeter.in"));
		// First line: n = sides of graph
		n = Integer.parseInt(in.readLine());
		// For the next n lines read n sized strings representing ice cream blob graph
		graph = new char[n][n];
		for (int r = 0; r < n; ++r)
			graph[r] = in.readLine().toCharArray();
		in.close();

		int[] maxBlob = new int[]{0, n + 1};	// {area, perimeter}
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < n; ++c) {
				// Group blobs into their own components and update largest blob
				if (graph[r][c] == '#') {
					int[] blob = bfs(r, c);
					// Update blob to largest area then smallest perimeter
					if (maxBlob[0] < blob[0] ||
					(maxBlob[0] == blob[0] && maxBlob[1] > blob[1]))
						maxBlob = blob;
				}
			}
		}

		// Write largest blob with smallest perimeter to output file
		PrintWriter out = new PrintWriter("perimeter.out");
		out.println(maxBlob[0] + " " + maxBlob[1]);
		out.close();
	}

	// Breadth First Search (BFS) perimeter and area of blob
	private static int[] bfs(int r, int c) {
		int area = 1, perimeter = 0;
		graph[r][c] = ' ';	// mark as visited
		Queue<int[]> q = new LinkedList<int[]>();
		q.add(new int[]{r, c});
		while (!q.isEmpty()) {
			int[] qd = q.poll();

			for (int[] d : directions) {
				int ar = qd[0] + d[0], ac = qd[1] + d[1];
				// If adjacent row/col outside of blob
				if (ar < 0 || ar >= n || 
				ac < 0 || ac >= n || 
				graph[ar][ac] == '.') {
					++perimeter;
				}
				// Else if adjacent row/col is part of the same blob component
				else if (graph[ar][ac] == '#') {
					++area;
					graph[ar][ac] = ' ';
					q.add(new int[]{ar, ac});
				}
			}
		}

		return new int[]{area, perimeter};
	}
}