import java.io.*;
import java.util.*;

public class Div7 {
	// Prefix sums - Array approach
	// T: O(n), M: O(1), where n is the number of cows
	public static void main(String[] args) throws IOException {
		// Open input file
		BufferedReader in = new BufferedReader(new FileReader("div7.in"));
		// First line: n = num of cows
		int n = Integer.parseInt(in.readLine());
		// For the next n lines create curr/temp prefix sum mod 7 variable
		int currModPS = 0;	// current mod 7 prefix sum
		int bestPhoto = 0;
		// Track first occurence of mod 7 prefix sum values; any value % 7 has 7 possible values
		int[] firstOcc = new int[7];
		Arrays.fill(firstOcc, -1);
		firstOcc[0] = 0;
		for (int idx = 0; idx < n; idx++) {
			currModPS = (currModPS + Integer.parseInt(in.readLine())) % 7;

			// Update first occurence list if mod 7 prefix sum not in first occurences list
			if (firstOcc[currModPS] == -1)
				firstOcc[currModPS] = idx;
			// Update best photo if pair exists in first occurences list
			else
				bestPhoto = Math.max(bestPhoto, idx - firstOcc[currModPS]);
		}
		in.close();

		// Write updated best photo to div7 output file
		PrintWriter out = new PrintWriter("div7.out");
		out.println(bestPhoto);
		out.close();
	}

	/*
	// Prefix sums - HashMap approach
	// T: O(n), M: O(1), where n is the number of cows
	public static void main(String[] args) throws IOException {
		// Open input file
		BufferedReader in = new BufferedReader(new FileReader("div7.in"));
		// First line: n = num of cows
		int n = Integer.parseInt(in.readLine());
		// For the next n lines create curr/temp prefix sum mod 7 variable
		int bestPhoto = 0;
		int currModPS = 0;
		Map<Integer, int[]> modMap = new HashMap<>();	// map mod 7'ed prefix sums; up to 7 possible values
		for (int idx = 0; idx < n; idx++) {
			currModPS = (currModPS + Integer.parseInt(in.readLine())) % 7;

			// Update best photo if pair exists
			if (modMap.containsKey(currModPS)) {
				modMap.get(currModPS)[1] = idx;
				bestPhoto = Math.max(bestPhoto, modMap.get(currModPS)[1] - modMap.get(currModPS)[0]);
			} else {
				modMap.put(currModPS, new int[]{idx, idx});
			}
		}

		// Write updated best photo to div7 output file
		PrintWriter pw = new PrintWriter("div7.out");
		pw.println(bestPhoto);
		pw.close();
	}
	*/

	/*
	// Prefix sums - Dictionary expanded approach
	// T: O(n), M: O(n), where n is the number of cows
	public static void main(String[] args) throws IOException {
		// Open input file
		BufferedReader in = new BufferedReader(new FileReader("div7.in"));
		// First line: n = num of cows
		int n = Integer.parseInt(in.readLine());
		// For the next n lines create prefix sums array
		long[] prefix_sums = new long[n + 1];
		for (int idx = 1; idx <= n; idx++) {
			prefix_sums[idx] = prefix_sums[idx - 1] + Integer.parseInt(in.readLine());
		}
		in.close();
		// System.out.println(Arrays.toString(prefix_sums));

		// mod 7 prefix sums array
		int[] mod_prefix_sums = new int[n];
		for (int idx = 0; idx < n; idx++) {
			mod_prefix_sums[idx] = (int) (prefix_sums[idx + 1] % 7);
		}
		// System.out.println(Arrays.toString(mod_prefix_sums));

		// Map mod 7 prefix sums to their first and last indices
		Map<Integer, List<Integer>> modMap = new HashMap<>();	// map mod 7'ed prefix sums; up to 7 possible values
		for (int idx = 0; idx < n; idx++) {
			int mod_num = mod_prefix_sums[idx];
			if (mod_num < 0)
				System.out.println("mod_num: " + mod_num + " idx: " + idx);
			if (!modMap.containsKey(mod_num)) {
				modMap.put(mod_num, new ArrayList<>());
			}
			modMap.get(mod_num).add(idx);
		}
		// System.out.println(modMap);

		// Find best/largest photo
		int bestPhoto = 0;
		for (Map.Entry<Integer, List<Integer>> entry : modMap.entrySet()) {
			List<Integer> idx_list = entry.getValue();
			bestPhoto = Math.max(bestPhoto, idx_list.get(idx_list.size() - 1) - idx_list.get(0));
		}

		// Write updated best photo to div7 output file
		PrintWriter pw = new PrintWriter("div7.out");
		pw.println(bestPhoto);
		pw.close();
	}
	*/
}
