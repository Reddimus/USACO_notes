import java.util.*;
import java.io.*;

public class MilkPails {
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new FileReader("pails.in"));
		StringTokenizer st = new StringTokenizer(br.readLine());
		final int X = Integer.parseInt(st.nextToken());
		final int Y = Integer.parseInt(st.nextToken());
		final int M = Integer.parseInt(st.nextToken());
		br.close();

		int amountLeft = M;
		while(amountLeft >= X) {
			if (amountLeft < Y)
				amountLeft -= X;
			else if(amountLeft % Y > amountLeft % X)
				amountLeft -= X;
			else
				amountLeft -= Y;
		}

		PrintWriter out = new PrintWriter("pails.out");
		out.println(M - amountLeft);
		out.close();
	}
}
