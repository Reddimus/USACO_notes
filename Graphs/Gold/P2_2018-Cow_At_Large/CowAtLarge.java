// Graphs - Breath-First Search (BFS) w/ greedy approach
// T & M: O(V + E), where V = N = # of barns, E = # of paths/tunnels

import java.io.*;
import java.util.*;

public class CowAtLarge {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("atlarge.in"));
		// Read in first line: n = # of barns, k = Bessie's starting barn
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		// For the next n - 1 lines, read in the barns connected by a path/tunnel
		ArrayList<Integer>[] graph = new ArrayList[n + 1];
		for (int idx = 0; idx < n + 1; ++idx)
			graph[idx] = new ArrayList<>();
		for (int ln = 0; ln < n - 1; ++ln) {
			st = new StringTokenizer(in.readLine());
			int t1 = Integer.parseInt(st.nextToken());
			int t2 = Integer.parseInt(st.nextToken());
			graph[t1].add(t2);
			graph[t2].add(t1);
		}
		in.close();

		ArrayList<Integer> exits = new ArrayList<>();
		for (int idx = 1; idx <= n; ++idx)
			if (graph[idx].size() == 1)
				exits.add(idx);

		int[] distFarmer = new int[n + 1];	// stores min steps for farmer to reach node
		Arrays.fill(distFarmer, -1);
		for (int exit : exits)
			distFarmer[exit] = 0;			// initialize exit nodes to 0 steps

		// BFS to compute the minimum steps for farmers to reach each barn from exits
		Queue<Integer> q = new LinkedList<>(exits);
		while (!q.isEmpty()) {
			int qdBarn = q.poll();

			for (int adj : graph[qdBarn]) {
				// If adjacent barn has not yet been mapped to minumum steps
				if (distFarmer[adj] == -1) {
					distFarmer[adj] = distFarmer[qdBarn] + 1;	// increment farmer's steps
					q.add(adj);
				}
			}
		}

		int farmersNeeded = 0;

		// stores min steps for bessie to reach node
		int[] distBessie = new int[n + 1];
		Arrays.fill(distBessie, -1);
		distBessie[k] = 0;	// initialize Bessie's starting node to 0 steps

		// As Bessie explores the graph, count the farmers needed to catch her using BFS
		q.add(k);
		while (!q.isEmpty()) {
			int qdBarn = q.poll();

			// If Bessie's current step count >= farmer's current step count
			if (distBessie[qdBarn] >= distFarmer[qdBarn]) {
				++farmersNeeded;
				continue;
			}

			for (int adj : graph[qdBarn]) {
				// If adjacent barn has not yet been visited by Bessie
				if (distBessie[adj] == -1) {
					distBessie[adj] = distBessie[qdBarn] + 1;	// increment Bessie's steps
					q.add(adj);
				}
			}
		}

		// Write the number of farmers needed to catch Bessie to output file
		PrintWriter out = new PrintWriter("atlarge.out");
		out.println(farmersNeeded);
		out.close();
	}
}