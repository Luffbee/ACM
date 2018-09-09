// jisuanke Skr
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;

const int N = 2e6+10;
const int LETTER = 10;
const int MOL = 1000000007;

inline int conv(char c) {
  return c-'0';
}

struct Node {
  int len, go[LETTER], fail;
} node[N];
int tot, h1, h0, last;

void init() {
  h1 = ++tot;
  h0 = ++tot;
  node[h1].len = -1;
  node[h1].fail = -1;
  node[h0].len = 0;
  node[h0].fail = h1;
  last = h0;
}

void mktree(char * s) {
  for (int i = 0; s[i]; ++i) {
    int x = conv(s[i]);
    while (s[i-node[last].len-1] != s[i]) last = node[last].fail;
    if (!node[last].go[x]) {
      node[last].go[x] = ++tot;
      node[tot].len = node[last].len+2;
      int p = node[last].fail;
      if (p == -1) node[tot].fail = h0;
      else {
        while (s[i-node[p].len-1] != s[i]) p = node[p].fail;
        node[tot].fail = node[p].go[x];
      }
    }
    last = node[last].go[x];
  }
}

LL mpow[N], ans;

void dfs(int no, LL x) {
  for (int i = 1; i <= 9; ++i) {
    if (node[no].go[i]) {
      LL y = (x*10 + i + mpow[node[no].len+1] * i) % MOL;
      ans = (ans + y) % MOL;
      dfs(node[no].go[i], y);
    }
  }
}

char txt[N];

int main() {
  ios::sync_with_stdio(false); cin.tie(0);
  cin >> (txt+1);
  init();
  mktree(txt+1);
  mpow[0] = 1;
  for (int i = 1; txt[i]; ++i) {
    mpow[i] = mpow[i-1] * 10 % MOL;
  }
  ans = mpow[0] = 0;
  dfs(h0, 0);
  dfs(h1, 0);
  cout << ans << '\n';
}

