# Prefix sums approach
# T & M: O(n), where n is size of Fjs actions

# Gather list of fjs choices from input file
with open('hps.in', 'r') as f:
    # first line: n = amount of games played
    n = int(f.readline().strip())
    # Intialize prefix sum arrays with 0th index dummy value
    hooves = [0] * (n + 1)
    paper = [0] * (n + 1)
    scissors = [0] * (n + 1)
    # Populate the hooves, paper, and scissors prefix arrays (Notes down action wins for every iteration)
    for i in range(1, n + 1):
        # update prefix sums with prev vals
        hooves[i] += hooves[i - 1]
        paper[i] += paper[i - 1]
        scissors[i] += scissors[i - 1]
        # grab input & assign win to best choice
        action = f.readline().strip()
        if action == "H":
            paper[i] += 1
        elif action == "P":
            scissors[i] += 1
        elif action == "S":
            hooves[i] += 1
# Using prefix sums allows us to check all win combinations in O(n) time
max_wins = 0
for i in range(1, n + 1):
    # calculate max current wins
    before_wins = max(hooves[i], paper[i], scissors[i])
    # calculate max wins after current iteration to the end
    after_wins = max(hooves[n] - hooves[i], paper[n] - paper[i], scissors[n] - scissors[i])
    max_wins = max(max_wins, before_wins + after_wins)
# write max_wins answer to output file
print(max_wins, file=open("hps.out", "w"))
