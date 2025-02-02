import java.io.*;
import java.util.*;

public class Triangles {
    public static void main(String[] args) throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("triangles.in"));
        // Read first line: N = Distinct points
        final int N = Integer.parseInt(fin.readLine());
        // For the next N lines, read in x and y coordinates
        Map<Integer, List<Integer>> horizontalIntersect = new HashMap<>();   
        Map<Integer, List<Integer>> verticalIntersect = new HashMap<>();     
        for (int i = 0; i < N; i++) {
            StringTokenizer st = new StringTokenizer(fin.readLine());
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());

            horizontalIntersect.putIfAbsent(y, new ArrayList<>());
            horizontalIntersect.get(y).add(x);

            verticalIntersect.putIfAbsent(x, new ArrayList<>());
            verticalIntersect.get(x).add(y);
        }
        fin.close();

        // Find all possible triangles
        int maxArea = 0;
        for (final int yBase : horizontalIntersect.keySet()) {
            final int xListSize = horizontalIntersect.get(yBase).size();
            for (int i = 0; i < xListSize; i++) {
                final int xBase1 = horizontalIntersect.get(yBase).get(i);
                for (int j = i + 1; j < xListSize; j++) {
                    final int xBase2 = horizontalIntersect.get(yBase).get(j);
                    final int baseLength = Math.abs(xBase1 - xBase2);
                    
                    // Find the height/area of the triangle from each base point
                    for (int k = 0; k < verticalIntersect.get(xBase1).size(); k++) {
                        final int yHeight = verticalIntersect.get(xBase1).get(k);
                        final int height = Math.abs(yHeight - yBase);
                        maxArea = Math.max(maxArea, baseLength * height);
                    }

                    for (int k = 0; k < verticalIntersect.get(xBase2).size(); k++) {
                        final int yHeight = verticalIntersect.get(xBase2).get(k);
                        final int height = Math.abs(yHeight - yBase);
                        maxArea = Math.max(maxArea, baseLength * height);
                    }
                }
            }
        }

        PrintWriter fout = new PrintWriter("triangles.out");
        fout.println(maxArea);
        fout.close();
    }
}
