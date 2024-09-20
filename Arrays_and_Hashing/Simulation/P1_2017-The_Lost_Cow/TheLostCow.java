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
		int x = Integer.parseInt(st.nextToken());
		int y = Integer.parseInt(st.nextToken());
		in.close();

		Direction direction = new Direction(false, true);
		int totalDistance = 0, directionDistance = 1;
		while ((direction.right && x > y || y > x + directionDistance) ||
		(direction.left && x < y || y < x - directionDistance)) {
			directionDistance *= 2;
			totalDistance += directionDistance;
			direction.toggle();
		}
		totalDistance += Math.abs(y - x);

		PrintWriter out = new PrintWriter("lostcow.out");
		out.println(totalDistance);
		out.close();
	}
}
