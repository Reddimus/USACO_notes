import java.io.*;
import java.util.*;

// Sliding window approach
// T: O(n log n), S: O(1) if not counting the input array
public class DiamondCollector {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("diamond.in"));
		// Read in 1st line: N = # of diamonds, K = max difference in size
		StringTokenizer st = new StringTokenizer(fin.readLine());
		final int N = Integer.parseInt(st.nextToken());
		final int K = Integer.parseInt(st.nextToken());
		// For the next N lines, read in the sizes of the diamonds
		int[] diamonds = new int[N];
		for (int i = 0; i < N; i++)
			diamonds[i] = Integer.parseInt(fin.readLine());
		fin.close();

		// Sort the array of diamond sizes
		Arrays.sort(diamonds);

		int most = 0;
		int start = 0;

		// Sliding window approach; Expand the window from the right
		for (int end = 0; end < N; end++) {
			while (diamonds[end] - diamonds[start] > K)
				start++; // Shrink the window from the left
			// Update the maximum number of fittable diamonds
			most = Math.max(most, end - start + 1);
		}

		PrintWriter fout = new PrintWriter("diamond.out");
		fout.println(most);
		fout.close();
	}
}
