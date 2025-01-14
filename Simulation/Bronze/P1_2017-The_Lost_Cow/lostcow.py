with open('lostcow.in', 'r') as fin:
    x, y = map(int, fin.readline().split())

left, right = False, True
total_distance = 0
direction_distance = 1

# While our x +- direction_distance is not in the range of Y
while ((right and x > y or y > x + direction_distance) or
       (left and x < y or y < x - direction_distance)):
    # Double the distance and toggle the direction
    direction_distance *= 2
    total_distance += direction_distance
    left, right = not left, not right  # Toggle the direction

total_distance += abs(x - y)  # Add the remaining distance

with open('lostcow.out', 'w') as fout:
    print(total_distance, file=fout)
