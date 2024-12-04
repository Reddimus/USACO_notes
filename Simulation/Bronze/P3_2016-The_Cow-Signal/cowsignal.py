with open("cowsignal.in", "r") as fin:
    # Read in first line: M = # of lines, N = # of chars in each line, K = multiplier
    M, N, K = map(int, fin.readline().split())
    signal: list[str] = [fin.readline() for row in range(M)]

print("M:", M, "N:", N, "K:", K)
print("Signal:")
for row in signal:
    print(row, end="")
print()