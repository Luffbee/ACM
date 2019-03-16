#include <bits/stdc++.h>
using namespace std;

int const MAXN = 1e4;
int const MAXM = 3e4+10;
struct SAT2 {
  // _maxn: number of node splited
  // _maxm: number of edges
  static int const _maxn = 2*MAXN;
  static int const _maxm = 2*MAXM;
  int V, tot;
  int eto[_maxm], enxt[_maxm];
  int head[_maxn];
  inline int NewNode(int to, int nxt) {
    eto[tot] = to;
    enxt[tot] = nxt;
    return tot++;
  }
  inline void addedge(int a, int b) {
    head[a] = NewNode(b, head[a]);
  }
  int la[_maxn];
  int getla(int x) {
    return (la[x] == x ? x : (la[x] = getla(la[x])));
  }
  inline void merge(int x, int y) {
    if (getla(x) != getla(y)) la[la[x]] = la[y];
  }
  int sk[_maxn], skt;
  int dfn[_maxn], low[_maxn], idx;
  char instack[_maxn];
  void tarjan(int cur) {
    if (dfn[cur] != 0) return;
    dfn[cur] = ++idx;
    low[cur] = dfn[cur];
    sk[skt++] = cur;
    instack[cur] = 1;
    for (int p = head[cur]; p != -1; p = enxt[p]) {
      int to = eto[p];
      if (dfn[to] == 0) {
        tarjan(to);
        low[cur] = min(low[cur], low[to]);
      } else {
        if (instack[to]) low[cur] = min(low[cur], dfn[to]);
      }
    }
    if (dfn[cur] == low[cur]) {
      int v; la[cur] = cur;
      do {
        v = sk[--skt];
        la[v] = cur;
        instack[v] = 0;
      } while (v != cur);
    }
  }

  bool issat() {
    skt = idx = 0;
    memset(dfn, 0, sizeof(int)*V*2);
    for (int i = 0; i < V; ++i)
      tarjan(i*2), tarjan(i*2+1);
    for (int i = 0; i < V; ++i)
      if (getla(i*2) == getla(i*2+1)) return false;
    return true;
  }
  
  int getv(bool * res) {
    static vector<int> vecla[_maxn];
    static int *in = dfn, *ord = low, cnt;
    static queue<int> q;
    static char *ans = instack;
    for (int i = 0; i < V*2; ++i)
      in[i] = ans[i/2] = 0, vecla[i].clear();
    for (int i = 0; i < V*2; ++i) {
      int lai = getla(i), lap;
      for (int p = head[i]; p != -1; p = enxt[p]) {
        if ((lap=getla(eto[p])) != lai)
          ++in[lap], vecla[lai].push_back(lap);
      }
    }
    while (!q.empty()) q.pop();
    cnt = 0;
    for (int i = 0; i < V*2; ++i)
      if (getla(i) == i && !in[i]) q.push(i);
    while (!q.empty()) {
      int t = q.front(); q.pop();
      ord[cnt++] = t;
      for (int i = 0; i < (int)vecla[t].size(); ++i)
        if (--in[vecla[t][i]] == 0) q.push(vecla[t][i]);
    }
    while (cnt--) {
      int t = ord[cnt];
      if (!ans[t])
        ans[t] = 1, ans[getla(t^1)] = -1;
    }
    int ret = 0;
    for (int i = 1; i < V; ++i) {
      if (ans[getla(i*2)] > 0)
        ++ret, res[i] = true;
      else res[i] = false;
    }
    return ret;
  }

  void init(int n=_maxn/2) {
    V = n;
    int sz = n*2;
    tot = 0;
    memset(head, -1, sizeof(int)*sz);
  }
} sat2;


// Light OJ 1251 (this fucking oj can't use iostream)
bool remain[10000];
int main() {
  int T; scanf("%d", &T);
  for (int cas = 1; cas <= T; ++cas) {
    printf("Case %d: ", cas);
    int n, m; scanf("%d%d", &n, &m);
    sat2.init(m+1);
    for (int i = 0; i < n; ++i) {
      int xx, yy; cin >> xx >> yy;
      if (xx == -yy) continue;
      int x = abs(xx), y = abs(yy);
      if (xx < 0 && yy < 0) sat2.addedge(x*2, y*2+1), sat2.addedge(y*2, x*2+1);
      else if (xx < 0 && yy > 0) sat2.addedge(x*2, y*2), sat2.addedge(y*2+1, x*2+1);
      else if (xx > 0 && yy < 0) sat2.addedge(x*2+1, y*2+1), sat2.addedge(y*2, x*2);
      else sat2.addedge(x*2+1, y*2), sat2.addedge(y*2+1, x*2);
    }
    bool ok = sat2.issat();
    if (ok) {
      puts("Yes");
      printf("%d", sat2.getv(remain));
      for (int i = 1; i <= m; ++i)
        if (remain[i]) printf(" %d", i);
      puts("");
    } else puts("No");
  }
}
