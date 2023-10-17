import java.util.*;
import java.io.*;

public class FruitFeast {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("feast.in"));
		// Read single line from input file
		// t = max fullness, a = orange fullness, b = lemon fullness
		StringTokenizer st = new StringTokenizer(in.readLine());
		int t = Integer.parseInt(st.nextToken());
		int a = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		in.close();

		// dp[drinkedWater?][fullness], where 1 = true, 0 = false
		boolean[][] dp = new boolean[2][t+1];
		dp[0][0] = true;	// base case 0 fullness
		for (int idx = 0; idx <= t; ++idx) {
			// Find fullness of orange(s) and lemon(s) without water
			if (0 <= idx - a)
				dp[0][idx] |= dp[0][idx-a];
			if (0 <= idx - b)
				dp[0][idx] |= dp[0][idx-b];
			// Find fullness after drinking water
			dp[1][idx/2] |= dp[0][idx];
		}

		// Using fullness after drinking water find new fullness
		// Find max fullness/last true fullness value
		int maxFullness = 0;
		for (int idx = 0; idx <= t; ++idx) {
			if (0 <= idx - a)
				dp[1][idx] |= dp[1][idx-a];
			if (0 <= idx - b)
				dp[1][idx] |= dp[1][idx-b];
			if (dp[1][idx])
				maxFullness = idx;
		}
		
		PrintWriter out = new PrintWriter("feast.out");
		out.println(maxFullness);
		out.close();
	}
}
