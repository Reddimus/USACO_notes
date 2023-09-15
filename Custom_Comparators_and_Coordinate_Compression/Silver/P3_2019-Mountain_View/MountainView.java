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
// CORRECT BUT MEMORY LIMIT EXCEEDED
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
		HashMap<Integer, Mountain> mnts = new HashMap<Integer, Mountain>();
		for (int ln = 0; ln < n; ln++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());
			if (!mnts.containsKey(x-y)) {
				mnts.put(x-y, new Mountain(x-y, x+y));
			}
			// Forget about the smaller mountain (compress data) 
			else if (x+y > mnts.get(x-y).xFinal) {
				int xf = Math.max(mnts.get(x-y).xFinal, x+y);
				mnts.put(x-y, new Mountain(x-y, xf));
			}
		}
		in.close();

		// sort mountains by first appearing mountains only
		Mountain[] mountains = new Mountain[n];
		int idx = 0;
		for (Mountain m : mnts.values()) {
			mountains[idx] = m;
			idx++;
		}
		mnts = null;
		Arrays.sort(mountains, Comparator.comparingInt(m -> m.xInit));

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
*/