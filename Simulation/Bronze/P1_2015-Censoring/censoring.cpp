#include <bits/stdc++.h>

using namespace std;

int main() {
    freopen("censor.in", "r", stdin);
    string s, t;
    cin >> s >> t;

    string censoredContent;
    for (char sc : s) {
        censoredContent.push_back(sc);

        if (censoredContent.size() >= t.size() &&
        censoredContent.compare(censoredContent.size() - t.size(), t.size(), t) == 0)
            censoredContent.resize(censoredContent.size() - t.size());
    }

    freopen("censor.out", "w", stdout);
    cout << censoredContent << endl;
    return 0;
}
