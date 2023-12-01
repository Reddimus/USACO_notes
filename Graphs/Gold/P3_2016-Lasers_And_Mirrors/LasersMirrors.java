import java.io.*;
import java.util.*;

public class LasersMirrors {
    static class Coordinates {
        int x, y;
        Coordinates(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("lasers.in"));

        // First line: n = number of mirrors, laser coordinates, barn coordinates
        StringTokenizer st = new StringTokenizer(in.readLine());
        int n = Integer.parseInt(st.nextToken());
        Coordinates laser = new Coordinates(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));

    }
}