# [USACO 2013 US Open, Silver](https://usaco.org/index.php?page=open13problems)

## [Problem 3. Luxury River Cruise](https://usaco.org/index.php?page=viewproblem2&cpid=284)

Problem 3: Luxury River Cruise [Josh Alman and Nathan Pinsker, 2013]

Farmer John is taking Bessie and the cows on a cruise! They are sailing on a
network of rivers with N ports (1 <= N <= 1,000) labeled 1..N, and Bessie
starts at port 1. Each port has exactly two rivers leading out of it which
lead directly to other ports, and rivers can only be sailed one way.

At each port, the tour guides choose either the "left" river or the "right"
river to sail down next, but they keep repeating the same choices over and
over. More specifically, the tour guides have chosen a short sequence of M
directions (1 <= M <= 500), each either "left" or "right", and have
repeated it K times (1 <= K <= 1,000,000,000). Bessie thinks she is going
in circles -- help her figure out where she ends up!

PROBLEM NAME: cruise

INPUT FORMAT:

* Line 1: Three space-separated integers N, M, and K.

* Lines 2..N+1: Line i+1 has two space-separated integers,
        representing the number of the ports that port i's left and
        right rivers lead to, respectively.

* Line N+2: M space-separated characters, either 'L' or 'R'. 'L'
        represents a choice of  'left' and 'R' represents a choice of
        'right'.

SAMPLE INPUT (file cruise.in):

```plaintext
4 3 3
2 4
3 1
4 2
1 3
L L R
```

INPUT DETAILS:

The port numbers are arranged clockwise in a circle, with 'L' being a
clockwise rotation and 'R' being a counterclockwise rotation. The sequence
taken is LLRLLRLLR.

OUTPUT FORMAT:

* Line 1: A single integer giving the number of the port where
        Bessie's cruise ends.

SAMPLE OUTPUT (file cruise.out):

4

OUTPUT DETAILS:

After the first iteration of the sequence of directions, Bessie is at port
2 (1 -> 2 -> 3 -> 2); after the second, she is at port 3 (2 -> 3 -> 4 ->
3), and at the end she is at port 4 (3 -> 4 -> 1 -> 4).
