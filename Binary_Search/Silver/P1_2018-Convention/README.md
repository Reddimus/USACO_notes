# USACO 2018 December Contest, Silver
## Problem 1. Convention

### Description

Farmer John is hosting a new bovine grass-eating convention at his farm!

Cows from all over the world are arriving at the local airport to attend the convention and eat grass. Specifically, there are \( N \) cows arriving at the airport (1≤\( N \)≤\( 10^5 \)) and cow \( i \) arrives at time \( t_i \) (0≤\( t_i \)≤\( 10^9 \)). Farmer John has arranged \( M \) (1≤\( M \)≤\( 10^5 \)) buses to transport the cows from the airport. Each bus can hold up to \( C \) cows in it (1≤\( C \)≤\( N \)). Farmer John is waiting with the buses at the airport and would like to assign the arriving cows to the buses. A bus can leave at the time when the last cow on it arrives. Farmer John wants to be a good host and so does not want to keep the arriving cows waiting at the airport too long. What is the smallest possible value of the maximum waiting time of any one arriving cow if Farmer John coordinates his buses optimally? A cow's waiting time is the difference between her arrival time and the departure of her assigned bus.

It is guaranteed that \( MC \geq N \).

### INPUT FORMAT (file convention.in)

The first line contains three space-separated integers \( N \), \( M \), and \( C \). The next line contains \( N \) space-separated integers representing the arrival time of each cow.

### OUTPUT FORMAT (file convention.out)

Please write one line containing the optimal minimum maximum waiting time for any one arriving cow.

#### SAMPLE INPUT
6 3 2  
1 1 10 14 4 3  


#### SAMPLE OUTPUT
4  

If the two cows arriving at time 1 go in one bus, cows arriving at times 3 and 4 in the second, and cows arriving at times 10 and 14 in the third, the longest time a cow has to wait is 4 time units (the cow arriving at time 10 waits from time 10 to time 14)
