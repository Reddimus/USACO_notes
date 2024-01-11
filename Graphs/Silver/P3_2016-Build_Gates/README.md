# [USACO 2016 January Contest, Silver](http://www.usaco.org/index.php?page=jan16results)
## [Problem 3. Build Gates](http://www.usaco.org/index.php?page=viewproblem2&cpid=596)

Farmer John decides to build a new fence around parts of his farm, but he keeps getting distracted and ends up building the fence into a much stranger shape than he intended!

Specifically, FJ starts at position `(0,0)` and takes `N` steps, each moving one unit of distance north, south, east, or west. Each step he takes, he lays a unit of fence behind him. For example, if his first step is to the north, he adds a segment of fence from `(0,0)` to `(0,1)`. FJ might re-visit points multiple times and he may even lay the same segment of fence multiple times. His fence might even cross over itself if his path cuts through a run of fencing he has already built.

Needless to say, FJ is rather dismayed at the result after he completes the fence. In particular, he notices that it may be the case that he has now partitioned off some areas of the farm from others, so that one can no longer walk from one region to another without crossing a fence. FJ would like to add gates to his fences to fix this problem. A gate can be added to any unit-length segment of fence he has built, allowing passage between the two sides of this segment.

Please determine the minimum number of gates FJ needs to build so that every region of the farm is once again reachable from every other region.

### INPUT FORMAT (file gates.in):

The first line of input contains `N` `(1≤N≤1000)`. The next line contains a string of length `N` describing FJ's path. Each character is either `N (north)`, `E (east)`, `S (south)`, or `W (west)`.

### OUTPUT FORMAT (file gates.out):

Write out a single integer giving the minimum number of gates FJ needs to build to restore complete connectivity to all regions of his farm. Note that the answer could be zero if the farm is connected to begin with.

### SAMPLE INPUT:

```
14
NNNESWWWSSEEEE
```

### SAMPLE OUTPUT:

```
2
```