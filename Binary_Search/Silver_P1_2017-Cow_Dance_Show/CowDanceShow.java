/*
USACO 2017 January Contest, Silver
Problem 1. Cow Dance Show

After several months of rehearsal, the cows are just about ready to put on their annual dance 
performance; this year they are performing the famous bovine ballet "Cowpelia".

The only aspect of the show that remains to be determined is the size of the stage. A stage 
of size K can support K cows dancing simultaneously. The N cows in the herd (1≤N≤10,000) 
are conveniently numbered 1…N in the order in which they must appear in the dance. Each 
cow i plans to dance for a specific duration of time d(i). Initially, cows 1…K appear 
on stage and start dancing. When the first of these cows completes her part, she leaves 
the stage and cow K+1 immediately starts dancing, and so on, so there are always K cows 
dancing (until the end of the show, when we start to run out of cows). The show ends when 
the last cow completes her dancing part, at time T.

Clearly, the larger the value of K, the smaller the value of T. Since the show cannot last 
too long, you are given as input an upper bound Tmax specifying the largest possible value 
of T. Subject to this constraint, please determine the smallest possible value of K.

INPUT FORMAT (file cowdance.in):
The first line of input contains N and Tmax, where Tmax is an integer of value at most 1 million.

The next N lines give the durations d(1)…d(N) of the dancing parts for cows 1…N. Each d(i) 
value is an integer in the range 1…100,000.

It is guaranteed that if K=N, the show will finish in time.

OUTPUT FORMAT (file cowdance.out):
Print out the smallest possible value of K such that the dance performance will take no more 
than Tmax units of time.

SAMPLE INPUT:
5 8
4
7
8
6
4

SAMPLE OUTPUT:
4
*/

import java.io.*;
import java.util.*;

// Binary search - PriorityQueue approach
// T: O(n log n), M: O(n), where n is the number of cows

public class CowDanceShow {
    // Make vals accessible by all methods
    private static int n, t_max;
    private static List<Integer> dances = new ArrayList<Integer>();
    // k represents the size of the stage to support n amount of cows dancing
    private static boolean within_contract(int k) {
        PriorityQueue<Integer> stage = new PriorityQueue<Integer>(dances.subList(0, k));
        int max_dance = Integer.MIN_VALUE;
        // elapse shortest dance time to open dance spot and add next cow to stage
        for (int idx = k; idx < n; idx++) {
            int min_dance = stage.poll();
            max_dance = Math.max(max_dance, min_dance + dances.get(idx));
            stage.add(min_dance + dances.get(idx));
        }
        // elapse remaining dance time
        return max_dance <= t_max;
    }
    public static void main(String[] args) throws IOException {
        // open input file
        BufferedReader in = new BufferedReader(new FileReader("cowdance.in"));
        StringTokenizer st = new StringTokenizer(in.readLine());
        // first line: n = number of cows, tmax = max stage time
        n = Integer.parseInt(st.nextToken());
        t_max = Integer.parseInt(st.nextToken());
        // for the next n lines read each cow's dance time
        for (int i = 0; i < n; i++)
            dances.add(Integer.parseInt(in.readLine()));

        // Binary Search for smallest possible stage size within contract time limit
        int lo = 1, hi = n;
        while (lo < hi) {
            int mid  = lo + (hi - lo) / 2;
            if (!within_contract(mid))
                lo = mid + 1;   // increase stage size to reduce time on stage and be within contract time limit
            else
                hi = mid;
        }

        // Write output file
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cowdance.out")));
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
    private static boolean within_contract(int k) {
        int[] stage = Arrays.copyOfRange(dances, 0, k);
        int t_cnt = 0, d_idx = k;
        while (d_idx < n) {
            // find the shortest dance time in the stage
            int min_dance = Integer.MAX_VALUE;
            for (int i = 0; i < k; i++)
                min_dance = Math.min(min_dance, stage[i]);
            t_cnt += min_dance;
            if (t_cnt > tmax)
                return false;
            // elapse time by shortest dance time to open dance spot and add next cow to stage
            for (int i = 0; i < k; i++) {
                stage[i] -= min_dance;
                if (stage[i] == 0) {
                    stage[i] = dances[d_idx];
                    d_idx++;
                }
            }
        }
        int max_dance = Integer.MIN_VALUE;
        for (int i = 0; i < k; i++)
            max_dance = Math.max(max_dance, stage[i]);        
        return t_cnt + max_dance <= tmax;
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
            if (!within_contract(mid))
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