#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int N = 1e5+10;
int n, m;

struct Node {
  pii v;
  int sz;
  Node * son, * nxt;
  Node() {}
  Node(pii vv): v(vv), sz(0), son(NULL), nxt(NULL) {};
} node[N];

inline pii getMin(Node * hp) {
  pii ret = hp->v;
  for (hp = hp->nxt; hp; hp = hp->nxt) {
    ret = min(ret, hp->v);
  }
  return ret;
}

inline Node * merge(Node * ch, Node * par) {
  if (ch->v < par->v) swap(ch, par);
  ch->nxt = par->son;
  par->son = ch;
  par->sz++;
  return par;
}

inline bool zipable(Node * p) {
  if (p->nxt == NULL) return false;
  Node * pp = p->nxt;
  if (p->sz != pp->sz) return false;
  if (pp->nxt == NULL) return true;
  if (pp->sz == pp->nxt->sz) return false;
  return true;
}

inline Node * zip(Node * head) {
  Node ** p = &head, * pp = head->nxt;
  while (pp) {
    while (zipable(*p)) {
      pp = pp->nxt;
      *p = merge(*p, (*p)->nxt);
      (*p)->nxt = pp;
    }
    if (!pp) break;
    p = &(*p)->nxt;
    pp = (*p)->nxt;
  }
  return head;
}

inline Node * meld(Node * hp1, Node * hp2) {
  Node * head = NULL;
  Node ** p = &head;
  while (hp1 && hp2) {
    if (hp1->sz < hp2->sz) {
      *p = hp1;
      hp1 = hp1->nxt;
    } else {
      *p = hp2;
      hp2 = hp2->nxt;
    }
    p = &(*p)->nxt;
  }
  if (hp1) *p = hp1;
  else *p = hp2;
  return head ? zip(head) : NULL;
}

Node * stk[100];
inline Node * reverse(Node * hp) {
  if (!hp) return hp;
  int cnt = 0;
  while (hp) stk[cnt++] = hp, hp = hp->nxt;
  Node * ret = stk[--cnt];
  Node * p = ret;
  while (cnt) p->nxt = stk[--cnt], p = p->nxt;
  p->nxt = NULL;
  return ret;
}

inline Node * pop(Node * hp, pii & mn) {
  Node * p;
  if (hp->v == mn) {
    p = hp->son;
    hp = hp->nxt;
  } else {
    for (p = hp; ; p = p->nxt) {
      if (p->nxt->v == mn) break;
    }
    Node * tmp = p->nxt->son;
    p->nxt = p->nxt->nxt;
    p = tmp;
  }
  p = reverse(p);
  return meld(hp, p);
}

int fa[N];

int find(int x) {
  return x == fa[x] ? x : fa[x] = find(fa[x]);
}

Node * hp[N];
bool use[N];

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    int a; cin >> a;
    hp[i] = &node[i];
    hp[i]->v = pii(a, i);
    use[i] = true;
    fa[i] = i;
  }
  while (m--) {
    int op; cin >> op;
    if (op == 1) {
      int x, y; cin >> x >> y;
      if (!use[x] || !use[y]) continue;
      x = find(x);
      y = find(y);
      if (x == y) continue;
      fa[x] = y;
      hp[y] = meld(hp[y], hp[x]);
      hp[x] = NULL;
    } else {
      int x; cin >> x;
      if (!use[x]) {
        cout << "-1\n";
        continue;
      }
      int y = find(x);
      pii mn = getMin(hp[y]);
      use[mn.second] = false;
      cout << mn.first << '\n';
      hp[y] = pop(hp[y], mn);
    }
  }
}
