// Prefix sums approach
// T: O(n + q), M: O(n), where n is num of cows, and q is num of queries

import java.io.*;
import java.util.*;

public class BreedCounting {
	public static void main(String[] args) throws IOException{
		// Open input file
		BufferedReader in = new BufferedReader(new FileReader("bcount.in"));
		// first line: n = num of cows, q = num of queries
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int q = Integer.parseInt(st.nextToken());
		
		// For next n lines read cow breed IDs and create prefix sum lists
		int[] holsteins = new int[n+1], guernseys = new int[n+1], jerseys = new int[n+1];
		for (int idx = 1; idx < n + 1; idx++) {
			holsteins[idx] += holsteins[idx - 1];
			guernseys[idx] += guernseys[idx - 1];
			jerseys[idx] += jerseys[idx - 1];
			int cow_id = Integer.parseInt(in.readLine());
			switch (cow_id) {
				case 1:
					holsteins[idx]++;
					break;
				case 2:
					guernseys[idx]++;
					break;
				case 3:
					jerseys[idx]++;
					break;
			}
		}

		// For next q lines solve num of cow breeds in query range and write queries ids to output file
		PrintWriter out = new PrintWriter("bcount.out");
		for (int ln = 0; ln < q; ln++) {
			st = new StringTokenizer(in.readLine());
			int start = Integer.parseInt(st.nextToken());
			int end = Integer.parseInt(st.nextToken());
			out.println((holsteins[end] - holsteins[start - 1]) + 
				" " + (guernseys[end] - guernseys[start - 1]) + 
				" " + (jerseys[end] - jerseys[start - 1]));
		}
		in.close();
		out.close();
	}
}