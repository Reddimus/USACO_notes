import java.io.*;
import java.util.*;

public class CircularBarn {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("cbarn.in"));

		// Read in total number of rooms (N)
		final int N = Integer.parseInt(br.readLine());

		// Read in the number of cows in each room
		int[] rooms = new int[N];
		for (int i = 0; i < N; ++i)
			rooms[i] = Integer.parseInt(br.readLine());
		
		br.close();

		// Try each room as the first room to unlock
		int minDist = Integer.MAX_VALUE;
		for (int unlock = 0; unlock < N; ++unlock) {
			// Calculate the distance for this unlock
			int dist = 0;
			for (int r = 0; r < N; ++r)
				dist += rooms[(unlock + r) % N] * r;
			minDist = Math.min(minDist, dist);
		}

		PrintWriter out = new PrintWriter("cbarn.out");
		out.println(minDist);
		out.close();
	}
}
