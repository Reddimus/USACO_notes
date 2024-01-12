import java.io.*;
import java.util.*;

public class ClosingFarm {
	static class DisjointSetUnion {
		int[] parent, size;
		DisjointSetUnion(int n) {
			parent = new int[n];
			size = new int[n];
			for (int i = 0; i < n; i++) {
				parent[i] = i;
				size[i] = 1;
			}
		}

		// Recursively find and assign parent of current node
		int findParent(int node) {
			if (parent[node] == node) 
				return node;
			// Path compression optimization
			parent[node] = findParent(parent[node]);
			return parent[node];
		}

		// Attempt to union two components
		boolean unionComponenets(int a, int b) {
			a = findParent(a);
			b = findParent(b);
			if (a == b)	// If nodes are already in same component
				return false;

			// Union by size optimization
			if (size[a] < size[b]) {
				int temp = a;
				a = b;
				b = temp;
			}
			// Merge smaller component (b) into larger component (a)
			parent[b] = a;
			size[a] += size[b];
			return true;
		}
	}
	public static void main(String[] args) throws IOException {
		
	}
}
