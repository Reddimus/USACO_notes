/*
USACO 2020 US Open Contest, Silver
Problem 1. Social Distancing

Farmer John is worried for the health of his cows after an outbreak of the highly contagious 
bovine disease COWVID-19.

In order to limit transmission of the disease, Farmer John's N cows (2≤N≤10^5) have decided 
to practice "social distancing" and spread themselves out across the farm. The farm is shaped 
like a 1D number line, with M mutually-disjoint intervals (1≤M≤10^5) in which there is grass 
for grazing. The cows want to locate themselves at distinct integer points, each covered in 
grass, so as to maximize the value of D, where D represents the distance between the closest 
pair of cows. Please help the cows determine the largest possible value of D.

INPUT FORMAT (file socdist.in):
The first line of input contains N and M. The next M lines each describe an interval in terms
of two integers a and b, where 0≤a≤b≤10^18. No two intervals overlap or touch at their endpoints. 
A cow standing on the endpoint of an interval counts as standing on grass.

OUTPUT FORMAT (file socdist.out):
Print the largest possible value of D such that all pairs of cows are D units apart. A solution 
with D>0 is guaranteed to exist.

SAMPLE INPUT:
5 3
0 2
4 7
9 9

SAMPLE OUTPUT:
2

One way to achieve D=2 is to have cows at positions 0, 2, 4, 6 and 9.

SCORING:
- Test cases 2-3 satisfy b≤10^5.
- Test cases 4-10 satisfy no additional constraints.
 */

import java.io.*;
import java.util.*;

// Binary search on multiple answers method
// T: O(N log D + M log M) = O((N+M)log(maxDist)), M: O(M), where N is the number of cows, M is the number of intervals, and D is the range of distance
public class SocDist {
    private static long[][] intervals;  // make intervals accessible by all methods
    private static int n, m;  // number of cows and intervals respectively

    // method to test if a certain minimum distance can be achieved between cows
    private static boolean possible_placement(long min_dist){
        // initialize previous cow location to be right before the first position
        long prev_cow_loc = intervals[0][0] - min_dist;
        int remaining_cows = n;
        for (long[] interval : intervals){
            long start = interval[0], end = interval[1];
            // if cow placement is not in the grassy area, update prev_cow_loc right before next grassy area
            if (prev_cow_loc + min_dist < start)
                prev_cow_loc = start - min_dist;
            // maximize minimum distance cow placements in one grassy area
            while (start <= prev_cow_loc + min_dist && prev_cow_loc + min_dist <= end){
                prev_cow_loc += min_dist;
                remaining_cows--;
            }
        }
        // all cows should be placed to return true
        return (remaining_cows <= 0);
    }

    public static void main(String[] args) throws IOException{
        // Read and create inputs
        BufferedReader in = new BufferedReader(new FileReader("socdist.in"));
        StringTokenizer st = new StringTokenizer(in.readLine());
        // first line: n = number of cows, m = number of intervals
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        // Create a 2D array of all the intervals in the next m lines
        intervals = new long[m][2];
        for (int interval = 0; interval < m; interval++){
            // use new StringTokenizer for each line
            st = new StringTokenizer(in.readLine());
            intervals[interval][0] = Long.parseLong(st.nextToken());  // start point
            intervals[interval][1] = Long.parseLong(st.nextToken());  // end point
        }
        in.close();

        // Only sort intervals by start point because there are no overlapping intervals
        Arrays.sort(intervals, Comparator.comparingLong(a -> a[0]));

        // Use Binary search algorithm to quickly test multiple solutions
        // worst case = 1, best case = equally distant cows
        long lo = 1, hi = (intervals[m-1][1] - intervals[0][0]) / (n - 1);
        while (lo < hi){
            long mid = lo + (hi - lo + 1) / 2;
            // create an algorithm that tests out this minimum distance
            if (possible_placement(mid))
                lo = mid;
            else
                hi = mid - 1;
        }
        
        // Write minimum distance of optimally distant cows to output file
        PrintWriter pw = new PrintWriter("socdist.out");
        pw.println(lo);
        pw.close();
    }
}
