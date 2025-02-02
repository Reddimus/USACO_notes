import java.io.*;
import java.util.*;

public class CowNomics {
    public static void main(String[] args) throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("cownomics.in"));
        // First line: N = cows with and without spots, M = length of genome
        StringTokenizer st = new StringTokenizer(fin.readLine());
        final int N = Integer.parseInt(st.nextToken());
        final int M = Integer.parseInt(st.nextToken());

        // Each genome and the individual characters in each genome
        char[][] spottedCows = new char[N][M];
        char[][] plainCows = new char[N][M];
        for (int i = 0; i < N; i++) 
            spottedCows[i] = fin.readLine().toCharArray();
        for (int i = 0; i < N; i++)
            plainCows[i] = fin.readLine().toCharArray();
        fin.close();

        int possPositions = 0;
        for (int charIdx = 0; charIdx < M; charIdx++) {
            boolean duplicate = false;
            for (int cow1 = 0; cow1 < N; cow1++) {
                for (int cow2 = 0; cow2 < N; cow2++) {
                    if (spottedCows[cow1][charIdx] == plainCows[cow2][charIdx]) {
                        duplicate = true;
                        break;
                    }
                }
            }
            if (!duplicate) possPositions++;
        }

        PrintWriter fout = new PrintWriter("cownomics.out");
        fout.println(possPositions);
        fout.close();
    }
}
