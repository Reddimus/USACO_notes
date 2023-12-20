import java.io.*;
import java.util.*;

public class CircularBarn {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("cbarn2.in"));
		/// Read first line: n = rooms, k = unlocked exterior doors
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		// For the next n lines, read in the number of desired cows in each room (r_i)
		Deque<Integer> rooms = new ArrayDeque<Integer>();
		for (int i = 0; i < n; ++i)
			rooms.add(Integer.parseInt(in.readLine()));
		in.close();

		// // print rooms deque
		// System.out.println("rooms deque: " + rooms);

		long minDist = Long.MAX_VALUE;
		// Rotate through all the starting position of the rooms for each dp table
		for (int startPos = 0; startPos < n; ++startPos) {
			long[][] dp = new long[k+1][n+1];
			for (long[] row : dp)
				Arrays.fill(row, Long.MAX_VALUE);
			dp[0][n] = 0;	// 0 doors unlocked base case

			Integer[] roomsArr = rooms.toArray(new Integer[0]);	// Make rotated rooms callable by index
			// Iterate through number of doors used
			for (int unlockedDoors = 1; unlockedDoors <= k; ++unlockedDoors) {
				// Iterate through all possible number of doors unlocked
				for (int newDoorPos = 0; newDoorPos < n; ++newDoorPos) {
					if (unlockedDoors >= k && newDoorPos >= 1)
						break;
					// Calculate distance for rooms between new and last door
					long partialDist = 0;
					// Loop through last door positions
					for (int lastDoorPos = newDoorPos + 1; lastDoorPos <= n; ++lastDoorPos) {
						// Add distance needed to fill the new room at lastDoorPos - 1
						partialDist += roomsArr[lastDoorPos - 1] * (lastDoorPos - newDoorPos - 1);
						long newDist = dp[unlockedDoors - 1][lastDoorPos];
						if (newDist < Long.MAX_VALUE)
							newDist += partialDist;
						dp[unlockedDoors][newDoorPos] = Math.min(dp[unlockedDoors][newDoorPos], newDist);

						// // print dp table
						// // System.out.println("dp table at startPos " + startPos + ", unlockedDoors " + unlockedDoors + ", newDoorPos " + newDoorPos + ", lastDoorPos " + lastDoorPos + 
						// System.out.println("dp table at startPos = " + startPos + ", unlockedDoors = " + unlockedDoors + ", newDoorPos = " + newDoorPos + ", lastDoorPos = " + lastDoorPos);
						// // print column headers
						// System.out.print("\t\t\t");
						// for (int DoorPos = 0; DoorPos <= n; ++DoorPos)
						// 	System.out.print("DPos" + DoorPos + "\t");
						// System.out.println();
						// // print dp table
						// for (int unlockedD = 0; unlockedD <= k; ++unlockedD) {
						// 	System.out.print("unlocked " + unlockedD + ": \t");
						// 	for (int DoorPos = 0; DoorPos <= n; ++DoorPos) {
						// 		if (dp[unlockedD][DoorPos] == Long.MAX_VALUE)
						// 			System.out.print("inf\t");
						// 		else
						// 			System.out.print(dp[unlockedD][DoorPos] + "\t");
						// 	}
						// 	System.out.println();
						// }
						// System.out.println();
					}
				}
			}
			// Update the best answer using the current dp with current starting position
			minDist = Math.min(minDist, dp[k][0]);
			// Rotate first room to end
			rooms.add(rooms.removeFirst());

			// System.out.println("minDist = min(minDist, dp[" + k + "][0]) = min(" + minDist + ", " + dp[k][0] + ")" + "= " + minDist);
			// System.out.println("rooms deque: " + rooms);
		}

		// Write the minDist accross all starting positions, with all possible doors unlocked
		PrintWriter out = new PrintWriter("cbarn2.out");
		out.println(minDist);
		out.close();
	}
}
