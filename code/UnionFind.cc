// BEGIN CUT
#include <iostream>
#include <vector>
using namespace std;

// END CUT
struct UnionFind {
    vector < int > parent;
    vector < int > rank;
    UnionFind(int n) : parent(n), rank(n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    int find_set (int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set (parent[v]);
    }
    void union_sets (int a, int b) {
        a = find_set (a);
        b = find_set (b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap (a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                ++rank[a];
        }
    }
};
// BEGIN CUT

int main()
{
	int n = 5;
	UnionFind C(n);
	C.union_sets(0, 2);
	C.union_sets(1, 0);
	C.union_sets(3, 4);
	for (int i = 0; i < n; i++) cout << i << " " << C.find_set(i) << endl;
	return 0;
}

// END CUT
