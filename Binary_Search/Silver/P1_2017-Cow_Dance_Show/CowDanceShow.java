// Binary search - PriorityQueue approach
// T: O(n log n), M: O(n), where n is the number of cows

import java.io.*;
import java.util.*;

public class CowDanceShow {
    // Make values accessible by all methods
    private static int n, tMax;
    private static List<Integer> dances = new ArrayList<Integer>();

    // k represents the size of the stage to support n amount of cows dancing
    private static boolean withinContract(int k) {
        PriorityQueue<Integer> stage = new PriorityQueue<Integer>(dances.subList(0, k));
        int maxDance = 0;
        // elapse shortest dance time to open dance spot and add next cow to stage
        for (int idx = k; idx < n; idx++) {
            int minDance = stage.poll();
            maxDance = Math.max(maxDance, minDance + dances.get(idx));
            stage.add(minDance + dances.get(idx));
        }
        // elapse remaining dance time
        return maxDance <= tMax;
    }

    public static void main(String[] args) throws IOException {
        // open input file
        BufferedReader in = new BufferedReader(new FileReader("cowdance.in"));
        StringTokenizer st = new StringTokenizer(in.readLine());
        // first line: n = number of cows, tmax = max stage time
        n = Integer.parseInt(st.nextToken());
        tMax = Integer.parseInt(st.nextToken());
        // for the next n lines read each cow's dance time
        for (int i = 0; i < n; i++)
            dances.add(Integer.parseInt(in.readLine()));
        in.close();
        
        // Binary Search for smallest possible stage size within contract time limit
        int lo = 1, hi = n;
        while (lo < hi) {
            int mid  = lo + (hi - lo) / 2;
            if (!withinContract(mid))
                lo = mid + 1;   // increase stage size to reduce time on stage and be within contract time limit
            else
                hi = mid;
        }

        // Write output file
        PrintWriter out = new PrintWriter("cowdance.out");
        out.println(hi);
        out.close();
    }
}

/*
// Binary search - Array approach
// T: O(n^2 log n), M: O(n), where n is the number of cows

public class CowDanceShow {
    // make vals accessible by all methods
    private static int[] dances;
    private static int n, tmax;

    // k represents the size of the stage to support n amount of cows dancing
    private static boolean withinContract(int k) {
        int[] stage = Arrays.copyOfRange(dances, 0, k);
        int t_cnt = 0, d_idx = k;
        while (d_idx < n) {
            // find the shortest dance time in the stage
            int minDance = Integer.MAX_VALUE;
            for (int i = 0; i < k; i++)
                minDance = Math.min(minDance, stage[i]);
            t_cnt += minDance;
            if (t_cnt > tmax)
                return false;
            // elapse time by shortest dance time to open dance spot and add next cow to stage
            for (int i = 0; i < k; i++) {
                stage[i] -= minDance;
                if (stage[i] == 0) {
                    stage[i] = dances[d_idx];
                    d_idx++;
                }
            }
        }
        int maxDance = Integer.MIN_VALUE;
        for (int i = 0; i < k; i++)
            maxDance = Math.max(maxDance, stage[i]);        
        return t_cnt + maxDance <= tmax;
    }

    public static void main(String[] args) throws Exception{
        // open input file
        BufferedReader in = new BufferedReader(new FileReader("cowdance.in"));
        StringTokenizer st = new StringTokenizer(in.readLine());
        // first line: n = number of cows, tmax = max stage time
        n = Integer.parseInt(st.nextToken()); 
        tmax = Integer.parseInt(st.nextToken());
        // for the next n lines read each cow's dance time
        dances = new int[n];
        for (int i = 0; i < n; i++)
            dances[i] = Integer.parseInt(in.readLine());
        in.close();
        
        // Binary Search for smallest possible stage size within contract time limit
        int lo = 1, hi = n;
        while (lo < hi) {
            int mid  = lo + (hi - lo) / 2;
            if (!withinContract(mid))
                lo = mid + 1;
            else
                hi = mid;
        }

        // Write output file
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cowdance.out")));
        out.println(hi);
        out.close();
    }
}
*/