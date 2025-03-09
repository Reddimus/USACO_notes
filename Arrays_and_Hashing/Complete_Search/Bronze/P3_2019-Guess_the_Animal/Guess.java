import java.util.*;
import java.io.*;

public class Guess {
    public static void main(String[] args) throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("guess.in"));
        // Read in 1st line: N = number of animals
        final int N = Integer.parseInt(fin.readLine());
        // For the next N lines, map animal name to a set of attributes
        HashSet<String>[] animals = new HashSet[N];
        for (int a = 0; a < N; a++) {
            StringTokenizer st = new StringTokenizer(fin.readLine());
            st.nextToken(); // animal name (unused)
            int attrNum = Integer.parseInt(st.nextToken());
            animals[a] = new HashSet<>();
            for (int j = 0; j < attrNum; j++) {
                animals[a].add(st.nextToken());
            }
        }
        fin.close();

        int maxYes = 0;
        // Compare every pair of animals for common characteristics
        for (int a1 = 0; a1 < N; a1++) {
            for (int a2 = a1 + 1; a2 < N; a2++) {
                HashSet<String> common = new HashSet<>(animals[a1]);
                common.retainAll(animals[a2]);
                maxYes = Math.max(maxYes, common.size() + 1);
            }
        }

        PrintWriter fout = new PrintWriter("guess.out");
        fout.println(maxYes);
        fout.close();
    }
}
