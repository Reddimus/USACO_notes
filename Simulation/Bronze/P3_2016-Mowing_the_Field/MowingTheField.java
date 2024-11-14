import java.util.*;
import java.io.*;

class Coordinate {
	public int x, y;

	public Coordinate(int x, int y) {
		this.x = x;
		this.y = y;
	}

	@Override
	public int hashCode() {
		return Objects.hash(x, y);
	}

	@Override
	public boolean equals(Object obj) {
		return obj instanceof Coordinate && x == ((Coordinate)obj).x && y == ((Coordinate)obj).y;
	}
}

public class MowingTheField {

	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("mowing.in"));

		final int N = Integer.parseInt(in.readLine());
		char[] directions = new char[N];  // Array for directions
		int[] steps = new int[N];         // Array for steps

		// Read directions and steps using StringTokenizer
		for (int i = 0; i < N; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			directions[i] = st.nextToken().charAt(0);  // Read direction as char
			steps[i] = Integer.parseInt(st.nextToken());  // Read steps as int
		}
		in.close();

		// FJ's starting position is (0, 0)
		Coordinate curr = new Coordinate(0, 0);
		// Map to record the last time each cell was visited
		HashMap<Coordinate, Integer> visits = new HashMap<>(Map.of(curr, 0));

		int time = 0;
		int maxRegrow = Integer.MAX_VALUE;

		// Process each movement command
		for (int i = 0; i < N; i++) {
			int dx = 0, dy = 0;

			// Determine movement delta based on direction
			switch (directions[i]) {
				case 'N': dy = 1; break;
				case 'S': dy = -1; break;
				case 'E': dx = 1; break;
				case 'W': dx = -1; break;
			}

			// Move in the specified direction for numSteps
			for (int j = 0; j < steps[i]; j++) {
				curr = new Coordinate(curr.x + dx, curr.y + dy);
				time++;

				// Check if the cell was visited before
				if (visits.containsKey(curr)) {
					int lastVisitTime = visits.get(curr);
					maxRegrow = Math.min(maxRegrow, time - lastVisitTime);
				}

				// Update the last visit time for the current cell
				visits.put(new Coordinate(curr.x, curr.y), time);
			}
		}

		// Output result, -1 if no revisit occurred
		PrintWriter out = new PrintWriter(new FileWriter("mowing.out"));
		out.println(maxRegrow == Integer.MAX_VALUE ? -1 : maxRegrow);
		out.close();
	}
}
