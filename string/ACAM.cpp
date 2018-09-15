#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int conv(char x) { return x - 'a'; }
struct Trie {
  int num, fail, next[26], match;
} pool[N];
Trie *const trie = pool + 1;
int cnt;
void init() {
  memset(pool, 0, 2 * sizeof(Trie));
  cnt = 0;
  trie[0].fail = -1;
}
void insert(char *s) {
  int cur = 0;
  for (int i = 0; s[i]; ++i) {
    int &pos = trie[cur].next[conv(s[i])];
    if (!pos)
      memset(&trie[pos = ++cnt], 0, sizeof(Trie));
    cur = pos;
  }
  trie[cur].num++;
}
void build() {
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int t = q.front();
    q.pop();
    for (int i = 0; i < 26; ++i) {
      int &cur = trie[t].next[i];
      if (cur) {
        q.push(cur);
        trie[cur].fail = trie[trie[t].fail].next[i];
        trie[cur].match = trie[cur].num ? cur : trie[trie[cur].fail].match;
      } else
        cur = trie[trie[t].fail].next[i];
    }
  }
}
int search(char *s) {
  int ret = 0, cur = 0;
  for (int i = 0; s[i]; ++i) {
    cur = trie[cur].next[conv(s[i])];
    for (int t = trie[cur].match; t; t = trie[trie[t].fail].match)
      ret += trie[t].num;
  }
  return ret;
}
