import java.io.*;

// Prefix sums approach
// T & M: O(n), where n is size of Fjs actions
public class HPS {
    public static void main(String[] args) throws Exception {
        BufferedReader in = new BufferedReader(new FileReader("hps.in"));
        // first line: n = amount of games played
        int n = Integer.parseInt(in.readLine());
        // Intialize prefix sum arrays with 0th index dummy value
        int[] hooves = new int[n + 1];
        int[] paper = new int [n + 1];
        int[] scissors = new int[n + 1];
        // Populate the hooves, paper, and scissors prefix arrays (Notes down action wins for every iteration)
        for (int idx = 1; idx <= n; idx++){
            // update prefix sums with prev vals
            hooves[idx] += hooves[idx - 1];
            paper[idx] += paper[idx - 1];
            scissors[idx] += scissors[idx - 1];
            // grab input & assign win to best choice
            char action = in.readLine().charAt(0);
            switch (action){
                case 'H':
                    paper[idx]++;
                    break;
                case 'P':
                    scissors[idx]++;
                    break;
                case 'S':
                    hooves[idx]++;
                    break;
            }
        }
        in.close();

        // Using prefix sums allows us to check all win combinations in O(n) time
        int maxWins = 0;
        for (int idx = 1; idx <= n; idx++) {
            // calculate max current wins
            int beforeWins = Math.max(hooves[idx], Math.max(paper[idx], scissors[idx]));
            // calculate max wins after current iteration to the end
            int afterWins = Math.max(hooves[n] - hooves[idx], Math.max(paper[n] - paper[idx], scissors[n] - scissors[idx]));
            maxWins = Math.max(maxWins, beforeWins + afterWins);
        }
        
        // write maxWins answer to output file
        PrintWriter out = new PrintWriter("hps.out");
        out.println(maxWins);
        out.close();
    }
}
