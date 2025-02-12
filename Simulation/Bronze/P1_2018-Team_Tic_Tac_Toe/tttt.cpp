#include <bits/stdc++.h>
#define ROWS 3
#define COLS 3

using namespace std;

string board[ROWS];

bool check_horizontal(unordered_set<char>& teams) {
    for (int r = 0; r < ROWS; r++) {
        int validCharCount = 0;
        unordered_set<char> currCowTeammates;
        for (int c = 0; c < COLS; c++) {
            if (teams.find(board[r][c]) != teams.end()) {
                currCowTeammates.insert(board[r][c]);
                validCharCount++;
            }
        }

        if (validCharCount == 3 && currCowTeammates.size() == teams.size())
            return true;
    }
    return false;
}

bool check_vertical(unordered_set<char>& teams) {
    for (int c = 0; c < COLS; c++) {
        int validCharCount = 0;
        unordered_set<char> currCowTeammates;
        for (int r = 0; r < ROWS; r++) {
            if (teams.find(board[r][c]) != teams.end()) {
                currCowTeammates.insert(board[r][c]);
                validCharCount++;
            }
        }

        if (validCharCount == 3 && currCowTeammates.size() == teams.size())
            return true;
    }
    return false;
}

bool check_diagonals(unordered_set<char>& teams) {
    int validCharCount = 0;
    unordered_set<char> currCowTeammates;
    for (int i = 0; i < ROWS; i++) {
        if (teams.find(board[i][i]) != teams.end()) {
            currCowTeammates.insert(board[i][i]);
            validCharCount++;
        }
    }

    if (validCharCount == 3 && currCowTeammates.size() == teams.size())
        return true;

    validCharCount = 0;
    currCowTeammates.clear();
    for (int i = 0; i < ROWS; i++) {
        if (teams.find(board[i][ROWS - i - 1]) != teams.end()) {
            currCowTeammates.insert(board[i][ROWS - i - 1]);
            validCharCount++;
        }
    }

    return validCharCount == 3 && currCowTeammates.size() == teams.size();
}

bool check_win(vector<char> teams) {
    unordered_set<char> ts(teams.begin(), teams.end());
    return check_horizontal(ts) ||
        check_vertical(ts) ||
        check_diagonals(ts);
}

int main() {
    freopen("tttt.in", "r", stdin);
    for (int r = 0; r < ROWS; r++)
        cin >> board[r];
    
    unordered_set<char> cowTeams;
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            cowTeams.insert(board[r][c]);

    int singleWins = 0;
    for (char ct : cowTeams)
        if (check_win({ct}))
            singleWins++;

    int doubleWins = 0;
    for (char ct1 : cowTeams)
        for (char ct2 : cowTeams)
            if (ct1 < ct2 && check_win({ct1, ct2}))
                doubleWins++;

    freopen("tttt.out", "w", stdout);
    cout << singleWins << endl;
    cout << doubleWins << endl;
    return 0;
}
