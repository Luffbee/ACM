#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using pii = pair<LL, int>;

const int N = 1e5+10;

vector<pii> edge[N];

void add(int u, int v, int l) {
  edge[u].push_back(pii(l, v));
  //edge[v].push_back(pii(u, l));
}

LL dis[N];
bool use[N];
void dijkstra(int s, int n) {
  memset(dis+1, 0x3f, sizeof(LL) * n);
  priority_queue<pii> pq;
  dis[s] = 0;
  pq.push(pii(0, s));
  while (!pq.empty()) {
    int u = pq.top().second;
    LL d = -pq.top().first;
    pq.pop();
    if (use[u]) continue;
    use[u] = true;
    for (pii e : edge[u]) {
      int v = e.second;
      LL dd = d + e.first;
      if (dd < dis[v]) {
        dis[v] = dd;
        pq.push(pii(-dd, v));
      }
    }
  }
}

int main() {
  int n, m, s; cin >> n >> m >> s;
  for (int i = 0; i < m; ++i) {
    int a, b, t; cin >> a >> b >> t;
    add(a, b, t);
  }
  dijkstra(s, n);
  for (int i = 1; i <= n; ++i) {
    cout << dis[i] << ' ';
  } cout << endl;
}


