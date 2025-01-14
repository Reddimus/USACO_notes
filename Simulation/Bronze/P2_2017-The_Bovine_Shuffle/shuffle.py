SHUFFLE_NUM = 3

with open("shuffle.in", "r") as fin:
    # Read in first line: n = # of cows
    N = int(fin.readline())
    # Read in second line: shuffles for each cow
    shuffles = list(map(int, fin.readline().split()))
    # Read in third line: initial cow ids
    ids = list(map(int, fin.readline().split()))

for _ in range(SHUFFLE_NUM):
    past_order = ids.copy()  # Save the current order before updating
    for i in range(N):
        ids[i] = past_order[shuffles[i] - 1]  # Adjust for 0-based indexing

# Write the result to the output file
with open("shuffle.out", "w") as fout:
    for cow_id in ids:
        fout.write(f"{cow_id}\n")
