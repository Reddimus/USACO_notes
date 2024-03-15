// Flood Fill - Depth First Search approach
// T: O(N^6 + |PCLs|^2), M: O(N^2)
// Where `N` is side length of the N x N image

import java.io.*;
import java.util.*;

class PCL {
	public int r1, c1;
	public int r2, c2;

	public PCL(int r1, int c1, int r2, int c2) {
		this.r1 = r1;
		this.c1 = c1;
		this.r2 = r2;
		this.c2 = c2;
	}

	public boolean isInside(PCL other) {
		return r1 >= other.r1 && c1 >= other.c1 && r2 <= other.r2 && c2 <= other.c2;
	}
}

public class WheresBessie {
	private static int n;
	private static char[][] image;
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("where.in"));
		// Read first line: n = side length of the N x N image
		n = Integer.parseInt(in.readLine());
		// For the next N lines read in image descriptions
		image = new char[n][n];
		for (int i = 0; i < n; i++) 
			image[i] = in.readLine().toCharArray();
		in.close();

		// Brute force all possible subrectangles
		List<PCL> pcls = new ArrayList<PCL>();
		for (int r1 = 0; r1 < n; ++r1) 
			for (int c1 = 0; c1 < n; ++c1) 
				for (int r2 = r1; r2 < n; ++r2) 
					for (int c2 = 0; c2 < n; ++c2) 
						if (isPCL(r1, c1, r2, c2)) 
							pcls.add(new PCL(r1, c1, r2, c2));
		
		// Filter out overlapping PCLs & count the number of valid PCLs
		int pclCount = 0;
		for (PCL iPCL : pcls) {
			boolean validPCL = true;
			for (PCL jPCL : pcls) {
				if (iPCL != jPCL && iPCL.isInside(jPCL)) {
					validPCL = false;
					break;
				}
			}
			if (validPCL) 
				++pclCount;
		}

		PrintWriter out = new PrintWriter("where.out");
		out.println(pclCount);
		out.close();
	}

	// Check wheter the given sub rectangle is a PCL
	private static boolean isPCL(int r1, int c1, int r2, int c2) {
		// keep track of number of color components
		int[] regionCount = new int[26];

		// Update shared variables for flood fill function
		visited = new boolean[n][n];
		rMin = r1; rMax = r2; cMin = c1; cMax = c2;	
		// Within the sub rectangle, flood fill each color component
		for (int r = rMin; r <= rMax; ++r) {
			for (int c = cMin; c <= cMax; ++c) {
				if (!visited[r][c]) {
					char color = image[r][c];
					floodFill(r, c, color);
					++regionCount[color - 'A'];
				}
			}
		}

		// Determine if the sub rectangle is a PCL
		int colorCount = 0;
		boolean singleRegion = false, multiRegion = false;
		for (int i = 0; i < 26 && colorCount <= 2; ++i) {
			if (regionCount[i] == 0) 
				continue;

			if (regionCount[i] == 1) 
				singleRegion = true;
			else if (regionCount[i] > 1) 
				multiRegion = true;
			++colorCount;
		}
		return colorCount == 2 && singleRegion && multiRegion;
	}

	private static boolean[][] visited;
	private static int rMin, rMax, cMin, cMax;
	// Depth first search common color within sub rectangle boundaries
	private static void floodFill(int r, int c, char color) {
		if (r < rMin || r > rMax ||
		c < cMin || c > cMax ||
		image[r][c] != color ||
		visited[r][c]) 
			return;
		
		visited[r][c] = true;

		floodFill(r + 1, c, color);
		floodFill(r - 1, c, color);
		floodFill(r, c + 1, color);
		floodFill(r, c - 1, color);
	}
}
