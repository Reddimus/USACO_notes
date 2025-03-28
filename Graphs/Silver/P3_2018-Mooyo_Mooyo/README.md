# [USACO 2018 December Contest, Silver](https://usaco.org/index.php?page=dec18results)

## [Problem 3. Mooyo Mooyo](https://usaco.org/index.php?page=viewproblem2&cpid=860)

With plenty of free time on their hands (or rather, hooves), the cows on Farmer
John's farm often pass the time by playing video games.  One of their favorites
is based on a popular human video game called Puyo Puyo; the cow version is of
course called Mooyo Mooyo.

The game of Mooyo Mooyo is played on a tall narrow grid $N$ cells tall
($1 \leq N \leq 100$) and 10 cells wide.  Here is an example with $N = 6$:

```plaintext
0000000000
0000000300
0054000300
1054502230
2211122220
1111111223
```

Each cell is either empty (indicated by a 0), or a haybale in one of nine
different colors (indicated by characters 1..9).  Gravity causes haybales to
fall downward, so there is never a 0 cell below a haybale.  

Two cells belong to the same connected region if they are directly adjacent
either horizontally or vertically, and they have the same nonzero color.  Any
time a connected region exists with at least $K$ cells, its haybales all
disappear, turning into zeros.  If multiple such connected regions exist at the
same time, they all disappear simultaneously.  Afterwards, gravity might cause
haybales to fall downward to fill some of the resulting cells that became zeros.
In the resulting configuration, there may again be connected regions of size at
least $K$ cells.  If so, they also disappear (simultaneously, if there are
multiple such regions), then gravity pulls the remaining cells downward, and the
process repeats until no connected regions of size at least $K$ exist.  

Given the state of a Mooyo Mooyo board, please output a final picture of the
board after these operations have occurred.

### INPUT FORMAT (file mooyomooyo.in)

The first line of input contains $N$ and $K$ ($1 \leq K \leq 10N$). The
remaining $N$ lines specify the initial state of the board.

### OUTPUT FORMAT (file mooyomooyo.out)

Please output $N$ lines, describing a picture of the final board state.

### SAMPLE INPUT

```plaintext
6 3
0000000000
0000000300
0054000300
1054502230
2211122220
1111111223
```

### SAMPLE OUTPUT

```plaintext
0000000000
0000000000
0000000000
0000000000
1054000000
2254500000
```

In the example above, if $K = 3$, then there is a connected region of size at
least $K$ with color 1 and also one with color 2.  Once these are simultaneously
removed, the board temporarily looks like this:

```plaintext
0000000000
0000000300
0054000300
1054500030
2200000000
0000000003
```

Then, gravity takes effect and the haybales drop to this configuration:

```plaintext
0000000000
0000000000
0000000000
0000000000
1054000300
2254500333
```

Again, there is a region of size at least $K$ (with color 3).  Removing it
yields the final board configuration:

```plaintext
0000000000
0000000000
0000000000
0000000000
1054000000
2254500000
```

Problem credits: Brian Dean
