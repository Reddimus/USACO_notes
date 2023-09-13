# USACO 2017 January Contest, Silver
## Problem 2. Hoof, Paper, Scissors

http://www.usaco.org/index.php?page=viewproblem2&cpid=691

You have probably heard of the game "Rock, Paper, Scissors". The cows like to play a similar game they call "Hoof, Paper, Scissors".  

The rules of "Hoof, Paper, Scissors" are simple. Two cows play against each-other. They both count to three and then each simultaneously makes a gesture that represents either a hoof, a piece of paper, or a pair of scissors. Hoof beats scissors (since a hoof can smash a pair of scissors), scissors beats paper (since scissors can cut paper), and paper beats hoof (since the hoof can get a papercut). For example, if the first cowmakes a "hoof" gesture and the second a "paper" gesture, then the second cow wins. Of course, it is also possible to tie, if both cows make the same gesture.  

Farmer John wants to play against his prize cow, Bessie, at N games of "Hoof, Paper, Scissors" `(1≤N≤100,000)`. Bessie, being an expert at the game, can predict each of FJ's gestures before he makes it. Unfortunately, Bessie, being a cow, is also very lazy. As a result, she tends to play the same gesture multiple times in a row. In fact, she is only willing to switch gestures at most once over the entire set of games. For example, she might play "hoof" for the first x games, then switch to "paper" for the remaining N-x games.  

Given the sequence of gestures FJ will be playing, please determine the maximum number of games that Bessie can win.

### Input Format (`hps.in`)
The first line contains N.  
The remaining N lines contain FJ's gestures, each either `H`, `P`, or `S`.  

### Output Format (`hps.out`)
Print the maximum number of games Bessie can win, considering she can only change gestures once.

### Sample Input
```
5
P
P
H
P
S
```


### Sample Output
```
4
```