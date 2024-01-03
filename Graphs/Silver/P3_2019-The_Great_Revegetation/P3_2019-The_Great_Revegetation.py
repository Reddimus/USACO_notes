with open("revegetate.in", "r") as f:
    n, m = map(int, f.readline().split())
    adj = [[] for ln in range(n)]
    for ln in range(m):
        grass_type, a, b = f.readline().split()
        a, b = int(a) - 1, int(b) - 1
        adj[a].append((b, grass_type == 'S'))
        adj[b].append((a, grass_type == 'S'))
        
print(adj)