import java.io.*;
import java.util.*;

public class LifeGuards {
	static class Shift_Event implements Comparable<Shift_Event> {
		public int time, lifeguardID;
		public boolean isStart;
		
		public Shift_Event(int time, int lifeguardID, boolean isStart) {
			this.time = time;
			this.lifeguardID = lifeguardID;
			this.isStart = isStart;
		}

		// Override compareTo method to only compare times
		@Override
		public int compareTo(Shift_Event other) {
			return this.time - other.time;
		}
	}
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("lifeguards.in"));
		// First line: n = number of cow lifeguards
		int n = Integer.parseInt(br.readLine());
		// For the next n lines track start/end times + lifeguard IDs
		Shift_Event[] shifts = new Shift_Event[2 * n];
		for (int lg_id = 0; lg_id < n; lg_id++) {
			StringTokenizer st = new StringTokenizer(br.readLine());
			int start = Integer.parseInt(st.nextToken());
			int end = Integer.parseInt(st.nextToken());
			// Add start/end times to events list
			shifts[2*lg_id] = new Shift_Event(start, lg_id, false);
			shifts[2*lg_id+1] = new Shift_Event(end, lg_id, true);
		}

	}
}