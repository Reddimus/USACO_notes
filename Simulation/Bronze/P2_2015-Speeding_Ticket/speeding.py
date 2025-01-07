with open("speeding.in", "r") as fin:
    # Read first line: n = road segments, m = bessie's segments
    n, m = map(int, fin.readline().split())
    # For the next n lines read in road segments
    speed_limits = [0] * 100
    last_position = 0
    for ln in range(n):
        length, speed_limit = map(int, fin.readline().split())
        # For each mile in the road assign the speed limit using last position -> last position + length
        for mile in range(last_position, last_position + length):
            speed_limits[mile] = speed_limit

        # Update last position
        last_position += length

    # For the next m lines read in bessie's segments
    bessie_speeds = [0] * 100
    last_position = 0
    for ln in range(m):
        length, speed = map(int, fin.readline().split())
        for mile in range(last_position, last_position + length):
            bessie_speeds[mile] = speed

        last_position += length

max_over: int = max(bessie_speeds[mile] - speed_limits[mile] for mile in range(100))

print(max_over, file=open("speeding.out", "w"))
