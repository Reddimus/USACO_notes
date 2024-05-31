with open("highcard.in") as f:
    n = int(f.readline())
    Elsie = [int(f.readline()) for _ in range(n)]
Elsie.sort()  # Sort Elsie's cards
Bessie = sorted(set(range(1, 2 * n + 1)) - set(Elsie)) # Calculate the cards Bessie has

l = r = 0
while r < n:
    # Find the first card in Bessie's set that is larger than Elsie's current card
    while r < n and Elsie[l] > Bessie[r]:
        r += 1
    # Move to the next round
    l += 1
    r += 1

print(l, file=open("highcard.out", "w"))
