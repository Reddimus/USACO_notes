/*
USACO 2017 February Contest, Silver
Problem 2. Why Did the Cow Cross the Road II

The long road through Farmer John's farm has N crosswalks across it, conveniently numbered 1…N 
(1≤N≤100,000). To allow cows to cross at these crosswalks, FJ installs electric crossing signals, 
which light up with a green cow icon when it is ok for the cow to cross, and red otherwise. 
Unfortunately, a large electrical storm has damaged some of his signals. Given a list of the 
damaged signals, please compute the minimum number of signals that FJ needs to repair in order 
for there to exist some contiguous block of at least K working signals.

INPUT FORMAT (file maxcross.in):
The first line of input contains N, K, and B (1≤B,K≤N). The next B lines each describe the ID 
number of a broken signal.

OUTPUT FORMAT (file maxcross.out):
Please compute the minimum number of signals that need to be repaired in order for there to be 
a contiguous block of K working signals somewhere along the road.

SAMPLE INPUT:
10 6 5
2
10
1
5
9

SAMPLE OUTPUT:
1
*/

// Sliding window approach
// T & M: O(n), where n is number of crosswalks

import java.io.*;
import java.util.*;

public class MaxCross {
	public static void main(String[] args) throws IOException {
		// Open input file
		BufferedReader in = new BufferedReader(new FileReader("maxcross.in"));
		// First line: n = crosswalks, k = contiguous working signals goal, b = broken signals
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int b = Integer.parseInt(st.nextToken());
		// For the next b lines, mark broken signals in list; signal_id = index, 1 = broken
		int[] broken = new int[n+1];
		for (int signal_id = 0; signal_id < b; signal_id++)
			broken[Integer.parseInt(in.readLine())] = 1;
		in.close();

		// Initialize first set of k working signals within index window range
		int tmp_fixed = 0;
		int l_idx = 1, r_idx = k+1;
		for (int idx = l_idx; idx < r_idx; idx++)
			tmp_fixed += broken[idx];

		// Slide window across broken signals lists using previous initialization values
		int min_fixed = tmp_fixed;
		while (r_idx <= n) {
			tmp_fixed += broken[r_idx] - broken[l_idx];
			min_fixed = Math.min(min_fixed, tmp_fixed);
			l_idx++;
			r_idx++;
		}

		// Write min num of signals that need to be repaired for k contiguous working signals
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("maxcross.out")));
		out.println(min_fixed);
		out.close();
	}
}