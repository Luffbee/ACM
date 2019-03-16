const int N = 2e6+10;
const int LETTER = 10;
const int MOL = 1000000007;

inline int conv(char c) { return c-'0'; }

struct Node {
  int len, go[LETTER], fail;
} node[N];
int tot, h1, h0, last;

void init() {
  h1 = ++tot; h0 = ++tot;
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

