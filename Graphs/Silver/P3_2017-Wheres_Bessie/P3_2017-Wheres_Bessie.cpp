// Flood Fill - Depth First Search approach
// T: O(N^4), M: O(N^2)
// Where `N` is side length of the N x N image

#include <bits/stdc++.h>

using namespace std;

#define NMAX 20

int n;
char image[NMAX][NMAX];

struct PCL {
	int r1, c1;
	int r2, c2;

	bool is_inside(PCL other) {
		return r1 >= other.r1 && c1 >= other.c1 && r2 <= other.r2 && c2 <= other.c2;
	}
};

// Check wheter the given sub rectangle is a PCL
bool is_pcl(int rMin, int cMin, int rMax, int cMax) {
	// keep track of number of color components
	int regionCount[26] = {0};

	bool visited[NMAX][NMAX] = {false};
	// Depth first search common color within sub rectangle boundaries
	function<void(int, int, char)> floodfill = [&](int r, int c, char color) {
		if (r < rMin || r > rMax || 
		c < cMin || c > cMax || 
		image[r][c] != color || 
		visited[r][c])
			return;
		
		visited[r][c] = true;
		
		floodfill(r + 1, c, color);
		floodfill(r - 1, c, color);
		floodfill(r, c + 1, color);
		floodfill(r, c - 1, color);
	};
	
	// Within the sub rectangle, flood fill each color component
	for (int r = rMin; r <= rMax; ++r) {
		for (int c = cMin; c <= cMax; ++c) {
			if (!visited[r][c]) {
				char color = image[r][c];
				floodfill(r, c, color);
				++regionCount[color - 'A'];
			}
		}
	}

	// Determine if the sub rectangle is a PCL
	int colorCount = 0;
	bool singleRegion = false, multiRegion = false;
	for (int i = 0; i < 26 && colorCount <= 2; ++i) {
		if (regionCount[i] == 0)
			continue;
		
		if (regionCount[i] == 1)
			singleRegion = true;
		else if (regionCount[i] > 1)
			multiRegion = true;
		++colorCount;
	}
	return colorCount == 2 && singleRegion && multiRegion;
}

int main() {
	freopen("where.in", "r", stdin);
	// Read first line: n = side length of the N x N image
	cin >> n;
	// For the next N lines read in image descriptions
	for (int r = 0; r < n; ++r) 
		for (int c = 0; c < n; ++c) 
			cin >> image[r][c];

	// Brute force every sub rectangle to find PCLs
	vector<PCL> pcls;
	for (int r1 = 0; r1 < n; ++r1) 
		for (int c1 = 0; c1 < n; ++c1) 
			for (int r2 = r1; r2 < n; ++r2) 
				for (int c2 = c1; c2 < n; ++c2) 
					if (is_pcl(r1, c1, r2, c2)) 
						pcls.push_back({r1, c1, r2, c2});

	// Filter out overlapping PCLs & count the number of valid PCLs
	int pclCount = 0;
	for (int i = 0; i < pcls.size(); ++i) {
		bool validPCL = true;
		for (int j = 0; j < pcls.size(); ++j) {
			if (i != j && pcls[i].is_inside(pcls[j])) {
				validPCL = false;
				break;
			}
		}
		pclCount += validPCL;
	}

	freopen("where.out", "w", stdout);
	cout << pclCount << endl;
	return 0;
}