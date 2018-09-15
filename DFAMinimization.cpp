#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+10;
const int B = 16;
struct DFA {
  int n, b, cnt, start;
  int go[N][B], cls[N], pos[N];
  int stat[N], bnd[N][3];
  bool acc[N], vis[N], inq[N];
  vector<int> from[N][B];

  inline void init(int nn, int bb, int s) {
    n = nn, b = bb, start = s;
    memset(vis, 0, sizeof(bool) * n);
    memset(inq, 0, sizeof(bool) * n);
    memset(acc, 0, sizeof(bool) * n);
    cnt = 0;
  }

  inline void add(int x, int t, int y) {
    go[x][t] = y;
  }

  inline void accept(int x) {
    acc[x] = true;
  }

  inline int size(int x) {
    return bnd[x][1] - bnd[x][0] + 1;
  }

  inline void addclass(int l, int r) {
    bnd[cnt][0] = bnd[cnt][2] = l;
    bnd[cnt][1] = r;
    for (int i = l; i <= r; ++i) cls[stat[i]] = cnt;
    cnt++;
  }

  inline void refine(int c, int p) {
    if (p == bnd[c][2]) bnd[c][2]++;
    else {
      int x = stat[p], y = stat[bnd[c][2]];
      swap(stat[p], stat[bnd[c][2]++]);
      swap(pos[x], pos[y]);
    }
  }

  inline void initMini() {
    int l = 0, r = 0, k = 0;
    stat[r++] = start;
    vis[start] = true;
    while (l != r) {
      int x = stat[l++];
      if (acc[x]) swap(stat[l-1], stat[k++]);
      for (int i = 0; i < b; ++i) {
        int y = go[x][i];
        from[y][i].push_back(x);
        if (!vis[y]) {
          stat[r++] = y;
          vis[y] = true;
        }
      }
    }
    for (int i = 0; i < r; ++i) pos[stat[i]] = i;
    addclass(0, k-1);
    addclass(k, r-1);
  }

  void minimization() {
    initMini();
    queue<int> q;
    vector<int> tmp;
    q.push(0);
    inq[0] = true;
    while (!q.empty()) {
      int x = q.front(); q.pop();
      int l = bnd[x][0], r = bnd[x][1];
      inq[x] = false;
      for (int t = 0; t < b; ++t) {
        tmp.clear();
        for (int i = l; i <= r; ++i) {
          for (int y : from[stat[i]][t]) {
            refine(cls[y], pos[y]);
            tmp.push_back(cls[y]);
          }
        }
        for (int c : tmp) {
          if (bnd[c][2] == bnd[c][0]) continue;
          else if (bnd[c][1] < bnd[c][2]) bnd[c][2] = bnd[c][0];
          else {
            addclass(bnd[c][0], bnd[c][2]-1);
            bnd[c][0] = bnd[c][2];
            if (inq[c] || size(c) > size(cnt-1)) c = cnt-1;
            q.push(c);
            inq[c] = true;
          }
        }
      }
    }
  }

  void show() {
    cout << cnt << ' ' << cls[0] << '\n';
    for (int i = 0; i < cnt; ++i) {
      if (acc[stat[bnd[i][0]]]) cout << "G ";
      else cout << "B ";
    } cout << '\n';
    for (int i = 0; i < cnt; ++i) {
      for (int j = 0; j < b; ++j) {
        cout << cls[go[stat[bnd[i][0]]][j]] << ' ';
      } cout << '\n';
    }
  }
} dfa;

int main() {
  int b, m; cin >> b >> m;
  dfa.init(m, b, 0);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < b; ++j) {
      dfa.add(i, j, (i * b + j) % m);
    }
  }
  dfa.accept(0);
  dfa.minimization();
  dfa.show();
}
