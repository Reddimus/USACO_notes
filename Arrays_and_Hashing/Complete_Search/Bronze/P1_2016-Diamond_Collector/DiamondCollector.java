import java.io.*;
import java.util.*;

// Sliding window approach
// T: O(n log n), S: O(1) if not counting the input array
public class DiamondCollector {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("diamond.in"));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[] diamonds = new int[n];
		for (int i = 0; i < n; i++)
			diamonds[i] = Integer.parseInt(fin.readLine());
		fin.close();

		// Sort the array of diamond sizes
		Arrays.sort(diamonds);

		int most = 0;
		int start = 0;

		// Sliding window approach
		for (int end = 0; end < n; end++) {
			// Expand the window until the range is valid
			while (diamonds[end] - diamonds[start] > k)
				start++; // Shrink the window from the left
			// Update the maximum number of fittable diamonds
			most = Math.max(most, end - start + 1);
		}

		PrintWriter fout = new PrintWriter("diamond.out");
		fout.println(most);
		fout.close();
	}
}
