// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using pii = pair<int, int>;

const int N = 1e4+10;
const int K = 1e7+10;
const int INF = 0x3f3f3f3f;


vector<pii> edge[N];

void add(int u, int v, int l) {
  edge[u].push_back(pii(v, l));
  edge[v].push_back(pii(u, l));
}

bool vis[N];
int sz[N];

int centroid(int cur, int fa, int n) {
  int ret = cur;
  sz[cur] = 1;
  for (pii e : edge[cur]) {
    int v = e.first;
    if (v == fa || vis[v]) continue;
    int t = centroid(v, cur, n);
    sz[cur] += sz[v];
    if (sz[v] > n/2) ret = t;
  }
  return ret;
}

vector<int> tmp, qq;

void dfs(int cur, int fa, int dep) {
  tmp.push_back(dep);
  for (pii e : edge[cur]) {
    int v = e.first;
    if (vis[v] || v == fa) continue;
    dfs(v, cur, dep+e.second);
  }
}

int k[100], m;
bool has[100];
bitset<10000001> s;
void solv(int root, int dep) {
  tmp.clear();
  dfs(root, 0, dep);
  for (int t : tmp) {
    for (int i = 0; i < m; ++i) {
      if (k[i] >= t && s[k[i]-t]) has[i] = true;
    }
  }
  for (int t : tmp) {
    if (!s[t]) {
      qq.push_back(t);
      s.set(t);
    }
  }
}

void TreeDivide(int root, int n) {
  int c = centroid(root, 0, n);
  vis[c] = true;
  s.set(0);
  qq.clear();
  for (pii e : edge[c]) {
    int v = e.first;
    solv(v, e.second);
  }
  for (int t : qq) s.reset(t);
  for (pii e : edge[c]) {
    int v = e.first;
    if (vis[v]) continue;
    TreeDivide(v, sz[v]);
  }
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  int n; cin >> n >> m;
  for (int i = 0; i < n-1; ++i) {
    int u, v, l; cin >> u >> v >> l;
    add(u, v, l);
  }
  for (int i = 0; i < m; ++i) {
    cin >> k[i];
  }
  TreeDivide(1, n);
  for (int i = 0; i < m; ++i) {
    if (has[i] || k[i] == 0) cout << "AYE\n";
    else cout << "NAY\n";
  }
}


