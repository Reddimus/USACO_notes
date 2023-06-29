'''
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
'''

# Prefix sums approach
# T & M: O(n), where n is size of Fjs actions
# Gather list of fjs choices from input file
with open('hps.in', 'r') as f:
    n = int(f.readline().strip())
    # use n + 1 for arrays so we have a dummy 0 value in the 0th idx
    # Dummy value 0 @ idx = 0 allows for prefix sums
    hooves = [0 for _ in range(n + 1)]
    paper = [0 for _ in range(n + 1)]
    scissors = [0 for _ in range(n + 1)]

    for i in range(1, n + 1):
        hooves[i] += hooves[i - 1]
        paper[i] += paper[i - 1]
        scissors[i] += scissors[i - 1]

        action = f.readline().strip()
        if action == "H":
            paper[i] += 1
        elif action == "P":
            scissors[i] += 1
        elif action == "S":
            hooves[i] += 1

max_wins = 0
for i in range(n + 1):
    before_wins = max(hooves[i], paper[i], scissors[i])
    after_wins = max(hooves[n] - hooves[i], paper[n] - paper[i], scissors[n] - scissors[i])
    max_wins = max(max_wins, before_wins + after_wins)

print(max_wins, file=open("hps.out", "w"))
