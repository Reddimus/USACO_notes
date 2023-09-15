// Custom Comparator Sorting approach
// T: O(nlogn), M: O(n), where n is the number of mountains

import java.io.*;
import java.util.*;

public class MountainView {
	static class Mountain {
		int xInit, xFinal;
		Mountain(int xInit, int xFinal) {
			this.xInit = xInit;
			this.xFinal = xFinal;
		}
	}

	public static void main(String[] args) throws IOException {
		// Read input file
		BufferedReader in = new BufferedReader(new FileReader("mountains.in"));
		// Read first line: n = number of mountains
		int n = Integer.parseInt(in.readLine());
		// For the next n lines calculate the xi, xf coordinates of each mountain
		Mountain[] mountains = new Mountain[n];
		for (int ln = 0; ln < n; ln++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			mountains[ln] = new Mountain(x-y, x+y);
		}
		in.close();

		// sort by first appearing mountains and biggest mountains
		Arrays.sort(mountains, Comparator.comparingInt((Mountain m) -> m.xInit).thenComparingInt(m -> -m.xFinal));

		// Count how many visible peaks Bessie can see
		int visible = 1;
		Mountain prevBiggest = mountains[0];
		for (Mountain mountain : mountains) {
			if (mountain.xFinal > prevBiggest.xFinal) {
				visible++;
				prevBiggest = mountain;
			}
		}

		// Write amount of visible peaks to output file
		PrintWriter out = new PrintWriter("mountains.out");
		out.println(visible);
		out.close();
	}
}


/*
// Custom Comparator and Coordinate Compression approach
// T: O(nlogn), M: O(n), where n is the number of mountains

import java.io.*;
import java.util.*;

public class MountainView {
	static class Mountain {
		int xInit, xFinal;
		Mountain(int xInit, int xFinal) {
			this.xInit = xInit;
			this.xFinal = xFinal;
		}
	}

	public static void main(String[] args) throws IOException {
		// Read input file
		BufferedReader in = new BufferedReader(new FileReader("mountains.in"));
		// Read first line: n = number of mountains
		int n = Integer.parseInt(in.readLine());
		// For the next n lines calculate the xi, xf coordinates of each mountain
		HashMap<Integer, Integer> seenXinit = new HashMap<Integer, Integer>();
		ArrayList<Mountain> mountains = new ArrayList<>();
		for (int ln = 0; ln < n; ln++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			if (!seenXinit.containsKey(x-y)) {
				seenXinit.put(x-y, mountains.size());
				mountains.add(new Mountain(x-y, x+y));
			}
			// Forget about the smaller mountain (compress data) 
			else {
				int prevIdx = seenXinit.get(x-y);
				mountains.get(prevIdx).xFinal = Math.max(mountains.get(prevIdx).xFinal, x+y);
			}
		}
		in.close();

		// Sort mountains by first appearing mountains only
		Collections.sort(mountains, Comparator.comparingInt((Mountain m) -> m.xInit));

		// Count how many visible peaks Bessie can see
		int visible = 1;
		Mountain prevBiggest = mountains.get(0);
		for (Mountain mountain : mountains) {
			if (mountain.xFinal > prevBiggest.xFinal) {
				visible++;
				prevBiggest = mountain;
			}
		}

		// Write amount of visible peaks to output file
		PrintWriter out = new PrintWriter("mountains.out");
		out.println(visible);
		out.close();
	}
}
*/