# First line: n = number of cows
n = int(input())
# For the next n lines: x, y = coordinates of cow
cows = [tuple(map(int, input().split())) for ln in range(n)]

# Coordinate compression
cows.sort()  # Sort by x
reduced_x = {cows[c][0]: c for c in range(n)}
cows.sort(key=lambda c: c[1])  # Sort by y
reduced_y = {cows[c][1]: c for c in range(n)}

for i in range(n):
    x, y = cows[i]
    cows[i] = reduced_x[x], reduced_y[y]

# Sort by x again
cows.sort()
# Make prefix sums for the y-lines
lt_y = [[0] * (n + 1) for r in range(n)]
gt_y = [[0] * (n + 1) for r in range(n)]
for c in range(n):
    curr_y = cows[c][1]
    for x in range(1, n + 1):
        lt_y[curr_y][x] = lt_y[curr_y][x - 1] + (cows[x - 1][1] < curr_y)
        gt_y[curr_y][x] = gt_y[curr_y][x - 1] + (cows[x - 1][1] > curr_y)

total = 0
for c1 in range(n - 1):
    for c2 in range(c1 + 1, n):
        bottom = min(cows[c1][1], cows[c2][1])
        top = max(cows[c1][1], cows[c2][1])

        bottom_total = 1 + lt_y[bottom][c2 + 1] - lt_y[bottom][c1]
        top_total = 1 + gt_y[top][c2 + 1] - gt_y[top][c1]
        total += bottom_total * top_total

# Include boxes where Farmer John just contains either a single cow or none at all
total += n + 1

print(total)

# Run in cmd prompt: python3 P2_2020-Rectangular_Pasture.py < input.in