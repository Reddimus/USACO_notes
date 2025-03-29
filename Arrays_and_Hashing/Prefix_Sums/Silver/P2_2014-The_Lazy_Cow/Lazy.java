import java.io.*;
import java.util.*;

public class Lazy {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new FileReader("lazy.in"));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		final int N = Integer.parseInt(st.nextToken());
		final int K = Integer.parseInt(st.nextToken());

		// The side length needed to accomodate fro the 45 degree angle
		int newN = 2 * N - 1;
		int[][] field = new int[newN][newN];
		for (int r = 0; r < newN; r++)
			Arrays.fill(field[r], -1);  // fill with -1's to indicate invalid locations

		// read input and store it rotated by 45 degrees
		for (int i = 0; i < N; i++) {
			st = new StringTokenizer(fin.readLine());
			for (int j = 0; j < N; j++) {
				field[i + j][N - i + j - 1] = Integer.parseInt(st.nextToken());
			}
		}
		fin.close();

		int[][] prefix = new int[newN + 1][newN + 1];
		for (int i = 0; i < newN; i++) {
			for (int j = 0; j < newN; j++) {
				// prevent including -1's in the prefix sum
				int val = Math.max(field[i][j], 0);
				prefix[i + 1][j + 1] = val + prefix[i + 1][j] + prefix[i][j + 1] - prefix[i][j];
			}
		}

		int mostGrass = 0;
		for (int i = K; i < newN - K; i++) {
			for (int j = K; j < newN - K; j++) {
				// don't start at invalid locations
				if (field[i][j] == -1)
					continue;


				mostGrass = Math.max(
				    mostGrass,
					prefix[i + K + 1][j + K + 1] - prefix[i + K + 1][j - K] -
						prefix[i - K][j + K + 1] + prefix[i - K][j - K]
				);
			}
		}

		PrintWriter fout = new PrintWriter("lazy.out");
		// check if Bessie can reach everything
		fout.println(K >= N ? prefix[newN][newN] : mostGrass);
		fout.close();
	}
}
