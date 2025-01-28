ROWS = COLS = 3

board = open("tttt.in").read().splitlines()

def check_horizontal(teams):
    for r in range(ROWS):
        valid_char_count = 0
        curr_teams = set()
        for c in range(COLS):
            if board[r][c] in teams:
                valid_char_count += 1
                curr_teams.add(board[r][c])

        if valid_char_count == 3 and len(curr_teams) == len(teams):
            return True

    return False

def check_vertical(teams):
    for c in range(COLS):
        valid_char_count = 0
        curr_teams = set()
        for r in range(ROWS):
            if board[r][c] in teams:
                valid_char_count += 1
                curr_teams.add(board[r][c])

        if valid_char_count == 3 and len(curr_teams) == len(teams):
            return True
    return False

def check_diagonal(teams):
    # Main diagonal
    valid_char_count = 0
    curr_teams = set()
    for i in range(3):
        if board[i][i] in teams:
            valid_char_count += 1
            curr_teams.add(board[i][i])

    if valid_char_count == 3 and len(curr_teams) == len(teams):
        return True

    # Other diagonal
    valid_char_count = 0
    curr_teams = set()
    for i in range(3):
        if board[i][2-i] in teams:
            valid_char_count += 1
            curr_teams.add(board[i][2-i])

    return valid_char_count == 3 and len(curr_teams) == len(teams)

def check_win(teams):
    teams = set(teams)
    return (
        check_horizontal(teams) or
        check_vertical(teams) or
        check_diagonal(teams)
    )

cow_teams = set(board[r][c] for r in range(ROWS) for c in range(COLS))

single_wins = 0
for team in cow_teams:
    if check_win([team]):
        single_wins += 1

pair_wins = 0
for team1 in cow_teams:
    for team2 in cow_teams:
        if team1 < team2 and check_win([team1, team2]):
            pair_wins += 1

with open("tttt.out", "w") as fout:
    fout.write(f"{single_wins}\n")
    fout.write(f"{pair_wins}\n")
