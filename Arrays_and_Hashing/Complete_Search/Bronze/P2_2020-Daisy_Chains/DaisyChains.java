import java.io.*;
import java.util.*;

public class DaisyChains {
	public static void main(String[] args) throws IOException {
		Scanner sc = new Scanner(System.in);
		// Read in 1st line: n = # of flowers
		final int N = sc.nextInt();
		// Read in 2nd line: the petals of each flower
		int[] flowerPetals = new int[N];
		for (int i = 0; i < N; i++)
			flowerPetals[i] = sc.nextInt();
		sc.close();

		int avgFlowerPicCount = N;
		for (int i = 0; i < N - 1; i++) {
			int sum = flowerPetals[i];

			Map<Integer, Integer> petalCount = new HashMap<>();
			petalCount.put(flowerPetals[i], 1);
			for (int j = i + 1; j < N; j++) {
				sum += flowerPetals[j];

				petalCount.put(
					flowerPetals[j],
					petalCount.getOrDefault(flowerPetals[j], 0) + 1
				);

				int length = j - i + 1;
				if (sum % length != 0)
					continue;

				// Check # of flowers with the current average # of petals in the window range
				if (petalCount.getOrDefault(sum / length, 0) > 0)
					avgFlowerPicCount++;
			}
		}

		System.out.println(avgFlowerPicCount);
	}
}
