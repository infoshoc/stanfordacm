//BEGIN CUT
#include <cstdio>
//END CUT

struct SegmentTree{
    static const int N = 1e5;  // limit for array size
    int n;  // array size
    int t[2 * N];

    void build() {  // build the tree
        for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
    }

    void modify(int p, int value) {  // set value at position p
        for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
    }

    int query(int l, int r) {  // sum on interval [l, r)
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += t[l++];
            if (r&1) res += t[--r];
        }
        return res;
    }
};

// BEGIN CUT

SegmentTree st;

int main() {
  scanf("%d", &st.n);
  for (int i = 0; i < st.n; ++i) scanf("%d", st.t + st.n + i);
  st.build();
  st.modify(0, 1);
  printf("%d\n", st.query(3, 11));
  return 0;
}

// END CUT
