#include <bits/stdc++.h>

using namespace std;
//using LL = long long;
//using pii = pair<LL, int>;
typedef long long LL;
typedef pair<LL, int> pii;

const int N = 5e3+10;
const LL INF = 0x3f3f3f3f3f3f3f3f;

vector<pii> edge[N];
vector<pii> edge2[N];

void add(int u, int v, LL l) {
  edge[u].push_back(pii(l, v));
  edge2[v].push_back(pii(l, u));
}

LL dis[N];
void dijkstra(int s) {
  priority_queue<pii> pq;
  pq.push(pii(0, s));
  while (!pq.empty()) {
    int u = pq.top().second;
    LL d = -pq.top().first;
    pq.pop();
    if (dis[u] <= d) continue;
    dis[u] = d;
    for (int i = 0; i < (int)edge2[u].size(); ++i) {
      int v = edge2[u][i].second;
      if (dis[u] + edge2[u][i].first < dis[v]) {
        pq.push(pii(-dis[u]-edge2[u][i].first, v));
      }
    }
  }
}

typedef pair<LL, pii> tup;
int tim[N];
LL Astar(int s, int t, int k, int n) {
  priority_queue<tup> pq2;
  memset(dis+1, 0x3f, sizeof(LL) * n);
  memset(tim+1, 0, sizeof(int) * n);
  dijkstra(t);
  if (dis[s] == INF) {
    return -1;
  }
  pq2.push(tup(-dis[s], pii(0, s)));
  LL ans = -1;
  while (!pq2.empty()) {
    LL d = -pq2.top().second.first;
    int u = pq2.top().second.second;
    pq2.pop();
    tim[u]++;
    if (u == t && tim[u] == k) {
      ans = d;
      break;
    }
    for (int i = 0; i < (int)edge[u].size(); ++i) {
      int v = edge[u][i].second;
      if (tim[v] < k) {
        pq2.push(tup(-dis[v]-d-edge[u][i].first, pii(-d-edge[u][i].first, v)));
      }
    }
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  int n, m;
  while (cin >> n >> m) {
    for (int i = 1; i <= n; ++i) edge[i].clear(), edge2[i].clear();
    int s, e, k, t;
    cin >> s >> e >> k >> t;
    for (int i = 0; i < m; ++i) {
      int u, v, w; cin >> u >> v >> w;
      add(u, v, w);
    }
    LL ans = Astar(s, e, k, n);
    if (ans == -1 || ans > t) cout << "Whitesnake!\n";
    else cout << "yareyaredawa\n";
  }
}


