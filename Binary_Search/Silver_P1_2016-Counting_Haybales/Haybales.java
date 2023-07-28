/*
Counting Haybales - USACO Silver P1 2016 prompt:

Farmer John has just arranged his N haybales (1≤N≤100,000) at various points along 
the one-dimensional road running across his farm. To make sure they are spaced out 
appropriately, please help him answer Q queries (1≤Q≤100,000), each asking for the 
number of haybales within a specific interval along the road.

INPUT FORMAT (file haybales.in):
The first line contains N and Q.

The next line contains N distinct integers, each in the range 0…1,000,000,000, 
indicating that there is a haybale at each of those locations.

Each of the next Q lines contains two integers A and B (0≤A≤B≤1,000,000,000) 
giving a query for the number of haybales between A and B, inclusive.

OUTPUT FORMAT (file haybales.out):
You should write Q lines of output. For each query, output the number of haybales 
in its respective interval.

SAMPLE INPUT:
4 6
3 2 7 5
2 3
2 4
2 5
2 7
4 6
8 10

SAMPLE OUTPUT:
2
2
3
4
1
0
*/

import java.io.*;
import java.util.*;

// Binary search method
// T: O((n + q) log n)), M: O(n), where n is number of haybales, and q is num of intervals

public class Haybales {
    static int lowerBound(int[] arr, int target) {
        int l_idx = 0, r_idx = arr.length;
        while (l_idx < r_idx) {
            int mid = l_idx + (r_idx - l_idx) / 2;
            if (arr[mid] >= target)
                r_idx = mid;
            else
                l_idx = mid + 1;
        }
        return l_idx;  // if target not found returns out of bounds idx (n)
    }

    static int upperBound(int[] arr, int target) {
        int lo = 0, hi = arr.length;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (arr[mid] > target)
                hi = mid;
            else
                lo = mid + 1;
        }
        return hi;
    }

    public static void main(String[] args) throws IOException {
        // Open and read the input file
        BufferedReader f = new BufferedReader(new FileReader("haybales.in"));
        // Prepare for writing to the output file
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("haybales.out")));
        
        // The first line contains n and q
        StringTokenizer st = new StringTokenizer(f.readLine());
        int n = Integer.parseInt(st.nextToken());
        int q = Integer.parseInt(st.nextToken());

        // The next line contains the haybale locations
        int[] haybale_locs = new int[n];
        st = new StringTokenizer(f.readLine());
        for (int i = 0; i < n; i++)
            haybale_locs[i] = Integer.parseInt(st.nextToken());
        
        // Sort the haybale locations array
        Arrays.sort(haybale_locs);

        // For the next q lines, process the intervals
        for(int i = 0; i < q; i++) {
            st = new StringTokenizer(f.readLine());
            int start = Integer.parseInt(st.nextToken());
            int end = Integer.parseInt(st.nextToken());
            // binary search lower/upper bound area of answers
            int l_idx = lowerBound(haybale_locs, start);
            int r_idx = upperBound(haybale_locs, end);
            // Write the number of haybales in the respective interval to the output file
            out.println(r_idx - l_idx);
        }
        // close files
        f.close();
        out.close();
    }
}