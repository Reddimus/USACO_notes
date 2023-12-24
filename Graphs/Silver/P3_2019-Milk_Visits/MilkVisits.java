// Breadth First Search (BFS) w/ Connected Components detection Graph approach
// T & M: O(n + m) | O(V + E), where n = num of farms, m = num of friends

import java.io.*;
import java.util.*;

public class MilkVisits {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("milkvisits.in"));
		// Read in First line: n = num of farms, m = num of FJ's friends
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());

		// Second line: string of farm types
		String milkTypes = " " + in.readLine();

		// For the next n-1 lines read in the edges of the graph
		ArrayList<Integer>[] farms = new ArrayList[n + 1];
		for (int idx = 0; idx < n + 1; ++idx)
			farms[idx] = new ArrayList<>();
		for (int ln = 0; ln < n - 1; ++ln) {
			st = new StringTokenizer(in.readLine());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());

			farms[x].add(y);
			farms[y].add(x);
		}

		// Process the tree & detect the different components
		int[] components = new int[n + 1];
		for (int farm = 1; farm <= n; ++farm) {
			// Don't process a farm if it's been visited already
			if (components[farm] != 0)
				continue;

			// BFS to find all the farms in the same subtree
			char type = milkTypes.charAt(farm);
			Queue<Integer> q = new LinkedList<>();
			q.add(farm);
			while (!q.isEmpty()) {
				int qdFarm = q.poll();
				
				// Mark the queue'd farm as same path as current component (farm)
				components[qdFarm] = farm;

				// Visit a neighbor if it's new & is of the same type
				for (int neighbor : farms[qdFarm])
					if (milkTypes.charAt(neighbor) == type && components[neighbor] == 0)
						q.add(neighbor);
			}
		}

		// For the next m lines read & check if friend's path satisfies them
		StringBuilder ans = new StringBuilder();
		for (int ln = 0; ln < m; ++ln) {
			st = new StringTokenizer(in.readLine());
			int start = Integer.parseInt(st.nextToken());
			int end = Integer.parseInt(st.nextToken());
			String preference = st.nextToken();

			boolean singleType = components[start] == components[end];
			boolean samePreference = milkTypes.charAt(start) == preference.charAt(0);
			ans.append(singleType && !samePreference ? 0 : 1);
		}
		in.close();

		// Write satisfaction of each friend in sting form to output file
		PrintWriter out = new PrintWriter("milkvisits.out");
		out.println(ans);
		out.close();
	}
}