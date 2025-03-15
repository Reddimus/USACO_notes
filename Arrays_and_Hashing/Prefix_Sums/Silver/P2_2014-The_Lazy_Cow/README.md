# [USACO 2014 March Contest, Silver](https://usaco.org/index.php?page=mar14problems)

## [Problem 2. The Lazy Cow](https://usaco.org/index.php?page=viewproblem2&cpid=416)

Problem 2: The Lazy Cow [Silver] [Brian Dean, 2014]

It's a hot summer day, and Bessie the cow is feeling quite lazy.  She wants
to locate herself at a position in her field so that she can reach as much
delicious grass as possible within only a short distance.

The field Bessie inhabits is described by an N by N grid of square cells  
(1 <= N <= 400).  The cell in row r and column c (1 <= r,c <= N) contains
G(r,c) units of grass (0 <= G(r,c) <= 1000).  From her initial square in
the grid, Bessie is only willing to take up to K steps (0 <= K <= 2*N).
Each step she takes moves her to a cell that is directly north, south,
east, or west of her current location.

For example, suppose the grid is as follows, where (B) describes Bessie's
initial position (here, in row 3, column 3):

```txt
50    5     25*   6     17    
14    3*    2*    7*    21    
99*   10*   1*(B) 2*    80*    
8     7*    5*    23*   11   
10    0     78*   1     9        
```

If K=2, then Bessie can only reach the locations marked with *s.

Please help Bessie determine the maximum amount of grass she can reach, if
she chooses the best possible initial location in the grid.

PROBLEM NAME: lazy

INPUT FORMAT:

* Line 1: The integers N and K.

* Lines 2..1+N: Line r+1 contains N integers describing row r of the
        grid.

SAMPLE INPUT (file lazy.in):

```txt
5 2
50 5 25 6 17
14 3 2 7 21
99 10 1 2 80
8 7 5 23 11
10 0 78 1 9
```

OUTPUT FORMAT:

* Line 1: The maximum amount of grass Bessie can reach, if she chooses
        the best possible initial location (the location from which
        she can reach the most grass).

SAMPLE OUTPUT (file lazy.out):

```txt
342
```

OUTPUT DETAILS:

In the example above, Bessie can reach 342 total units of grass if she
locates herself in the middle of the grid.
