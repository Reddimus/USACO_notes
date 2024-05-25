#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    // Open input file
    ifstream fin("Binary_Search/Silver_P1_2017-Why_Did_The_Cow_Cross_The_Road/helpcross.in");
    if (!fin) {
        cerr << "Error opening input file" << endl;
        return 1;
    }

    int c, n;
    fin >> c >> n;

    vector<int> chick_sched(c);
    vector<pair<int, int>> cow_sched(n);

    // Read chicken schedules
    for (int i = 0; i < c; ++i) {
        fin >> chick_sched[i];
    }

    // Read cow schedules
    for (int i = 0; i < n; ++i) {
        fin >> cow_sched[i].first >> cow_sched[i].second;
    }

    fin.close();

    // Sort chicken and cow schedules
    sort(chick_sched.begin(), chick_sched.end());
    sort(cow_sched.begin(), cow_sched.end());

    int cnt_pairs = 0;
    int cow_idx = 0;
    priority_queue<int, vector<int>, greater<int>> available_cows;

    for (int chick_time : chick_sched) {
        // Add all the cows whose start times now include the chicken's time
        while (cow_idx < n && cow_sched[cow_idx].first <= chick_time) {
            available_cows.push(cow_sched[cow_idx].second);
            ++cow_idx;
        }

        // Remove all the ending times that end too early for the chicken
        while (!available_cows.empty() && available_cows.top() < chick_time) {
            available_cows.pop();
        }

        // Have the cow help the chicken with the earliest end time
        if (!available_cows.empty()) {
            ++cnt_pairs;
            available_cows.pop();
        }
    }

    // Open output file and write answer
    ofstream fout("Binary_Search/Silver_P1_2017-Why_Did_The_Cow_Cross_The_Road/helpcross.out");
    if (!fout) {
        cerr << "Error opening output file" << endl;
        return 1;
    }

    fout << cnt_pairs << endl;
    fout.close();

    return 0;
}