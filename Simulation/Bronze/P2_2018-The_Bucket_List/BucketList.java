import java.util.*;
import java.io.*;

public class BucketList {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("blist.in"));

        final int N = Integer.parseInt(in.readLine());
        int[] inUse = new int[1001];
        for (int cow = 0; cow < N; cow++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            int start = Integer.parseInt(st.nextToken());
            int end = Integer.parseInt(st.nextToken());
            int bucketsNeeded = Integer.parseInt(st.nextToken());

            for (int idx = start; idx <= end; idx++)
                inUse[idx] += bucketsNeeded;
        }
        in.close();

        int totalBuckets = 0;
        for (int idx = 0; idx < 1001; idx++)
            totalBuckets = Math.max(totalBuckets, inUse[idx]);
        PrintWriter out = new PrintWriter("blist.out");
        out.println(totalBuckets);
        out.close();
    }
}
