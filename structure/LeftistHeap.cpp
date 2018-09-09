#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int N = 1e5+10;
int n, m;

struct Node {
  pii v;
  int npl;
  int ls, rs;
} node[N];

inline void maintain(int x) {
  int & ls = node[x].ls;
  int & rs = node[x].rs;
  if (!ls || node[ls].npl < node[rs].npl) swap(ls, rs);
  node[x].npl = node[rs].npl+1;
}

int meld(int x, int y) {
  if (!x) return y;
  if (!y) return x;
  if (node[x].v > node[y].v) swap(x, y);
  node[x].rs = meld(node[x].rs, y);
  maintain(x);
  return x;
}

inline pii getMin(int x) {
  return node[x].v;
}

inline int pop(int x) {
  return meld(node[x].ls, node[x].rs);
}


int fa[N];
int find(int x) {
  return fa[x] ? fa[x] = find(fa[x]) : x;
}

bool use[N];
int hp[N];

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  cin >> n >> m;
  node[0].npl = -1;
  for (int i = 1; i <= n; ++i) {
    int a; cin >> a;
    node[i].v = pii(a, i);
    hp[i] = i;
  }
  while (m--) {
    int op; cin >> op;
    if (op == 1) {
      int x, y; cin >> x >> y;
      if (use[x] || use[y]) continue;
      x = find(x); y = find(y);
      if (x == y) continue;
      fa[x] = y;
      hp[y] = meld(hp[x], hp[y]);
    } else {
      int x; cin >> x;
      if (use[x]) {
        cout << "-1\n";
        continue;
      }
      int y = find(x);
      cout << getMin(hp[y]).first << '\n';
      use[getMin(hp[y]).second] = true;
      hp[y] = pop(hp[y]);
    }
  }
}
