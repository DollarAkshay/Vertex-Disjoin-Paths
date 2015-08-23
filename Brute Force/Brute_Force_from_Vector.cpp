#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

#define FOR(i,a,b)  for(int i=a; i<=b; ++i)
#define FORD(i,a,b) for(int i=a; i>=b; --i)
#define REP(i,n)    for(int i=0; i<n ; i++)
#define ll long long
#define sp system("pause")

int n;
vector<int> nodes;
vector<vector<int>> adjacency;

FILE *input = fopen("../Brute Force/Input.txt", "r");
FILE *output = fopen("../Brute Force/Vector Output.txt", "w");

void printPath(int a,int b,vector<int> path) {

	int dist = 0, prev = a;
	fprintf(output, "%d", a);
	for (int i = 0; i<path.size(); prev = path[i++]) {
		fprintf(output, "->%d", path[i]);
		dist += adjacency[prev][path[i]];
	}
	fprintf(output, "->%d", b);
	dist += adjacency[prev][b];
	fprintf(output, " (Dist : %d)\n", dist);

}

vector<int> getSubset(vector<int> a, int s) {

	vector<int> res;
	for (int i = 0; s && i<a.size(); s/=2, i++) {
		if (s%2==1)
			res.push_back(a[i]);
	}
	return res;
}

vector<int> subtractSubsetFromSet(vector<int> super, vector<int> sub) {

	vector<int> res;
	for (int i=0, j=0; i<super.size(); i++) {
		if (j>=sub.size() || super[i]!=sub[j]) 
			res.push_back(super[i]);
		else
			j++;
	}
	return res;
}

ll int printAllPathsBetween(int a, int b) {

	ll int subsetsCount1, subsetsCount2, pathCount = 0;
	vector<int> path1, path2;
	vector<int> pathnodes1(nodes), pathnodes2;

	pathnodes1.erase(pathnodes1.begin()+a);
	pathnodes1.erase(pathnodes1.begin()+b-1);

	subsetsCount1 = 1L<<pathnodes1.size();

	REP(i, subsetsCount1) {

		path1 = getSubset(pathnodes1, i);
		pathnodes2 = subtractSubsetFromSet(pathnodes1, path1);
		subsetsCount2 = 1L<<pathnodes2.size();

		REP(j, subsetsCount2) {
			path2 = getSubset(pathnodes2, j);
			printPath(a, b, path1);
			printPath(a, b, path2);
			fprintf(output, "\n");
			pathCount++;
		}
	}

	return pathCount;
}

int main(){

	//Reading Input 
	fscanf(input, "%d", &n);

	REP(i, n) {
		vector<int> temp;
		REP(j, n) {
			int dist;
			fscanf(input, "%d", &dist);
			temp.push_back(dist);
		}
		adjacency.push_back(temp);
	}
	printf("Done reading Input\n");

	// Reduce Number of nodes (for testing)
	n = 13;

	// Create a set of Nodes
	REP(i,n)
		nodes.push_back(i);

	// Print the paths
	int start = 0, end = n-1;
	clock_t t = clock();
	ll int pathCount = printAllPathsBetween(start, end);
	t = clock() - t;

	fprintf(output, "\n\n------------------- STATS -------------------\n");
	fprintf(output, " ! Time Taken = %f sec for %d nodes \n", (float)t/CLOCKS_PER_SEC, 13);
	fprintf(output, " ! Found %d paths between %d and %d \n", pathCount, start, end);
	printf("Done printing path\n");

	fclose(input);
	fclose(output);
	sp;

	return 0;
}

