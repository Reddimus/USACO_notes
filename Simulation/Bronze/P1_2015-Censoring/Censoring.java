import java.io.*;

public class Censoring {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("censor.in"));
		
		final char[] S = in.readLine().toCharArray();
		final String T = in.readLine();
		in.close();
		
		StringBuilder censoredContent = new StringBuilder();
		for (char c : S) {
			censoredContent.append(c);
			if (censoredContent.length() >= T.length() &&
			censoredContent.substring(censoredContent.length() - T.length()).equals(T)) {
				censoredContent.delete(censoredContent.length() - T.length(), censoredContent.length());
			}
		}
		
		PrintWriter out = new PrintWriter("censor.out");
		out.println(censoredContent.toString());
		out.close();
	}
}
