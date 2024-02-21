// Adjacency List Graphs - Topological Sort approach
// T & M: O(N + M), where N = # of sessions, M =  total days

import java.io.*;
import java.util.*;

public class Timeline {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("timeline.in"));
		// First line: n = # of milking sessions, m = total days, c = # of memories
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());
		// Second line: 1->n indexed sessions filled with min possible day milked 
		st = new StringTokenizer(in.readLine());
		int[] sessions = new int[n + 1];
		for (int idx = 1; idx <= n; ++idx) 
			sessions[idx] = Integer.parseInt(st.nextToken());
		// For the next c lines build 1-indexed memory graph
		ArrayList<int[]>[] memories = new ArrayList[n+1];
		for (int session = 1; session <= n; ++session)
			memories[session] = new ArrayList<>();
		for (int ln = 0; ln < c; ++ln) {
			st = new StringTokenizer(in.readLine());
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			// Session b happened at least x days after session a
			memories[a].add(new int[] {b, x});
		}
		in.close();

		// Build topological order of memory graph
		List<Integer> topologicalOrder = buildTopOrder(memories);

		// Update session dependencies in topological order of the memory graph
		for (int a : topologicalOrder) {
			for (int[] mem : memories[a]) {
				int b = mem[0], x = mem[1];
				sessions[b] = Math.max(sessions[b], sessions[a] + x);
			}
		}

		// Write 1-indexed session answers to output file
		PrintWriter out = new PrintWriter("timeline.out");
		for (int idx = 1; idx <= n; ++idx) 
			out.println(sessions[idx]);
		out.close();
	}

	// Recursively depth-first search session path to build topological order
	private static HashSet<Integer> visited = new HashSet<>();
	private static LinkedList<Integer> topOrder = new LinkedList<>();

	private static List<Integer> buildTopOrder(ArrayList<int[]>[] memories) {
		for (int session = 1; session < memories.length; ++session) 
			dfs(session, memories);
		return topOrder;
	}

	private static void dfs(int session, ArrayList<int[]>[] memories) {
		if (visited.contains(session))
			return;

		visited.add(session);

		for (int[] mem : memories[session]) 
			dfs(mem[0], memories);

		topOrder.addFirst(session);
	}
}