with open("blist.in", 'r') as fin:
    # Read in first line: n = # of buckets
    n = int(fin.readline())
    # For the next n lines, read in the start, end, and buckets needed
    in_use = [0] * 1001
    for _ in range(n):
        start, end, buckets_needed = map(int, fin.readline().split())
        for j in range(start, end + 1):
            in_use[j] += buckets_needed

print(max(in_use), file=open("blist.out", 'w'))
