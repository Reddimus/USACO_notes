#include <bits/stdc++.h>

using namespace std;


class UF {
public:
    vector<int> parents;

    UF(int n) {
        parents.resize(n);
        iota(parents.begin(), parents.end(), 0); // Efficient initialization
    }

    int find(int i) {
        if (parents[i] != i)
            parents[i] = find(parents[i]); // Path compression
        return parents[i];
    }

    void un(int i, int j) {
        int ri = find(i), rj = find(j);
        if (ri != rj)
            parents[ri] = rj; // Union by rank or size can be added for efficiency
    }

    bool co(int i, int j) {
        return find(i) == find(j);
    }
};

int n, m, t, F[100001], G[100001];
long long f[100001], g[100001];

int main() {
    freopen("test.in", "r", stdin);
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n >> m;
        UF uf(n + 1);
        memset(f, 127, sizeof(f));
        memset(g, 127, sizeof(g));
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            uf.un(u, v);
        }
        int l = uf.find(1), r = uf.find(n);
        f[l] = 0, g[r] = 0;
        int cntF = 0, cntG = 0;
        for (int i = 1; i <= n; i++){
            int u = uf.find(i);
            if (u == l) F[++cntF] = i;
            else if (u == r) G[++cntG] = i;
        }
        for (int i = 1; i <= n; i++){
            int u = uf.find(i);
            if (u != l){
                int idx = upper_bound(F + 1, F + cntF + 1, i) - F - 1;
                f[u] = min(f[u], (long long)(i - F[idx]) * (i - F[idx]));
                if (idx < cntF)
                    idx++, f[u] = min(f[u], (long long)(i - F[idx]) * (i - F[idx]));
                
            }
            if (u != r){
                int idx = upper_bound(G + 1, G + cntG + 1, i) - G;
                g[u] = min(g[u], (long long)(i - G[idx]) * (i - G[idx]));
                if (idx > 1)
                    idx--, g[u] = min(g[u], (long long)(i - G[idx]) * (i - G[idx]));
            }
        }
        long long ans = (long long)(n - 1ll) * (n - 1ll);;
        for (int i = 1; i <= n; i++)
            ans = min(ans, f[uf.find(i)] + g[uf.find(i)]);
        cout << ans << '\n';
    }
    return 0;
}