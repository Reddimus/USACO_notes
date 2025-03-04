with open("censor.in", "r") as fin:
    S = fin.readline().strip()
    T = fin.readline().strip()

stack = []
t_len = len(T)
for c in S:
    stack.append(c)
    if len(stack) >= t_len and "".join(stack[-t_len:]) == T:
        del stack[-t_len:]

print(''.join(stack), file=open("censor.out","w"))
