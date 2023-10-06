# USACO 2016 February Contest, Gold
## Problem 2. Circular Barn Revisited

http://www.usaco.org/current/index.php?page=viewproblem2&cpid=622

After the last debacle involving Farmer John's circular barn, one would think he had learned his lesson about non-traditional architecture. However, he thinks he can still make his circular barn function properly by allowing multiple cows into each room. To recap, the barn consists of a ring of `n` rooms, numbered clockwise from `1...n` around the perimeter of the barn `(3 <= n <= 100)`. Each room has doors to its two neighboring rooms, and also a door opening to the exterior of the barn.

Farmer John wants exactly `ri` cows to end up in room `i` `(1 <= ri <= 1,000,000)`. To herd the cows into the barn in an orderly fashion, he plans to unlock `k` exterior doors `(1 <= k <= 7)`, allowing the cows to enter through only those doors. Each cow then walks clockwise through the rooms until she reaches a suitable destination. Farmer John wants to unlock the exterior doors that will cause his cows to collectively walk a minimum total amount of distance after entering the barn.

### Input Format (file cbarn2.in):

The first line of input contains `n` and `k`. Each of the remaining `n` lines contain `r1...rn`.

### Output Format (file cbarn2.out):

Please write out the minimum amount of distance the cows need to travel.

### Sample Input
```
6 2
2
5
4
2
6
2
```

### Sample Output
```
14
```

Farmer John can unlock doors 2 and 5. 11 cows enter at door 2 and walk a total distance of 8 to get to rooms 2, 3, and 4. 10 cows enter at door 5 and walk a total distance of 6 to get to rooms 5, 6 and 1.

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
