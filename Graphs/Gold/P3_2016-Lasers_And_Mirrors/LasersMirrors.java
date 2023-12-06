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
        Coordinates laser = new Coordinates(
            Integer.parseInt(st.nextToken()), 
            Integer.parseInt(st.nextToken()));
        Coordinates barn = new Coordinates(
            Integer.parseInt(st.nextToken()), 
            Integer.parseInt(st.nextToken()));
        
        // For the next n lines, map mirror x & y coordinates for quick lookup
        Map<Integer, ArrayList<Integer>> xToY = new HashMap<>(), yToX = new HashMap<>();
        for (int mirror = 0; mirror < n; mirror++) {
            st = new StringTokenizer(in.readLine());
            int x = Integer.parseInt(st.nextToken()), y = Integer.parseInt(st.nextToken());

            xToY.putIfAbsent(x, new ArrayList<>());
            xToY.get(x).add(y);

            yToX.putIfAbsent(y, new ArrayList<>());
            yToX.get(y).add(x);
        }
        in.close();

        // Breadth-first search intercepting mirrors or goals for shortest path
        int count = -1;
        Queue<Coordinates> q = new LinkedList<>();
        q.add(laser);
        for (int level = 0; !q.isEmpty(); ++level) {
            final int qSize = q.size();
            for (int qNum = 0; qNum < qSize; ++qNum) {
                Coordinates mirror = q.poll();

                // Check for goal
                if (mirror.x == barn.x || mirror.y == barn.y) {
                    count = level;
                    q = new LinkedList<>(); // Clear queue
                    break;
                }

                // Find intercepting mirrors
                for (int y : xToY.getOrDefault(mirror.x, new ArrayList<>()))
                    q.add(new Coordinates(mirror.x, y));
                for (int x : yToX.getOrDefault(mirror.y, new ArrayList<>()))
                    q.add(new Coordinates(x, mirror.y));

                // Mark all mirrors/coordinates subset as visited
                xToY.remove(mirror.x);
                yToX.remove(mirror.y); 
            }
        }

        // Write -1 if no solution, else write the minimum number of mirrors
        PrintWriter out = new PrintWriter("lasers.out");
        out.println(count);
        out.close();
    }
}