#include <bits/stdc++.h>
using namespace std;

int n, Bessie[50001], Elsie[50002];

int main() {
    freopen("highcard.in", "r", stdin);
    freopen("highcard.out", "w", stdout);
    cin >> n; 
    for (int i = 1; i <= n; i++) 
        cin >> Elsie[i];  
    Elsie[n + 1] = n * 2;  // Add a boundary value to prevent bessie cards from missing statistics
    sort(Elsie + 1, Elsie + 1 + n);  // Sort Elsie's cards

    // Calculate the cards Bessie has
    for (int i = 1, j = 1; i <= n + 1; i++) 
        for (int k = Elsie[i - 1] + 1; k < Elsie[i]; k++)
            Bessie[j++] = k;  // Fill Bessie's cards with the remaining cards not in Elsie's set

    int l = 1, r = 1;
    while (r <= n) {
        // Find the first card in Bessie's set that is larger than Elsie's current card
        while (r < n && Elsie[l] > Bessie[r])
            r++;
        l++, r++;  // Move to the next round
    }
    cout << l - 1 << endl;
}
