# USACO 2023 February Contest, Gold
# Problem 3. Piling Papers

http://usaco.org/index.php?page=viewproblem2&cpid=1307

Farmer John wrote down `N (1 ≤ N ≤ 300)` digits on pieces of paper. For each `i ∈ [1, N]`, the ith piece of paper contains digit `a_i (1 ≤ a_i ≤ 9)`.

The cows have two favorite integers `A` and `B (1 ≤ A ≤ B ≤ 10^18)`, and would like you to answer `Q (1 ≤ Q ≤ 5 · 10^4)` queries. For the ith query, the cows will move left to right across papers `l_i,..., r_i (1 ≤ l_i ≤ r_i ≤ N)`, maintaining an initially empty pile of papers. For each paper, they will either add it to the top of the pile, to the bottom of the pile, or neither. In the end, they will read the papers in the pile from top to bottom, forming an integer. Over all `3^(r_i-l_i+1)` ways for the cows to make choices during this process, count the number of ways that result in the cows reading an integer in `[A, B]` inclusive, and output this number modulo `10^9 + 7`.

### Input Format  (input arrives from the terminal / stdin):

- The first line contains three space-separated integers `N, A, and B`.
- The second line contains `N` space-separated digits `a_1, a_2,... ,a_N`.
- The third line contains an integer `Q`, the number of queries.
- The next `Q` lines each contain two space-separated integers `l_i` and `r_i`.

### Output Format (print output to the terminal / stdout):

For each query, a single line containing the answer.

### Sample Input:
```
5 13 327
1 2 3 4 5
3
1 2
1 3
2 5
```

### Sample Output:
```
2
18
34
```

For the first query, there are nine ways Bessie can stack papers when reading the interval [1,2]:

- Bessie can ignore 1 then ignore 2, getting 0.
- Bessie can ignore 1 then add 2 to the top of the stack, getting 2.
- Bessie can ignore 1 then add 2 to the bottom of the stack, getting 2.
- Bessie can add 1 to the top of the stack then ignore 2, getting 1.
- Bessie can add 1 to the top of the stack then add 2 to the top of the stack, getting 21.
- Bessie can add 1 to the top of the stack then add 2 to the bottom of the stack, getting 12.
- Bessie can add 1 to the bottom of the stack then ignore 2, getting 1.
- Bessie can add 1 to the bottom of the stack then add 2 to the top of the stack, getting 21.
- Bessie can add 1 to the bottom of the stack then add 2 to the bottom of the stack, getting 12.

Only the 2 ways that give 21 yield a number between 13 and 327, so the answer is 2.

### Scoring:

- Inputs 2-3: `B < 100`
- Inputs 4-5: `A = B`
- Inputs 6-13: No additional constraints.

### Hints:
- 


## Solutions:

https://github.com/Reddimus/USACO_notes/tree/main/Multi-D_Dynamic_Programming/Gold/P3_2023-Piling_Papers

### Intuition:


### Steps:
1. 

### Time & Space complexity:
**Time:** `O(N (log B)^2)`   
**Space:** `O( )`  

Where `n` is 

### C++ Code:
```cpp
```

### Java Code:
```java
```
