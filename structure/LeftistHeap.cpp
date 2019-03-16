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
inline pii getMin(int x) { return node[x].v; }
inline int pop(int x) { return meld(node[x].ls, node[x].rs); }
