with open("mowing.in", 'r') as fin:
    N = int(fin.readline())
    instructions = [fin.readline().split() for _ in range(N)]

curr_cord = (0, 0)
visited = {curr_cord: 0}
time = 0
max_regrow = float('inf')

# Process each movement command
for direction, steps in instructions:
    # Determine movement delta based on direction
    dx = dy = 0
    if direction == 'N':
        dy = 1
    elif direction == 'S':
        dy = -1
    elif direction == 'E':
        dx = 1
    elif direction == 'W':
        dx = -1

    # Move in the specified direction for numSteps
    for _ in range(int(steps)):
        curr_cord = (curr_cord[0] + dx, curr_cord[1] + dy)
        time += 1

        # Check if the cell was visited before
        if curr_cord in visited:
            last_visit_time = visited[curr_cord]
            max_regrow = min(max_regrow, time - last_visit_time)

        # Update the last visit time for the current cell
        visited[curr_cord] = time

# Output the result, -1 if no revisit occurred
print(
    max_regrow if max_regrow != float('inf') else -1,
    file=open("mowing.out", 'w')
)
