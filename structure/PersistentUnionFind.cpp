// luogu-judger-enable-o2
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6+10;
int a[N], n;

struct Node {
  int ls, rs;
} node[22*N];
int tot;

int build(int l, int r) {
  int ret = tot++;
  if (l == r) {
    node[ret].ls = a[l];
    node[ret].rs = 1;
  } else {
    int mid = (l+r)/2;
    node[ret].ls = build(l, mid);
    node[ret].rs = build(mid+1, r);
  }
  return ret;
}

int modify(int old, int l, int r, int x, int v, int k) {
  int ret = tot++;
  int tmp = ret;
  while (l != r) {
    int mid = (l+r)/2;
    if (x <= mid) {
      node[tmp].ls = tot;
      node[tmp].rs = node[old].rs;
      old = node[old].ls;
      r = mid;
    } else {
      node[tmp].ls = node[old].ls;
      node[tmp].rs = tot;
      old = node[old].rs;
      l = mid+1;
    }
    tmp = tot++;
  }
  node[tmp].ls = v;
  node[tmp].rs = k;
  return ret;
}

int get(int no, int l, int r, int x) {
  while (l != r) {
    int mid = (l+r)/2;
    if (x <= mid) {
      no = node[no].ls;
      r = mid;
    } else {
      no = node[no].rs;
      l = mid+1;
    }
  }
  return no;
}

int find(int rt, int x) {
  int no = get(rt, 1, n, x);
  while (node[no].ls != x) {
    x = node[no].ls;
    no = get(rt, 1, n, x);
  }
  return no;
}

int merge(int rt, int x, int y) {
  int nox = find(rt, x);
  int noy = find(rt, y);
  int ret = rt, num;
  if (nox == noy) return ret;
  x = node[nox].ls;
  y = node[noy].ls;
  num = node[nox].rs + node[noy].rs;
  if (node[nox].rs > node[noy].rs) swap(x, y);
  ret = modify(rt, 1, n, x, y, 0);
  ret = modify(ret, 1, n, y, y, num);
  return ret;
}

int root[N];

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  int m; cin >> n >> m;
  for (int i = 1; i <= n; ++i) a[i] = i;
  root[0] = build(1, n);
  for (int i = 1; i <= m; ++i) {
    int op; cin >> op;
    if (op == 1) {
      int x, y; cin >> x >> y;
      root[i] = merge(root[i-1], x, y);
    } else if (op == 2) {
      int k; cin >> k;
      root[i] = root[k];
    } else if (op == 3) {
      int x, y; cin >> x >> y;
      root[i] = root[i-1];
      int nox = find(root[i], x);
      int noy = find(root[i], y);
      if (nox == noy) cout << "1\n";
      else cout << "0\n";
    }
  }
}

