import java.io.*;
import java.util.*;

public class Div7 {
    // Prefix sums - Array approach
    // T: O(n), M: O(1), where n is the number of cows
    public static void main(String[] args) throws IOException {
        // Open input file
        BufferedReader br = new BufferedReader(new FileReader("div7.in"));
        // First line: n = num of cows
        int n = Integer.parseInt(br.readLine());
        // For the next n lines create curr/temp prefix sum mod 7 variable
        int curr_mod_ps = 0;
        int best_photo = 0;
        int[] first_occ = new int[7];
        Arrays.fill(first_occ, -1);
        first_occ[0] = 0;
        for (int idx = 0; idx < n; idx++) {
            curr_mod_ps = (curr_mod_ps + Integer.parseInt(br.readLine())) % 7;

            // Update first occurence list if mod 7 prefix sum not in first occurences list
            if (first_occ[curr_mod_ps] == -1)
                first_occ[curr_mod_ps] = idx;
            // Update best photo if pair exists in first occurences list
            else
                best_photo = Math.max(best_photo, idx - first_occ[curr_mod_ps]);
        }
        br.close();

        // Write updated best photo to div7 output file
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("div7.out")));
        pw.println(best_photo);
        pw.close();
    }

    /*
    // Prefix sums - HashMap approach
    // T: O(n), M: O(1), where n is the number of cows
    public static void main(String[] args) throws IOException {
        // Open input file
        BufferedReader br = new BufferedReader(new FileReader("div7.in"));
        // First line: n = num of cows
        int n = Integer.parseInt(br.readLine());
        // For the next n lines create curr/temp prefix sum mod 7 variable
        int best_photo = 0;
        int curr_mod_ps = 0;
        Map<Integer, int[]> mod_map = new HashMap<>();	// map mod 7'ed prefix sums; up to 7 possible values
        for (int idx = 0; idx < n; idx++) {
            curr_mod_ps = (curr_mod_ps + Integer.parseInt(br.readLine())) % 7;

            // Update best photo if pair exists
            if (mod_map.containsKey(curr_mod_ps)) {
                mod_map.get(curr_mod_ps)[1] = idx;
                best_photo = Math.max(best_photo, mod_map.get(curr_mod_ps)[1] - mod_map.get(curr_mod_ps)[0]);
            } else {
                mod_map.put(curr_mod_ps, new int[]{idx, idx});
            }
        }

        // Write updated best photo to div7 output file
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("div7.out")));
        pw.println(best_photo);
        pw.close();
    }
    */

    /*
    // Prefix sums - Dictionary expanded approach
    // T: O(n), M: O(n), where n is the number of cows
    public static void main(String[] args) throws IOException {
        // Open input file
        BufferedReader br = new BufferedReader(new FileReader("div7.in"));
        // First line: n = num of cows
        int n = Integer.parseInt(br.readLine());
        // For the next n lines create prefix sums array
        int[] prefix_sums = new int[n + 1];
        for (int idx = 1; idx <= n; idx++) {
            prefix_sums[idx] = prefix_sums[idx - 1] + Integer.parseInt(br.readLine());
        }

        // mod 7 prefix sums array
        int[] mod_prefix_sums = new int[n];
        for (int idx = 0; idx < n; idx++) {
            mod_prefix_sums[idx] = prefix_sums[idx + 1] % 7;
        }

        // Map mod 7 prefix sums to their first and last indices
        Map<Integer, List<Integer>> mod_map = new HashMap<>();	// map mod 7'ed prefix sums; up to 7 possible values
        for (int idx = 0; idx < n; idx++) {
            int mod_num = mod_prefix_sums[idx];
            if (!mod_map.containsKey(mod_num)) {
                mod_map.put(mod_num, new ArrayList<>());
            }
            mod_map.get(mod_num).add(idx);
        }

        // Find best/largest photo
        int best_photo = 0;
        for (Map.Entry<Integer, List<Integer>> entry : mod_map.entrySet()) {
            List<Integer> idx_list = entry.getValue();
            if (idx_list.size() > 1) {
                best_photo = Math.max(best_photo, idx_list.get(idx_list.size() - 1) - idx_list.get(0));
            }
        }

        // Write updated best photo to div7 output file
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("div7.out")));
        pw.println(best_photo);
        pw.close();
    }
    */
}
