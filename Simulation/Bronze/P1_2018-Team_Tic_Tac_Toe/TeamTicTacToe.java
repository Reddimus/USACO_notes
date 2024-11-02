import java.util.*;
import java.io.*;

public class TeamTicTacToe {
    static char[][] board = new char[3][3];

    static boolean checkHorizontalWin(Set<Character> cowTeams) {
        for (int r = 0; r < 3; ++r) {
            int validCharCount = 0;
            Set<Character> currCowTeammates = new HashSet<>();
            for (int c = 0; c < 3; ++c) {
                if (cowTeams.contains(board[r][c])) {
                    currCowTeammates.add(board[r][c]);
                    validCharCount++;
                }
            }
            
            if (validCharCount == 3 && currCowTeammates.size() == cowTeams.size())
                return true;
        }
        return false;
    }

    static boolean checkVerticalWin(Set<Character> cowTeams) {
        for (int c = 0; c < 3; ++c) {
            int countValidChars = 0;
            Set<Character> currCowTeammates = new HashSet<>();
            for (int r = 0; r < 3; ++r) {
                if (cowTeams.contains(board[r][c])) {
                    currCowTeammates.add(board[r][c]);
                    countValidChars++;
                }
            }

            if (countValidChars == 3 && currCowTeammates.size() == cowTeams.size())
                return true;
        }
        return false;
    }

    static boolean checkDiagonalWin(Set<Character> cowTeams) {
        Set<Character> currCowTeammates = new HashSet<>();
        int countValidChars = 0;
        for (int i = 0; i < 3; ++i) {
            if (cowTeams.contains(board[i][i])) {
                currCowTeammates.add(board[i][i]);
                countValidChars++;
            }
        }
        if (countValidChars == 3 && currCowTeammates.size() == cowTeams.size())
            return true;

        currCowTeammates.clear();
        countValidChars = 0;
        for (int i = 0; i < 3; ++i) {
            if (cowTeams.contains(board[i][2 - i])) {
                currCowTeammates.add(board[i][2 - i]);
                countValidChars++;
            }
        }
        return countValidChars == 3 && currCowTeammates.size() == cowTeams.size();
    }

    static boolean checkWin(List<Character> cowMembers) {
        Set<Character> cowTeams = new HashSet<>(cowMembers);
        return (
            checkHorizontalWin(cowTeams) ||
            checkVerticalWin(cowTeams) ||
            checkDiagonalWin(cowTeams)
        );
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("tttt.in"));
        for (int r = 0; r < 3; ++r)
            board[r] = in.readLine().toCharArray();
        in.close();

        HashSet<Character> cowTeams = new HashSet<>();

        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                cowTeams.add(board[r][c]);

        int singleWins = 0;
        for (char cowTeam : cowTeams)
            if (checkWin(List.of(cowTeam)))
                singleWins++;

        int doubleWins = 0;
        for (char cowTeam1 : cowTeams)
            for (char cowTeam2 : cowTeams)
                if (cowTeam1 < cowTeam2 && checkWin(List.of(cowTeam1, cowTeam2)))
                    doubleWins++;

        PrintWriter out = new PrintWriter(new FileWriter("tttt.out"));
        out.println(singleWins);
        out.println(doubleWins);
        out.close();
    }
}