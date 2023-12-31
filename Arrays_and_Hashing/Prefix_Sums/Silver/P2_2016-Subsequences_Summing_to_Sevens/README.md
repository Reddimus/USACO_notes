# USACO 2016 January Contest, Silver
## Problem 2. Subsequences Summing to Sevens

### Description

Farmer John's N cows are standing in a row, as they have a tendency to do from time to time. Each cow is labeled with a distinct integer ID number so FJ can tell them apart. FJ would like to take a photo of a contiguous group of cows but, due to a traumatic childhood incident involving the numbers 1…6, he only wants to take a picture of a group of cows if their IDs add up to a multiple of 7.

Please help FJ determine the size of the largest group he can photograph.

### INPUT FORMAT (file div7.in):
The first line of input contains N (1≤N≤50,000). The next N lines each contain the N integer IDs of the cows (all are in the range 0…1,000,000).

### OUTPUT FORMAT (file div7.out):
Please output the number of cows in the largest consecutive group whose IDs sum to a multiple of 7. If no such group exists, output 0.

You may want to note that the sum of the IDs of a large group of cows might be too large to fit into a standard 32-bit integer. If you are summing up large groups of IDs, you may therefore want to use a larger integer data type, like a 64-bit "long long" in C/C++.

### SAMPLE INPUT:
7  
3  
5  
1  
6  
2  
14  
10  


### SAMPLE OUTPUT:
5  

In this example, 5+1+6+2+14 = 28.

http://www.usaco.org/index.php?page=viewproblem2&cpid=595

Solution:
https://github.com/Reddimus/USACO_notes/tree/main/Prefix_Sums/Silver/P2_2016-Subsequences_Summing_to_Sevens
