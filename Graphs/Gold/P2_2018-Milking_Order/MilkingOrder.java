// Adjacency List Graphs - Topological Sort approach
// T: O(log M * (E * N log N)), M: O(N + E)
// Where n is the number of cows, m is the number of observations, and e is the number of edges

import java.io.*;
import java.util.*;

public class MilkingOrder {
	private static int n, m;
	private static int[][] observations;
	private static int[] answer;
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("milkorder.in"));
		// First line: n = # of cows, m = # of observations
		StringTokenizer st = new StringTokenizer(in.readLine());
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		// For the next m lines, read in the observation paths
		observations = new int[m][];
		for (int i = 0; i < m; ++i) {
			st = new StringTokenizer(in.readLine());
			int mi = Integer.parseInt(st.nextToken());
			int[] observation = new int[mi];
			for (int j = 0; j < mi; ++j) 
				observation[j] = Integer.parseInt(st.nextToken());
			observations[i] = observation;
		}
		in.close();

		// Binary search for maximum number of observations that can be satisfied
		int lo = 0, hi = m;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			// Topological sort to find if graph is valid & build answer
			if (check_x_conditions(mid)) 
				lo = mid + 1;
			else 
				hi = mid;
		}

		// Write the maximum number of x-ordered observations to the output file
		PrintWriter out = new PrintWriter("milkorder.out");
		for (int idx = 0; idx < n - 1; ++idx)
			out.print(answer[idx] + " ");
		out.println(answer[n - 1]);
		out.close();
	}

	// Topological sort the x-observations graph to check if all cows can be visited
	private static boolean check_x_conditions(int x) {
		int[] indegree = new int[n + 1];
		ArrayList<Integer>[] graph = new ArrayList[n + 1];
		for (int cow = 1; cow <= n; ++cow) 
			graph[cow] = new ArrayList<>();
		// Using up to x observations build adjacency list & count edges per node
		for (int i = 0; i < x; ++i) {
			// Map observation path by pairs
			for (int j = 0; j < observations[i].length - 1; ++j) {
				graph[observations[i][j]].add(observations[i][j + 1]);
				++indegree[observations[i][j + 1]];
			}
		}

		// Queue non-dependent cows in lexicographical order
		PriorityQueue<Integer> pq = new PriorityQueue<>();
		for (int cow = 1; cow <= n; ++cow) 
			if (indegree[cow] == 0) 
				pq.add(cow);

		// Traverse non-dependent cows in lexicographical order from graph
		int[] tempAnswer = new int[n];
		int visits = 0;
		for (visits = 0; !pq.isEmpty(); ++visits) {
			int cow = pq.poll();
			tempAnswer[visits] = cow;

			for (int adj : graph[cow]) {
				--indegree[adj];	// Remove the edge from the adjacent cow/node
				if (indegree[adj] == 0) 
					pq.add(adj);
			}
		}

		// Check if all cows/nodes were visited
		if (visits < n) 
			return false;
		answer = tempAnswer;
		return true;
	}
}
