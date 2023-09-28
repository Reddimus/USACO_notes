# USACO 2016 December Contest, Gold
## Problem 2. Cow Checklist

Every day, Farmer John walks through his pasture to check on the well-being of each of his cows. On his farm he has two breeds of cows, Holsteins and Guernseys. His `H` Holsteins are conveniently numbered `1...H`, and his `G` Guernseys are conveniently numbered `1...G` `(1 <= H <= 1000, 1 <= G <= 1000)`. Each cow is located at a point in the 2D plane (not necessarily distinct).

Farmer John starts his tour at Holstein 1, and ends at Holstein `H`. He wants to visit each cow along the way, and for convenience in maintaining his checklist of cows visited so far, he wants to visit the Holsteins and Guernseys in the order in which they are numbered. In the sequence of all `H+G` cows he visits, the Holsteins numbered `1...H` should appear as a (not necessarily contiguous) subsequence, and likewise for the Guernseys. Otherwise stated, the sequence of all `H+G` cows should be formed by interleaving the list of Holsteins numbered `1...H` with the list of Guernseys numbered `1...G`.

When FJ moves from one cow to another cow traveling a distance of `D`, he expends `D^2` energy. Please help him determine the minimum amount of energy required to visit all his cows according to a tour as described above.

### Input Format (file checklist.in):

The first line of input contains `H` and `G`, separated by a space.
The next `H` lines contain the x and y coordinates of the `H` Holsteins, and the next `G` lines after that contain coordinates of the Guernseys. Each coordinate is an integer in the range `0...1000`.

### Output Format (file checklist.out):

Write a single line of output, giving the minimum energy required for FJ's tour of all the cows.

### Sample Input
```
3 2
0 0
1 0
2 0
0 3
1 3
```

### Sample Output
```
20
```

### Hints:
- 

# Solutions:

https://github.com/Reddimus/USACO_notes/tree/main/Multi-D_Dynamic_Programming/Gold/P1_2020-Time_Is_Mooney

### Intuition:

### Steps:
1. 

### Time & Space complexity:
**Time:** `O(
**Space:** `O(

Where `n` is 

### C++ Code:
```cpp
```

### Java Code:
```java
```
