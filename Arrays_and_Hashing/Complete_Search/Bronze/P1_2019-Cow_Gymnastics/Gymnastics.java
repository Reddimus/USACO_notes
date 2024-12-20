import java.io.*;
import java.util.*;

public class Gymnastics {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("gymnastics.in"));
		// Read in 1st line: K = practice sessions, N = # of cows
		StringTokenizer st = new StringTokenizer(fin.readLine());
		final int K = Integer.parseInt(st.nextToken());
		final int N = Integer.parseInt(st.nextToken());
		// For the next K lines, read in the cows' rankings
		int[][] dayCowRankings = new int[K][N + 1];
		for (int day = 0; day < K; day++) {
			st = new StringTokenizer(fin.readLine());
			for (int ranking = 0; ranking < N; ranking++)
				dayCowRankings[day][Integer.parseInt(st.nextToken())] = ranking;
		}
		fin.close();

		int distinctCows = 0;
		for (int cow1 = 1; cow1 <= N; cow1++) {
			for (int cow2 = 1; cow2 <= N; cow2++) {
				if (cow1 == cow2)
					continue;

				int distinctDays = 0;
				for (int day = 0; day < K && dayCowRankings[day][cow1] < dayCowRankings[day][cow2]; day++)
					distinctDays++;
				
				if (distinctDays == K)
					distinctCows++;
			}
		}

		PrintWriter fout = new PrintWriter("gymnastics.out");
		fout.println(distinctCows);
		fout.close();
	}
}
