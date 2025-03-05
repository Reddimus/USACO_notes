import java.io.*;

public class CircleCross {
    public static void main(String[] args) throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("circlecross.in"));
        char[] s = fin.readLine().toCharArray();
        fin.close();

        int crossPairs = 0;
        for (int i = 0; i < s.length - 3; i++)
            for (int j = i + 1; j < s.length - 2; j++)
                for (int k = j + 1; k < s.length - 1; k++)
                    for (int l = k + 1; l < s.length; l++)
                        if (s[i] == s[k] && s[j] == s[l])
                            crossPairs++;
        
        PrintWriter fout = new PrintWriter("circlecross.out");
        fout.println(crossPairs);
        fout.close();
    }
}
