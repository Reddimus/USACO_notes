import java.io.*;
import java.util.*;

class CowInformation implements Comparable<CowInformation> {
	char statement;
	int pos;

	public CowInformation(char statement, int pos) {
		this.statement = statement;
		this.pos = pos;
	}

	@Override
	public int compareTo(CowInformation c) {
		if (pos != c.pos)
			return pos - c.pos;
		return statement - c.statement;
	}
}

public class CoutningLiars {
	public static void main(String[] args) throws IOException {
		Scanner sc = new Scanner(System.in);
		// Read in 1st line: n = # of other cows
		final int N = sc.nextInt();
		// For the next n lines, read in the cow's statement and position
		CowInformation[] cowInfo = new CowInformation[N];
		for (int i = 0; i < N; i++)
			cowInfo[i] = new CowInformation(sc.next().charAt(0), sc.nextInt());
		sc.close();

		// Sort by position, then by statement
		/*
		Arrays.sort(
			cowInfo,
			(a, b) -> {
				if (a.pos != b.pos)
					return a.pos - b.pos;
				return a.statement - b.statement;
			}
		);
		*/
		Arrays.sort(cowInfo);

		// lying_left[i] stores the number of cows to the left of cow i
		// that must be lying given that Bessie is at the position of cow i.
		int[] lyingLeft = new int[N];
		for (int i = 1; i < N; i++) {
			// Add up all the cows that are lying to the left of our position.
			lyingLeft[i] += lyingLeft[i - 1];

			/*
			* If the cow before says our position is to the left
			* but their position is strictly less than our position,
			* they're lying.
			*/
			if (cowInfo[i - 1].statement == 'L')
				lyingLeft[i]++;
		}

		// lying_right stores the same thing, but does it so for the cows
		// to the *right* of i.
		int[] lyingRight = new int[N];
		// Fill it up in much the same way.
		for (int i = N - 2; i >= 0; i--) {
			lyingRight[i] += lyingRight[i + 1];

			if (cowInfo[i + 1].statement == 'G')
				lyingRight[i]++;
		}

		int minLiars = N;
		for (int i = 0; i < N; i++)
			minLiars = Math.min(minLiars, lyingLeft[i] + lyingRight[i]);

		System.out.println(minLiars);
	}
}
