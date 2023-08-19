import java.io.*;
import java.util.*;

// Binary Search - Two Pointers approach
// T: O(n log n), M: O(n), where n = num of cows

public class Convention {
    static int n, m, c;
    static int[] arrivals;
    public static void main(String[] args) throws IOException {
        // Open input file
        BufferedReader in = new BufferedReader(new FileReader("convention.in"));
        StringTokenizer st = new StringTokenizer(in.readLine());
        // First line: n = num of cows, m = num of buses, c = bus capacity
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        c = Integer.parseInt(st.nextToken());
        // Second line: cow arrival times
        st = new StringTokenizer(in.readLine());
        arrivals = new int[n];
        for (int cow = 0; cow < n; cow++)
            arrivals[cow] = Integer.parseInt(st.nextToken());
        in.close();

        // Sort to group bus pairs easily
        Arrays.sort(arrivals);

        // Binary search min max waiting time
        int lo = 0, hi = arrivals[n - 1] - arrivals[0];
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (!validMaxWait(mid))
                lo = mid + 1;
            else
                hi = mid;
        }

        // Write converged answer hi [..false, false, TRUE, true...] representing min max arrival time
        PrintWriter out = new PrintWriter("convention.out");
        out.println(hi);
        out.close();
    }

    // check if max waiting time is valid under busses (m) and bus capacity (c) constraints
    private static boolean validMaxWait(int maxWait) {
        int buses = 0, l_idx = 0, r_idx = 0;
        while (r_idx < n) {
            // if first cow in bus (overlapping idxs); increment buses counter
            if (l_idx == r_idx) 
                buses++;
            
            // if bus waiting time out of range; update prev idx to curr idx (move to next bus)
            if (arrivals[r_idx] - arrivals[l_idx] > maxWait) {
                l_idx = r_idx;
            }
            // else if bus capacity (c) reached with new placement; update idxs to move on to next bus
            else if (r_idx + 1 - l_idx == c) {
                r_idx++;
                l_idx = r_idx;
            }
            // else cow time is valid for bus placement
            else {
                r_idx++;
            }
        }
        return buses <= m;
    }
}