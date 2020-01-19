// Implementation of min cost max flow algorithm using linked list
// For a regular max flow, set all edge costs to 0. If you use Dijkstra i.o.
// Levit next comments are true
//
// Running time, O(|V|^2) cost per augmentation
//     max flow:           O(|V|^3) augmentations
//     min cost max flow:  O(|V|^4 * MAX_EDGE_COST) augmentations
//
// INPUT:
//     - graph, constructed using AddEdge()
//     - source
//     - sink
//
// OUTPUT:
//     - (maximum flow value, minimum cost value)
//     - To obtain the actual flow, look at positive values only.

#include <cmath>
#include <vector>
#include <iostream>
#include <queue>
#include <limits>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long L;
typedef vector<L> VL;
typedef vector<VL> VVL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;

const L INF = numeric_limits<L>::max() / 4;

struct MinCostMaxFlow {
  const L INF = 1000*1000*1000;
  
  struct rib {
    L b, u, c, f;
    size_t back;
  };
  
  int n;
  vector<vector<rib>> g;
  
  MinCostMaxFlow(int n_): n(n_), g(n) {}
  
  void AddEdge(int a, int b, L cap, L cost) {
    rib r1 = { b, cap, cost, 0, g[b].size() };
    rib r2 = { a, 0, -cost, 0, g[a].size() };
    g[a].push_back (r1);
    g[b].push_back (r2);
  }
  
  pair<L, L> GetMaxFlow(int s, int t, int k=INF) {
    L flow = 0,  cost = 0;
    while (flow < k) {
      vector<int> id (n, 0);
      vector<int> d (n, INF);
      vector<int> q (n);
      vector<int> p (n);
      vector<size_t> p_rib (n);
      int qh=0, qt=0;
      q[qt++] = s;
      d[s] = 0;
      while (qh != qt) {
        int v = q[qh++];
        id[v] = 2;
        if (qh == n)  qh = 0;
        for (size_t i=0; i<g[v].size(); ++i) {
          rib & r = g[v][i];
          if (r.f < r.u && d[v] + r.c < d[r.b]) {
            d[r.b] = d[v] + r.c;
            if (id[r.b] == 0) {
              q[qt++] = r.b;
              if (qt == n)  qt = 0;
            }
            else if (id[r.b] == 2) {
              if (--qh == -1)  qh = n-1;
              q[qh] = r.b;
            }
            id[r.b] = 1;
            p[r.b] = v;
            p_rib[r.b] = i;
          }
        }
      }
      if (d[t] == INF)  break;
      L addflow = k - flow;
      for (int v=t; v!=s; v=p[v]) {
        int pv = p[v];  size_t pr = p_rib[v];
        addflow = min (addflow, g[pv][pr].u - g[pv][pr].f);
      }
      for (int v=t; v!=s; v=p[v]) {
        int pv = p[v];  size_t pr = p_rib[v],  r = g[pv][pr].back;
        g[pv][pr].f += addflow;
        g[v][r].f -= addflow;
        cost += g[pv][pr].c * addflow;
      }
      flow += addflow;
    }
    return {flow, cost};
  }
};;
// BEGIN CUT
// The following code solves UVA problem #10594: Data Flow

int main() {
  int N, M;

  while (cin >> N >> M) {
    VVL v(M, VL(3));
    for (int i = 0; i < M; i++)
      cin >> v[i][0] >> v[i][1] >> v[i][2];
    L D, K;
    cin >> D >> K;

    MinCostMaxFlow mcmf(N+1);
    for (int i = 0; i < M; i++) {
      mcmf.AddEdge(int(v[i][0]), int(v[i][1]), K, v[i][2]);
      mcmf.AddEdge(int(v[i][1]), int(v[i][0]), K, v[i][2]);
    }
    mcmf.AddEdge(0, 1, D, 0);
    
    pair<L, L> res = mcmf.GetMinCostMaxFlow(0, N);

    if (res.second == D) {
      cout << res.first << '\n';
    } else {
      cout << "Impossible.\n";
    }
  }
  
  return 0;
}
