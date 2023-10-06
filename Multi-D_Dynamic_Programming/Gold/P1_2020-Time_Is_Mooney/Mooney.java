import java.io.*;
import java.util.*;

public class Mooney {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("time.in"));

		// First line: n = num cities, m = num of one way roads, c = cost multiplier
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());
		// print n, m, c
		System.out.println(n + " " + m + " " + c);

		// Second line: moonies[i] = moonies earned in city i
		int[] moonies = new int[n];
		st = new StringTokenizer(in.readLine());
		for (int cityIdx = 0; cityIdx < n; ++cityIdx)
			moonies[cityIdx] = Integer.parseInt(st.nextToken());
		// print moonies
		System.out.println(Arrays.toString(moonies));

		// For the next m lines create adjacency list for one way roads between cities
		// index = city, value(s) = cities it connects to
		ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
		for (int cityIdx = 0; cityIdx < n; ++cityIdx)
			adj.add(new ArrayList<Integer>());
		for (int ln = 0; ln < m; ++ln) {
			st = new StringTokenizer(in.readLine());
			int city1 = Integer.parseInt(st.nextToken()) - 1;
			int city2 = Integer.parseInt(st.nextToken()) - 1;
			adj.get(city1).add(city2);
		}
		// print adj city : [cities it connects to]
		for (int cityIdx = 0; cityIdx < n; ++cityIdx)
			System.out.println(cityIdx + " : " + adj.get(cityIdx));
		in.close();
	}
}