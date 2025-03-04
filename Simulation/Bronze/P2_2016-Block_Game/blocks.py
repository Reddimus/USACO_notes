# Step 1: Read in the inputs
with open("blocks.in", "r") as fin:
    N = int(fin.readline())
    boards = [tuple(fin.readline().split()) for _ in range(N)]

ASCII_A = ord('a')

def count_freq(word):
    freq = [0] * 26
    for char in word:
        freq[ord(char) - ASCII_A] += 1
    return freq

max_blocks = [0] * 26
# Step 2: Look at both words at the same time
for word1, word2 in boards:
    # Step 3: Count the frequency of each character for both word1, word2
    char_count1, char_count2 = count_freq(word1), count_freq(word2)
    # Step 4: Count the max (worse case scenerio) blocks/characters needed
    for ci in range(26):
        max_blocks[ci] += max(char_count1[ci], char_count2[ci])

# Step 5: Print out the frequency of each character in max_blocks
with open("blocks.out", "w") as fout:
    for count in max_blocks:
        fout.write(f"{count}\n")
