#  Bucket sort approach
#  T: O(N), M: O(101 * 3 + 3) ≈ O(1)

with open("measurement.in", "r") as fin:
    # Read 1st line: number of measurements
    N = int(fin.readline().strip())
    bessie_timestamp = [0] * 101
    elsie_timestamp = [0] * 101
    mildred_timestamp = [0] * 101
    first_timestamp, last_timestamp = 101, 0
    # For the next N lines create bucket sorted arrays for each cow
    for i in range(N):
        timestamp, cow, change = fin.readline().split()
        timestamp, change = int(timestamp), int(change)

        if cow == "Bessie":
            bessie_timestamp[timestamp] += change
        elif cow == "Elsie":
            elsie_timestamp[timestamp] += change
        else:
            mildred_timestamp[timestamp] += change

        first_timestamp = min(first_timestamp, timestamp)
        last_timestamp = max(last_timestamp, timestamp)

display_changes = 0
lead_cows = set(['B', 'E', 'M'])
bessie_milk = elsie_milk = mildred_milk = 7
# For each milk production change
for i in range(first_timestamp, last_timestamp + 1):
    if (bessie_timestamp[i] == 0 and
    elsie_timestamp[i] == 0 and
    mildred_timestamp[i] == 0):
        continue

    # Re-calculate the milk production for each cow change
    bessie_milk += bessie_timestamp[i]
    elsie_milk += elsie_timestamp[i]
    mildred_milk += mildred_timestamp[i]

    max_milk = max(bessie_milk, elsie_milk, mildred_milk)
    curr_lead_cows = set()
    if bessie_milk == max_milk:
        curr_lead_cows.add('B')
    if elsie_milk == max_milk:
        curr_lead_cows.add('E')
    if mildred_milk == max_milk:
        curr_lead_cows.add('M')

    # If the lead cows have changed, increment the display changes
    if not curr_lead_cows == lead_cows:
        display_changes += 1
        lead_cows = curr_lead_cows

print(display_changes, file=open("measurement.out", "w"))
