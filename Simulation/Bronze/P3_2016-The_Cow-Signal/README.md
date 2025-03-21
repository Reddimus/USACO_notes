# [USACO 2016 December Contest, Bronze](https://usaco.org/index.php?page=dec16results)

## [Problem 3. The Cow-Signal](https://usaco.org/index.php?page=viewproblem2&cpid=665)

Bessie and her cow friends are playing as their favorite cow superheroes.  Of
course, everyone knows that any self-respecting superhero needs a signal to call
them to action. Bessie has drawn a special signal on a sheet of $M \times N$
paper ($1 \leq M \leq 10, 1 \leq N \leq 10$), but this is too small, much too
small! Bessie wants to amplify the signal so it is exactly $K$ times bigger
($1 \leq K \leq 10$) in each direction.

The signal will consist only of the '.' and 'X' characters.

### INPUT FORMAT (file cowsignal.in)

The first line of input contains $M$, $N$, and $K$, separated by spaces.  

The next $M$ lines each contain a length-$N$ string, collectively describing the
picture of the signal.

### OUTPUT FORMAT (file cowsignal.out)

You should output $KM$ lines, each with $KN$ characters, giving a picture of the
enlarged signal.

### SAMPLE INPUT

```plaintext
5 4 2
XXX.
X..X
XXX.
X..X
XXX.
```

### SAMPLE OUTPUT

```plaintext
XXXXXX..
XXXXXX..
XX....XX
XX....XX
XXXXXX..
XXXXXX..
XX....XX
XX....XX
XXXXXX..
XXXXXX..
```

Problem credits: Nathan Pinsker
