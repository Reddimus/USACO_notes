# Read in 1st line: n = # of flowers
N = int(input())
# Read in 2nd line: the petals of each flower
flower_petals = list(map(int, input().split()))

avg_count = N
for i in range(N - 1):
    current_sum = flower_petals[i]

    petal_count = [0] * 1000
    petal_count[flower_petals[i]] += 1
    for j in range(i + 1, N):
        current_sum += flower_petals[j]
        petal_count[flower_petals[j]] += 1

        length = j - i + 1
        if current_sum % length != 0:
            continue

        if petal_count[current_sum // length] > 0:
            avg_count += 1

print(avg_count)
