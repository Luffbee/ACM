#include <bits/stdc++.h>
const int N = 2e5 + 10;
int link[2 * N], len[2 * N], go[2 * N][26];
int head = 1, last = 1, tot = 1;
int New(int mxlen) {
  ++tot;
  len[tot] = mxlen;
  return tot;
}
void add(int c) {
  int p = New(len[last] + 1), x = last;
  for (last = p; x && !go[x][c]; x = link[x])
    go[x][c] = p;
  if (!x)
    link[p] = head;
  else {
    int q = go[x][c];
    if (len[q] == len[x] + 1)
      link[p] = q;
    else {
      int r = New(len[x] + 1);
      memcpy(go[r], go[q], sizeof(go[r]));
      link[r] = link[q];
      link[q] = link[p] = r;
      for (; x && go[x][c] == q; x = link[x])
        go[x][c] = r;
    }
  }
}
