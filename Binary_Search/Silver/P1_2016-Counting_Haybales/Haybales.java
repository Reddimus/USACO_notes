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
        int lIdx = 0, rIdx = arr.length;
        while (lIdx < rIdx) {
            int mid = lIdx + (rIdx - lIdx) / 2;
            if (arr[mid] >= target)
                rIdx = mid;
            else
                lIdx = mid + 1;
        }
        return lIdx;  // if target not found returns out of bounds idx (n)
    }

    static int upperBound(int[] arr, int target) {
        int lIdx = 0, rIdx = arr.length;
        while (lIdx < rIdx) {
            int mid = lIdx + (rIdx - lIdx) / 2;
            if (arr[mid] > target)
                rIdx = mid;
            else
                lIdx = mid + 1;
        }
        return rIdx;
    }

    public static void main(String[] args) throws IOException {
        // Open and read the input file
        BufferedReader in = new BufferedReader(new FileReader("haybales.in"));
        
        // The first line contains n and q
        StringTokenizer st = new StringTokenizer(in.readLine());
        final int n = Integer.parseInt(st.nextToken());
        final int q = Integer.parseInt(st.nextToken());

        // The next line contains the haybale locations
        final int[] haybaleLocs = new int[n];
        st = new StringTokenizer(in.readLine());
        for (int idx = 0; idx < n; ++idx)
            haybaleLocs[idx] = Integer.parseInt(st.nextToken());
        
        // Sort the haybale locations array
        Arrays.sort(haybaleLocs);

        // Prepare for writing to the output file
        PrintWriter out = new PrintWriter("haybales.out");
        // For the next q lines, process the intervals
        for(int ln = 0; ln < q; ++ln) {
            st = new StringTokenizer(in.readLine());
            int start = Integer.parseInt(st.nextToken());
            int end = Integer.parseInt(st.nextToken());
            // binary search lower/upper bound area of answers
            int lIdx = lowerBound(haybaleLocs, start);
            int rIdx = upperBound(haybaleLocs, end);
            // Write the number of haybales in the respective interval to the output file
            out.println(rIdx - lIdx);
        }

        in.close();
        out.close();
    }
}
