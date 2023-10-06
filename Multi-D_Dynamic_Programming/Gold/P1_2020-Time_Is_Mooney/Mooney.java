// 2-D Dynamic Programming + Graph Traversal approach
// T: O(maxDays * n * m), M: O(maxDays * n)
// Where n = num cities, m = num of one way roads, maxDays = 1000

import java.io.*;
import java.util.*;

public class Mooney {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("time.in"));

		// First line: n = num cities, m = num of one way roads, c = cost multiplier
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());

		// Second line: moonies[i] = moonies earned in city i
		int[] moonies = new int[n];
		st = new StringTokenizer(in.readLine());
		for (int cityIdx = 0; cityIdx < n; ++cityIdx)
			moonies[cityIdx] = Integer.parseInt(st.nextToken());

		// For the next m lines create adjacency list for one way roads between cities
		// index = city, value(s) = cities it connects to
		ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
		for (int cityIdx = 0; cityIdx < n; ++cityIdx)
			adj.add(new ArrayList<Integer>());
		for (int ln = 0; ln < m; ++ln) {
			st = new StringTokenizer(in.readLine());
			int city1 = Integer.parseInt(st.nextToken()) - 1;
			int city2 = Integer.parseInt(st.nextToken()) - 1;
			adj.get(city1).add(city2);
		}
		in.close();

		// dp[day][city], where maxDays = 1000
		int dp[][] = new int[1001][n];
		for (int[] row : dp)
			Arrays.fill(row, -1);
		dp[0][0] = 0;	// base case
		
		// For each day, stockpile moonies in each city visited using one way roads
		int maxMoony = 0;
		for (int day = 0; day <= 1000; ++day) {
			for (int city = 0; city < n; ++city) {
				if (dp[day][city] != -1) {
					for (int nextCity : adj.get(city))
						dp[day+1][nextCity] = Math.max(dp[day+1][nextCity], dp[day][city] + moonies[nextCity]);
				}
			}

			// We are only looking for maxMoony that loops back to city 1
			if (dp[day][0] != -1) {
				int tempMoony = dp[day][0] - (c * day * day);
				// If all potential maxMoony values have been calculated, break
				if (tempMoony < 0 && maxMoony != 0)
					break;
				maxMoony = Math.max(maxMoony, tempMoony);
			}
		}

		// Write maxMoony generated from visiting cities to output file
		PrintWriter out = new PrintWriter("time.out");
		out.println(maxMoony);
		out.close();
	}
}