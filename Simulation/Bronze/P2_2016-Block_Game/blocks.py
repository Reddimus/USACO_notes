with open("blocks.in", "r") as fin:
    N = int(fin.readline())
    boards = [tuple(fin.readline().split()) for _ in range(N)]

def count_freq(word):
    freq = [0] * 26
    for char in word:
        freq[ord(char) - ord('a')] += 1
    return freq

max_blocks = [0] * 26
for word1, word2 in boards:
    char_count1, char_count2 = count_freq(word1), count_freq(word2)
    for ci in range(26):
        max_blocks[ci] += max(char_count1[ci], char_count2[ci])

with open("blocks.out", "w") as fout:
    for count in max_blocks:
        fout.write(f"{count}\n")
