// 1-D Dynamic Programming w/ vector + Bottom-Up Approach
// T: O(n*k), M: O(n)
// Where n is the number of cows and k is the max size of team(s)

import java.io.*;
import java.util.*;

public class Teamwork {
	public static void main(String[] args) throws IOException {
		// Open input file
		BufferedReader in = new BufferedReader(new FileReader("teamwork.in"));
		// Read First line: n = num of cows, k = max size of team(s)
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());

		// Stockpile the sum of max skills by checking every possible team size
		int skills[] = new int[n];
		int dp[] = new int[n];
		for (int rIdx = 0; rIdx < n; ++rIdx) {
			// For the next n lines store cow's skill
			skills[rIdx] = Integer.parseInt(in.readLine());
			// Constantly update the max skill of the current team
			int maxSkill = skills[rIdx];
			for (int lIdx = rIdx; 0 <= lIdx; --lIdx) {
				int currSize = rIdx - lIdx + 1;
				if (currSize > k)
					break;
				maxSkill = Math.max(maxSkill, skills[lIdx]);
				// Check if there is a previous team
				if (lIdx > 0)
					dp[rIdx] = Math.max(dp[rIdx], dp[lIdx - 1] + maxSkill * currSize);
				else
					dp[rIdx] = Math.max(dp[rIdx], maxSkill * currSize);
			}
		}
		in.close();

		// Print stockpiled sum of max skills to output file
		PrintWriter out = new PrintWriter("teamwork.out");
		out.println(dp[n - 1]);
		out.close();
	}
}
