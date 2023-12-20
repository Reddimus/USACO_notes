// Custom Comparators + Sort + Greedy approach
// T: O(n * m), M: O(n + m + r) 
// Where n is num of cows, m is num of shops, and r is num of neighbors

import java.io.*;
import java.util.*;

public class RentalService {
	static class Shop {
		int demand, rate;
		Shop(int demand, int rate) {
			this.demand = demand;
			this.rate = rate;
		}
	}

	public static void main(String[] args) throws IOException {
		// Open Rental input file
		BufferedReader in = new BufferedReader(new FileReader("rental.in"));
		// Read first line: n = num of cows, m = num of shops, r = num of neighbors
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int r = Integer.parseInt(st.nextToken());
		// For the next n lines track milk produced per cow
		Integer[] milk = new Integer[n];
		for (int cow = 0; cow < n; cow++)
			milk[cow] = Integer.parseInt(in.readLine());
		// For the next m lines track demand & rate of each shop that wants to buy milk
		Shop[] shops = new Shop[m];
		for (int shopCustomer = 0; shopCustomer < m; shopCustomer++) {
			st = new StringTokenizer(in.readLine());
			int demand = Integer.parseInt(st.nextToken());
			int rate = Integer.parseInt(st.nextToken());
			shops[shopCustomer] = new Shop(demand, rate);
		}
		// For the next r lines track neighbor's that want to rent cows
		Integer[] rent = new Integer[r];
		for (int neighborCustomer = 0; neighborCustomer < r; neighborCustomer++)
			rent[neighborCustomer] = Integer.parseInt(in.readLine());
		in.close();

		// Sort in reverse; we always want to milk the cow that produces the most milk
		Arrays.sort(milk, Collections.reverseOrder());
		Arrays.sort(shops, Collections.reverseOrder(Comparator.comparingInt(a -> a.rate)));
		Arrays.sort(rent, Collections.reverseOrder());

		// Calculate maximum revenue
		long revenue = 0;
		boolean cachedPrice = false;
		int jugs = 0, jugsPrice = 0, lastSold = 0, tempIdx = 0;
		int cowIdx = 0, shopIdx = 0, rentIdx = 0;
		while (cowIdx < n) {
			if (!cachedPrice) {
				// Calculate potential revenue if cow were to be milked
				jugs = milk[cowIdx];
				jugsPrice = 0;
				lastSold = 0;
				tempIdx = shopIdx;
				while (tempIdx < m) {
					int sold = Math.min(jugs, shops[tempIdx].demand);
					jugsPrice += sold * shops[tempIdx].rate;
					jugs -= sold;
					if (jugs == 0) {
						lastSold = sold;
						break;
					}
					tempIdx++;
				}
			}

			// Compare rent a cow price to potential milked price
			if (rentIdx < r && rent[rentIdx] > jugsPrice) {
				revenue += rent[rentIdx];
				cachedPrice = true;
				rentIdx++;
				n--;	// rent cow that produces least milk
			}
			else {
				revenue += jugsPrice;
				shopIdx = tempIdx;
				if (shopIdx < m)
					shops[shopIdx].demand -= lastSold;
				cachedPrice = false;
				cowIdx++;
			}
		}
		
		// Write maximum revenue/profit to output file 
		PrintWriter out = new PrintWriter("rental.out");
		out.println(revenue);
		out.close();
	}
}


/*
// Custom Comparators + Sort + Greedy approach | without cached value
// T: O(n * m), M: O(n + m + r) 
// Where n is num of cows, m is num of shops, and r is num of neighbors

import java.io.*;
import java.util.*;

public class RentalService {
	static class Shop {
		int demand, rate;
		Shop(int demand, int rate) {
			this.demand = demand;
			this.rate = rate;
		}
	}

	public static void main(String[] args) throws IOException {
		// Open Rental input file
		BufferedReader in = new BufferedReader(new FileReader("rental.in"));
		// Read first line: n = num of cows, m = num of shops, r = num of neighbors
		StringTokenizer st = new StringTokenizer(in.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int r = Integer.parseInt(st.nextToken());
		// For the next n lines track milk produced per cow
		Integer[] milk = new Integer[n];
		for (int cow = 0; cow < n; cow++)
			milk[cow] = Integer.parseInt(in.readLine());
		// For the next m lines track demand & rate of each shop that wants to buy milk
		Shop[] shops = new Shop[m];
		for (int shopCustomer = 0; shopCustomer < m; shopCustomer++) {
			st = new StringTokenizer(in.readLine());
			int demand = Integer.parseInt(st.nextToken());
			int rate = Integer.parseInt(st.nextToken());
			shops[shopCustomer] = new Shop(demand, rate);
		}
		// For the next r lines track neighbor's that want to rent cows
		Integer[] rent = new Integer[r];
		for (int neighborCustomer = 0; neighborCustomer < r; neighborCustomer++)
			rent[neighborCustomer] = Integer.parseInt(in.readLine());
		in.close();

		// Sort in reverse; we always want to milk the cow that produces the most milk
		Arrays.sort(milk, Collections.reverseOrder());
		Arrays.sort(shops, Collections.reverseOrder(Comparator.comparingInt(a -> a.rate)));
		Arrays.sort(rent, Collections.reverseOrder());

		// Calculate maximum revenue
		long revenue = 0;
		int cowIdx = 0, shopIdx = 0, rentIdx = 0;
		while (cowIdx < n) {
			// Calculate potential revenue if cow were to be milked
			int jugs = milk[cowIdx], jugsPrice = 0, lastSold = 0;
			int tempIdx = shopIdx;
			while (tempIdx < m) {
				int sold = Math.min(jugs, shops[tempIdx].demand);
				jugsPrice += sold * shops[tempIdx].rate;
				jugs -= sold;
				if (jugs == 0) {
					lastSold = sold;
					break;
				}
				tempIdx++;
			}

			// Compare rent a cow price to potential milked price
			if (rentIdx < r && rent[rentIdx] > jugsPrice) {
				revenue += rent[rentIdx];
				rentIdx++;
				n--;	// rent cow that produces least milk
			}
			else {
				revenue += jugsPrice;
				shopIdx = tempIdx;
				if (shopIdx < m)
					shops[shopIdx].demand -= lastSold;
				cowIdx++;
			}
		}
		
		// Write maximum revenue/profit to output file 
		PrintWriter out = new PrintWriter("rental.out");
		out.println(revenue);
		out.close();
	}
}
*/