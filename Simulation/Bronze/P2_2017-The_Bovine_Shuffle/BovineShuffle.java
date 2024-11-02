import java.util.*;
import java.io.*;

public class BovineShuffle {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("shuffle.in"));
        final int N = Integer.parseInt(in.readLine());
        int[] shuffles = Arrays.stream(in.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int[] ids = Arrays.stream(in.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        in.close();

        final int SHUFFLE_NUM = 3;

        System.out.println("Shuffles: " + Arrays.toString(shuffles));
        System.out.println("IDs: " + Arrays.toString(ids));
        System.out.println();

        for (int i = 0; i < SHUFFLE_NUM; i++) {
            int[] pastOrder = new int[N];
            for (int j = 0; j < N; j++)
                pastOrder[j] = ids[shuffles[j] - 1];
            ids = pastOrder;
            System.out.println("IDs: " + Arrays.toString(ids));
        }

        PrintWriter out = new PrintWriter("shuffle.out");
        for (int id : ids)
            out.println(id);
        out.close();
    }
}
