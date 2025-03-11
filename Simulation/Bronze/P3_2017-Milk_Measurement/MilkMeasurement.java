import java.io.*;
import java.util.*;

class MilkMeasurement {
	// Bucket sort approach
	// T: O(N), M: O(101 * 3 + 3) ≈ O(1)
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("measurement.in"));
		// First line: N == number of milk production changes
		final int N = Integer.parseInt(in.readLine());
		// For the next N lines read in cow timestamp, cow name, and current milk production change
		int bessieTimestamp[] = new int[101];
		int elsieTimestamp[] = new int[101];
		int mildredTimestamp[] = new int[101];
		int firstTimestamp = 101, lastTimestamp = 0;
		for (int i = 0; i < N; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			int timestamp = Integer.parseInt(st.nextToken());
			String cow = st.nextToken();
			int change = Integer.parseInt(st.nextToken());
			
			switch (cow) {
				case "Bessie":
					bessieTimestamp[timestamp] += change;
					break;
				case "Elsie":
					elsieTimestamp[timestamp] += change;
					break;
				case "Mildred":
					mildredTimestamp[timestamp] += change;
					break;
			}

			firstTimestamp = Math.min(firstTimestamp, timestamp);
			lastTimestamp = Math.max(lastTimestamp, timestamp);
		}
		in.close();

		int displayChanges = 0;
		Set<Character> leadCows = new HashSet<>(List.of('B', 'E', 'M'));
		// For each milk production change
		int bessieMilk = 7, elsieMilk = 7, mildredMilk = 7;
		for (int i = firstTimestamp; i <= lastTimestamp; ++i) {
			if (bessieTimestamp[i] == 0 &&
			elsieTimestamp[i] == 0 &&
			mildredTimestamp[i] == 0)
				continue;

			// Re-calculate the milk production for each cow change
			bessieMilk += bessieTimestamp[i];
			elsieMilk += elsieTimestamp[i];
			mildredMilk += mildredTimestamp[i];

			int maxMilk = Math.max(bessieMilk, Math.max(elsieMilk, mildredMilk));
			Set<Character> currentLeadCows = new HashSet<>();
			if (bessieMilk == maxMilk)
				currentLeadCows.add('B');
			if (elsieMilk == maxMilk)
				currentLeadCows.add('E');
			if (mildredMilk == maxMilk)
				currentLeadCows.add('M');

			// If the lead cows have changed, increment the display changes
			if (!currentLeadCows.equals(leadCows)) {
				++displayChanges;
				leadCows = currentLeadCows;
			}
		}

		// Write the amount of display changes to the output file
		PrintWriter out = new PrintWriter("measurement.out");
		out.println(displayChanges);
		out.close();
	}
}