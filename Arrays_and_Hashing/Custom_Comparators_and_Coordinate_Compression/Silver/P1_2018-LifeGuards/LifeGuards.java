// Custom Comparators + Sorting + Sweep Line Approach
// T: O(n log n), M: O(n), where n is amount of shifts

import java.io.*;
import java.util.*;

public class LifeGuards {
	
	static class ShiftEvent {
		public int time, lifeguardID;
		public boolean isStart;
		
		public ShiftEvent(int time, int lifeguardID, boolean isStart) {
			this.time = time;
			this.lifeguardID = lifeguardID;
			this.isStart = isStart;
		}
	}

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("lifeguards.in"));
		// First line: n = number of cow lifeguards
		int n = Integer.parseInt(br.readLine());
		// For the next n lines track start/end times + lifeguard IDs (id is based on idx)
		ShiftEvent[] shifts = new ShiftEvent[2 * n];
		for (int idx = 0; idx < n; idx++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int start = Integer.parseInt(st.nextToken());
			int end = Integer.parseInt(st.nextToken());
			shifts[2*idx] = new ShiftEvent(start, idx, true);
			shifts[2*idx+1] = new ShiftEvent(end, idx, false);
		}
		br.close();

		// Sort events by time only
		Arrays.sort(shifts, Comparator.comparingInt(a -> a.time));

		int totalTime = 0, prevTime = 0;
		int[] aloneTime = new int[n];			// idx is lifeguard id, value is total alone time
		Set<Integer> onDuty = new HashSet<Integer>();	// tracked by lifeguard id
		// iterate through shift events calculating result using sweep line approach
		for (ShiftEvent se : shifts) {
			if (onDuty.size() == 1)
				aloneTime[onDuty.iterator().next()] += se.time - prevTime;

			if (onDuty.size() > 0)
				totalTime += se.time - prevTime;

			if (se.isStart)
				onDuty.add(se.lifeguardID);
			else
				onDuty.remove(se.lifeguardID);

			prevTime = se.time;
		}

		// Write total time - life guard with least alone time to output file
		PrintWriter out = new PrintWriter("lifeguards.out");
		out.println(totalTime - Arrays.stream(aloneTime).min().getAsInt());
		out.close();
	}
}
