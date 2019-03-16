const int N = 1e3+10;
const int M = 1e4+10;
const LL INF = 0x3f3f3f3f3f3f3f3f;

struct Edge {
  LL w;
  int v, nxt;
} edge[M], edge2[M];
int etot;

int head[N], head2[N];

void add(int u, int v, LL l) {
  ++etot;
  edge[etot] = {l, v, head[u]};
  head[u] = etot;
  edge2[etot] = {l, u, head2[v]};
  head2[v] = etot;
}

// M + N * log(M)
struct Node {
  pii v;
  int nql, ls, rs;
} node[M+15*N] = {{pii(0, 0), -1, 0, 0}};
int tot;
int newNode() {
  ++tot;
  node[tot] = {{0, 0}, 0, 0, 0};
  return tot;
}

int meld(int x, int y) {
  if (!x) return y;
  if (!y) return x;
  int ret = newNode();
  if (node[x].v > node[y].v) swap(x, y);
  node[ret].v = node[x].v;
  int & ls = node[ret].ls = node[x].ls;
  int & rs = node[ret].rs = meld(node[x].rs, y);
  if (!ls || node[ls].nql < node[rs].nql) swap(ls, rs);
  node[ret].nql = node[rs].nql+1;
  return ret;
}

inline int pop(int x) {
  return meld(node[x].ls, node[x].rs);
}

inline pii getMin(int x) {
  return node[x].v;
}

// meld inplace
int meld_in(int x, int y) {
  if (!x) return y;
  if (!y) return x;
  if (node[x].v > node[y].v) swap(x, y);
  int & ls = node[x].ls;
  int & rs = node[x].rs = meld(node[x].rs, y);
  if (!ls || node[ls].nql < node[rs].nql) swap(ls, rs);
  node[x].nql = node[rs].nql+1;
  return x;
}

int newHeap(const vector<pii> & vs) {
  static int q[2*M];
  int l = 0, r = 0;
  q[l] = 0;
  for (pii v : vs) {
    q[r++] = newNode();
    node[tot].v = v;
  }
  while (r-l > 1) {
    int x = q[l++], y = q[l++];
    q[r++] = meld_in(x, y);
  }
  return q[l];
}

int fa[N];
LL dis[N];
bool use[N];
void dijkstra(int s, int n) {
  memset(dis+1, 0x3f, sizeof(LL)*n);
  for (int i = 1; i <= n; ++i) use[i] = false;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  dis[s] = fa[s] = 0;
  pq.push(pii(0, s));
  while (!pq.empty()) {
    int u = pq.top().second;
    LL d = pq.top().first;
    pq.pop();
    if (use[u]) continue;
    use[u] = true;
    for (int i = head2[u]; i; i = edge2[i].nxt) {
      int v = edge2[i].v;
      LL dd = d + edge2[i].w;
      if (dd < dis[v]) {
        dis[v] = dd;
        fa[v] = i;
        pq.push(pii(dd, v));
      }
    }
  }
}

int hp[N];
bool vis[N];
vector<pii> tmp;
void dfs(int x, int d) {
  tmp.clear();
  vis[x] = true;
  for (int i = head[x]; i; i = edge[i].nxt) {
    int y = edge[i].v;
    if (i != fa[x]) tmp.push_back(pii(edge[i].w+dis[y]-dis[x], i));
  }
  hp[x] = newHeap(tmp);
  if (!fa[x]) return;
  int f = edge[fa[x]].v;
  if (!vis[f]) dfs(f, d+1);
  hp[x] = meld(hp[x], hp[f]);
}

LL Kpath(int s, int t, int k, int n) {
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  dijkstra(t, n);
  for (int i = 1; i <= n; ++i) vis[i] = false;
  for (int i = 1; i <= n; ++i) if (!vis[i]) dfs(i, 1);
  if (dis[s] == INF) return -1;
  if (k == 1) return dis[s];
  k--;
  LL ans = -1;
  if (hp[s]) pq.push({node[hp[s]].v.first, hp[s]});
  while (!pq.empty()) {
    pii t = pq.top(); pq.pop();
    LL d = t.first;
    if (--k == 0) {
      ans = d + dis[s];
      break;
    }
    int nid = t.second;
    int u = edge[node[nid].v.second].v;
    int ls = node[nid].ls, rs = node[nid].rs;
    if (hp[u]) pq.push({d+node[hp[u]].v.first, hp[u]});
    d -= node[nid].v.first;
    if (ls) pq.push({d+node[ls].v.first, ls});
    if (rs) pq.push({d+node[rs].v.first, rs});
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  tmp.reserve(M);
  int n, m;
  while (cin >> n >> m) {
    tot = etot = 0;
    int s, e, k, t;
    cin >> s >> e >> k >> t;
    memset(head+1, 0, sizeof(int)*n);
    memset(head2+1, 0, sizeof(int)*n);
    for (int i = 0; i < m; ++i) {
      int u, v, w; cin >> u >> v >> w;
      add(u, v, w);
    }
    LL ans = Kpath(s, e, k, n);
    if (ans == -1 || ans > t) cout << "Whitesnake!\n";
    else cout << "yareyaredawa\n";
  }
}


