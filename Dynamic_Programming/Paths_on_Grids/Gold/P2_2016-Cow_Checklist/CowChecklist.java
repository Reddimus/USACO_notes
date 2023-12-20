// Paths on Grids + 3-D Dynamic Programming approach
// T&M: O(h * g), where h = Holsteins, g = Guernseys

import java.io.*;
import java.util.*;

public class CowChecklist {
	static class Coordinates {
		final int x, y;
		Coordinates(int x, int y) {
			this.x = x;
			this.y = y;
		}
	}

	// Find the distance between two points then square it
	private static final long energy(final Coordinates a, final Coordinates b) {
		final int xDist = a.x - b.x, yDist = a.y - b.y;
		return (xDist * xDist) + (yDist * yDist);
	}

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("checklist.in"));
		// Read first line input: h = Holstein num, g = guernseys num
		StringTokenizer st = new StringTokenizer(in.readLine());
		int h = Integer.parseInt(st.nextToken());
		int g = Integer.parseInt(st.nextToken());
		// For the next H lines then next G lines read breed coordinates
		Coordinates hs[] = new Coordinates[h];
		for (int idx = 0; idx < h; ++idx){
			st = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			hs[idx] = new Coordinates(x, y);
		}
		Coordinates gs[] = new Coordinates[g];
		for (int idx = 0; idx < g; ++idx){
			st = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			gs[idx] = new Coordinates(x, y);
		}
		in.close();

		// dp[h+1][g+1][2] filled with MAX values to solve for min dist across breeds
		// where hIdx = 0 are dummy values, & gIdx = 0 are base cases/dummy values
		// Where the 3rd dimension is 0 = Holstein, 1 = Guernsey
		long dp[][][] = new long[h+1][g+1][2];
		for (long[][] hArr : dp) {
			for (long[] gArr : hArr) {
				Arrays.fill(gArr, Integer.MAX_VALUE);
			}
		}
		dp[1][0][0] = 0;	// Base case: Start with 0 distance at first holstein cow
		for (int hIdx = 1; hIdx <= h; ++hIdx) {
			for (int gIdx = 0; gIdx <= g; ++gIdx) {
				// Check neigbouring holsteins distances
				if (1 < hIdx) {
					dp[hIdx][gIdx][0] = 
						Math.min(dp[hIdx][gIdx][0], 
								dp[hIdx-1][gIdx][0] + energy(hs[hIdx-2], hs[hIdx-1]));
				}
				// Check neigbouring guernseys distances
				if (1 < gIdx) {
					dp[hIdx][gIdx][1] = 
						Math.min(dp[hIdx][gIdx][1], 
								dp[hIdx][gIdx-1][1] + energy(gs[gIdx-2], gs[gIdx-1]));
				}
				// Check across breeds distances
				if (0 < hIdx && 0 < gIdx) {
					final long crossEnergy = energy(hs[hIdx-1], gs[gIdx-1]);
					dp[hIdx][gIdx][0] = 
						Math.min(dp[hIdx][gIdx][0], dp[hIdx-1][gIdx][1] + crossEnergy);
					dp[hIdx][gIdx][1] = 
						Math.min(dp[hIdx][gIdx][1], dp[hIdx][gIdx-1][0] + crossEnergy);
				}
			}
		}

		// Answer must end with last holstein cow
		PrintWriter out = new PrintWriter("checklist.out");
		out.println(dp[h][g][0]);
		out.close();
	}
}
