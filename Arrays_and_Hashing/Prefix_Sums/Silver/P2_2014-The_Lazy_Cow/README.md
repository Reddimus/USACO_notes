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

## Solution Explanation

Apply a rotation of 45 degrees on the grid like follows. Our goal is that, instead of a diamond as seen in the problem statement, the cells that Bessie can walk to form a square.

<table>
	<tr>
		<td colspan="2">0</td>
		<td colspan="2">0</td>
		<td colspan="2">50</td>
		<td colspan="2">0</td>
		<td colspan="2">0</td>
	</tr>
	<tr>
		<td></td>
		<td colspan="2">0</td>
		<td colspan="2">14</td>
		<td colspan="2">5</td>
		<td colspan="2">0</td>
		<td></td>
	</tr>
	<tr>
		<td colspan="2">0</td>
		<td colspan="2">99</td>
		<td colspan="2">3</td>
		<td colspan="2">25</td>
		<td colspan="2">0</td>
	</tr>
	<tr>
		<td></td>
		<td colspan="2">8</td>
		<td colspan="2">10</td>
		<td colspan="2">2</td>
		<td colspan="2">6</td>
		<td></td>
	</tr>
	<tr>
		<td colspan="2">10</td>
		<td colspan="2">7</td>
		<td colspan="2">1</td>
		<td colspan="2">7</td>
		<td colspan="2">17</td>
	</tr>
	<tr>
		<td></td>
		<td colspan="2">0</td>
		<td colspan="2">5</td>
		<td colspan="2">2</td>
		<td colspan="2">21</td>
		<td></td>
	</tr>
	<tr>
		<td colspan="2">0</td>
		<td colspan="2">78</td>
		<td colspan="2">23</td>
		<td colspan="2">80</td>
		<td colspan="2">0</td>
	</tr>
	<tr>
		<td></td>
		<td colspan="2">0</td>
		<td colspan="2">1</td>
		<td colspan="2">11</td>
		<td colspan="2">0</td>
		<td></td>
	</tr>
	<tr>
		<td colspan="2">0</td>
		<td colspan="2">0</td>
		<td colspan="2">9</td>
		<td colspan="2">0</td>
		<td colspan="2">0</td>
	</tr>
</table>

If we simply cram all the diagonals into rows, it creates this weird brick-like structure.
This makes no sense as all as there are half-distances, how do you even put this into a 2D array?
To resolve the half-distances issue, we simply expand the grid by a factor of 2, adding zeroes in as filler.
Note that we add zeroes because they cannot impact the final sum.

<table>
	<tr>
		<td>0</td>
		<td>0</td>
		<td>0</td>
		<td>0</td>
		<td>50</td>
		<td>0</td>
		<td>0</td>
		<td>0</td>
		<td>0</td>
	</tr>
	<tr>
		<td>0</td>
		<td>0</td>
		<td>0</td>
		<td>14</td>
		<td>0</td>
		<td>5</td>
		<td>0</td>
		<td>0</td>
		<td>0</td>
	</tr>
	<tr>
		<td>0</td>
		<td>0</td>
		<td>99</td>
		<td>0</td>
		<td>3</td>
		<td>0</td>
		<td>25</td>
		<td>0</td>
		<td>0</td>
	</tr>
	<tr>
		<td>0</td>
		<td>8</td>
		<td>0</td>
		<td>10</td>
		<td>0</td>
		<td>2</td>
		<td>0</td>
		<td>6</td>
		<td>0</td>
	</tr>
	<tr>
		<td>10</td>
		<td>0</td>
		<td>7</td>
		<td>0</td>
		<td>1 (B)</td>
		<td>0</td>
		<td>7</td>
		<td>0</td>
		<td>17</td>
	</tr>
	<tr>
		<td>0</td>
		<td>0</td>
		<td>0</td>
		<td>5</td>
		<td>0</td>
		<td>2</td>
		<td>0</td>
		<td>21</td>
		<td>0</td>
	</tr>
	<tr>
		<td>0</td>
		<td>0</td>
		<td>78</td>
		<td>0</td>
		<td>23</td>
		<td>0</td>
		<td>80</td>
		<td>0</td>
		<td>0</td>
	</tr>
	<tr>
		<td>0</td>
		<td>0</td>
		<td>0</td>
		<td>1</td>
		<td>0</td>
		<td>11</td>
		<td>0</td>
		<td>0</td>
		<td>0</td>
	</tr>
	<tr>
		<td>0</td>
		<td>0</td>
		<td>0</td>
		<td>0</td>
		<td>9</td>
		<td>0</td>
		<td>0</td>
		<td>0</td>
		<td>0</td>
	</tr>
</table>

<Info title="Thinking from a geometric standpoint">

Initially, the distance between adjacent cells is $1$ and the distance between cells connected diagonally is $\sqrt{2}$.
What we have done here is a dilation by a scale of $\sqrt{2}$, making the distance between adjacent cells now $\sqrt{2}$ and between cells $\sqrt{2} \cdot \sqrt{2} = 2$.

If we then rotate by 45 degrees and add 0s inbetween, everything falls into place. Try to visualize this in your head!

</Info>

To demonstrate what we have achieved, now look at the cells that Bessie (B) can reach when K = 2, the exact situation in the problem statement.

<table>
	<tr>
		<td>99</td>
		<td>0</td>
		<td>3</td>
		<td>0</td>
		<td>25</td>
	</tr>
	<tr>
		<td>0</td>
		<td>10</td>
		<td>0</td>
		<td>2</td>
		<td>0</td>
	</tr>
	<tr>
		<td>7</td>
		<td>0</td>
		<td>1 (B)</td>
		<td>0</td>
		<td>7</td>
	</tr>
	<tr>
		<td>0</td>
		<td>5</td>
		<td>0</td>
		<td>2</td>
		<td>0</td>
	</tr>
	<tr>
		<td>78</td>
		<td>0</td>
		<td>23</td>
		<td>0</td>
		<td>80</td>
	</tr>
</table>

This range is now a square, which grants us much more possibilities!

To calculate the sum of the numbers in these squares, which are now the shapes of squares, we can use 2D prefix sums to calculate the sum of these square in constant time.
This way, we can brute force through all the squares Bessie can be and take the maximum sum.
