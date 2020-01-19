int l = 179; // question is count paths of this length
int ans = 0;

bool used[maxn];
int s[maxn]; // subtree sizes

void sizes (int v, int p) {
    s[v] = 1;
    for (int u : g[v])
        if (u != p && !used[u])
            sizes(u, v), s[v] += s[u];
}

int centroid (int v, int p, int n) {
    for (int u : g[v])
        if (u != p && !used[u] && s[u] > n/2)
            return centroid(u, v, n);
    return v;
}

// t is depth of vertices in subtree
void dfs (int v, int p, int d, vector<int> &t) {
    t.push_back(d);
    for (int u : g[v])
        if (u != p && !used[u])
            dfs(u, v, d + 1, t);
} 

void solve (int v) {
    /* BEGIN CUT */
    sizes(v);
    vector<int> d(s[v], 0);
    d[0] = 1;
    for (int u : g[v]) {
        if (!used[u]) {
            vector<int> t;
            dfs(u, v, 1, t);
            for (int x : t)
                if (x <= l)
                    ans += d[l-x];
            for (int x : t)
                d[x]++;
        }
    }
    /* END CUT */

    used[v] = 1;
    for (int u : g[v])
        if (!used[u])
            solve(centroid(u, v, s[u]));
}


