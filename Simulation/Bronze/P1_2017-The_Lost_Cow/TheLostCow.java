import java.io.*;
import java.util.*;

class Direction {
	public boolean left, right;

	Direction(boolean left, boolean right) {
		this.left = left;
		this.right = right;
	}

	public void toggle() {
		left = !left;
		right = !right;
	}
}

public class TheLostCow {
	public static void main(String[] args) throws IOException {
		BufferedReader in = new BufferedReader(new FileReader("lostcow.in"));
		StringTokenizer st = new StringTokenizer(in.readLine());
		final int X = Integer.parseInt(st.nextToken());
		final int Y = Integer.parseInt(st.nextToken());
		in.close();

		Direction direction = new Direction(false, true);
		int totalDistance = 0, directionDistance = 1;
		// While our x +- directionDistance is not in the range of Y
		while ((direction.right && X > Y || Y > X + directionDistance) ||
		(direction.left && X < Y || Y < X - directionDistance)) {
			// double the distance and toggle the direction
			directionDistance *= 2;
			totalDistance += directionDistance;
			direction.toggle();
		}
		totalDistance += Math.abs(X - Y);

		PrintWriter out = new PrintWriter("lostcow.out");
		out.println(totalDistance);
		out.close();
	}
}
