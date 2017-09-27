#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <iostream>

using namespace std;
const int MAXN = 5e3;
const int MAXM = 5e4;

struct MCMF {
  static const int INF = 0x3f3f3f3f;
  static const int _maxn = MAXN + 5;
  static const int _maxm = MAXM * 2 + 10;
  int S, T, V;
  int head[_maxn], nxt[_maxm], st[_maxm], ed[_maxm];
  int len[_maxm], cap[_maxm], flow[_maxm];
  int tot, mncost, mxflow;
  inline void _addedge(int s, int t, int l, int c) {
    st[tot] = s;
    ed[tot] = t;
    len[tot] = l;
    cap[tot] = c;
    flow[tot] = 0;
    nxt[tot] = head[s];
    head[s] = tot++;
  }
  inline void addedge(int s, int t, int l, int c) {
    _addedge(s, t, l, c);
    _addedge(t, s, -l, 0);
  }
  inline void init(int n = _maxn) {
    V = n;
    memset(head, -1, sizeof(int) * V);
    tot = 0;
  }
  char vis[_maxn];
  int *zkwlen;
  // int zkwlen[_maxm];
  int zkwpri;
  int zkwAug(int no, int m) {
    static int d;
    static int u;
    if (no == T) {
      mncost += zkwpri * m;
      return m;
    }
    vis[no] = 1;
    int l = m;
    for (int i = head[no]; i != -1; i = nxt[i]) {
      u = cap[i] - flow[i];
      if (u > 0 && !zkwlen[i] && !vis[ed[i]]) {
        d = zkwAug(ed[i], u > l ? l : u);
        flow[i] += d;
        flow[i ^ 1] -= d;
        l -= d;
        if (!l)
          return m;
      }
    }
    return m - l;
  }
  inline bool zkwRelabel() {
    int d = INF;
    for (int i = 0; i < V; ++i)
      if (vis[i])
        for (int j = head[i]; j != -1; j = nxt[j])
          if (cap[j] - flow[j] && !vis[ed[j]] && zkwlen[j] < d)
            d = zkwlen[j];
    if (d == INF)
      return false;
    for (int i = 0; i < V; ++i)
      if (vis[i])
        for (int j = head[i]; j != -1; j = nxt[j])
          zkwlen[j] -= d, zkwlen[j ^ 1] += d;
    zkwpri += d;
    return true;
  }
  bool PDRelabel() {
    static int d[_maxn];
    memset(d, 0x3f, sizeof(int) * V);
    static int Q[_maxn];
    int ql, qr;
    ql = qr = 0;
    const int mol = _maxn;
    d[T] = 0;
    Q[qr++] = T;
    vis[T] = 1;
    while (qr - ql) {
      int dt, no = Q[ql++];
      ql %= mol;
      --vis[no];
      for (int i = head[no]; i != -1; i = nxt[i]) {
        dt = d[no] - zkwlen[i];
        if (cap[i ^ 1] - flow[i ^ 1] > 0 && dt < d[ed[i]]) {
          d[ed[i]] = dt;
          if (dt <= d[qr - ql ? Q[ql] : 0]) {
            Q[ql = (ql - 1 + mol) % mol] = ed[i];
            ++vis[ed[i]];
          } else if (!vis[ed[i]]) {
            Q[qr++] = ed[i];
            qr %= mol;
            ++vis[ed[i]];
          }
        }
      }
    }
    for (int i = 0; i < V; ++i)
      for (int j = head[i]; j != -1; j = nxt[j])
        zkwlen[j] += d[ed[j]] - d[i];
    zkwpri += d[S];
    return d[S] < INF;
  }
  inline int zkw() {
    zkwpri = 0, mncost = 0, mxflow = 0;
    // for (int i = 0; i < tot; ++i) zkwlen[i] = len[i];
    zkwlen = len;
    int d;
    do {
      do {
        memset(vis, 0, sizeof(bool) * V);
        d = zkwAug(S, INF);
        mxflow += d;
      } while (d);
    } while (zkwRelabel());
    return mncost;
  }
  inline int primedual() {
    zkwpri = 0, mncost = 0, mxflow = 0;
    // for (int i = 0; i < tot; ++i) zkwlen[i] = len[i];
    zkwlen = len;
    int d;
    memset(vis, 0, sizeof(bool) * V);
    while (PDRelabel()) {
      do {
        d = zkwAug(S, INF);
        mxflow += d;
        memset(vis, 0, sizeof(bool) * V);
      } while (d);
    }
    return mncost;
  }

  int calc(int s, int t) {
    S = s, T = t;
    // return zkw();
    return primedual();
  }
} mcmf;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m, S, T;
  cin >> n >> m >> S >> T;
  mcmf.init(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v, w, f;
    cin >> u >> v >> w >> f;
    mcmf.addedge(u, v, f, w);
  }
  mcmf.calc(S, T);
  cout << mcmf.mxflow << ' ' << mcmf.mncost << endl;
}
