// Graphs - Flood Fill/Depth First Search approach
// T & M: O(n^2 + x * y)
// Where n is the number of steps Farmer John takes and x & y are the number of steps between the min and max x/y coordinates of the fence.

import java.io.*;
import java.util.*;

public class BuildGates {
	private static int minX, minY, maxX, maxY;
	private static boolean[][] fences;

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("gates.in"));
		int n = Integer.parseInt(in.readLine());	// Number of steps
		String moves = in.readLine();	// Directions of steps (North, East, South, West)
		in.close();

		// Initialize starting position and set of fence coordinates
		int sides = n * 4 + 1;
		int x = sides / 2, y = sides / 2;
		minX = sides - 1;
		minY = sides - 1;
		maxX = 0;
		maxY = 0;
		fences = new boolean[sides][sides];
		fences[y][x] = true;

		// Track fence positions based on Farmer John's movements
		Map<Character, int[]> directions = new HashMap<>();
		directions.put('N', new int[] {0, -1});	// Move up 1 row in 2-D array
		directions.put('E', new int[] {1, 0});
		directions.put('S', new int[] {0, 1});	// Move down 1 row in 2-D array
		directions.put('W', new int[] {-1, 0});
		for (char m : moves.toCharArray()) {
			// Scale movements by 2 steps to view smallest regions
			x += directions.get(m)[0];
			y += directions.get(m)[1];
			fences[y][x] = true;
			x += directions.get(m)[0];
			y += directions.get(m)[1];
			fences[y][x] = true;
			minX = Math.min(minX, x);
			minY = Math.min(minY, y);
			maxX = Math.max(maxX, x);
			maxY = Math.max(maxY, y);
		}

		// Expand boundaries to include outer region surrounding the fence
		--minX;
		--minY;
		++maxX;
		++maxY;

		// Find number of regions our fence graph is split into
		seen = new boolean[sides][sides];
		int regions = 0;
		for (int r = minY; r <= maxY; ++r) {
			for (int c = minX; c <= maxX; ++c) {
				if (!seen[r][c] && !fences[r][c]) {
					dfs(c, r);
					++regions;
				}
			}
		}

		// Every region inside the fences needs a gate
		PrintWriter out = new PrintWriter("gates.out");
		out.println(regions - 1);
		out.close();
	}

	// Flood-fill/depth first search for current component
	private static boolean[][] seen;
	public static void dfs(int x, int y) {
		if (x < minX || maxX < x ||
		y < minY || maxY < y ||
		seen[y][x] || 
		fences[y][x]) 
			return;

		seen[y][x] = true;

		dfs(x + 1, y);
		dfs(x - 1, y);
		dfs(x, y + 1);
		dfs(x, y - 1);
	}
}
