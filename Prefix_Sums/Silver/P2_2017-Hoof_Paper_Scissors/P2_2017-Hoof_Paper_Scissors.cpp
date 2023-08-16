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

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Prefix sums approach
// T & M: O(n), where n is size of Fjs actions
int main(){
    ifstream in("hps.in");
    // first line: n = amount of games played
    int n;
    in >> n;
    // Intialize prefix sum arrays with 0th index dummy value
    vector<int> hooves(n+1);
    vector<int> paper(n+1);
    vector<int> scissors(n+1);
    // Populate the hooves, paper, and scissors prefix arrays (Notes down action wins for every iteration)
    for (int game = 1; game < n + 1; game++) {
        // update prefix sums with prev vals
        hooves[game] += hooves[game - 1];
        paper[game] += paper[game - 1];
        scissors[game] += scissors[game - 1];
        // grab input
        char fj_action;
        in >> fj_action;
        // assign win to best choice
        switch (fj_action) {
            case 'H':
                paper[game]++;
                break;
            case 'P':
                scissors[game]++;
                break;
            case 'S':
                hooves[game]++;
                break;
        }
    }
    // Using prefix sums allows us to check all win combinations in O(n) time
    int maxWins = 0;
    for (int i = 1; i < n + 1; i++) {
        // calculate max current wins
        int beforeWins = max(hooves[i], max(paper[i], scissors[i]));
        // calculate max wins after current iteration to the end
        int afterWins = max(hooves[n] - hooves[i], max(paper[n] - paper[i], scissors[n] - scissors[i]));
        maxWins = max(maxWins, beforeWins + afterWins);
    }
    // Write maxWins answer to output file
    ofstream pw("hps.out");
    pw << maxWins << "\n";
    pw.close();
    return 0;
}