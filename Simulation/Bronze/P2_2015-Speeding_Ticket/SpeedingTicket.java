import java.util.*;
import java.io.*;

public class SpeedingTicket {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("speeding.in"));

		final int ROAD_LENGTH = 100;

		// Read first line: n = road segments, m = bessie's segments
		StringTokenizer st = new StringTokenizer(in.readLine());
		final int n = Integer.parseInt(st.nextToken());
		final int m = Integer.parseInt(st.nextToken());

		// For the next n lines read in road segments
		int[] speedLimits = new int[ROAD_LENGTH];
		int lastPosition = 0;
		for (int ln = 0; ln < n; ++ln) {
			st = new StringTokenizer(in.readLine());
			final int length = Integer.parseInt(st.nextToken());
			final int speedLim = Integer.parseInt(st.nextToken());

			for (int idx = lastPosition; idx < lastPosition + length; ++idx) 
				speedLimits[idx] = speedLim;
			
			lastPosition += length;
		}

		// For the next m lines read in Bessie's segments
		int[] bessieSpeed = new int[ROAD_LENGTH];
		int lastPos = 0;
		for (int ln = 0; ln < m; ++ln) {
			st = new StringTokenizer(in.readLine());
			final int length = Integer.parseInt(st.nextToken());
			final int speed = Integer.parseInt(st.nextToken());

			for (int idx = lastPos; idx < lastPos + length; ++idx)
				bessieSpeed[idx] = speed;

			lastPos += length;
		}

		in.close();

		// For the length of the road, find the max difference between speed limits and Bessie's speed
		int maxOver = 0;
		for (int idx = 0; idx < ROAD_LENGTH; ++idx)
			maxOver = Math.max(maxOver, bessieSpeed[idx] - speedLimits[idx]);
		
		// Write the max over speed to the output file
		PrintWriter out = new PrintWriter("speeding.out");
		out.println(maxOver);
		out.close();
	}
}