// 3-Dimensional Dynamic Programming approach
// T&M: O(n*k), where n is the number of games and k is the number of switches

import java.io.*;
import java.util.*;

public class HPS {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("hps.in"));
		// Read first line: n = num of gestures, k = num of gesture switches
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		// For the next n lines store gestures into a list
		int[] gestures = new int[n];
		for (int idx = 0; idx < n; ++idx) {
			char gesture = in.readLine().charAt(0);
			if (gesture == 'H') {
				gestures[idx] = 0;
			} else if (gesture == 'P') {
				gestures[idx] = 1;
			} else {
				gestures[idx] = 2;
			}
		}
		in.close();
		
		// Initialize 3D dp arr to store the maximum number of wins for each state 
		// dp[n][k+1][3] = dp[nIdx][kIdx][g]
		// where nIdx is the current game number, kIdx represents the current number of switches, and g represents the current gesture in the dp array
		int[][][] dp = new int[n][k + 1][3];
		for (int nIdx = 0; nIdx < n; ++nIdx) {
			for (int kIdx = 0; kIdx <= k; ++kIdx) {
				for (int g = 0; g < 3; ++g) {
					// Increment score if current gesture wins in this round
					if (g == gestures[nIdx]) {
						++dp[nIdx][kIdx][g];
					}
					
					if (nIdx + 1 < n) {
						if (kIdx + 1 <= k) {
							// Update future state if a switch is made
							// if at least one switch is available, then the max wins of the next state is the max wins of the current state plus the current gesture
							dp[nIdx + 1][kIdx + 1][0] = Math.max(dp[nIdx + 1][kIdx + 1][0], dp[nIdx][kIdx][g]);
							dp[nIdx + 1][kIdx + 1][1] = Math.max(dp[nIdx + 1][kIdx + 1][1], dp[nIdx][kIdx][g]);
							dp[nIdx + 1][kIdx + 1][2] = Math.max(dp[nIdx + 1][kIdx + 1][2], dp[nIdx][kIdx][g]);
						}
						// Update future state without a switch
						dp[nIdx + 1][kIdx][g] = Math.max(dp[nIdx + 1][kIdx][g], dp[nIdx][kIdx][g]);
					}
				}
			}
		}
		
		// Write the accumlated max wins of the last game to the output file
		int maxWins = Math.max(dp[n - 1][k][0], Math.max(dp[n - 1][k][1], dp[n - 1][k][2]));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("hps.out")));
		out.println(maxWins);
		out.close();
	}
}
