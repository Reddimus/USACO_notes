/*
Silver P2 2017-Hoof Paper Scissors prompt:

You have probably heard of the game "Rock, Paper, Scissors". The cows like to play 
a similar game they call "Hoof, Paper, Scissors".

The rules of "Hoof, Paper, Scissors" are simple. Two cows play against each-other. 
They both count to three and then each simultaneously makes a gesture that 
represents either a hoof, a piece of paper, or a pair of scissors. Hoof beats 
scissors (since a hoof can smash a pair of scissors), scissors beats paper 
(since scissors can cut paper), and paper beats hoof (since the hoof can get a 
papercut). For example, if the first cow makes a "hoof" gesture and the second a 
"paper" gesture, then the second cow wins. Of course, it is also possible to tie, 
if both cows make the same gesture.

Farmer John wants to play against his prize cow, Bessie, at N games of "Hoof, 
Paper, Scissors" (1≤N≤100,000). Bessie, being an expert at the game, can predict 
each of FJ's gestures before he makes it. Unfortunately, Bessie, being a cow, is 
also very lazy. As a result, she tends to play the same gesture multiple times in 
a row. In fact, she is only willing to switch gestures at most once over the 
entire set of games. For example, she might play "hoof" for the first x games, 
then switch to "paper" for the remaining N-x games.

Given the sequence of gestures FJ will be playing, please determine the maximum 
number of games that Bessie can win.

INPUT FORMAT (file hps.in):
The first line of the input file contains N.
The remaining N lines contains FJ's gestures, each either H, P, or S.

OUTPUT FORMAT (file hps.out):
Print the maximum number of games Bessie can win, given that she can only change
gestures at most once.

SAMPLE INPUT:
5
P
P
H
P
S

SAMPLE OUTPUT:
4
*/

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
